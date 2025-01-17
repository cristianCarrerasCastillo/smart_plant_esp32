#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "funcionesEeprom.h"
#include "EEPROM.h"
#include "ESP8266WebServer.h"
#include "pages.h"
//#include <ESPAsyncWebServer.h> incluir despues

// -------- configuración para wifi --------------
// Esta configuración es para levantar el esp32 en modo AP si es que no se puede conectar a ningun wifi.
#define SSIDCONFIG "Plant-Wifi"
#define PASSWORDCONFIG "PlantWifi1234"
// se usa para leer el wifi desde el EEPROM
char ssid[20];
char password[20];

ESP8266WebServer server(80);
ESP8266WebServer server2(80);
//AsyncWebServer Aserver(80);
IPAddress ip(192, 168, 1, 130);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress internalIp;

String mensaje = ""; // mensaje que se quiera añadir a la pagina web

// ---------- config variables workflow --------------
char humbral_humedad[4];
int trigger_humedad;
char name_device[5];
char ip_server[15];

// --------- control para motor y lectura de humedad -----------
const int sensor_humedad = A0;
int motor = D0; //Tip 120 conectado a pin digital D0
int read_humedad = 0;

void wifi_config() {
  int len_ssid = 0;
  int len_pass = 0;

  len_ssid = sizeof(ssid);
  len_pass = sizeof(password);

  String wifi_id = "";
  String wifi_pass = "";

  wifi_id = leerEeprom(0,len_ssid);
  wifi_pass = leerEeprom(len_ssid,(len_ssid +len_pass));
  wifi_id.toCharArray(ssid,sizeof(ssid));
  wifi_pass.toCharArray(password,sizeof(password));
  Serial.println(wifi_id);
  Serial.println(wifi_pass);
}

void escanear() {
  int n = WiFi.scanNetworks(); //devuelve el número de redes encontradas
  Serial.println("escaneo terminado");
  if (n == 0) { //si no encuentra ninguna red
    Serial.println("no se encontraron redes");
    mensaje = "no se encontraron redes";
  }
  else
  {
    Serial.print(n);
    Serial.println(" redes encontradas");
    mensaje = "";
    for (int i = 0; i < n; ++i)
    {
      // agrega al STRING "mensaje" la información de las redes encontradas 
      mensaje = (mensaje)+"<option value='" + WiFi.SSID(i) +"'>" + WiFi.SSID(i) + "</option>\r\n";
      delay(10);
    }
    Serial.println(mensaje);
  }
}

void paginaConfig(){
  escanear();
  server.send(200, "text/html", header_html + body_page_wifi_scan(mensaje) + footer_html);
}

void setup_wifi() {
  // Conexión WIFI 
  int contconexion=0;

  WiFi.mode(WIFI_STA); //para que no inicie el SoftAP en el modo normal
  WiFi.begin(ssid,password); 
  while (WiFi.status() != WL_CONNECTED and contconexion <30){
    delay(500);
    Serial.print(".");
    contconexion++;
  }
    if(WiFi.status() != WL_CONNECTED){
    Serial.println("");
    Serial.println("Error de conexion");  
    return;  
    }
  else{
    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println(ssid);
    Serial.println(WiFi.localIP());
  }
  Serial.println("");
}

void guardar_conf() {
  Serial.println(server.arg("ssid"));//Recibimos los valores que envia por GET el formulario web
  grabarEeprom(0, server.arg("ssid"));
  grabarEeprom(sizeof(ssid), server.arg("pass"), sizeof(password));
  mensaje = "<body><h1>Se esta guardando la Configuracion </h1></body>";
  server.send(200, "text/html", header_html + mensaje + footer_html);
  wifi_config();
  setup_wifi();
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Clave Invalida");
    paginaConfig();
  }
  else{
    server.close();
    ESP.restart();
  }  
}

void guardar_conf_workflow(){

  Serial.print("----- El valor recibido es: ");
  Serial.println(server2.arg("triggerHumedad"));//Recibimos los valores que envia por GET el formulario web
  Serial.print("-------- El leido recibido es: ");
  Serial.println(leerEeprom((sizeof(ssid)+sizeof(password)),50));
  grabarEeprom((sizeof(ssid)+sizeof(password)), server2.arg("triggerHumedad"), (sizeof(ssid)+sizeof(password)+sizeof(humbral_humedad)));
  mensaje = "<body><h1>Configuracion Guardada...</h1></body>";
  trigger_humedad = server2.arg("triggerHumedad").toInt();
  Serial.print("triggerHumedad: ");
  Serial.println(humbral_humedad);
  server2.send(200, "text/html", header_html + mensaje + footer_html);
}

void modoconf() {
  WiFi.softAP(SSIDCONFIG, PASSWORDCONFIG);
  IPAddress myIP = WiFi.softAPIP();//ip por defecto para conectarse es la 192.168.4.1 <--------------
  Serial.print("IP del acces point: ");
  Serial.println(myIP);
  Serial.println("WebServer iniciado...");

  borrarEeprom(0,100);//borra los datos ssid y pass que estaban guardados anteriormente al no encontrarlos en la memoria
  server.on("/", paginaConfig); //esta es la pagina de configuracion
  server.on("/guardar_conf", guardar_conf); //Graba en la eeprom la configuracion
  server.begin();
  while (true) {
    server.handleClient();
  }
  Serial.println("Se cierra el servidor 1");
  server.close();
}

int LeerHumedad(){
  read_humedad = analogRead(sensor_humedad);
  Serial.println(read_humedad);
  read_humedad = map(read_humedad, 0, 950, 0, 100);
  read_humedad = 100 - read_humedad;
  return(read_humedad);
}

void handle_OnConnect() {
  int humedad = LeerHumedad();
  server2.send(200, "text/html",header_html + body_page_Hum(String(humedad)) + script +footer_html);
}

void handle_Config() {
  
  Serial.print("el trigger es de: ");
  Serial.println(trigger_humedad);
  server2.send(200, "text/html",header_html + body_config(String(trigger_humedad)) + script+ footer_html);
}

void leerTriggerHumedad(){
  trigger_humedad = leerEeprom((sizeof(ssid)+sizeof(password)),(sizeof(ssid)+sizeof(password)+sizeof(humbral_humedad))).toInt();
}

void setup() {
  Serial.begin(9600);

  EEPROM.begin(512);
  delay(10);
  wifi_config();
  setup_wifi();
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("modo softAp iniciado");
    modoconf();
  }
  leerTriggerHumedad();
  server2.on("/", handle_OnConnect);
  server2.on("/config", handle_Config);
  server2.on("/saveConfig", guardar_conf_workflow);//Graba en la eeprom la configuracion de variables que se usan en el workflow
  server2.begin();
  
  Serial.println(WiFi.localIP());
  delay(10);
}

void loop() {
  int prom_humedad = 0;
  read_humedad = LeerHumedad();
  Serial.print("Humedad en: ");
  Serial.println(read_humedad);
  Serial.print("trigger_humedad: ");
  Serial.println(trigger_humedad);
  for(int i=0; i <= 3; i++){
    prom_humedad = prom_humedad + read_humedad;
  }

  prom_humedad = prom_humedad / 3;

  if(prom_humedad < trigger_humedad){
    Serial.println("Se enciende el motor");
    analogWrite(motor, 255);
    delay(2500);
  }
  else{
    Serial.println("Se apaga el motor");
    analogWrite(motor, 0);
    delay(3600);
  }
  Serial.println("termino del loop");
  server2.handleClient();
}


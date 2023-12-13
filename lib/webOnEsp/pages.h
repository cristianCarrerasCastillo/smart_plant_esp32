#ifndef _PAGES_H
#define _PAGES_H
#include <string.h>

String body_page_wifi_scan(String red){
    String body = "<body>";
    body+="    <div class='center container border-gradient'>";
    body+="    <center><h1>Ingrese Wifi</h1></center>";
    body+="    <form action='guardar_conf' method='get'>";
    body+="    <center>SSID <select placeholder='Nombre Wifi' name='ssid' type='text'>";
    body+="        <option value='a'>Selecione WiFi</option>";
    body+=red;
    body+="    </select>";
    body+="    </center>";
    body+="    <br>";
    body+="    <center>PASS <input placeholder='Password' name='pass' type='password'></center><br>";
    body+="    <center><input class='btn' type='submit' value='GUARDAR'/></center><br>";
    body+="    </form>";
    
    return body;
}

String footer_html = "    </div>"
"    <footer>"
"        <p>Dev: Cristian Carreras</p>"
"    </footer>   "
"</body>"
""
"</html>";

String header_html = "<!DOCTYPE html>"
"<html lang='es'>"
"<head>"
"<meta charset=' UTF-8 '>"
"    <meta http-equiv='X-UA-Compatible' content='IE=edge'>"
"    <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"    <title>Temperatura & Humedad</title>"
"    <style>"
"        * {"
"            margin: 0;"
"            padding: 0;"
"            color: rgb(93, 190, 214);"
"            margin-top: 10px;"
"        }"
"        body {"
"            font-family: Arial, Helvetica, sans-serif;"
"            font-size: 14px;"
"            background-color: #333333;"
"        }"
"        h1 {"
"            "
"            text-align: center;"
"        }"
"        .container {"
"            width: 50%;"
"            height: 100%;"
"            display: flex;"
"            flex-direction: column;"
"            justify-content: center;"
"            align-items: center;"
"            margin: auto;"
"            border-radius: 10px;"
"        }"
"        .title {"
"            border: 1px solid;"
"            border-image-slice: 1;"
"            border-image-source: linear-gradient(to left, #54d0d4, #9ad53a);"
"            border-radius: 5px;"
"            font-size: large;"
"            text-align: center;"
"            width: 80%;"
"            margin: 5%;"
""
"        }"
"        .content-table {"
"            font-size:x-large;"
"            margin-bottom: 5%;"
"        }"
"        .border-gradient {"
"        border: 5px solid;"
"        border-image-slice: 1;"
"        border-image-source: linear-gradient(to left, #54d0d4, #9ad53a);"
"        }"
"        footer{"
"            position: absolute;"
"            bottom: 0;"
"            width: 100%;"
"            height: 5%;"
"            text-align: center;"
"            font-size: small;"
"        }"
"        p{"
"            color:rgb(93, 190, 214);"
"        }"
"        .emoji{"
"            font-size: 200%;"
"        }"
"        #value-sensor{"
"            font-weight: bold;"
"            font-size: xx-large;"
"        }"
"       tr:nth-child(odd){"
"            background-color:  #474747;"
"        }"
"   body {"
"    font-family: Arial, Helvetica, sans-serif;"
"  }"
"  "
"  .mobile-container {"
"    max-width: 480px;"
"    margin: auto;"
"    background-color: #555;"
"    height: 500px;"
"    color: white;"
"    border-radius: 10px;"
"  }"
"  "
"  .topnav {"
"    overflow: hidden;"
"    background-color: #333;"
"    position: relative;"
"  }"
"  "
"  .topnav #myLinks {"
"    display: none;"
"  }"
"  "
"  .topnav a {"
"    float: left;"
"    color: white;"
"    padding: 14px 16px;"
"    text-decoration: none;"
"    font-size: 17px;"
"  }"
"  "
"  .topnav a.icon {"
"    float: right;"
"  }"
"  "
"  .topnav a:hover {"
"    background-color: #ddd;"
"    color: black;"
"  }"
"  "
"  .active {"
"    background-color: #04AA6D;"
"    color: white;"
"  }"
"  #myLinks a {"
"    margin-top: 0; "
"    color: rgb(93, 190, 214);"
"    text-decoration: none;"
"    display: block;"
"}"
".icon {"
"    font-size: 18px; "
"    margin-top: 0; "
"}"
""
"    </style>"
"</head>";

String script = "<script>"
"function myFunction() {"
"  var x = document.getElementById('myLinks');"
"  if (x.style.display === 'block') {"
"    x.style.display = 'none';"
"  } else {"
"    x.style.display = 'block';"
"  }"
"}"
"</script>";

String body_page_Hum(String hum){
    String body ="<body>";
    body +="<div class='mobile-container}'>";
    body +="<!-- Top Navigation Menu -->";
    body +="<div class='topnav'>";
    body +="  <a href='/' class='active'>Smart Plant</a>";
    body +="  <div id='myLinks'>";
    body +="    <a href='config'>Config</a>";
    body +="  </div>";
    body +="  <a href='javascript:void(0);' class='icon' onclick='myFunction()'>";
    body +="    <i class='fa fa-bars'>Menu</i>";
    body +="  </a>";
    body +="</div>";
    body +="    <div class='container border-gradient'>";
    body +="        <div class='content-table'>";
    body +="                <br>";
    body +="                <span class='emoji'>&#128167</span>";
    body +="                <span> Humedad </span>";
    body +="                <span id='value-sensor'> ";
    body +=hum;
    body +="%</span>";
    body +="       </div>";
    body +="    </div>";
    return body;
}

String body_config(String trigger){
    String body ="<body>";
    body +="<div class='mobile-container}'>";
    body +="<!-- Top Navigation Menu -->";
    body +="<div class='topnav'>";
    body +="  <a href='/' class='active'>Smart Plant</a>";
    body +="  <div id='myLinks'>";
    body +="    <a href='config'>Config</a>";
    body +="  </div>";
    body +="  <a href='javascript:void(0);' class='icon' onclick='myFunction()'>";
    body +="    <i class='fa fa-bars'>Menu</i>";
    body +="  </a>";
    body +="</div>";
    body +="    <div class='container border-gradient'>";
    body +=" <center><h1>Configuraciones</h1></center>";
    body +=" <form action='saveConfig' method='get'>";
    body +=" Umbral de Humedad <input placeholder='Valor actual:";
    body += trigger;
    body +=", Valor debe estar entre 0 y 1023' name='triggerHumedad'><br>";
    /*
    body +=" Nombre equipo <input placeholder=' Proximamente' name='nameDevice' disabled><br>";
    body +=" Ip Servidor <input placeholder=' Proximamente' name='ipServer'disabled><br>";
    body +=" Test Bomba <input class='btn' type='checkbox' value='TEST'disabled /><br>";
    */
    body+="    <center><input class='btn' type='submit' value='GUARDAR'/></center><br>";
    body+="    </form>";
    body +="       </div>";
    body +="    </div>";
    Serial.println("termine de exponer el body del config");
    return body;
}

#endif
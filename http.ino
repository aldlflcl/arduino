// html->string 변환사이트
// http://davidjwatts.com/youtube/esp8266/esp-convertHTM.html#
// https://tomeko.net/online_tools/cpp_text_escape.php?lang=en
String webHead="<html> <head> <meta name='PLC_Control' content='width=device-width, initial-scale=1.0'/> <meta http-equiv='Content-Type' content='text/html;charset=utf-8' /> <style type=\"text/css\"> .button{ text-decoration:none; font-family:Arial; text-indent:0px; line-height:30px; -moz-border-radius:8px; -webkit-border-radius:8px; border-radius:8px; text-align:center; vertical-align:middle; display:inline-block; font-size:20px; color:#ffffff; background: blue; width:100px; height:60px; padding:13px; border-color:#ffffff; border-width:2px; border-style:solid; } .button-on{background-color:#18e018c2;} .button-off{background-color:#c91818;} </style> </head> <body> <h1>41415078 이정완</h1> <br>";

String webTail="</body> </html>";


void handleRoot() {
  String s=""; 
  s+="<form action='/on'>";
  if(ledOn[0] == 1)
{
  s=s+"<button type='submit' name='button' value='0' class='button button-on' > P40 </button> </a>";
}
  else
  {
   s=s+"<button type='submit' name='button' value='0' class='button button-off' > P40 </button> </a>";
  }
    if(ledOn[1] == 1)
{
  s=s+"<button type='submit' name='button' value='1' class='button button-on' > P41 </button> </a>";
}
  else
  {
    s=s+"<button type='submit' name='button' value='1' class='button button-off' > P41 </button> </a>";
  }
    if(ledOn[2] == 1)
{
  s=s+"<button type='submit' name='button' value='2' class='button button-on' > P42 </button> </a>";
}
  else
  {
    s=s+"<button type='submit' name='button' value='2' class='button button-off' > P42 </button> </a>";
  }
    if(ledOn[3] == 1)
{
  s=s+"<button type='submit' name='button' value='3' class='button button-on' > P43 </button> </a>";
}
  else
  {
    s=s+"<button type='submit' name='button' value='3' class='button button-off' > P43 </button> </a>";
  }
  s+="</form>";

  if(ledOn[0] == 1 && ledOn[1] == 1 && ledOn[2] == 1 && ledOn[3] == 1) 
  {
  ledOn[4] = 1;
  s=s+"<a href=\"onAll\"> <button id= \"buttonAll\" class= \"button button-on\"> All </button> </a>"; 
 }
  else 
  {
    ledOn[4] = 0;
  s=s+"<a href=\"onAll\"> <button id= \"buttonAll\" class= \"button button-off\"> All </button> </a>"; 
  }
  s=s+"<br><br>AP & IP :&emsp;"+sChipId+"&emsp;"+WiFi.localIP().toString();
  server.send(200, "text/html", webHead+s+webTail);
}

void handleWifi() {
  WiFiManager wm;
  wm.resetSettings();
  wm.resetSettings();
  ESP.reset();
}

void handleOnOff() {
  int no=server.arg("button").toInt();
  if(ledOn[no]==1)
    ledOn[no]=0;
  else
    ledOn[no]=1;
  cal();
  GoHome();
}

void handleOnOffAll() 
{
  flag = true;
  if(flag == true)
  {
      if(ledOn[4] == 0){
      ledOn[4] = 1;
      ledOn[0] = 1;
      ledOn[1] = 1;
      ledOn[2] = 1;
      ledOn[3] = 1;
      cal();
      GoHome();
     }
      else
      {
          ledOn[4] = 0;
          ledOn[0] = 0;
          ledOn[1] = 0;
          ledOn[2] = 0;
          ledOn[3] = 0;
          cal();
         GoHome();
            }
}
flag = false;
}

void GoHome() {
  String s,ipS;
  //IPAddress ip;
  ipS=toStringIp(WiFi.localIP());
  s="<meta http-equiv='refresh' content=\"0;url='http://"+ipS+"/'\">";
  server.send(200, "text/html", s);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleScan() {
  String s;
  s="{\"chipId\":\""+sChipId+"\",\"ip\":\""+WiFi.localIP().toString()+"\"}";
  server.send(200, "text/html", s);
}
void cal(){
  int sum = ledOn[0]+ledOn[1]*2+ledOn[2]*4+ledOn[3]*8;
  ss = "\0";
  ss +=char(5);
  ss += "00WSS0104%PW4000";
  ss += String(sum, HEX);
  ss +=char(4);
  Serial.println(" ");
  Serial.println(ss); 
  Serial1.print(ss);
 }

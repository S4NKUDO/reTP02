#include <Arduino.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// PID (Pour Mijoteuse)
#include <PID_v1.h>
double Setpoint;
double Input;
double Output;

const double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// ---- Pour faire des requêtes HTTP ----
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

ESP8266WebServer httpd(80);

const char *ssid = "RETP022025";
const char *pwd = "RETP022025";

String GetContentType(String filename)
{
  struct Mime
  {
    String ext, type;
  } mimeTypes[] = {
      {".html", "text/html"},
      {".js", "application/javascript"},
      {".css", "text/css"},
  };

  for (unsigned int i = 0; i < sizeof(mimeTypes) / sizeof(Mime); i++)
    if (filename.endsWith(mimeTypes[i].ext))
      return mimeTypes[i].type;
  
  return "application/octet-stream";
}

void setup()
{
  Serial.begin(115200);

  WiFi.softAP(ssid, pwd);
  Serial.print(WiFi.softAPIP()); // Mets en claire l'IP de l'access point
}

void loop()
{
}
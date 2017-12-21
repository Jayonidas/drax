// Includes
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Network Info
const char* ssid = "HauntedMansion";
const char* password = "monkeybaileyluna";

// Pins
const int pRelay01 = 13; // GPIO13

// Logging
const bool debug = true;

// Server Object
ESP8266WebServer server(80);

// Setup
void setup() {

  // Pin Modes
  pinMode(pRelay01,OUTPUT);

  // Pin States
  digitalWrite(pRelay01,HIGH); // HIGH = OFF (N.O. Relay)

  if(debug){
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }

  // Connect to Wifi Network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if(debug){
      Serial.print(".");
    }
  }
  if(debug){
    Serial.println("");
    Serial.println("WiFi connected successfully.");
  }
  
  // Handlers
  server.on("/", handleRootPath);
  server.on("/parameters", handleArgs);
  
  // Start the Server
  server.begin();
  if(debug){
    Serial.println("Server listening.");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  }
    
  
}


void handleRootPath(){
  server.send(200, "text/plain", "Nothing here!");
}


void handleArgs(){

  for (int i = 0; i < server.args(); i++) {
  
    if(server.argName(i) == "RelayState"){
      if(server.arg(i) == 1){
        server.send(200, "text/plain", String(digitalRead(pRelay01)));
      }
    }

    if(server.argName(i) == "RelayToggle"){
      if(server.arg(i) == 0){
        digitalWrite(pRelay01,LOW);
      }
      if(server.arg(i) == 1){
        digitalWrite(pRelay01,HIGH);
      }
      
    }
  
  }
  
}

// Loop
void loop() {
  server.handleClient();
}

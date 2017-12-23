// Notes:
// Servo range (full): 400-2544
// gate range: 400-875

// Includes
#include <ESP8266WebServer.h>
#include <Servo.h>

// Network Info
const char* ssid = "HauntedMansion";
const char* password = "monkeybaileyluna";

// Pin Layout (NodeMCU)
const int pRelay01 = 12; // GPIO12 (D6)
const int pRelay02 = 13; // GPIO13 (D7)
const int pRelay03 = 15; // GPIO15 (D8)
const int pServo = 14; // TEMP

// Relay ID Array
int relays[4] = {
  0,
  pRelay01,
  pRelay02,
  pRelay03
};

// Logging
const bool debug = true;

// Server Object
ESP8266WebServer server(80);

// Servo Object
Servo myServo;

int pos = 400;

// Setup
void setup() {

  myServo.attach(pServo);
  myServo.writeMicroseconds(400);

  // Pin Modes
  pinMode(pRelay01,OUTPUT);
  pinMode(pRelay02,OUTPUT);
  pinMode(pRelay03,OUTPUT);

  // Initial Pin States
  digitalWrite(pRelay01,LOW);
  digitalWrite(pRelay02,LOW);
  digitalWrite(pRelay03,LOW);

  if(debug){
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }

  // Connect Device to Wifi Network
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
  
  // Server Handlers
  server.on("/", handleRootPath);
  server.on("/toggleRelay",handleToggleRelay);
  server.on("/queryRelay",handleQueryRelay);
  server.on("/openBlastGate",handleBlastGate);
  
  // Start the Server
  server.begin();
  if(debug){
    Serial.println("Server listening...");
    Serial.print("URL: http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
    Serial.println("");
  }
    
}

// Loop
void loop() {
  server.handleClient();
}

void handleRootPath(){
  server.send(200, "text/plain", "");
  if(debug){
    Serial.println("Client hit the root directory.");
  }
}

void handleBlastGate(){
  int gateId = server.arg(0).toInt();
  int action = server.arg(1).toInt();
  if(action == 1){
    myServo.writeMicroseconds(950);
    Serial.println("Opening.");
  }
  if(action == 0){
    myServo.writeMicroseconds(500);
    Serial.println("Closing.");
  }
  server.send(200, "text/plain", "Ok!");
}

void handleQueryRelay(){
  
  int result = 999;
  int relayId = server.arg(0).toInt();
  String message;
  
  if(server.argName(0) == "relay"){
    
    result = digitalRead(relays[relayId]);

    // Send Response to Client
    server.send(200, "text/plain", String(result));
    
    // Logging
    if(debug){
      String message = "Client queried the state of relay["+String(relayId)+"]. Result: "+String(result)+".";
      Serial.println(message);
    }
    
  }
  
}

void handleToggleRelay(){
  
  int relayId = server.argName(0).toInt();
  int relayToggle = server.arg(0).toInt();
  String message;
  
  if(relayToggle == 0){ // OFF
    
    digitalWrite(relays[relayId],LOW);
    
    if(debug){
      message = "Toggled relay["+String(relayId)+"] OFF.";
    } else {
      message = "0";
    }

    // Send Response to Client
    server.send(200, "text/plain", message);
    
    // Logging
    if(debug){
      Serial.println(message);
    }
    
  }
  
  if(relayToggle == 1){ // ON
    
    digitalWrite(relays[relayId],HIGH);
    
    if(debug){
      message = "Toggled relay["+String(relayId)+"] ON.";
    } else {
      message = "1";
    }

    // Send Response to Client
    server.send(200, "text/plain", message);
    
    // Logging
    if(debug){
      Serial.println(message);
    }
  }  

}

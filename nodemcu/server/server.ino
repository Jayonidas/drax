// Includes
#include <ESP8266WiFi.h>

// Network Data
const char* ssid = "HauntedMansion";
const char* password = "monkeybaileyluna";

// Pins
const int pRelay01 = 13; // GPIO13

// Logging
const bool debug = true;

// Wifi Server Object
WiFiServer server(80);

// Setup
void setup() {

  // Pin Modes
  pinMode(pRelay01,OUTPUT);

  // Pin States
  digitalWrite(pRelay01,HIGH); // HIGH = OFF (N.O. Relay)

  if(debug){
    Serial.begin(9600);
    delay(1000);
  
    // Connect to WiFi network
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
    Serial.println("WiFi connected");
  }
  
  // Start the Server
  server.begin();
  if(debug){
    Serial.println("Server Started!");
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  }
  
}

// Loop
void loop() {
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New Client!");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  int value = LOW;
  if (request.indexOf("/RELAY=ON") != -1)  {
    digitalWrite(pRelay01, LOW);
    value = LOW;
  }
  if (request.indexOf("/RELAY=OFF") != -1)  {
    digitalWrite(pRelay01, HIGH);
    value = HIGH;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Relay State: ");
 
  if(value == HIGH) {
    client.print("Closed");
  } else {
    client.print("Open");
  }
  client.println("<br><br>");
  client.println("<a href=\"/RELAY=ON\"\"><button>Open Relay</button></a>");
  client.println("<a href=\"/RELAY=OFF\"\"><button>Close Relay</button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client Disconnected.");
  Serial.println("");  
  
}

#include <TroykaGPS.h>
#include <SPI.h>
#include <WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define MAX_SIZE_MASS 16

char time[MAX_SIZE_MASS];
char ssid[] = "yourNetwork";                                        // Network name
char pass[] = "secretPassword";                                     // Password from the wi-fi network
int keyIndex = 0;                                                   // Index number of the network key (required only for WEP)
int status = WL_IDLE_STATUS;
float Longitude, Width;

IPAddress server(74,125,232,128);                                   // Google IP address (without DNS)
//char server[] = "www.google.com";                                 // Google DNS address

WiFiClient client;                                                  // Initializing the Ethernet library using the IP address and port of the server to connect to (default port 80 for HTTP)

void setup() {
  Serial.begin(115200);
  while (!Serial) {}                                                // Waiting for the COM port to open. Required only when connecting the board via USB
  
  WiFi.begin("SSID", "PASSWORD");                                   // WiFi connection
  while (WiFi.status() != WL_CONNECTED) {                           // Waiting for a Wi-Fi connection
    delay(500);
    Serial.println("Waiting for connection");
  }

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  String fv = WiFi.firmwareVersion();

  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }
  // Attempt to connect to Wifi network
  while (status != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);                                // Network connection with WPA/WPA2 encryption. You need to change this line if you are using an open network or a network with WEP encryption
    delay(10000);                                                   // 10 seconds delay for connection
  }

  Serial.println("Connected to wifi");
  Serial.println("\nStarting connection to server...");

  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // HTTP request:
    client.println("POST /search?q=arduino HTTP/1.1");
    client.println("get_new_task");
  }
}
 
void loop(){
  if (WiFi.status() == WL_CONNECTED) {                              // Checking the status of the Wi Fi connection
    if (gps.available()) {
      gps.readParsing();
      switch(gps.getState()) {
        case GPS_OK:
          Longitude = gps.getLatitudeBase10();
          Width = gps.getLongitudeBase10();
          Serial.println("GPS is OK");
          HTTPClient http;                                          // Declaring an HttpClient class object
          http.begin("server");                                     // The addressee of the request
          http.addHeader("Content-Type", "text/plain");             // Specifying the content type header
          float httpCode = http.POST(Longitude, 6);                 // Sending a request
          float httpCode = http.POST(Width, 6);                     // Sending a request
          String payload = http.getString();                        // Get an answer
          Serial.println(httpCode);                                 // Output the HTTP response code
          Serial.println(payload);                                  // Output of the response to the request
          http.end();                                               // Close connection
          break;
        case GPS_ERROR_DATA:
          Serial.println("GPS error data");
          break;
        case GPS_ERROR_SAT:
          Serial.println("GPS no connect to satellites");
          break;
      }
    }
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(30000);                                                     // Send a request every 30 seconds
}

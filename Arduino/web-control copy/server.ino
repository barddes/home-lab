#include <WiFi.h>
WiFiServer server(80);

void webServerSetup() {
  server.begin();
  logtime();
  Serial.println("WebServer started");
}

void handleWebConnection() {
  WiFiClient client = server.available();
  if (client) {
    logtime();
    Serial.println("Web client connected");
    
    // read request line
    char error = '-';
    Request* request = readRequest(client, &error);

    switch(error) {
      case 'A':
      logtime();
      Serial.println("Error: client not available");
      return;
      case 'D':
      logtime();
      Serial.println("Error: client not connected");
      return;
    }

    logtime();
    Serial.print("Request parsed: ");
    Serial.print(request->method);
    Serial.print(" ");
    Serial.println(request->path);

    // send response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.print("<blink>Request parsed: ");
    client.print(request->method);
    client.print(" ");
    client.print(request->path);
    client.println("</blink>");
    client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 2 on.<br>");
    client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 2 off.<br>");
    client.println();

    client.stop();

    logtime();
    Serial.println("Request ended");
  }
}
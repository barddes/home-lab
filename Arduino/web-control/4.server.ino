void startWebServer() {
  server.on("/", HTTP_GET, handlePlant);
  server.on("/metrics", HTTP_GET, handleMetrics);
  server.on("/ping", HTTP_GET, handlePing);
  server.on("/plant", HTTP_GET, handlePlant);
  server.on("/pump", handlePump);
  server.on("/check", handleCheck);
  server.on("/sensor", handleSensor);

  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("HTTP server started");
}

void handlePing(AsyncWebServerRequest* request) {
  digitalWrite(LED_BUILTIN, 1);
  request->send(200, "text/plain", "pong");
  digitalWrite(LED_BUILTIN, 0);
}

void handleMetrics(AsyncWebServerRequest* request) {
  digitalWrite(LED_BUILTIN, 1);
  request->send(200, "text/plain", getMetrics());
  digitalWrite(LED_BUILTIN, 0);
}

void handleNotFound(AsyncWebServerRequest* request) {
  digitalWrite(LED_BUILTIN, 1);
  request->send(404, "text/plain", "Not Found");
  digitalWrite(LED_BUILTIN, 0);
}
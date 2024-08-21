#include <WiFi.h>

typedef enum {
    GET, POST
} RequestMethod;

typedef struct Request{
    RequestMethod method;
    String path;
} Request;

String readToken(WiFiClient client, char *error) {
    String token = "";
    while(1) {
        char c = client.read();
        switch(c) {
            case -1:
            *error = 'A';
            return token;

            case ' ':
            case '\r':
            case '\n':
            return token;

            default:
            token += c;
        }
    }
}

Request *readRequest(WiFiClient client, char* error) {
    if(!client.connected()) {
        *error = 'D';
        return NULL;
    }

    if(!client.available()) {
        *error = 'A';
        return NULL;
    }

    Request* request = malloc(sizeof(Request));
    String method = readToken(client, error);
    if (method.equalsIgnoreCase("GET"))  request->method = GET;
    if (method.equalsIgnoreCase("POST")) request->method = POST;
    request->path = readToken(client, error);

    return request;
}
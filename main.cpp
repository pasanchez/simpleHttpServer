#include <stdio.h>
#include "Server.h"

int main() {

    printf("Starting server.\n");
    Server server(8000);
    printf("Listening....\n");
    server.registerAction("/",[](std::string requestUrl)->std::string {
        std::string response = "HTTP/1.0 200 OK\r\n Content-Length: 45\r\n\r\n";
        response += "<html><body>";
        response += "<b><big> IT WORKS!!</big></b> <br>";
        response += "</body></html>";
        return  response;
    });
    server.listen();
    return 0;
}
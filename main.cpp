#include <stdio.h>
#include "Server.h"

int main() {

    printf("Starting server.\n");
    Server server(8000);
    printf("Listening....\n");
    server.registerAction("/",[](std::unordered_map<std::string,std::string> params)->std::string {
        std::string response;
        response = "HTTP/1.0 200 OK\r\n Content-Length: 45\r\n\r\n";
        response += "<html><body>";
        if (params.find("name") != params.end() && params.find("age") != params.end()) {
            response += "<b><big> Your name is " + params["name"] + " and you are " + params["age"] +
                        " years old</big></b> <br>";
        } else {
            response += "<b><big>Bad syntax. Usage: /?name=userName&age=3</big></b> <br>";
        }
        response += "</body></html>";
        return  response;
    });
    server.listen();
    return 0;
}
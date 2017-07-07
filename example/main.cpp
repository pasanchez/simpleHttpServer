#include <stdio.h>
#include "../Server.h"
#include "json/json.h"


std::string jsonConstructor(std::string name, std::string age);

int main(int argc, char* argv[]) {

    uint16 port;

    if (argc > 1) {
        try {
            port = (uint16) std::stoul(argv[1]);
        }catch (std::exception exception) {
            printf("%s\n",exception.what());
            port = 8080;
        }
    } else {
        port = 8080;
    }

    printf("Starting server.\n");
    Server server(port);
    printf("Listening on port %d....\n",port);
    server.registerAction("/",[](std::unordered_map<std::string,std::string> params)->std::string {
        std::string response;
        response = "HTTP/1.0 200 OK\r\n Content-Length: 45\r\n\r\n";
        response += "<html><body>";
        if (params.find("name") != params.end() && params.find("age") != params.end()) {
            response += jsonConstructor(params["name"],params["age"]);
        } else {
            response += "<b><big>Bad syntax. Usage: /?name=userName&age=3</big></b> <br>";
        }
        response += "</body></html>";
        return  response;
    });
    server.listen();
    return 0;
}


std::string jsonConstructor(std::string name, std::string age){
    Json::Value json;
    json["name"] = name;
    json["age"] = age;
    std::stringstream output;
    output << json;
    return output.str();
}
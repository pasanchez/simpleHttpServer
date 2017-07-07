#include "Server.h"

#pragma clang diagnostic push
using namespace boost::asio::ip;

Server::Server(uint16 portNumber) {
    this->portNumber = portNumber;
}

void Server::listen() {
    try {
        boost::asio::io_service io_service;
        s = new tcp::socket(io_service);
        acceptor = new tcp::acceptor(io_service,tcp::endpoint(tcp::v4(),portNumber));
        this->continueLooping = true;
        while (this->continueLooping) {
            acceptor->accept(*s);
            boost::system::error_code error;

            // read request
            boost::asio::streambuf requestBuff;
            boost::asio::read_until(*s, requestBuff, "\r\n");
            std::istream is(&requestBuff);
            char getBuff[1024];
            std::string firstLine;
            std::getline(is, firstLine);
            sscanf(firstLine.c_str(),"%*s %s %*s",getBuff);
            std::string get(getBuff);

            // send response
            std::string response = this->doAction(get);
            auto buff = boost::asio::buffer(&response[0],response.size());
            boost::asio::write(*s, buff , error);
            s->close();
        }
    }catch (std::exception &e) {
        fprintf(stderr,"%s\n",e.what());
    }

}

std::string Server::doAction(std::string requestUrl) {
    unsigned long position = requestUrl.find("?",0);
    std::string url = requestUrl.substr(0,position);
    std::string params = requestUrl.substr(position+1, requestUrl.length()-position-1);
    if (this->handlerTable.find(url) != this->handlerTable.end()) {
        return this->handlerTable[url](splitParams(params));
    } else {
        std::string response = "HTTP/1.0 404 NOT FOUND\r\n Content-Length: 45\r\n\r\n";
        response += "<html><body>";
        response += "<b><big>Error 404. The requested url " + url + " could not be loaded.</big></b> <br>";
        response += "</body></html>";
        return response;
    }
}

void Server::registerAction(std::string url,connection_handler_t handler) {
    this->handlerTable[url] = handler;
}

void Server::stop() {
    this->continueLooping = false;
}

std::unordered_map<std::string, std::string> Server::splitParams(std::string params) {
    std::unordered_map<std::string, std::string> paramTable;
    if (params.empty()) return paramTable;
    unsigned long position;
    unsigned long prevPosition = 0;
    do {
        position = params.find("&",prevPosition);
        std::string var;
        if (position != std::string::npos) {
            var = params.substr(prevPosition,position-prevPosition);
        } else {
            var = params.substr(prevPosition,params.length()-prevPosition);
        }
        unsigned long ePos = var.find("=",0);
        paramTable[var.substr(0,ePos)] = var.substr(ePos+1,var.length()-ePos-1);
        prevPosition = position + 1;
    }while(position != std::string::npos);
    return paramTable;
}

#pragma clang diagnostic pop
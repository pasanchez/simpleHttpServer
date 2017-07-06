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
    if (this->handlerTable.find(requestUrl) != this->handlerTable.end()) {
        return this->handlerTable[requestUrl](requestUrl);
    } else {
        std::string response = "HTTP/1.0 404 NOT FOUND\r\n Content-Length: 45\r\n\r\n";
        response += "<html><body>";
        response += "<b><big>Error 404. The requested url " + requestUrl + " could not be loaded.</big></b> <br>";
        response += "</body></html>";
        return response;
    }
}

void Server::registerAction(std::string url, std::function<std::string(std::string)> handler) {
    this->handlerTable[url] = handler;
}

void Server::stop() {
    this->continueLooping = false;
}

#pragma clang diagnostic pop
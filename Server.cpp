#include "Server.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
using namespace boost::asio::ip;

Server::Server(uint16 portNumber) {
    this->portNumber = portNumber;
}

void Server::listen() {
    try {
        boost::asio::io_service io_service;
        s = new tcp::socket(io_service);
        acceptor = new tcp::acceptor(io_service,tcp::endpoint(tcp::v4(),portNumber));
        while (true) {
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

    printf("Requested URL: %s\n", requestUrl.c_str());

    // Here we could do different actions for each url requested, but we will return always
    // the same page.

    std::string response = "HTTP/1.0 200 OK\r\n Content-Length: 45\r\n\r\n";
    response += "<html><body>";
    response += "<b><big>You requested: " + requestUrl + "</big></b> <br>";
    response += "</body></html>";
    return  response;
}

#pragma clang diagnostic pop
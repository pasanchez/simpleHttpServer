

#ifndef FOODPLANNER_SERVER_H
#define FOODPLANNER_SERVER_H


#include <tiff.h>
#include <boost/asio.hpp>

using namespace boost::asio::ip;


class Server {

public:
    Server(uint16 portNumber);
    void listen();

private:
    std::string doAction(std::string requestUrl);
    uint16 portNumber;
    tcp::socket *s;
    tcp::acceptor *acceptor;
};


#endif //FOODPLANNER_SERVER_H

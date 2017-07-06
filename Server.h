

#ifndef FOODPLANNER_SERVER_H
#define FOODPLANNER_SERVER_H


#include <tiff.h>
#include <boost/asio.hpp>
#include <unordered_map>

using namespace boost::asio::ip;


class Server {

public:
    Server(uint16 portNumber);
    void registerAction(std::string url, std::function<std::string(std::unordered_map<std::string,std::string>)> handler);
    void listen();
    void stop();

private:
    std::unordered_map<std::string, std::function<std::string(std::unordered_map<std::string,std::string>)>> handlerTable;
    std::string doAction(std::string requestUrl);
    std::unordered_map<std::string, std::string> splitParams(std::string params);
    uint16 portNumber;
    tcp::socket *s;
    tcp::acceptor *acceptor;
    bool continueLooping;
};


#endif //FOODPLANNER_SERVER_H

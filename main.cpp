#include <boost/asio.hpp>
#include <iostream>
#include "tcpserver.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: join_server <port>\n";
        return 1;
    }

    boost::asio::io_context io;
    Server server(io, static_cast<unsigned short>(std::stoi(argv[1])));
    io.run();
}

#pragma once

#include <boost/asio.hpp>
#include "storage.h"

class Server {
public:
    Server(boost::asio::io_context& io, unsigned short port);

private:
    void accept();

    boost::asio::ip::tcp::acceptor m_acceptor;
    Storage m_tables;
};

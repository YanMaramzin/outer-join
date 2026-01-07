#include "tcpserver.h"
#include "session.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io, unsigned short port)
    : m_acceptor(io, tcp::endpoint(tcp::v4(), port)) {
    accept();
}

void Server::accept() {
    m_acceptor.async_accept(
        [this](auto ec, tcp::socket socket) {
            if (!ec)
                std::make_shared<Session>(std::move(socket), m_tables)->start();

            accept();
        });
}

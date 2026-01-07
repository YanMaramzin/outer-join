#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include "storage.h"

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::ip::tcp::socket socket, Storage &tables);

    void start();

private:
    void read();
    void process(const std::string& line);
    void write(const std::string& msg);

    boost::asio::ip::tcp::socket m_socket;
    boost::asio::streambuf m_buffer;
    Storage &m_tables;
};

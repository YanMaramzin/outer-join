#include <sstream>
#include "session.h"

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket, Storage &tables)
    : m_socket(std::move(socket)), m_tables(tables) {}

void Session::start() {
    read();
}

void Session::read() {
    auto self = shared_from_this();
    boost::asio::async_read_until(
        m_socket, m_buffer, '\n',
        [this, self](auto ec, auto) {
            if (!ec) {
                std::istream is(&m_buffer);
                std::string line;
                std::getline(is, line);
                process(line);
                read();
            }
        });
}

void Session::process(const std::string& line) {
    try {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "INSERT") {
            char table;
            int id;
            std::string name;
            iss >> table >> id >> name;
            m_tables.insert(table, id, name);
            write("OK\n");
        }
        else if (cmd == "TRUNCATE") {
            char table;
            iss >> table;
            m_tables.truncate(table);
            write("OK\n");
        }
        else if (cmd == "INTERSECTION") {
            for (auto& [id, a] : m_tables.A) {
                if (m_tables.B.contains(id)) {
                    write(std::to_string(id) + "," + a + "," + m_tables.B[id] + "\n");
                }
            }
            write("OK\n");
        }
        else if (cmd == "SYMMETRIC_DIFFERENCE") {
            for (auto& [id, a] : m_tables.A) {
                if (!m_tables.B.contains(id))
                    write(std::to_string(id) + "," + a + ",\n");
            }
            for (auto& [id, b] : m_tables.B) {
                if (!m_tables.A.contains(id))
                    write(std::to_string(id) + ",," + b + "\n");
            }
            write("OK\n");
        }
        else {
            write("ERR unknown command\n");
        }
    }
    catch (const std::exception& e) {
        write(std::string("ERR ") + e.what() + "\n");
    }
}

void Session::write(const std::string& msg) {
    auto self = shared_from_this();
    boost::asio::async_write(
        m_socket,
        boost::asio::buffer(msg),
        [self](auto, auto) {});
}

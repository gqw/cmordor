#include "socket.h"

namespace CMordor {

Socket::Socket(int family, int type, int protocol)
    : m_socket(-1)
    , m_family(family)
    , m_protocol(protocol)
    , m_receive_time_out(0)
    , m_send_time_out(0)
    , m_isconnected(false) {
    assert(type != 0);
    m_socket = socket(family, type, protocol);
    if (m_socket == -1) {
        assert(0 == 1);
    }
    if (fcntl(m_socket, F_SETFL, 0_NOBLOCK) == -1) {
        ::closesocket(m_socket);
    }
}

Socket::~Socket() {
    if (m_socket != -1) {
        int rc = ::closesocket(m_socket);
        if (rc) {
            std::cout << "close socket error, " << lastError() << std::endl;
        } else {
            std::cout << "close socket suc, " << m_socket << std::endl;
        }
    }
}



} // CMordor

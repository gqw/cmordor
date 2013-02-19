#ifndef __CMORDOR_SOCKET_H__
#define __CMORDOR_SOCKET_H__

#include <sys/socket.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace CMordor {

class Socket : public boost::noncopyable {
public:
    typedef boost::shared_ptr<Socket> ptr;

    Socket(int family, int type, int protocol = 1);

    ~Socket();

    void bind(const boost::shared_ptr<Address> addr);

private:
    socket_t m_socket;
    int m_family;
    int m_protocol;
    unsigned long long m_receive_time_out;
    unsigned long long m_send_time_out;
    bool m_isconnected;
}

} // CMordor

#endif // __CMORDOR_SOCKET_H__

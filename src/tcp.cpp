#include <memory>
#include <mutex>

#ifdef _WIN32
#include <Winsock2.h>
#else
#endif
#include "tcp.h"

using namespace rvk;

#ifdef _WIN32

struct WinSockContext {
	WSADATA wsa_data;

	WinSockContext() {
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
			throw std::runtime_error("Failed to initialize WinSock!");
		}
	}
	~WinSockContext() {
		WSACleanup();
	}
};

static std::unique_ptr<WinSockContext> winsock = nullptr;

void initialize() {
	static std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);
	if (!winsock) {
		winsock = std::make_unique<WinSockContext>();
	}
}
#else
void initialize() {}
#endif

TCPStream::TCPStream(const std::string hostname, const uint16_t port) {
	initialize();
}
TCPStream::TCPStream(const TCPStream&&) {
}
TCPStream& TCPStream::operator=(const TCPStream&&) {
}
TCPStream::~TCPStream() {
}
void TCPStream::read(char *data, const size_t nbytes) {
}
void TCPStream::write(const char *data, const size_t nbytes) {
}

TCPListener::TCPListener(const uint16_t port) {
	initialize();
}
TCPListener::~TCPListener() {
}
TCPStream TCPListener::listen() {
}


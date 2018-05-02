#include <memory>
#include <mutex>
#include <atomic>

#ifdef _WIN32
#include <Winsock2.h>
#define SHUT_RDWR SD_BOTH
#else
#include <sys/socket.h>
#include <sys/types.h> 
#include <netdb.h>
#include <unistd.h>
#endif
#include "tcp.h"

using namespace rvk;

#ifdef _WIN32

struct WinSockContext {
	WinSockContext() {
		WSADATA wsa_data;
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
	static std::atomic<bool> initialized = false;
	if (!initialized) {
		static std::mutex mutex;
		std::lock_guard<std::mutex> lock(mutex);
		if (!winsock) {
			winsock = std::make_unique<WinSockContext>();
		}
		initialized = true;
	}
}
#else
void initialize() {}
#endif

TCPStream::TCPStream(const std::string hostname, const uint16_t port) {
	initialize();
	// TODO: I guess here we should be using getaddrinfo instead of gethostbyname now
}
TCPStream::TCPStream(const TCPStream&&) {
}
TCPStream& TCPStream::operator=(const TCPStream&&) {
}
TCPStream::~TCPStream() {
	if (socket > -1) {
		shutdown(socket, SHUT_RDWR);
#ifdef _WIN32
		closesocket(socket);
#else
		close(socket);
#endif
	}
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


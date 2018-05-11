#include <memory>
#include <cstring>
#include <mutex>
#include <atomic>
#include <iostream>

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
	addrinfo hints;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	// TODO WILL: What do we include for getaddrinfo in winsock?
	addrinfo *result = nullptr;
	const std::string service = std::to_string(port);
	const int err = getaddrinfo(hostname.c_str(), service.c_str(), &hints, &result);
	if (err != 0) {
		std::cerr << "TCPStream: Error in getaddrinfo: " << gai_strerror(err) << std::endl;
		throw std::runtime_error("getaddrinfo failed with host '" + hostname
				+ "' and port " + service);
	}
	for (addrinfo *ad = result; ad != nullptr; ad = ad->ai_next) {
		std::cout << "Testing port socket\n";
		socket = ::socket(ad->ai_family, ad->ai_socktype, ad->ai_protocol);
		if (socket == -1) {
			continue;
		}
		if (connect(socket, ad->ai_addr, ad->ai_addrlen) != -1) {
			std::cout << "Connected socket\n";
		}
#ifdef _WIN32
		closesocket(socket);
#else
		close(socket);
#endif
	}
	freeaddrinfo(result);
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
	addrinfo hints;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	// TODO WILL: What do we include for getaddrinfo in winsock?
	addrinfo *result = nullptr;
	const std::string service = std::to_string(port);
	const int err = getaddrinfo(nullptr, service.c_str(), &hints, &result);
	if (err != 0) {
		std::cerr << "TCPListener: Error in getaddrinfo: " << gai_strerror(err) << std::endl;
		throw std::runtime_error("getaddrinfo failed with port " + service);
	}
	for (addrinfo *ad = result; ad != nullptr; ad = ad->ai_next) {
		std::cout << "Testing port socket\n";
		socket = ::socket(ad->ai_family, ad->ai_socktype, ad->ai_protocol);
		if (socket == -1) {
			continue;
		}
		if (bind(socket, ad->ai_addr, ad->ai_addrlen) != -1) {
			std::cout << "Bound to socket\n";
		}
#ifdef _WIN32
		closesocket(socket);
#else
		close(socket);
#endif
	}
	freeaddrinfo(result);

	if (listen(socket, 4) != 0) {
		std::cout << "Failed to listen on socket\n";
	}
}
TCPListener::~TCPListener() {
}
TCPStream TCPListener::accept() {
	sockaddr_in peer_addr;
	socklen_t len = sizeof(peer_addr);
	int peer_sock = ::accept(socket, reinterpret_cast<sockaddr*>(&peer_addr), &len);
	if (peer_sock == -1) {
		std::cout << "Failed to accept peer socket\n";
	}
	// TODO: Setup some opts like nodelay and sigpipe no throw
}


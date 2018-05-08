#pragma once

#include <string>
#include "rvk_export.h"
#include "reader_writer.h"

namespace rvk {

class RVK_EXPORT TCPStream : public Reader, Writer {
	int socket;

public:
	// Connect to the host on the desired port
	TCPStream(const std::string hostname, const uint16_t port);
	TCPStream(const TCPStream&&);
	TCPStream& operator=(const TCPStream&&);
	~TCPStream();

	TCPStream(const TCPStream&) = delete;
	TCPStream& operator=(const TCPStream&) = delete;

	void read(char *data, const size_t nbytes) override;
	void write(const char *data, const size_t nbytes) override;
};

class RVK_EXPORT TCPListener {
	int socket;

public:
	// Bind to a port on this host
	TCPListener(const uint16_t port);
	~TCPListener();

	TCPListener(const TCPListener&) = delete;
	TCPListener& operator=(const TCPListener&) = delete;

	// Wait for a new connection on the port and return it
	TCPStream accept();
};

}


#include <iostream>
#include <thread>
#include "rvk.h"

const static int NUM_PINGS = 5;
const static uint16_t LISTEN_PORT = 6910;

void sender() {
	for (int i = 0; i < NUM_PINGS; ++i) {
		rvk::TCPStream stream("localhost", LISTEN_PORT);
		stream << int(i);
		int returned = 0;
		stream >> returned;
		std::cout << "Got back " << returned << "\n";
	}
}

int main(int, char**) {
	rvk::TCPListener listener(LISTEN_PORT);

	std::thread send_thread(sender);
	for (int i = 0; i < NUM_PINGS; ++i) {
		auto stream = listener.accept();
		int value = 0;
		stream >> value;
		std::cout << "Read value " << value << "\n";
		stream << value + 1;
	}

	send_thread.join();
	return 0;
}


#include <cstring>
#include <stdexcept>
#include "read_buffer.h"

using namespace rvk;

ReadBuffer::ReadBuffer(std::vector<char> buffer)
	: begin(0), buffer(buffer)
{}
void ReadBuffer::read(char *out, const size_t nbytes) {
	if (begin + nbytes >= buffer.size()) {
		throw std::runtime_error("Buffer out of bytes for read");
	}
	std::memcpy(out, &buffer[begin], nbytes);
	begin += nbytes;
}

ReadBuffer& operator>>(ReadBuffer &b, std::string &s) {
	uint64_t size = 0;
	b >> size;
	s = std::string(size, '\0');
	b.read(&s[0], size);
	return b;
}


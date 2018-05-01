#include <cstring>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "buffer.h"

using namespace rvk;

Buffer::Buffer(const size_t capacity)
	: begin(0), end(0), buffer(capacity, 0)
{}
void Buffer::write(const char *data, const size_t nbytes) {
	if (end + nbytes >= buffer.size()) {
		buffer.resize(std::max(size_t(std::ceil(buffer.size() * 1.5)),
					buffer.size() + nbytes));
	}
	std::memcpy(&buffer[end], data, nbytes);
	end += nbytes;
}
void Buffer::read(char *out, const size_t nbytes) {
	if (begin + nbytes > end) {
		throw std::runtime_error("Buffer out of bytes for read");
	}
	std::memcpy(out, &buffer[begin], nbytes);
	begin += nbytes;
}


#include <cstring>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "write_buffer.h"

using namespace rvk;

WriteBuffer::WriteBuffer(const size_t initial_capacity)
	: end(0), buffer(initial_capacity, 0)
{}
void WriteBuffer::write(const char *data, const size_t nbytes) {
	if (end + nbytes >= buffer.size()) {
		buffer.resize(std::max(size_t(std::ceil(buffer.size() * 1.5)),
					buffer.size() + nbytes));
	}
	std::memcpy(&buffer[end], data, nbytes);
	end += nbytes;
}


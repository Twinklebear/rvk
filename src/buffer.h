#pragma once

#include <type_traits>
#include <vector>
#include "rvk_export.h"

namespace rvk {

class RVK_EXPORT Buffer {
	size_t begin, end;
	std::vector<char> buffer;

public:
	Buffer(const size_t capacity = 4 * 1024);
	void write(const char *data, const size_t nbytes);
	void read(char *out, const size_t nbytes);
};

}

template<typename T, typename std::is_trivially_copyable<T>::value>
rvk::Buffer& operator<<(rvk::Buffer &b, const T &t) {
	b.write(reinterpret_cast<const char*>(&t), sizeof(T));
	return b;
}

template<typename T, typename std::is_trivially_copyable<T>::value>
rvk::Buffer& operator>>(rvk::Buffer &b, T &t) {
	b.read(reinterpret_cast<char*>(&t), sizeof(T));
	return b;
}


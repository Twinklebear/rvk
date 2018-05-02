#pragma once

#include <type_traits>
#include <string>
#include <vector>
#include "rvk_export.h"

namespace rvk {

class RVK_EXPORT WriteBuffer {
	size_t end;
	std::vector<char> buffer;

public:
	WriteBuffer(const size_t initial_capacity = 4 * 1024);
	void write(const char *data, const size_t nbytes);
};

}

rvk::WriteBuffer& operator<<(rvk::WriteBuffer &b, const std::string &s);

template<typename T, typename = std::enable_if_t<std::is_trivially_copyable<T>::value>>
rvk::WriteBuffer& operator<<(rvk::WriteBuffer &b, const T &t) {
	b.write(reinterpret_cast<const char*>(&t), sizeof(T));
	return b;
}

template<typename T, typename = std::enable_if_t<std::is_trivially_copyable<T>::value>>
rvk::WriteBuffer& operator<<(rvk::WriteBuffer &b, const std::vector<T> &t) {
	const uint64_t size = s.size();
	b << size;
	for (const auto &e : t) {
		b << e;
	}
	return b;
}


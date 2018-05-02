#pragma once

#include <type_traits>
#include <string>
#include <vector>
#include "rvk_export.h"

namespace rvk {

class RVK_EXPORT ReadBuffer {
	size_t begin;
	std::vector<char> buffer;

public:
	ReadBuffer(std::vector<char> buffer);
	void read(char *data, const size_t nbytes);
};

}

rvk::ReadBuffer& operator>>(rvk::ReadBuffer &b, std::string &s);

template<typename T, typename = std::enable_if_t<std::is_trivially_copyable<T>::value>>
rvk::ReadBuffer& operator>>(rvk::ReadBuffer &b, T &t) {
	b.read(reinterpret_cast<char*>(&t), sizeof(T));
	return b;
}

template<typename T, typename = std::enable_if_t<std::is_trivially_copyable<T>::value>>
rvk::ReadBuffer& operator>>(rvk::ReadBuffer &b, std::vector<T> &t) {
	uint64_t size = 0;
	b >> size;
	t = std::vector<T>(size, T{});
	for (auto &e : t) {
		b >> e;
	}
	return b;
}


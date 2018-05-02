#pragma once

#include <type_traits>
#include <string>
#include <vector>
#include "rvk_export.h"

namespace rvk {

class RVK_EXPORT Reader {
public:
	virtual ~Reader();
	virtual void read(char *data, const size_t nbytes) = 0;
};

class RVK_EXPORT Writer {
public:
	virtual ~Writer();
	virtual void write(const char *data, const size_t nbytes) = 0;
};

}

rvk::Reader& operator>>(rvk::Reader &b, std::string &s);

template<typename T, typename = std::enable_if_t<std::is_trivially_copyable<T>::value>>
rvk::Reader& operator>>(rvk::Reader &b, T &t) {
	b.read(reinterpret_cast<char*>(&t), sizeof(T));
	return b;
}

template<typename T, typename = std::enable_if_t<std::is_trivially_copyable<T>::value>>
rvk::Reader& operator>>(rvk::Reader &b, std::vector<T> &t) {
	uint64_t size = 0;
	b >> size;
	t = std::vector<T>(size, T{});
	for (auto &e : t) {
		b >> e;
	}
	return b;
}

rvk::Writer& operator<<(rvk::Writer &b, const std::string &s);

template<typename T, typename = std::enable_if_t<std::is_trivially_copyable<T>::value>>
rvk::Writer& operator<<(rvk::Writer &b, const T &t) {
	b.write(reinterpret_cast<const char*>(&t), sizeof(T));
	return b;
}

template<typename T, typename = std::enable_if_t<std::is_trivially_copyable<T>::value>>
rvk::Writer& operator<<(rvk::Writer &b, const std::vector<T> &t) {
	const uint64_t size = t.size();
	b << size;
	for (const auto &e : t) {
		b << e;
	}
	return b;
}



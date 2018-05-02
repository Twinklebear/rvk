#include "reader_writer.h"

using namespace rvk;

Reader::~Reader() {}

Writer::~Writer() {}

Reader& operator>>(Reader &b, std::string &s) {
	uint64_t size = 0;
	b >> size;
	s = std::string(size, '\0');
	b.read(&s[0], size);
	return b;
}

Writer& operator<<(Writer &b, const std::string &s) {
	const uint64_t size = s.size();
	b << size;
	b.write(s.c_str(), size);
	return b;
}

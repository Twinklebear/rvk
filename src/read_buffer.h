#pragma once

#include <type_traits>
#include <string>
#include <vector>
#include "rvk_export.h"
#include "reader_writer.h"

namespace rvk {

class RVK_EXPORT ReadBuffer : public Reader {
	size_t begin;
	std::vector<char> buffer;

public:
	ReadBuffer(std::vector<char> buffer);
	void read(char *data, const size_t nbytes) override;
};

}


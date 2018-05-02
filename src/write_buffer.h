#pragma once

#include <type_traits>
#include <string>
#include <vector>
#include "rvk_export.h"
#include "reader_writer.h"

namespace rvk {

class RVK_EXPORT WriteBuffer : public Writer {
	size_t end;
	std::vector<char> buffer;

public:
	WriteBuffer(const size_t initial_capacity = 4 * 1024);
	void write(const char *data, const size_t nbytes) override;
};

}


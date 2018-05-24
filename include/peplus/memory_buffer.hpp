#ifndef PEPLUS_MEMORYBUFFER_HPP_
#define PEPLUS_MEMORYBUFFER_HPP_

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace peplus {

class MemoryBuffer
{
public:
	virtual ~MemoryBuffer() = default;
	virtual std::size_t read(std::size_t offset, std::size_t data_size, void * into_buffer) const = 0;
};

class LocalMemoryBuffer final : public MemoryBuffer
{
public:
	LocalMemoryBuffer(const void * data, std::size_t size);

	virtual std::size_t read(std::size_t offset, std::size_t data_size, void * into_buffer) const override;

private:
	const char * _data;
	std::size_t  _size;
};

inline LocalMemoryBuffer::LocalMemoryBuffer(const void * data, std::size_t size)
	: _data { static_cast<const char *>(data) }, _size { size } {}

inline std::size_t LocalMemoryBuffer::read(std::size_t offset, std::size_t data_size, void * into_buffer) const
{
	if (offset >= _size)
		throw std::out_of_range("Invalid offset given");

	const std::size_t bytes_to_read = std::min(data_size, _size - offset);
	std::copy_n(_data + offset, bytes_to_read, static_cast<char *>(into_buffer));
	return bytes_to_read;
}

}

#endif
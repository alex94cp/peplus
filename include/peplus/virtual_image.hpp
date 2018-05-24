#ifndef PEPLUS_VIRTUALIMAGE_HPP_
#define PEPLUS_VIRTUALIMAGE_HPP_

#include <peplus/image_common.hpp>
#include <peplus/detail/image_base.hpp>

#include <optional>
#include <type_traits>

namespace peplus {

template <unsigned int XX>
using VirtualImage = detail::ImageBase<XX, VirtualOffset>;

using VirtualImage32 = VirtualImage<32>;
using VirtualImage64 = VirtualImage<64>;

template <unsigned int XX, class Offset>
std::optional<VirtualOffset> to_image_offset(const VirtualImage<XX> & image, Offset offset)
{
	if constexpr (std::is_same_v<Offset, VirtualOffset>) {
		return offset;
	} else {
		return image.to_virtual_offset(offset);
	}
}

}

#endif
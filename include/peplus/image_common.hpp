#ifndef PEPLUS_IMAGECOMMON_HPP_
#define PEPLUS_IMAGECOMMON_HPP_

#include <peplus/detail/image_base.hpp>
#include <peplus/detail/image_offset.hpp>
#include <peplus/detail/facades/import_descriptor_facade.hpp>

namespace peplus {

namespace literals = detail::literals;
namespace offset_literals = detail::offset_literals;

using detail::ImageType;
using detail::ImageMachine;

using detail::FileOffset;
using detail::VirtualOffset;

using detail::is_named_import_v;
using detail::is_unnamed_import_v;

}

#endif
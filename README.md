# PEPlus

A cross-platform header-only PE parser library for C++17

## Motivation

From developer tools to antivirus software, a lot of programs need to extract some information from PE files (including executables and dynamic link libraries). Although there are some existing solutions for that (such as [pefile](https://github.com/erocarrera/pefile) for python), there isn't a clear winner when it comes to C++.

PEPlus is an attempt to make PE parsing simple in C++. It takes advantage of new features present in C++17 (such as user-defined literals and range-based for-loops) so that the code you write is both expressive and easy to read.

## Features

* Native
* Easy to use
* Open-source
* Header-only
* Cross-platform
* Actively maintained
* PE/PE+ format support

## Usage

These are all the include files you need to know about:

```cpp
#include <peplus/local_buffer.hpp>  // Local memory buffer classes
#include <peplus/any_buffer.hpp>    // Type-erasing buffer interface

#include <peplus/file_image.hpp>    // PE file image parser class
#include <peplus/virtual_image.hpp> // Loaded PE image parser class
```

Creating a parser instance is simple:

```cpp
using namespace peplus;

const char image_data[] = { /* your image data here */ };

FileImage64<local_buffer> image { image_data };
```

This is how you access the optional header:

```cpp
const auto opt_header = image.optional_header();
// Bonus tip: use opt_header.offset() to get its location
```

Accessing the export directory and looking up an export symbol:

```cpp
if (const auto export_dir = image.export_directory()) {
	if (const auto export_info = export_dir->find("GetProcAddress")) {
		// export_info->address contains GetProcAddress location
	}
}
```

Enumerating your image dependencies:

```cpp
for (const auto import_dtor : image.import_descriptors()) {
	// import_dtor.name_str() returns imported module name
}
```

Enumerating your image resources:

```cpp
if (const auto resource_dir = image.resource_directory()) {
	for (const auto res_entry : resource_dir->entries()) {
		// do something with each resource entry
	}
}
```

Reading data from your image is simple too:

```cpp
using namespace peplus::literals::offset_literals;

char buffer[3];
std::fill_n(buffer, sizeof(buffer), 0);
image.read(0_rva, 2, buffer); // now buffer equals "MZ"
```
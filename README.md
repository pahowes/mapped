# MEMMAP

Memory Mapped Files for C++

# Building

The `mapped::file` class is distributed only as a header. There is nothing to compile in this
repository other than tests which also illustrate how to use `mapped::file`.

## Dependencies

* [CMake](http://www.cmake.org) 2.8.12 or newer
* C compiler. The following have been tested:
  * [llvm](http://llvm.org) 3.4 or newer
  * [gcc](http://gcc.gnu.org) 4.8.3 or newer
  * [Visual Studio](http://www.visualstudio.com)

## Instructions

I highly recommend building outside of the source tree so that build products do not pollute the
repository. The simplest way to accomplish this is to create a sub-directory named "build" as
follows:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

# Examples

Use of this class is intentional minimalistic. Only two lines of code are necessary to map a file
with read-only, non-shared access:

    mapped::file f("path/to/file");
    mapped::buffer_t b = mf.map();

If the file is small enough to transfer into memory, it could be loaded into a string as follows:

    std::string s(reinterpret_cast<const char*>(b.first), b.second);

# TODO List

1.  More tests.
2.  Implement some of the other entities that `mmap` can map.

# Contributing

1.  Fork it
2.  Create a feature branch (`git checkout -b new-feature`)
3.  Commit changes (`git commit -am "Added new feature xyz"`)
4.  Push the branch (`git push origin new-feature`)
5.  Create a new pull request.

# Maintainers

* Paul Howes (http://github.com/PaulHowes/)

# License

`memmap` class copyright 2015 Paul Howes and is licensed under the Apache License.

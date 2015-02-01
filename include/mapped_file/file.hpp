#pragma once

#include <mapped_file/config.hpp>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <memory>
#include <system_error>

namespace mapped {
  /**
   * @brief buffer_t represents a point to a buffer and and the size of the buffer.
   */
  typedef std::pair<const void*, size_t> buffer_t;

  /**
   * @brief Implements a memory mapped file.
   *
   * Memory mapped files are fundamental to the operating system. This is the same technology used
   * to implement swap files, used to increase the amount of virtual memory available to a system.
   *
   * Use of this class is intentional minimalistic. Only three lines of code are necessary to map
   * a file with read-only access into a string:
   *
   *     mapped::file f("path/to/file");
   *     mapped::buffer_t b = mf.map();
   *     std::string s(reinterpret_cast<const char*>(b.first), b.second);
   *
   * Unmapping the file and closing it are automatically handled by file::~file()
   */
  class file {
    public:
      /**
       * @brief Constructs a new mapped::file object and initializes the path.
       * @param[in] path Path of the file to map
       */
      file(std::string const& path) :
        config_(new config(path)), fd_(0), buffer_(nullptr), size_(0) {
      }

      /**
       * @brief Destructor
       */
      ~file() {
        if(buffer_) {
          munmap(buffer_, size_);
        }

        if(fd_) {
          close(fd_);
        }
      }

      /**
       * @brief Maps a file into memory.
       * @return mapped::buffer_t object that describes the memory block.
       */
      buffer_t map() {
        // Determines the size of the file.
        struct stat st;
        if(-1 == stat(config_->path.c_str(), &st)) {
          throw std::system_error(errno, std::system_category());
        }
        size_ = size_t(st.st_size);

        // Converts the open_mode configuration parameter to a value that ::open will recognize,
        // and a protection mode value for ::mmap.
        int mode = 0;
        int prot = 0;
        switch(config_->open_mode) {
          case omode::read_only:
            mode = O_RDONLY;
            prot = PROT_READ;
            break;
          case omode::write_only:
            mode = O_WRONLY;
            prot = PROT_WRITE;
            break;
          case omode::read_write:
            mode = O_RDWR;
            prot = PROT_READ | PROT_WRITE;
            break;
        }

        // Converts the mapping flag.
        int flags = MAP_FILE;
        switch(config_->map_flags) {
          case mflags::privat:
            flags |= MAP_PRIVATE;
            break;
          case mflags::shared:
            flags |= MAP_SHARED;
            break;
        }

        // Opens the file.
        if(-1 == (fd_ = open(config_->path.c_str(), mode))) {
          fd_ = 0;
          throw std::system_error(errno, std::system_category());
        }

        // Maps the file.
        if(MAP_FAILED == (buffer_ = mmap(nullptr, size_, prot, flags, fd_, 0))) {
          buffer_ = nullptr;
          close(fd_);
          fd_ = 0;
          throw std::system_error(errno, std::system_category());
        }

        return buffer_t(buffer_, size_);
      }

    private:

      // Configuration for mapping the file.
      std::unique_ptr<config> config_;

      // File descriptor for the mapped file.
      int fd_;

      // Mapped buffer.
      void* buffer_;

      // Size of mapped buffer.
      size_t size_;
  };
}


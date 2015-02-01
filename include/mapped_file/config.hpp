#pragma once

#include <string>

/**
 * @namespace mapped
 */
namespace mapped {
  /**
   * @brief Mode in which to open a file.
   */
  enum class omode {
    /**
     * @brief Open the file with read-only access.
     */
    read_only,

    /**
     * @brief Open the file with write-only access.
     */
    write_only,

    /**
     * @brief Open the file with read-write access.
     */
    read_write
  };

  /**
   * @brief Flags that determine the type of mapping to use.
   */
  enum class mflags {
    /**
     * @brief The file is locked so that no other process may simultaneously access the file.
     */
    privat,

    /**
     * @brief The file is left available for other processes to access.
     */
    shared
  };

  /**
   * @brief Configuration parameters that describe how to map the file.
   */
  struct config {
    /**
     * @brief Constructs a new mapped::config object, initialized with the path of the file
     *        to map.
     * @param[in] p Path of the file to map.
     *
     * Using this constructor also sets config::open_mode to omode::read_only and config::map_flags
     * to mflags::privat.
     */
    config(std::string const& p) :
      path(p), open_mode(omode::read_only), map_flags(mflags::privat) { }

    /**
     * @brief Path of the file to map.
     */
    std::string path;

    /**
     * @brief One of the mapped::omode values that describes how to open the file.
     */
    omode open_mode;

    /**
     * @brief One of the mapped::mflags value that describes the protection level used by the
     *        mapping.
     */
    mflags map_flags;
  };
}

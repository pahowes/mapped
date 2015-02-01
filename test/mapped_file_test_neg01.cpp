#include <mapped_file.hpp>
#include <iostream>

int main() {
  try {
    mapped::file mf("this_file_does_not_exist");
    mapped::buffer_t b = mf.map();
  }
  catch(std::system_error const& ex) {
    std::cout << "Caught error with code: " << ex.code() << " and description: " << ex.what()
      << std::endl;
    return 0;
  }
  return -1;
}


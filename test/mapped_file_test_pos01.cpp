#include <mapped_file.hpp>
#include <iostream>

int main() {
  mapped::file mf("../README.md");
  mapped::buffer_t b = mf.map();
  std::string s(reinterpret_cast<const char*>(b.first), b.second);
  std::cout << s << std::endl;
  return 0;
}

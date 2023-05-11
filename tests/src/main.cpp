#include <iostream>
#include <restbl/restbl.h>

#include "utils/file_util.h"

int main(int argc, char** argv) {
  std::cout << "[c++] Init Testing" << std::endl;
  const auto data = file::util::ReadAllBytes(argv[1]);
  oepd::restbl::RESTBL restbl{data};

  for (const auto [name, size] : restbl.m_name_table) {
    std::cout << name << std::endl;
  }

  std::cout << "[c++] End Testing" << std::endl;
}
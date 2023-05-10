#include <restbl/restbl.h>
#include <iostream>

#include "utils/file_util.h"

int main(int argc, char** argv) {
  std::cout << "[c++] Init Testing" << std::endl;
  const auto data = file::util::ReadAllBytes(argv[1]);
}
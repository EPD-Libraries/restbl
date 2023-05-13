#include "restbl/restbl.h"

namespace oepd {

namespace restbl {

RESTBL::RESTBL(std::string_view yml_text) {}

RESTBL RESTBL::FromText(std::string_view yml_text) {
  return RESTBL{yml_text};
}

std::string RESTBL::ToText() {}

}  // namespace restbl

}  // namespace oepd
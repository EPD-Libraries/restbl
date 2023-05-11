#include "restbl/restbl.h"

namespace oepd {

namespace restbl {

RESTBL::RESTBL(tcb::span<const u8> data) : m_reader{data, exio::Endianness::Little} {
  const auto header = *m_reader.Read<restbl::Header>();
  if (header.magic != restbl::Magic) {
    throw exio::InvalidDataError("Invalid RESTBL magic");
  }

  for (size_t i = 0; i < header.crc_table_num; i++) {
    const auto entry = *m_reader.Read<restbl::HashEntry>();
    m_crc_table.insert({entry.hash, entry.size});
  }

  for (size_t i = 0; i < header.name_table_num; i++) {
    const auto entry = *m_reader.Read<restbl::NameEntry>();
    m_name_table.insert({entry.name, entry.size});
  }
}

RESTBL RESTBL::FromBinary(tcb::span<const u8> data) {
  return RESTBL{data};
}

std::vector<u8> RESTBL::ToBinary() {
  // serialize map
  return {};
}

}  // namespace restbl

}  // namespace oepd
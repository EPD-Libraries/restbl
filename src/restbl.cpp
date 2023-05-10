#include "restbl/restbl.h"

namespace oepd {

namespace restbl {

RESTBL::RESTBL(tcb::span<const u8> data) : m_reader{data, exio::Endianness::Little} {
  m_header = *m_reader.Read<restbl::Header>();
  if (m_header.magic != restbl::Magic) {
    throw exio::InvalidDataError("Invalid RESTBL magic");
  }
}

RESTBL RESTBL::FromBinary(tcb::span<const u8> data) {
  return RESTBL{data};
}

std::vector<u8> RESTBL::ToBinary() {
  // serialize map
}

u32 RESTBL::GetNumCrcTable() {
  // Return the map count
  return m_header.crc_table_num;
}

u32 RESTBL::GetNumNameTable() {
  // Return the map count
  return m_header.name_table_num;
}

}  // namespace restbl

}  // namespace oepd
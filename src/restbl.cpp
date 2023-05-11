#include "restbl/restbl.h"

namespace oepd {

namespace restbl {

RESTBL::RESTBL(tcb::span<const u8> data) : m_reader{data, exio::Endianness::Little} {
  const auto header = *m_reader.Read<restbl::Header>();
  if (header.magic != restbl::Magic) {
    throw exio::InvalidDataError("Invalid RESTBL magic");
  }

  m_unknown_1 = header.unknown_1;
  m_unknown_2 = header.unknown_2;

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
  Header header{.magic = restbl::Magic,
                .unknown_1 = m_unknown_1,
                .unknown_2 = m_unknown_2,
                .crc_table_num = static_cast<u32>(m_crc_table.size()),
                .name_table_num = static_cast<u32>(m_name_table.size())};

  exio::BinaryWriter writer{exio::Endianness::Little};
  writer.Write(header);

  std::vector<std::reference_wrapper<Table<u32>::value_type>> crc_sorted_table{m_crc_table.begin(), m_crc_table.end()};
  absl::c_sort(crc_sorted_table,
               [this](const Table<u32>::value_type& a, const Table<u32>::value_type& b) { return a.first < b.first; });

  for (const Table<u32>::value_type& entry : crc_sorted_table) {
    writer.Write(restbl::HashEntry{.hash = entry.first, .size = entry.second});
  }

  for (const auto [name, size] : m_name_table) {
    restbl::NameEntry entry{};
    entry.size = size;
    strcpy(entry.name, name.c_str());
    writer.Write(entry);
  }

  return writer.Finalize();
}

}  // namespace restbl

}  // namespace oepd
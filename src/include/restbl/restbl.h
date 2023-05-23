#pragma once

#include <absl/algorithm/container.h>
#include <absl/container/btree_map.h>
#include <exio/binary_reader.h>
#include <exio/binary_writer.h>
#include <exio/error.h>
#include <exio/swap.h>
#include <exio/types.h>
#include <exio/util/magic_utils.h>
#include <nonstd/span.h>

namespace oepd {

namespace restbl {

template <typename T>
using Table = absl::btree_map<T, u32>;

constexpr auto Magic = exio::util::MakeMagic("RESTBL");

struct Header {
  std::array<char, 6> magic;
  u32 version;
  u32 string_block_size;
  u32 crc_table_num;
  u32 name_table_num;
} __attribute__((packed));
static_assert(sizeof(Header) == 0x16);

struct HashEntry {
  u32 hash;
  u32 size;
};
static_assert(sizeof(HashEntry) == 0x08);

struct NameEntry {
  char name[160];
  u32 size;
};
static_assert(sizeof(NameEntry) == 0xA4);

class RESTBL {
public:
  RESTBL(tcb::span<const u8> data);
  RESTBL(std::string_view yml_text);

  static RESTBL FromBinary(tcb::span<const u8> data);
  static RESTBL FromText(std::string_view yml_text);
  std::vector<u8> ToBinary();
  std::string ToText();

  u32 m_version;
  u32 m_string_block_size;
  Table<u32> m_crc_table{};
  Table<std::string> m_name_table{};

private:
  exio::BinaryReader m_reader;
};

}  // namespace restbl

}  // namespace oepd
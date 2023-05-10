#include <absl/container/flat_hash_map.h>
#include <exio/binary_reader.h>
#include <exio/binary_writer.h>
#include <exio/error.h>
#include <exio/swap.h>
#include <exio/types.h>
#include <exio/util/magic_utils.h>
#include <nonstd/span.h>

namespace oepd {

namespace restbl {

constexpr auto Magic = exio::util::MakeMagic("RESTBL");

struct Header {
  std::array<char, 6> magic;
  u32 unknown_1;
  u32 unknown_2;
  u32 crc_table_num;
  u32 name_table_num;
  EXIO_DEFINE_FIELDS(Header, magic, unknown_1, unknown_2, crc_table_num, name_table_num);
};  // sizeof() = 22

struct Crc32Entry {
  u32 hash;
  u32 size;
  EXIO_DEFINE_FIELDS(Crc32Entry, hash, size);
};  // sizeof() = 8

struct NameEntry {
  std::array<char, 128> name;
  u32 size;
  EXIO_DEFINE_FIELDS(NameEntry, name, size);
};  // sizeof() = 132

class RESTBL {
public:
  RESTBL(tcb::span<const u8> data);

  static RESTBL FromBinary(tcb::span<const u8> data);
  std::vector<u8> ToBinary();

  u32 GetNumCrcTable();
  u32 GetNumNameTable();

  u32 GetEntry(u32 hash);
  u32 GetEntry(std::string_view name);

  using Table = absl::flat_hash_map<u32, u32>;
  Table m_files;

private:
  Header m_header;
  mutable exio::BinaryReader m_reader;
};

}  // namespace restbl

}  // namespace oepd
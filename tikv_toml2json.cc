#include "toml.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s toml_file\n", argv[0]);
    return 1;
  }
  auto config = toml::parse_file(argv[1]);
#if 0
  std::cout << toml::json_formatter{ config } << "\n";
#else
  auto rocksdb   = *config ["rocksdb"  ].as_table();
  auto defaultcf = *rocksdb["defaultcf"].as_table();
  auto lockcf    = *rocksdb["lockcf"   ].as_table();
  auto writecf   = *rocksdb["writecf"  ].as_table();
  rocksdb.erase("defaultcf");
  rocksdb.erase("lockcf");
  rocksdb.erase("writecf");
  decltype(config) result;
  result.insert("DBOptions", toml::table{{"dbo", rocksdb}});
  result.insert("CFOptions", toml::table{
    {"default", defaultcf},
    {"lock", lockcf},
    {"write", writecf},
  });
  std::cout << toml::json_formatter{ result } << "\n";
#endif
  return 0;
}

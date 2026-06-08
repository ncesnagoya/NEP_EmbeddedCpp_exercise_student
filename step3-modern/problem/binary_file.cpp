// binary_file クラス（モダンC++版）の実装部
#include "binary_file.h"

bool binary_file::open(const char* path, bool read_only)
{
  const char* mode = read_only ? "rb" : "wb+";
  std::FILE* fp = std::fopen(path, mode);
  if (fp == nullptr)
    return false;
  // 既に開いていれば古い FILE* は reset で自動的に閉じられる。
  // 新しい FILE* の所有権を unique_ptr に渡す。
  stream_.reset(fp);
  return true;
}

std::size_t binary_file::write(const unsigned char* buffer, std::size_t n)
{
  if (!is_open())
    return 0;
  // unique_ptr が持つ生ポインタは get() で取り出す
  return std::fwrite(buffer, sizeof(*buffer), n, stream_.get());
}

std::size_t binary_file::read(unsigned char* buffer, std::size_t n)
{
  if (!is_open())
    return 0;
  return std::fread(buffer, sizeof(*buffer), n, stream_.get());
}

long binary_file::seek(long pos)
{
  if (!is_open())
    return -1;
  return std::fseek(stream_.get(), pos, SEEK_SET);
}

long binary_file::tell()
{
  if (!is_open())
    return -1;
  return std::ftell(stream_.get());
}

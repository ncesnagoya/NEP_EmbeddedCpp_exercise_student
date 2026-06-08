// binary_fileクラスの実装部
#include "binary_file.h"

// ☆ 演習5-1 ☆
// 名前空間を定義する


  // コンストラクタ
  binary_file::binary_file()
    : stream_(nullptr)
  {
  }
  binary_file::binary_file(const char* path, bool read_only)
    : stream_(nullptr)
  {
    if (!open(path, read_only))
      throw std::runtime_error("binary_file:binary_file");
  }

    // デストラクタ
  binary_file::~binary_file() noexcept
  {
    close();
  }

  bool binary_file::is_open() const
  {
    return this->stream_ != nullptr;
  }

  bool binary_file::open(const char* path, bool read_only)
  {
    const char* mode;
    if (read_only)
      mode = "rb";
    else
      mode = "wb+";
    std::FILE* stream = std::fopen(path, mode);
    if (stream)
    {
      close();
      this->stream_ = stream;
      return true;
    }
    return false;
  }

  bool binary_file::close()
  {
    if (!is_open())
      return false;
    bool r = std::fclose(this->stream_) == 0;
    this->stream_ = nullptr;
    return r;
  }

  // ☆ 演習4-3 ☆
  // 派生クラスで上書きする


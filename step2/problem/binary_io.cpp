// binary_ioクラスの実装部
#include "binary_file.h"

// ☆ 演習5-1 ☆
// 名前空間を定義する


  // デフォルトコンストラクタ
  binary_io::binary_io()
  {
  }

  // デストラクタ
  binary_io::~binary_io() noexcept
  {
  }

  // ファイルの現在位置を変更する
  // 成功すれば変更後の位置を、失敗すればEOFを返す
  long binary_io::seek(long pos)
  {
    verify("seek");
    return do_seek(pos);
  }

  // ファイルの現在位置を取得する
  // 失敗すればEOFを返す
  long binary_io::tell()
  {
    verify("tell");
    return do_tell();
  }

  // 内部状態の診断（既定実装）
  // 派生クラス（binary_file）でオーバーライドされるため，通常このbinary_io側は呼ばれない
  // 引数funcには呼び出した関数名が渡される
  void binary_io::verify(const char* func) const
  {
    std::printf("%s", func);
  }

  // ☆ 演習4-3 ☆
  // binary_ioクラスを継承する
  std::size_t binary_file::do_read(void* buffer, std::size_t n)
  {
    return std::fread(buffer, 1, n, this->stream_);
  }

  std::size_t binary_file::do_write(const void* buffer, std::size_t n)
  {
    return std::fwrite(buffer, 1, n, this->stream_);
  }

  long binary_file::do_seek(long pos)
  {
    return std::fseek(this->stream_, pos, SEEK_SET);
  }

  long binary_file::do_tell()
  {
    return std::ftell(this->stream_);
  }

  void binary_file::verify(const char* func) const
  {
    if (this->stream_ == nullptr)
      throw std::logic_error(func);
  }

  // ☆ 演習7 , 演習8 ☆
  // 多重定義する , テンプレート化する
  // 両演習共に下記の関数を使用する
  std::size_t binary_io::read(unsigned char* buffer, std::size_t n)
  {
    if (buffer == nullptr)
      throw std::invalid_argument("binary_io::read");
    verify("read");
    return do_read(buffer, sizeof(*buffer) * n);
  }

  // データの書き込み
  std::size_t binary_io::write(const unsigned char* buffer, std::size_t n)
  {
    if (buffer == nullptr)
      throw std::invalid_argument("binary_io::write");
    verify("write");
    return do_write(buffer, sizeof(*buffer) * n);
  }


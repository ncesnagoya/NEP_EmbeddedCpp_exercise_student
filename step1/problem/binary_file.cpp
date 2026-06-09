// binary_fileクラスの実装部
#include "binary_file.h"

// ☆ 演習1-1☆
// コンストラクタを定義


// ☆演習1-2☆
// デストラクタを定義


// ファイルがオープンされているかどうかを調べる
bool binary_file::is_open() const
{
  return this->stream_ != nullptr;
}


// ファイルをオープンする
// 成功すればtrueを、失敗すればfalseを返す
bool binary_file::open(const char* path, bool read_only)
{
  this->stream_ = nullptr;
  const char* mode;
  if (read_only)
    mode = "rb";
  else
    mode = "wb+";
  FILE* stream = fopen(path, mode);
  if (stream)
  {
    close();
    this->stream_ = stream;
    return true;
  }
  return false;
}

// ファイルをクローズする
// 成功すればtrueを、失敗すればfalseを返す
bool binary_file::close()
{
  if (!is_open())
    return false;
  bool r = fclose(this->stream_) == 0;
  this->stream_ = nullptr;
  return r;
}

// ファイルの現在位置を変更する
// 成功すれば変更後の位置を、失敗すればEOFを返す
long binary_file::seek(long pos)
{
  if (!is_open())
    return EOF;
  return fseek(this->stream_, pos, SEEK_SET);
}

// ファイルの現在位置を取得する
// 失敗すればEOFを返す
long binary_file::tell()
{
  if (!is_open())
    return EOF;
  return ftell(this->stream_);
}

// ☆ 演習2-1 ☆
// データの書き込み関数を定義


// ☆ 演習2-2 ☆
// データの読み込み関数を定義



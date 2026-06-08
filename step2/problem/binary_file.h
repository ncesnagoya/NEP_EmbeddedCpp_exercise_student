// binary_fileクラスの宣言部
#ifndef BINARY_FILE_H_
#define BINARY_FILE_H_

#include "binary_io.h"

// ☆ 演習5-1 ☆
// 名前空間を定義する


  // バイナリファイルの入出力クラス
  // ☆ 演習4-1 ☆
  // binary_ioクラスの性質を受け継ぐ
  class binary_file
  {
  public:
    binary_file();
    binary_file(const char* path, bool read_only);

    virtual ~binary_file() noexcept;

    bool is_open() const;
    bool open(const char* path, bool read_only);
    bool close();
  private:

    // ☆ 演習4-3 ☆
    // 派生クラスで上書きする



  private:
    std::FILE* stream_;
  };

#endif

// binary_ioクラスの宣言部
#ifndef BINARY_IO_H_
#define BINARY_IO_H_

#include <cstdio>
#include <cstdlib>
#include <stdexcept>

// ☆ 演習5-1 ☆
// 名前空間を定義する


  // バイナリ入出力の基底クラス
  class binary_io
  {
  public:
    // デストラクタ
    virtual ~binary_io() noexcept = 0;
    // ☆ 演習7 , 演習8 ☆
    // 多重定義する , テンプレート化する
    // 両演習共に下記の関数を使用する
    std::size_t read(unsigned char* buffer, std::size_t n);
    std::size_t write(const unsigned char* buffer, std::size_t n);

    long seek(long pos);
    long tell();

  protected:
    // コンストラクタ
    binary_io();
  private:
    // コピーを禁止する。
    binary_io(const binary_io&);
    binary_io& operator=(const binary_io&);

    // ☆ 演習4-2 ☆
    // 派生クラスで上書き可能に変更する
    std::size_t do_read(void* buffer, std::size_t n) = 0;
    std::size_t do_write(const void* buffer, std::size_t n) = 0;
    long do_seek(long pos) = 0;
    long do_tell() = 0;
    void verify(const char* func) const;
  };

  // ☆ 演習8 ☆
  // テンプレート化する


#endif

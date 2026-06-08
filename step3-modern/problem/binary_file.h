// binary_file クラス（モダンC++版・問題）
//
// step1 の binary_file を C++11 以降の書き方に置き換える演習です。
// 下記の【演習M-1】【演習M-2】を実装してください。
//
//   演習M-1: コピー禁止を private ではなく = delete で表現する
//   演習M-2: FILE* を std::unique_ptr で管理し，デストラクタを書かずに
//            自動で fclose されるようにする（RAII）
//
// 完成すると，実行結果は step1 と同じ "same" になります（末尾に move の
// 確認行が1行増えます）。詳しくは同じフォルダの 補足教材.md を参照。
#ifndef BINARY_FILE_MODERN_H_
#define BINARY_FILE_MODERN_H_

#include <cstdio>
#include <cstddef>
#include <memory>

class binary_file {
public:
  binary_file() = default;
  binary_file(const char* path, bool read_only) { open(path, read_only); }

  // 【演習M-1】コピーコンストラクタとコピー代入演算子を = delete で禁止する
  //   ヒント: binary_file(const binary_file&) = delete; のように書く


  // ムーブは許可する（所有権の移動）
  binary_file(binary_file&&) = default;
  binary_file& operator=(binary_file&&) = default;

  bool open(const char* path, bool read_only);
  bool is_open() const { return stream_ != nullptr; }
  void close() { stream_.reset(); }

  std::size_t write(const unsigned char* buffer, std::size_t n);
  std::size_t read(unsigned char* buffer, std::size_t n);
  long seek(long pos);
  long tell();

private:
  // 【演習M-2】FILE* を unique_ptr で管理する
  //   (a) std::FILE* を引数に取り，nullでなければ fclose する
  //       カスタム削除子 file_closer を定義する
  //   (b) std::unique_ptr<std::FILE, file_closer> 型のメンバー stream_ を宣言する
  //
  //   ヒント:
  //     struct file_closer {
  //       void operator()(std::FILE* fp) const { if (fp) std::fclose(fp); }
  //     };
  //     std::unique_ptr<std::FILE, file_closer> stream_;

};

#endif

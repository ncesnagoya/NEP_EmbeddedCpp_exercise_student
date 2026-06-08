// モダンC++版 動作確認用 main
#include <cstdio>
#include <cstring>
#include <utility>   // std::move
#include "binary_file.h"

const std::size_t N = 256;

int main()
{
  binary_file bf("test", false);

  // コピーは = delete のためコンパイルエラーになる（演習M-1の確認）。
  // 試しに次の行のコメントを外すとビルドが失敗する：
  // binary_file bf_copy(bf);

  std::printf("is open? %c\n", bf.is_open() ? 'Y' : 'N');

  unsigned char data[N];
  for (std::size_t i = 0; i < N; i++)
    data[i] = static_cast<unsigned char>(i);

  std::size_t n = bf.write(data, N);
  std::printf("written size = %u\n", static_cast<unsigned>(n));

  std::printf("pos = %ld\n", bf.tell());
  bf.seek(0);
  std::printf("pos = %ld\n", bf.tell());

  unsigned char buffer[N];
  n = bf.read(buffer, N);
  std::printf("read size = %u\n", static_cast<unsigned>(n));

  if (std::memcmp(data, buffer, N) == 0)
    std::puts("same");
  else
    std::puts("not same");

  // ムーブは許可されている（所有権の移動）。
  // moved 側がファイルを引き継ぎ，元の bf は空になる。
  binary_file moved = std::move(bf);
  std::printf("after move: moved=%c bf=%c\n",
              moved.is_open() ? 'Y' : 'N',
              bf.is_open() ? 'Y' : 'N');

  // close() も moved のデストラクタも書いていないが，
  // unique_ptr が自動でファイルを閉じる（RAII）。
  return 0;
}

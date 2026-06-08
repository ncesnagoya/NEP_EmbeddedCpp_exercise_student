#include <cstdio>
#include <cstring>
#include "binary_file.h"

const std::size_t N = 256;

// ☆ 演習6 ☆
// 名前空間名を省略できるようにする

int main()
{
  // ☆ 演習5-2 ☆
  // コンストラクタの呼び出しを変更する
  binary_file bf("test", false);

  std::printf("is open? %c\n", bf.is_open() ? 'Y' : 'N');

  unsigned char data[N];
  for (size_t i = 0; i < N; i++)
    data[i] = i;

  std::size_t n;

  n = bf.write(data, N);
  std::printf("written size = %u\n", (unsigned)n);

  std::printf("pos = %ld\n", bf.tell());

  bf.seek(0);
  std::printf("pos = %ld\n", bf.tell());

  unsigned char buffer[N];
  n = bf.read(buffer, N);
  std::printf("read size = %u\n", (unsigned)n);

  if (std::memcmp(data, buffer, N) == 0)
  {
    std::puts("same");
  }
  else
  {
    std::puts("not same");
  }
  return 0;
}

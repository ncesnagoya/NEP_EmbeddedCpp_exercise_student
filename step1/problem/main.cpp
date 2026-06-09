#include <stdio.h>
#include <string.h>
#include "binary_file.h"

#define N 256

int main()
{
  // ☆ 演習1-3 ☆
  // コンストラクタを呼び出し


  printf("is open? %c\n", bf.is_open() ? 'Y' : 'N');

  unsigned char data[N];
  for (size_t i = 0; i < N; i++)
    data[i] = i;

  size_t n;

  // ☆演習2-3☆
  // データの書き込み関数を呼び出し


  printf("written size = %u\n", (unsigned)n);

  printf("pos = %ld\n", bf.tell());

  bf.seek(0);
  printf("pos = %ld\n", bf.tell());

  unsigned char buffer[N];

  // ☆演習2-3☆
  // データの読み込み関数を呼び出し


  printf("read size = %u\n", (unsigned)n);

// 書き込みデータと読み込みデータの比較
  if (memcmp(data, buffer, N) == 0)
  {
    puts("same");
  }
  else
  {
    puts("not same");
  }
  return 0;
}


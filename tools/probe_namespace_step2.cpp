// 演習5（名前空間）の確認用コード
// binary_file が名前空間の中に定義されていれば，名前空間名なしの
// この参照はコンパイルエラーになる（= 演習5が完了している）
#include "binary_file.h"

void probe()
{
  binary_file bf("probe", false); // 演習5完了後はコンパイルエラーになるべき
  (void)bf;
}

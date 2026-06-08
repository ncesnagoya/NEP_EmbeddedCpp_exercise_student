// 演習3（アクセス制御）の確認用コード
// コピーコンストラクタが private になっていれば，このファイルは
// コンパイルエラーになる（= 演習3が完了している）
#include "binary_file.h"

void probe()
{
  binary_file bf("probe", false);
  binary_file bf2(bf); // 演習3完了後はコンパイルエラーになるべき
  (void)bf2;
}

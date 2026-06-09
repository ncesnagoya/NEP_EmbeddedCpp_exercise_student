// binary_fileクラスの宣言部
#ifndef BINARY_FILE_H_
#define BINARY_FILE_H_

#include <stdio.h>

// バイナリファイルを扱うためのサンプルクラス
class binary_file
{
public:
  // ☆ 演習1-1 ☆
  // コンストラクタを定義


  // ☆ 演習1-2 ☆
  // デストラクタを定義


  // ☆ 演習2-1 ☆
  // データの書き込み関数を定義


  // ☆ 演習2-2 ☆
  // データの読み込み関数を定義



  // 演習で使用するメンバー関数
  bool is_open() const;
  bool open(const char* path, bool read_only);
  bool close();
  long seek(long pos);
  long tell();
  
  // 演習で使用するメンバー変数
  FILE* stream_;


  // ☆ 演習3 ☆
  // 指定の関数，変数をアクセス制御



};

#endif

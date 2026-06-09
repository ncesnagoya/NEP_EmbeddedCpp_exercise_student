#!/usr/bin/env bash
# 演習の自動チェックスクリプト
#
# 使い方: bash tools/check.sh step1   または   bash tools/check.sh step2
# （通常は make check-step1 / make check-step2 から呼び出す）
#
# チェック内容:
#   prep:（前提知識のミニ演習）
#     [1] prep/problem がコンパイルできる（C言語）
#     [2] 実行結果が期待出力（予習教材.md）と一致する
#   step1:
#     [1] step1/problem がコンパイルできる（演習1, 2）
#     [2] 実行結果が期待出力（４演習.pdf p.16 演習2,3）と一致する
#     [3] コピーコンストラクタが private になっている（演習3）
#   step2:
#     [1] step2/problem がコンパイルできる（演習4〜8）
#     [2] 実行結果の要点が期待出力（４演習.pdf p.25）と一致する
#         ※演習7で data の型を変更すると written size は変わるため，
#           型に依存しない行のみ確認する
#     [3] binary_file が名前空間の中に定義されている（演習5）
#   step3:（モダンC++オプション演習）
#     [1] step3-modern/problem がコンパイルできる（演習M-1, M-2）
#     [2] 実行結果が期待出力と一致する
#     [3] コピーが = delete で禁止されている（演習M-1）

set -u

STEP="${1:?usage: check.sh prep|step1|step2|step3}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"

PASS=0
FAIL=0
ok()  { echo "  [OK] $1"; PASS=$((PASS+1)); }
ng()  { echo "  [NG] $1"; FAIL=$((FAIL+1)); }

# --- prep（C言語のミニ演習）は専用処理 -----------------------------------
if [ "$STEP" = "prep" ]; then
  SRC="$ROOT/prep/problem"
  BUILD="$ROOT/build/check-prep"
  TOOLS="$ROOT/tools"
  CC="${CC:-cc}"
  CFLAGS="${CFLAGS:--Wall -Wextra}"
  mkdir -p "$BUILD"
  echo "=== prep チェック開始 ==="
  if $CC $CFLAGS -o "$BUILD/byte_store" "$SRC"/*.c 2> "$BUILD/build.log"; then
    ok "コンパイル成功"
    ( cd "$BUILD" && ./byte_store > output.txt 2>&1 )
    if [ $? -ne 0 ]; then
      ng "実行時エラー"
    elif diff -u "$TOOLS/expected_prep.txt" "$BUILD/output.txt" > "$BUILD/output.diff"; then
      ok "出力が期待値と一致（予習教材.md の期待出力）"
    else
      ng "出力が期待値と異なる"
      sed 's/^/    | /' "$BUILD/output.diff"
    fi
  else
    ng "コンパイルエラー（詳細: build/check-prep/build.log）"
    sed 's/^/    | /' "$BUILD/build.log" | head -15
  fi
  echo "=== prep 結果: OK ${PASS} 件 / NG ${FAIL} 件 ==="
  [ $FAIL -eq 0 ]
  exit $?
fi

if [ "$STEP" = "step3" ]; then
  SRC="$ROOT/step3-modern/problem"
else
  SRC="$ROOT/$STEP/problem"
fi
BUILD="$ROOT/build/check-$STEP"
TOOLS="$ROOT/tools"
CXX="${CXX:-g++}"
CXXFLAGS="${CXXFLAGS:--std=c++11 -Wall -Wextra}"

mkdir -p "$BUILD"
echo "=== ${STEP} チェック開始 ==="

# --- [1] ビルド ---------------------------------------------------------
if $CXX $CXXFLAGS -o "$BUILD/app" "$SRC"/*.cpp 2> "$BUILD/build.log"; then
  ok "コンパイル成功"
  BUILD_OK=1
else
  ng "コンパイルエラー（詳細: build/check-$STEP/build.log）"
  sed 's/^/    | /' "$BUILD/build.log" | head -15
  BUILD_OK=0
fi

# --- [2] 実行と出力チェック ---------------------------------------------
if [ "$BUILD_OK" = "1" ]; then
  ( cd "$BUILD" && ./app > output.txt 2>&1 )
  RET=$?
  if [ $RET -ne 0 ]; then
    ng "実行時エラー（終了コード $RET）"
  elif [ "$STEP" = "step1" ]; then
    if diff -u "$TOOLS/expected_step1.txt" "$BUILD/output.txt" > "$BUILD/output.diff"; then
      ok "出力が期待値と一致（４演習.pdf p.16）"
    else
      ng "出力が期待値と異なる"
      sed 's/^/    | /' "$BUILD/output.diff"
    fi
  elif [ "$STEP" = "step3" ]; then
    OUT="$BUILD/output.txt"
    head -1 "$OUT" | grep -q "^is open? Y$" \
      && ok "ファイルを開けている（is open? Y）" \
      || ng "1行目が 'is open? Y' でない"
    grep -q "^same$" "$OUT" \
      && ok "書き込みデータと読み込みデータが一致（same）" \
      || ng "'same' が出力されていない"
    grep -q "^after move: moved=Y bf=N$" "$OUT" \
      && ok "ムーブで所有権が移動している（演習M-2 / RAII）" \
      || ng "move の確認行が期待と異なる"
  else
    # step2: 演習7でdataの型を変えるとwritten size等は変わるため要点のみ確認
    OUT="$BUILD/output.txt"
    head -1 "$OUT" | grep -q "^is open? Y$" \
      && ok "ファイルを開けている（is open? Y）" \
      || ng "1行目が 'is open? Y' でない"
    grep -q "^read size = 256$" "$OUT" \
      && ok "読み込みサイズが正しい（read size = 256）" \
      || ng "'read size = 256' が出力されていない"
    tail -1 "$OUT" | grep -q "^same$" \
      && ok "書き込みデータと読み込みデータが一致（same）" \
      || ng "最終行が 'same' でない"
  fi
fi

# --- [3] コンパイルエラーになるべきコードの確認 -------------------------
# （本体がコンパイルできない間は判定できないためスキップ）
if [ "$BUILD_OK" != "1" ]; then
  echo "  [--] アクセス制御/名前空間/=deleteの確認はコンパイル成功後に行います"
  FAIL=$((FAIL+1))
elif [ "$STEP" = "step1" ]; then
  if $CXX $CXXFLAGS -fsyntax-only -I"$SRC" "$TOOLS/probe_copy_step1.cpp" 2> /dev/null; then
    ng "演習3未完了: コピーコンストラクタが private になっていない"
  else
    ok "アクセス制御が機能している（演習3: コピー禁止）"
  fi
elif [ "$STEP" = "step3" ]; then
  if $CXX $CXXFLAGS -fsyntax-only -I"$SRC" "$TOOLS/probe_copy_step1.cpp" 2> /dev/null; then
    ng "演習M-1未完了: コピーが = delete で禁止されていない"
  else
    ok "コピーが = delete で禁止されている（演習M-1）"
  fi
else
  if $CXX $CXXFLAGS -fsyntax-only -I"$SRC" "$TOOLS/probe_namespace_step2.cpp" 2> /dev/null; then
    ng "演習5未完了: binary_file が名前空間の中に定義されていない"
  else
    ok "名前空間が定義されている（演習5）"
  fi
fi

# --- 結果 ----------------------------------------------------------------
echo "=== ${STEP} 結果: OK ${PASS} 件 / NG ${FAIL} 件 ==="
[ $FAIL -eq 0 ]

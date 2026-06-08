#!/usr/bin/env python3
"""提出用zipを作成するスクリプト（make zip から呼び出される）。

各ステップで受講者が編集するソース（problem 配下の .c/.cpp/.h）を集めて
submission.zip を作成します。ビルド生成物・解答（answer など）・.git は含めません。

使い方:
    make zip
    （または python3 tools/make_zip.py）
"""
import os
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# 受講者が編集するソースの置き場所
DIRS = [
    "prep/problem",
    "step1/problem",
    "step2/problem",
    "step3-modern/problem",
]
EXTS = (".c", ".cpp", ".h")
OUT = os.path.join(ROOT, "submission.zip")


def main():
    if os.path.exists(OUT):
        os.remove(OUT)
    count = 0
    with zipfile.ZipFile(OUT, "w", zipfile.ZIP_DEFLATED) as z:
        for d in DIRS:
            full = os.path.join(ROOT, d)
            if not os.path.isdir(full):
                continue
            for fn in sorted(os.listdir(full)):
                if fn.endswith(EXTS):
                    z.write(os.path.join(full, fn), os.path.join(d, fn))
                    count += 1
    print(f"提出用zipを作成しました: submission.zip （{count} ファイル）")
    print("※ ファイル名に氏名を付けてから Google Drive に提出してください。")
    print("  例: submission.zip → YamadaTaro.zip")


if __name__ == "__main__":
    main()

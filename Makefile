# 組込みC++演習用 Makefile
#
# 使い方:
#   make prep         ... 予習ミニ演習 prep/problem をビルド
#   make run-prep     ... 予習ミニ演習をビルドして実行
#   make check-prep   ... 予習ミニ演習の自動チェック
#   make step1        ... step1/problem をビルド
#   make run-step1    ... step1/problem をビルドして実行
#   make check-step1  ... step1 の自動チェック（演習1〜3の完了確認）
#   make step2 / run-step2 / check-step2 ... step2 も同様
#   make step3 / run-step3 / check-step3 ... モダンC++オプション演習
#   make check        ... step1, step2, step3 をまとめてチェック
#   make zip          ... 提出用zip（submission.zip）を作成
#   make clean        ... ビルド生成物を削除

CXX      ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra
CC       ?= cc
CFLAGS   ?= -Wall -Wextra

.PHONY: all prep run-prep check-prep step1 step2 step3 run-step1 run-step2 run-step3 \
        check check-step1 check-step2 check-step3 zip clean

all: step1 step2 step3

prep:
	@mkdir -p build/prep
	$(CC) $(CFLAGS) -o build/prep/byte_store prep/problem/byte_store.c

run-prep: prep
	cd build/prep && ./byte_store

step1:
	@mkdir -p build/step1
	$(CXX) $(CXXFLAGS) -o build/step1/app step1/problem/*.cpp

step2:
	@mkdir -p build/step2
	$(CXX) $(CXXFLAGS) -o build/step2/app step2/problem/*.cpp

step3:
	@mkdir -p build/step3
	$(CXX) $(CXXFLAGS) -o build/step3/app step3-modern/problem/*.cpp

run-step1: step1
	cd build/step1 && ./app

run-step2: step2
	cd build/step2 && ./app

run-step3: step3
	cd build/step3 && ./app

check: check-prep check-step1 check-step2 check-step3

check-prep:
	@bash tools/check.sh prep

check-step1:
	@bash tools/check.sh step1

check-step2:
	@bash tools/check.sh step2

check-step3:
	@bash tools/check.sh step3

zip:
	@python3 tools/make_zip.py

clean:
	rm -rf build
	rm -f submission.zip

# 演習説明

## Step1

| 講義資料 | 演習 | 結果 |
| ------ | ------ | ----- |
| - | 初期状態 | コンパイルエラー | 
| コンストラクタとデストラクタ（P21～33）| 演習1-1,2,3 | <img width="158" alt="演習１完了" src="https://github.com/enPiT-Emb/QProX-EmbeddedCpp-exercise/assets/17119194/0744574d-a799-469b-94f8-85ad12511f67"> | 
| メンバー変数とメンバー関数（P34～50）| 演習2-1,2,3 | <img width="173" alt="演習２完了" src="https://github.com/enPiT-Emb/QProX-EmbeddedCpp-exercise/assets/17119194/4d4d4237-1323-4ad2-abbe-1ff6c49a61b7"> |
| アクセス制御（P51～53）| 演習3 | 出力は２と同じ。<br>main.cppを修正してアクセス制御が効くことを確認。 |

## step2

step2 は内容が多いため、2つの区切りで進めると理解しやすくなります。
**step2a を終えた時点で一度動作確認**してから step2b に進むことをおすすめします。

**step2a（クラスの継承・名前空間）**

| 講義資料 | 演習 | 結果 |
| ------ | ------ | ----- |
| 継承と仮想関数（P60～73）| 演習4-1～4-3 クラスの継承，仮想関数の定義 | 出力の変化なし |
| 名前の衝突を防ぐ「名前空間」（P75～91）| 演習5-1～5-2 名前空間1，演習6 名前空間2 | 出力の変化なし |

→ ここまでで `make run-step2` が step1 と同じ出力（`same`）になれば step2a 完了です。

**step2b（多重定義・テンプレート）**

| 講義資料 | 演習 | 結果 |
| ------ | ------ | ----- |
| 多重定義とテンプレート（P55～59, 92-103）| 演習7 多重定義 | 通常は変化なし <br> <img width="181" alt="スクリーンショット 2023-09-05 12 58 25" src="https://github.com/enPiT-Emb/QProX-EmbeddedCpp-exercise/assets/17119194/f17129e9-3f14-4e82-9912-33b328761033"> <br> dataの型を修正すると変化あり。例えば，long longだと以下のようになる。<br> <img width="181" alt="スクリーンショット 2023-09-05 12 37 05" src="https://github.com/enPiT-Emb/QProX-EmbeddedCpp-exercise/assets/17119194/f90cf68a-4911-422d-9a71-88e033ee0561">  |
| - | 演習8 テンプレート化 | 演習7と同じ |

- 3)_組込みでのC++.pptxと4)_C++11と14の話題.pptxは演習問題なし

****

# 教材構成

| フォルダ | 内容 | 位置づけ |
| ------ | ------ | ------ |
| `prep/` | 予習教材＋C言語ミニ演習（`予習教材.md`） | **講座前に各自で実施** |
| `step1/` | コンストラクタ・デストラクタ／メンバー／アクセス制御 | 当日（必修） |
| `step2/` | 継承・仮想関数／名前空間／多重定義・テンプレート | 当日＋自習 |
| `step3-modern/` | `= delete`・スマートポインタ（RAII）（`補足教材.md`） | **発展・オプション（自習推奨）** |

# 予習（講座前に実施してください）

`prep/予習教材.md` を開き，C言語の前提知識チェックと，最後のミニ演習（`prep/problem/byte_store.c`）を済ませておいてください。
アンケートで「事前の基礎理解がないと演習時間内では難しい」という声があったため，当日スムーズに進めるための準備です（所要30〜60分）。

```sh
make run-prep     # 予習ミニ演習をビルドして実行（cc が必要）
make check-prep   # 予習ミニ演習の自動チェック（出力が期待値と一致するか）
```

# 演習環境

演習環境の詳細（wandbox / GitHub Codespaces / ローカル環境）と期待出力は「４演習.pdf」の「演習環境」および「プログラムの出力例（ステップ１・ステップ２）」のページを参照してください。
本リポジトリは **GitHub Codespaces** に対応しています（環境構築不要・ブラウザのみで演習可能）。

## GitHub Codespaces での演習手順（受講者向け）

1. 自分のリポジトリ（講師から配布されたリンクで作成したもの）を開く
2. 「Code」→「Codespaces」→「Create codespace on main」をクリック
3. ブラウザ上に VSCode が起動したら，`step1/problem/` 内のファイルを編集する
4. ターミナルで以下を実行する

```sh
make run-prep     # 予習ミニ演習をビルドして実行
make check-prep   # 予習ミニ演習の自動チェック
make run-step1    # step1 をビルドして実行
make check-step1  # step1 の自動チェック（演習1〜3の完了確認）
make run-step2    # step2 をビルドして実行
make check-step2  # step2 の自動チェック（演習4〜8の完了確認）
make run-step3    # step3-modern（オプション）をビルドして実行
make check-step3  # step3 の自動チェック（演習M-1, M-2）
make check        # prep〜step3 をまとめてチェック
```

- 演習は `step1/problem/`，`step2/problem/`，`step3-modern/problem/` の中のファイルを編集して進めてください

### 自分のコードを公開したくない場合

- リポジトリを作成するとき，**Visibility で「Private（非公開）」を選べます**（配布元が公開でも、自分のリポジトリは非公開にできます）。
- 非公開リポジトリでも Codespaces の無料枠（月120コア時間・15GB）は同じように使えます。
- GitHub を使いたくない場合は、**wandbox**（ブラウザのみ）やローカル環境でも演習できます。

## 課題の提出（Google Drive）

提出は **ソースコードの zip を Google Drive にアップロード** する方法で統一します。

```sh
make zip          # submission.zip を作成（各ステップの problem ソースを同梱）
```

1. 演習が一区切りついたら，`make check` で自分の解答を確認する
2. `make zip` を実行すると，リポジトリ直下に `submission.zip` ができる
   （`prep/problem`，`step1/problem`，`step2/problem`，`step3-modern/problem` の `.c/.cpp/.h` を同梱。ビルド生成物・解答は含みません）
3. ファイル名に **氏名** を付けて（例：`YamadaTaro.zip`）、指定の **Google Drive 提出先フォルダ** にアップロードする

> 提出先フォルダ： `<Google Drive の提出先URL>`（講師が案内）

## 自動チェック（自分で確認するためのもの）

- `make check-prep` 〜 `make check-step3` で，コンパイル・実行結果・アクセス制御（演習3）・名前空間（演習5）・`= delete`（演習M-1）を自分で確認できます
- GitHub にプッシュした場合は GitHub Actions 上でも同じチェックが走り，コミット横に ✓ / ✗ が表示されます（任意。提出は上記 Google Drive で行います）
- 初期状態ではチェックは失敗（コンパイルエラー）します。演習を進めると順に OK が増えていきます
- 演習7で `data` の型を変更した場合，`written size` は型に応じて変わります（チェックは型に依存しない項目のみ確認します）

※ Codespaces の無料枠は個人アカウントで月120コア時間（2コアマシンで60時間）です。1日の講座であれば十分です。

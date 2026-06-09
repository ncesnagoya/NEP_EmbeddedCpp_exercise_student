/*
 * 予習ミニ演習（問題）
 *
 * このプログラムは，本演習の binary_file クラスの C 言語版です。
 * 下記の【予習P-1】〜【予習P-5】を埋めて，コンパイル・実行できるように
 * してください。正しく完成すると，次の出力になります。
 *
 *   is open? Y
 *   written size = 256
 *   read size = 256
 *   same
 *
 * ビルド: cc -Wall -Wextra -o byte_store byte_store.c
 * 実行:   ./byte_store
 *
 * ここで思い出した「構造体＋関数」を，step1 では「クラス」へ
 * 書き換えていきます。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 256

/* 【予習P-1: 構造体】
 * FILE ポインタ stream_ を1つ持つ構造体 byte_store を定義してください。
 */
struct byte_store {
    /* ここに FILE* stream_; を書く */
};

/* ファイルを開く。成功で 1，失敗で 0 を返す */
int bs_open(struct byte_store* bs, const char* path, int read_only)
{
    const char* mode = read_only ? "rb" : "wb+";
    bs->stream_ = fopen(path, mode);
    return bs->stream_ != NULL;
}

int bs_is_open(const struct byte_store* bs)
{
    return bs->stream_ != NULL;
}

void bs_close(struct byte_store* bs)
{
    if (bs->stream_) {
        fclose(bs->stream_);
        bs->stream_ = NULL;
    }
}

/* 【予習P-2: ファイルI/O】
 * fwrite を使って n バイト書き込み，書き込めたバイト数を返す関数
 * bs_write を完成させてください。ファイルが開いていなければ 0 を返します。
 */
size_t bs_write(struct byte_store* bs, const unsigned char* buffer, size_t n)
{
    if (!bs_is_open(bs))
        return 0;
    /* return fwrite(... , ... , ... , bs->stream_); を書く */
    return 0;
}

/* 【予習P-3: ファイルI/O】
 * fread を使って n バイト読み込み，読み込めたバイト数を返す関数
 * bs_read を完成させてください。
 */
size_t bs_read(struct byte_store* bs, unsigned char* buffer, size_t n)
{
    if (!bs_is_open(bs))
        return 0;
    /* return fread(... , ... , ... , bs->stream_); を書く */
    return 0;
}

int main(void)
{
    struct byte_store bs;
    bs.stream_ = NULL;

    if (!bs_open(&bs, "prep_test", 0)) {
        printf("open failed\n");
        return 1;
    }
    printf("is open? %c\n", bs_is_open(&bs) ? 'Y' : 'N');

    /* 【予習P-4: 動的メモリ確保】
     * data と buffer に，それぞれ N バイトを malloc で確保してください。
     * （確保できなかった場合の NULL チェックは下に用意してあります）
     */
    unsigned char* data = NULL;   /* malloc(N) に書き換える */
    unsigned char* buffer = NULL; /* malloc(N) に書き換える */
    if (data == NULL || buffer == NULL) {
        printf("malloc failed\n");
        free(data);
        free(buffer);
        bs_close(&bs);
        return 1;
    }

    for (size_t i = 0; i < N; i++)
        data[i] = (unsigned char)i;

    size_t n = bs_write(&bs, data, N);
    printf("written size = %u\n", (unsigned)n);

    fseek(bs.stream_, 0, SEEK_SET);
    n = bs_read(&bs, buffer, N);
    printf("read size = %u\n", (unsigned)n);

    if (memcmp(data, buffer, N) == 0)
        printf("same\n");
    else
        printf("not same\n");

    /* 【予習P-5: 後始末】
     * malloc で確保した data と buffer を free してください。
     */
    /* free(data); free(buffer); を書く */
    bs_close(&bs);
    return 0;
}

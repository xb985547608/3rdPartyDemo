#include <stdio.h>

#define __STDC_CONSTANT_MACROS

#include <libavformat/avformat.h>
#include <libavutil/dict.h>
/**
 * @brief 获取媒体文件的元数据
 */

int mainMetaData()
{
    AVFormatContext *fmt_ctx = NULL;
    AVDictionaryEntry *tag = NULL;
    int ret;

    if ((ret = avformat_open_input(&fmt_ctx, "h:/cloudmusic/mv/456.mp4", NULL, NULL)))
        return ret;

    while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        printf("%s=%s\n", tag->key, tag->value);

    avformat_close_input(&fmt_ctx);
    return 0;
}

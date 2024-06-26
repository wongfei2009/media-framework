
/*
 * Copyright (C) Roman Arutyunyan
 */


#ifndef _NGX_RTMP_CODEC_H_INCLUDED_
#define _NGX_RTMP_CODEC_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include "ngx_rtmp.h"


/* Audio codecs */
enum {
    /* Uncompressed codec id is actually 0,
     * but we use another value for consistency */
    NGX_RTMP_AUDIO_UNCOMPRESSED     = 16,
    NGX_RTMP_AUDIO_ADPCM            = 1,
    NGX_RTMP_AUDIO_MP3              = 2,
    NGX_RTMP_AUDIO_LINEAR_LE        = 3,
    NGX_RTMP_AUDIO_NELLY16          = 4,
    NGX_RTMP_AUDIO_NELLY8           = 5,
    NGX_RTMP_AUDIO_NELLY            = 6,
    NGX_RTMP_AUDIO_G711A            = 7,
    NGX_RTMP_AUDIO_G711U            = 8,
    NGX_RTMP_AUDIO_AAC              = 10,
    NGX_RTMP_AUDIO_SPEEX            = 11,
    NGX_RTMP_AUDIO_MP3_8            = 14,
    NGX_RTMP_AUDIO_DEVSPEC          = 15,
};


#define NGX_RTMP_EXT_HEADER_MASK    (0x80)

/* https://veovera.org/docs/enhanced/enhanced-rtmp-v1 */
enum {
    NGX_RTMP_PKT_TYPE_SEQUENCE_START,
    NGX_RTMP_PKT_TYPE_CODED_FRAMES,
    NGX_RTMP_PKT_TYPE_SEQUENCE_END,
    NGX_RTMP_PKT_TYPE_CODED_FRAMES_X,
};


/* Video codecs */
enum {
    NGX_RTMP_VIDEO_JPEG             = 1,
    NGX_RTMP_VIDEO_SORENSON_H263    = 2,
    NGX_RTMP_VIDEO_SCREEN           = 3,
    NGX_RTMP_VIDEO_ON2_VP6          = 4,
    NGX_RTMP_VIDEO_ON2_VP6_ALPHA    = 5,
    NGX_RTMP_VIDEO_SCREEN2          = 6,
    NGX_RTMP_VIDEO_H264             = 7
};

#define NGX_RTMP_CODEC_FOURCC_HEV1  (0x31766568)
#define NGX_RTMP_CODEC_FOURCC_HVC1  (0x31637668)


u_char *ngx_rtmp_get_audio_codec_name(ngx_uint_t id);
u_char *ngx_rtmp_get_video_codec_name(ngx_uint_t id);


typedef struct {
    ngx_uint_t                  width;
    ngx_uint_t                  height;
    ngx_uint_t                  duration;
    double                      frame_rate;
    ngx_uint_t                  video_data_rate;
    ngx_uint_t                  video_codec_id;
    ngx_uint_t                  video_captions;
    ngx_uint_t                  video_captions_tries;
    ngx_uint_t                  audio_data_rate;
    ngx_uint_t                  audio_codec_id;
    ngx_uint_t                  aac_profile;
    ngx_uint_t                  aac_chan_conf;
    ngx_uint_t                  aac_sbr;
    ngx_uint_t                  aac_ps;
    ngx_uint_t                  avc_profile;
    ngx_uint_t                  avc_compat;
    ngx_uint_t                  avc_level;
    ngx_uint_t                  avc_nal_bytes;
    ngx_uint_t                  avc_ref_frames;
    ngx_uint_t                  sample_rate;    /* 5512, 11025, 22050, 44100 */
    ngx_uint_t                  sample_size;    /* 1=8bit, 2=16bit */
    ngx_uint_t                  audio_channels; /* 1, 2 */
    u_char                      profile[32];
    u_char                      level[32];

    ngx_chain_t                *avc_header;
    ngx_chain_t                *aac_header;

    ngx_chain_t                *meta;
    ngx_uint_t                  meta_version;
} ngx_rtmp_codec_ctx_t;


static ngx_inline ngx_int_t
ngx_rtmp_is_codec_header(ngx_uint_t codec_id, ngx_chain_t *in)
{
    switch (codec_id) {

    case NGX_RTMP_CODEC_FOURCC_HEV1:
    case NGX_RTMP_CODEC_FOURCC_HVC1:
        /* HEVCDecoderConfigurationRecord configurationVersion byte */
        return in->buf->pos < in->buf->last
            && (in->buf->pos[0] & 0xf) == NGX_RTMP_PKT_TYPE_SEQUENCE_START;

    default:
        return in->buf->pos + 1 < in->buf->last && in->buf->pos[1] == 0;
    }
}


extern ngx_module_t  ngx_rtmp_codec_module;


#endif /* _NGX_RTMP_LIVE_H_INCLUDED_ */

#ifndef _NGX_LIVE_MEDIA_INFO_H_INCLUDED_
#define _NGX_LIVE_MEDIA_INFO_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include "ngx_live.h"
#include <ngx_live_kmp.h>
#include "media/media_format.h"
#include "ngx_buf_chain.h"


#define NGX_LIVE_MEDIA_INFO_MAX_EXTRA_DATA_LEN (65536)


typedef struct ngx_live_media_info_node_s  ngx_live_media_info_node_t;

typedef struct {
    ngx_live_media_info_node_t  *cur;
    ngx_queue_t                 *sentinel;
} ngx_live_media_info_iterator_t;

typedef void *(*ngx_live_media_info_alloc_pt)(void *ctx, size_t size);


ngx_int_t ngx_live_media_info_parse(ngx_log_t *log,
    ngx_live_media_info_alloc_pt alloc, void *alloc_ctx, kmp_media_info_t *src,
    ngx_buf_chain_t *extra_data, uint32_t extra_data_size, media_info_t *dest);


ngx_int_t ngx_live_media_info_queue_push(ngx_live_track_t *track,
    kmp_media_info_t *media_info_ptr, ngx_buf_chain_t *extra_data,
    uint32_t extra_data_size);

media_info_t *ngx_live_media_info_queue_get(ngx_live_track_t *track,
    uint32_t segment_index, kmp_media_info_t **kmp_media_info);

media_info_t *ngx_live_media_info_queue_get_last(ngx_live_track_t *track);

void ngx_live_media_info_queue_free(ngx_live_track_t *track,
    uint32_t min_segment_index);


ngx_flag_t ngx_live_media_info_iterator_init(
    ngx_live_media_info_iterator_t *iterator, ngx_live_track_t *track);

uint32_t ngx_live_media_info_iterator_next(
    ngx_live_media_info_iterator_t *iterator, uint32_t segment_index);

#endif /* _NGX_LIVE_MEDIA_INFO_H_INCLUDED_ */
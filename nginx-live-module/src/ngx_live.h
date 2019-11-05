#ifndef _NGX_LIVE_H_INCLUDED_
#define _NGX_LIVE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct ngx_live_channel_s     ngx_live_channel_t;


#include "ngx_live_variables.h"
#include "ngx_live_config.h"
#include "ngx_live_channel.h"
#include "ngx_live_script.h"
#include "ngx_live_core_module.h"


#define NGX_LIVE_VALIDATIONS  NGX_DEBUG
#define NGX_LOG_DEBUG_LIVE    NGX_LOG_DEBUG_CORE


#define ngx_array_entries(x)                    (sizeof(x) / sizeof(x[0]))

#define ngx_round_to_multiple(num, mult)        \
    ((((num) + (mult) / 2) / (mult)) * (mult))


#define ngx_live_get_module_ctx(ch, module)     (ch)->ctx[module.ctx_index]
#define ngx_live_set_ctx(ch, c, module)         ch->ctx[module.ctx_index] = c;

#define ngx_live_track_get_module_ctx(ch, module)  (ch)->ctx[module.ctx_index]

#define ngx_live_rescale_time(time, cur_scale, new_scale)                   \
    ((((uint64_t)(time)) * (new_scale) + (cur_scale) / 2) / (cur_scale))

typedef ngx_int_t (*ngx_live_channel_init_handler_pt)(
    ngx_live_channel_t *channel, size_t *track_ctx_size);
typedef ngx_int_t (*ngx_live_channel_handler_pt)(ngx_live_channel_t *channel);
typedef ngx_int_t (*ngx_live_track_handler_pt)(ngx_live_track_t *track);


typedef struct {
    ngx_conf_t     *cf;
    ngx_command_t  *cmds;
} ngx_live_block_conf_ctx_t;


char *ngx_live_block_command_handler(ngx_conf_t *cf, ngx_command_t *dummy,
    void *conf);


extern ngx_module_t  ngx_live_module;

#endif /* _NGX_LIVE_H_INCLUDED_ */
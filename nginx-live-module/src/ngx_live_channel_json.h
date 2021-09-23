/* auto-generated by generate_json_header.py */

#ifndef ngx_copy_fix
#define ngx_copy_fix(dst, src)   ngx_copy(dst, (src), sizeof(src) - 1)
#endif

/* ngx_live_track_input_skip writer */

static size_t
ngx_live_track_input_skip_get_size(ngx_live_track_input_skip_t *obj)
{
    size_t  result =
        sizeof("{\"duplicate\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"empty\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"no_media_info\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"no_key\":") - 1 + NGX_INT_T_LEN +
        sizeof("}") - 1;

    return result;
}

static u_char *
ngx_live_track_input_skip_write(u_char *p, ngx_live_track_input_skip_t *obj)
{
    p = ngx_copy_fix(p, "{\"duplicate\":");
    p = ngx_sprintf(p, "%ui", (ngx_uint_t) obj->duplicate);
    p = ngx_copy_fix(p, ",\"empty\":");
    p = ngx_sprintf(p, "%ui", (ngx_uint_t) obj->empty);
    p = ngx_copy_fix(p, ",\"no_media_info\":");
    p = ngx_sprintf(p, "%ui", (ngx_uint_t) obj->no_media_info);
    p = ngx_copy_fix(p, ",\"no_key\":");
    p = ngx_sprintf(p, "%ui", (ngx_uint_t) obj->no_key);
    *p++ = '}';

    return p;
}

/* ngx_live_track_input writer */

static size_t
ngx_live_track_input_get_size(ngx_live_track_input_t *obj)
{
    if (!obj->connection) {
        return sizeof("null") - 1;
    }
    size_t  result =
        sizeof("{\"connection\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"remote_addr\":\"") - 1 +
            ngx_json_str_get_size(&obj->remote_addr) +
        sizeof("\",\"uptime\":") - 1 + NGX_TIME_T_LEN +
        sizeof(",\"received_bytes\":") - 1 + NGX_OFF_T_LEN +
        sizeof(",\"skipped_frames\":") - 1 +
            ngx_live_track_input_skip_get_size(&obj->skipped) +
        sizeof("}") - 1;

    return result;
}

static u_char *
ngx_live_track_input_write(u_char *p, ngx_live_track_input_t *obj)
{
    if (!obj->connection) {
        p = ngx_copy_fix(p, "null");
        return p;
    }
    p = ngx_copy_fix(p, "{\"connection\":");
    p = ngx_sprintf(p, "%uA", (ngx_atomic_uint_t) obj->connection);
    p = ngx_copy_fix(p, ",\"remote_addr\":\"");
    p = ngx_json_str_write(p, &obj->remote_addr);
    p = ngx_copy_fix(p, "\",\"uptime\":");
    p = ngx_sprintf(p, "%T", (time_t) (ngx_time() - obj->start_sec));
    p = ngx_copy_fix(p, ",\"received_bytes\":");
    p = ngx_sprintf(p, "%O", (off_t) obj->received_bytes);
    p = ngx_copy_fix(p, ",\"skipped_frames\":");
    p = ngx_live_track_input_skip_write(p, &obj->skipped);
    *p++ = '}';

    return p;
}

/* ngx_live_track_json writer */

static size_t
ngx_live_track_json_get_size(ngx_live_track_t *obj)
{
    size_t  result =
        sizeof("{\"media_type\":\"") - 1 +
            ngx_live_track_media_type_names[obj->media_type].len +
        sizeof("\",\"type\":\"") - 1 +
            ngx_live_track_type_names[obj->type].len +
        sizeof("\",\"uptime\":") - 1 + NGX_TIME_T_LEN +
        sizeof(",\"opaque\":\"") - 1 + obj->opaque.len +
        sizeof("\",\"input\":") - 1 +
            ngx_live_track_input_get_size(&obj->input) +
        sizeof(",\"last_segment_bitrate\":") - 1 + NGX_INT32_LEN +
        sizeof(",") - 1 + ngx_live_core_json_get_size(obj, obj->channel,
            NGX_LIVE_JSON_CTX_TRACK) +
        sizeof("}") - 1;

    return result;
}

static u_char *
ngx_live_track_json_write(u_char *p, ngx_live_track_t *obj)
{
    u_char  *next;
    p = ngx_copy_fix(p, "{\"media_type\":\"");
    p = ngx_sprintf(p, "%V",
        &ngx_live_track_media_type_names[obj->media_type]);
    p = ngx_copy_fix(p, "\",\"type\":\"");
    p = ngx_sprintf(p, "%V", &ngx_live_track_type_names[obj->type]);
    p = ngx_copy_fix(p, "\",\"uptime\":");
    p = ngx_sprintf(p, "%T", (time_t) (ngx_time() - obj->start_sec));
    p = ngx_copy_fix(p, ",\"opaque\":\"");
    p = ngx_block_str_copy(p, &obj->opaque);
    p = ngx_copy_fix(p, "\",\"input\":");
    p = ngx_live_track_input_write(p, &obj->input);
    p = ngx_copy_fix(p, ",\"last_segment_bitrate\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->last_segment_bitrate);
    *p++ = ',';
    next = ngx_live_core_json_write(p, obj, obj->channel,
        NGX_LIVE_JSON_CTX_TRACK);
    p = next == p ? p - 1 : next;
    *p++ = '}';

    return p;
}

/* ngx_live_tracks_json writer */

size_t
ngx_live_tracks_json_get_size(ngx_live_channel_t *obj)
{
    ngx_queue_t  *q;
    size_t  result =
        sizeof("{") - 1 +
        sizeof("}") - 1;

    for (q = ngx_queue_head(&obj->tracks.queue);
        q != ngx_queue_sentinel(&obj->tracks.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_track_t *cur = ngx_queue_data(q, ngx_live_track_t, queue);
        result += cur->sn.str.len + cur->id_escape;
        result += ngx_live_track_json_get_size(cur) + sizeof(",\"\":") - 1;
    }

    return result;
}

u_char *
ngx_live_tracks_json_write(u_char *p, ngx_live_channel_t *obj)
{
    ngx_queue_t  *q;
    *p++ = '{';

    for (q = ngx_queue_head(&obj->tracks.queue);
        q != ngx_queue_sentinel(&obj->tracks.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_track_t *cur = ngx_queue_data(q, ngx_live_track_t, queue);

        if (q != ngx_queue_head(&obj->tracks.queue))
        {
            *p++ = ',';
        }
        *p++ = '"';
        p = ngx_json_str_write_escape(p, &cur->sn.str, cur->id_escape);
        *p++ = '"';
        *p++ = ':';
        p = ngx_live_track_json_write(p, cur);
    }

    *p++ = '}';

    return p;
}

/* ngx_live_track_ids_json writer */

size_t
ngx_live_track_ids_json_get_size(ngx_live_channel_t *obj)
{
    ngx_queue_t  *q;
    size_t  result =
        sizeof("[") - 1 +
        sizeof("]") - 1;

    for (q = ngx_queue_head(&obj->tracks.queue);
        q != ngx_queue_sentinel(&obj->tracks.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_track_t *cur = ngx_queue_data(q, ngx_live_track_t, queue);
        result += cur->sn.str.len + cur->id_escape + sizeof(",\"\"") - 1;
    }

    return result;
}

u_char *
ngx_live_track_ids_json_write(u_char *p, ngx_live_channel_t *obj)
{
    ngx_queue_t  *q;
    *p++ = '[';

    for (q = ngx_queue_head(&obj->tracks.queue);
        q != ngx_queue_sentinel(&obj->tracks.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_track_t *cur = ngx_queue_data(q, ngx_live_track_t, queue);

        if (q != ngx_queue_head(&obj->tracks.queue))
        {
            *p++ = ',';
        }
        *p++ = '"';
        p = ngx_json_str_write_escape(p, &cur->sn.str, cur->id_escape);
        *p++ = '"';
    }

    *p++ = ']';

    return p;
}

/* ngx_live_variant_json writer */

static size_t
ngx_live_variant_json_get_size(ngx_live_variant_t *obj)
{
    size_t  result =
        sizeof("{\"track_ids\":{") - 1 +
            ngx_live_variant_json_track_ids_get_size(obj) +
        sizeof("},\"opaque\":\"") - 1 + obj->opaque.len +
        sizeof("\",\"label\":\"") - 1 +
            ngx_json_str_get_size(&obj->conf.label) +
        sizeof("\",\"lang\":\"") - 1 + ngx_json_str_get_size(&obj->conf.lang) +
        sizeof("\",\"role\":\"") - 1 +
            ngx_live_variant_role_names[obj->conf.role].len +
        sizeof("\",\"is_default\":") - 1 + sizeof("false") - 1 +
        sizeof(",\"active\":") - 1 + sizeof("false") - 1 +
        sizeof("}") - 1;

    return result;
}

static u_char *
ngx_live_variant_json_write(u_char *p, ngx_live_variant_t *obj)
{
    p = ngx_copy_fix(p, "{\"track_ids\":{");
    p = ngx_live_variant_json_track_ids_write(p, obj);
    p = ngx_copy_fix(p, "},\"opaque\":\"");
    p = ngx_block_str_copy(p, &obj->opaque);
    p = ngx_copy_fix(p, "\",\"label\":\"");
    p = ngx_json_str_write(p, &obj->conf.label);
    p = ngx_copy_fix(p, "\",\"lang\":\"");
    p = ngx_json_str_write(p, &obj->conf.lang);
    p = ngx_copy_fix(p, "\",\"role\":\"");
    p = ngx_sprintf(p, "%V", &ngx_live_variant_role_names[obj->conf.role]);
    p = ngx_copy_fix(p, "\",\"is_default\":");
    if (obj->conf.is_default) {
        p = ngx_copy_fix(p, "true");
    } else {
        p = ngx_copy_fix(p, "false");
    }
    p = ngx_copy_fix(p, ",\"active\":");
    if (obj->active) {
        p = ngx_copy_fix(p, "true");
    } else {
        p = ngx_copy_fix(p, "false");
    }
    *p++ = '}';

    return p;
}

/* ngx_live_variants_json writer */

size_t
ngx_live_variants_json_get_size(ngx_live_channel_t *obj)
{
    ngx_queue_t  *q;
    size_t  result =
        sizeof("{") - 1 +
        sizeof("}") - 1;

    for (q = ngx_queue_head(&obj->variants.queue);
        q != ngx_queue_sentinel(&obj->variants.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_variant_t *cur = ngx_queue_data(q, ngx_live_variant_t, queue);
        result += cur->sn.str.len + cur->id_escape;
        result += ngx_live_variant_json_get_size(cur) + sizeof(",\"\":") - 1;
    }

    return result;
}

u_char *
ngx_live_variants_json_write(u_char *p, ngx_live_channel_t *obj)
{
    ngx_queue_t  *q;
    *p++ = '{';

    for (q = ngx_queue_head(&obj->variants.queue);
        q != ngx_queue_sentinel(&obj->variants.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_variant_t *cur = ngx_queue_data(q, ngx_live_variant_t, queue);

        if (q != ngx_queue_head(&obj->variants.queue))
        {
            *p++ = ',';
        }
        *p++ = '"';
        p = ngx_json_str_write_escape(p, &cur->sn.str, cur->id_escape);
        *p++ = '"';
        *p++ = ':';
        p = ngx_live_variant_json_write(p, cur);
    }

    *p++ = '}';

    return p;
}

/* ngx_live_variant_ids_json writer */

size_t
ngx_live_variant_ids_json_get_size(ngx_live_channel_t *obj)
{
    ngx_queue_t  *q;
    size_t  result =
        sizeof("[") - 1 +
        sizeof("]") - 1;

    for (q = ngx_queue_head(&obj->variants.queue);
        q != ngx_queue_sentinel(&obj->variants.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_variant_t *cur = ngx_queue_data(q, ngx_live_variant_t, queue);
        result += cur->sn.str.len + cur->id_escape + sizeof(",\"\"") - 1;
    }

    return result;
}

u_char *
ngx_live_variant_ids_json_write(u_char *p, ngx_live_channel_t *obj)
{
    ngx_queue_t  *q;
    *p++ = '[';

    for (q = ngx_queue_head(&obj->variants.queue);
        q != ngx_queue_sentinel(&obj->variants.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_variant_t *cur = ngx_queue_data(q, ngx_live_variant_t, queue);

        if (q != ngx_queue_head(&obj->variants.queue))
        {
            *p++ = ',';
        }
        *p++ = '"';
        p = ngx_json_str_write_escape(p, &cur->sn.str, cur->id_escape);
        *p++ = '"';
    }

    *p++ = ']';

    return p;
}

/* ngx_live_channel_blocked_json writer */

static size_t
ngx_live_channel_blocked_json_get_size(ngx_live_channel_t *obj)
{
    ngx_live_core_preset_conf_t *cpcf = ngx_live_get_module_preset_conf(obj,
        ngx_live_core_module);
    size_t  result =
        sizeof("{\"blocked\":true,\"preset\":\"") - 1 +
            ngx_json_str_get_size(&cpcf->name) +
        sizeof("\",\"mem_left\":") - 1 + NGX_SIZE_T_LEN +
        sizeof(",\"mem_limit\":") - 1 + NGX_SIZE_T_LEN +
        sizeof(",\"mem_blocks\":") - 1 +
            ngx_block_pool_json_get_size(obj->block_pool) +
        sizeof("}") - 1;

    return result;
}

static u_char *
ngx_live_channel_blocked_json_write(u_char *p, ngx_live_channel_t *obj)
{
    ngx_live_core_preset_conf_t *cpcf = ngx_live_get_module_preset_conf(obj,
        ngx_live_core_module);
    p = ngx_copy_fix(p, "{\"blocked\":true,\"preset\":\"");
    p = ngx_json_str_write(p, &cpcf->name);
    p = ngx_copy_fix(p, "\",\"mem_left\":");
    p = ngx_sprintf(p, "%uz", (size_t) obj->mem_left);
    p = ngx_copy_fix(p, ",\"mem_limit\":");
    p = ngx_sprintf(p, "%uz", (size_t) obj->mem_limit);
    p = ngx_copy_fix(p, ",\"mem_blocks\":");
    p = ngx_block_pool_json_write(p, obj->block_pool);
    *p++ = '}';

    return p;
}

/* ngx_live_channel_json writer */

size_t
ngx_live_channel_json_get_size(ngx_live_channel_t *obj)
{
    ngx_live_core_preset_conf_t *cpcf = ngx_live_get_module_preset_conf(obj,
        ngx_live_core_module);
    if (obj->blocked) {
        return ngx_live_channel_blocked_json_get_size(obj);
    }
    size_t  result =
        sizeof("{\"blocked\":false,\"uid\":\"") - 1 + 16 +
        sizeof("\",\"uptime\":") - 1 + NGX_TIME_T_LEN +
        sizeof(",\"read_time\":") - 1 + NGX_TIME_T_LEN +
        sizeof(",\"preset\":\"") - 1 + ngx_json_str_get_size(&cpcf->name) +
        sizeof("\",\"opaque\":\"") - 1 + obj->opaque.len +
        sizeof("\",\"initial_segment_index\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"mem_left\":") - 1 + NGX_SIZE_T_LEN +
        sizeof(",\"mem_limit\":") - 1 + NGX_SIZE_T_LEN +
        sizeof(",\"mem_watermark_events\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"mem_blocks\":") - 1 +
            ngx_block_pool_json_get_size(obj->block_pool) +
        sizeof(",\"last_segment_created\":") - 1 + NGX_TIME_T_LEN +
        sizeof(",\"last_accessed\":") - 1 + NGX_TIME_T_LEN +
        sizeof(",\"snapshots\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"tracks\":") - 1 + ngx_live_tracks_json_get_size(obj) +
        sizeof(",\"variants\":") - 1 + ngx_live_variants_json_get_size(obj) +
        sizeof(",") - 1 + ngx_live_core_json_get_size(obj, obj,
            NGX_LIVE_JSON_CTX_CHANNEL) +
        sizeof("}") - 1;

    return result;
}

u_char *
ngx_live_channel_json_write(u_char *p, ngx_live_channel_t *obj)
{
    ngx_live_core_preset_conf_t *cpcf = ngx_live_get_module_preset_conf(obj,
        ngx_live_core_module);
    u_char  *next;
    if (obj->blocked) {
        return ngx_live_channel_blocked_json_write(p, obj);
    }
    p = ngx_copy_fix(p, "{\"blocked\":false,\"uid\":\"");
    p = ngx_sprintf(p, "%016uxL", (uint64_t) obj->uid);
    p = ngx_copy_fix(p, "\",\"uptime\":");
    p = ngx_sprintf(p, "%T", (time_t) (ngx_time() - obj->start_sec));
    p = ngx_copy_fix(p, ",\"read_time\":");
    p = ngx_sprintf(p, "%T", (time_t) obj->read_time);
    p = ngx_copy_fix(p, ",\"preset\":\"");
    p = ngx_json_str_write(p, &cpcf->name);
    p = ngx_copy_fix(p, "\",\"opaque\":\"");
    p = ngx_block_str_copy(p, &obj->opaque);
    p = ngx_copy_fix(p, "\",\"initial_segment_index\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->initial_segment_index);
    p = ngx_copy_fix(p, ",\"mem_left\":");
    p = ngx_sprintf(p, "%uz", (size_t) obj->mem_left);
    p = ngx_copy_fix(p, ",\"mem_limit\":");
    p = ngx_sprintf(p, "%uz", (size_t) obj->mem_limit);
    p = ngx_copy_fix(p, ",\"mem_watermark_events\":");
    p = ngx_sprintf(p, "%ui", (ngx_uint_t) obj->mem_watermark_events);
    p = ngx_copy_fix(p, ",\"mem_blocks\":");
    p = ngx_block_pool_json_write(p, obj->block_pool);
    p = ngx_copy_fix(p, ",\"last_segment_created\":");
    p = ngx_sprintf(p, "%T", (time_t) obj->last_segment_created);
    p = ngx_copy_fix(p, ",\"last_accessed\":");
    p = ngx_sprintf(p, "%T", (time_t) obj->last_accessed);
    p = ngx_copy_fix(p, ",\"snapshots\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->snapshots);
    p = ngx_copy_fix(p, ",\"tracks\":");
    p = ngx_live_tracks_json_write(p, obj);
    p = ngx_copy_fix(p, ",\"variants\":");
    p = ngx_live_variants_json_write(p, obj);
    *p++ = ',';
    next = ngx_live_core_json_write(p, obj, obj, NGX_LIVE_JSON_CTX_CHANNEL);
    p = next == p ? p - 1 : next;
    *p++ = '}';

    return p;
}

/* ngx_live_channels_json writer */

size_t
ngx_live_channels_json_get_size(void *obj)
{
    ngx_queue_t  *q;
    size_t  result =
        sizeof("{") - 1 +
        sizeof("}") - 1;

    for (q = ngx_queue_head(&ngx_live_channels.queue);
        q != ngx_queue_sentinel(&ngx_live_channels.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_channel_t *cur = ngx_queue_data(q, ngx_live_channel_t, queue);
        result += cur->sn.str.len + cur->id_escape;
        result += ngx_live_channel_json_get_size(cur) + sizeof(",\"\":") - 1;
    }

    return result;
}

u_char *
ngx_live_channels_json_write(u_char *p, void *obj)
{
    ngx_queue_t  *q;
    *p++ = '{';

    for (q = ngx_queue_head(&ngx_live_channels.queue);
        q != ngx_queue_sentinel(&ngx_live_channels.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_channel_t *cur = ngx_queue_data(q, ngx_live_channel_t, queue);

        if (q != ngx_queue_head(&ngx_live_channels.queue))
        {
            *p++ = ',';
        }
        *p++ = '"';
        p = ngx_json_str_write_escape(p, &cur->sn.str, cur->id_escape);
        *p++ = '"';
        *p++ = ':';
        p = ngx_live_channel_json_write(p, cur);
    }

    *p++ = '}';

    return p;
}

/* ngx_live_channel_ids_json writer */

size_t
ngx_live_channel_ids_json_get_size(void *obj)
{
    ngx_queue_t  *q;
    size_t  result =
        sizeof("[") - 1 +
        sizeof("]") - 1;

    for (q = ngx_queue_head(&ngx_live_channels.queue);
        q != ngx_queue_sentinel(&ngx_live_channels.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_channel_t *cur = ngx_queue_data(q, ngx_live_channel_t, queue);
        result += cur->sn.str.len + cur->id_escape + sizeof(",\"\"") - 1;
    }

    return result;
}

u_char *
ngx_live_channel_ids_json_write(u_char *p, void *obj)
{
    ngx_queue_t  *q;
    *p++ = '[';

    for (q = ngx_queue_head(&ngx_live_channels.queue);
        q != ngx_queue_sentinel(&ngx_live_channels.queue);
        q = ngx_queue_next(q))
    {
        ngx_live_channel_t *cur = ngx_queue_data(q, ngx_live_channel_t, queue);

        if (q != ngx_queue_head(&ngx_live_channels.queue))
        {
            *p++ = ',';
        }
        *p++ = '"';
        p = ngx_json_str_write_escape(p, &cur->sn.str, cur->id_escape);
        *p++ = '"';
    }

    *p++ = ']';

    return p;
}

/* auto-generated by generate_json_builder.py */

#ifndef ngx_copy_fix
#define ngx_copy_fix(dst, src)   ngx_copy(dst, (src), sizeof(src) - 1)
#endif


static size_t
ngx_kmp_push_track_video_json_get_size(ngx_kmp_push_track_t *obj)
{
    size_t  result =
        sizeof("\"media_type\":\"video\",\"bitrate\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"codec_id\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"extra_data\":\"") - 1 + obj->extra_data.len * 2 +
        sizeof("\",\"width\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"height\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"frame_rate\":") - 1 + NGX_INT32_LEN + 3 +
        sizeof(",\"cea_captions\":") - 1 + sizeof("false") - 1;

    return result;
}

static u_char *
ngx_kmp_push_track_video_json_write(u_char *p, ngx_kmp_push_track_t *obj)
{
    uint32_t  n, d;
    p = ngx_copy_fix(p, "\"media_type\":\"video\",\"bitrate\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->media_info.bitrate);
    p = ngx_copy_fix(p, ",\"codec_id\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->media_info.codec_id);
    p = ngx_copy_fix(p, ",\"extra_data\":\"");
    p = ngx_hex_dump(p, obj->extra_data.data, obj->extra_data.len);
    p = ngx_copy_fix(p, "\",\"width\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->media_info.u.video.width);
    p = ngx_copy_fix(p, ",\"height\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->media_info.u.video.height);
    p = ngx_copy_fix(p, ",\"frame_rate\":");
    d = obj->media_info.u.video.frame_rate.denom;
    if (d) {
        n = obj->media_info.u.video.frame_rate.num;
        p = ngx_sprintf(p, "%uD.%02uD", (uint32_t) (n / d), (uint32_t) (n % d
            * 100) / d);

    } else {
        *p++ = '0';
    }
    p = ngx_copy_fix(p, ",\"cea_captions\":");
    if (obj->media_info.u.video.cea_captions) {
        p = ngx_copy_fix(p, "true");
    } else {
        p = ngx_copy_fix(p, "false");
    }

    return p;
}

static size_t
ngx_kmp_push_track_audio_json_get_size(ngx_kmp_push_track_t *obj)
{
    size_t  result =
        sizeof("\"media_type\":\"audio\",\"bitrate\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"codec_id\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"extra_data\":\"") - 1 + obj->extra_data.len * 2 +
        sizeof("\",\"channels\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"channel_layout\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bits_per_sample\":") - 1 + NGX_INT32_LEN +
        sizeof(",\"sample_rate\":") - 1 + NGX_INT32_LEN;

    return result;
}

static u_char *
ngx_kmp_push_track_audio_json_write(u_char *p, ngx_kmp_push_track_t *obj)
{
    p = ngx_copy_fix(p, "\"media_type\":\"audio\",\"bitrate\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->media_info.bitrate);
    p = ngx_copy_fix(p, ",\"codec_id\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->media_info.codec_id);
    p = ngx_copy_fix(p, ",\"extra_data\":\"");
    p = ngx_hex_dump(p, obj->extra_data.data, obj->extra_data.len);
    p = ngx_copy_fix(p, "\",\"channels\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->media_info.u.audio.channels);
    p = ngx_copy_fix(p, ",\"channel_layout\":");
    p = ngx_sprintf(p, "%uL", (uint64_t)
        obj->media_info.u.audio.channel_layout);
    p = ngx_copy_fix(p, ",\"bits_per_sample\":");
    p = ngx_sprintf(p, "%uD", (uint32_t)
        obj->media_info.u.audio.bits_per_sample);
    p = ngx_copy_fix(p, ",\"sample_rate\":");
    p = ngx_sprintf(p, "%uD", (uint32_t) obj->media_info.u.audio.sample_rate);

    return p;
}

static size_t
ngx_kmp_push_track_publish_json_get_size(ngx_kmp_push_track_t *obj)
{
    size_t  result =
        sizeof("\"event_type\":\"publish\",\"input_id\":\"") - 1 +
            obj->input_id.len + ngx_escape_json(NULL, obj->input_id.data,
            obj->input_id.len) +
        sizeof("\"") - 1;

    return result;
}

static u_char *
ngx_kmp_push_track_publish_json_write(u_char *p, ngx_kmp_push_track_t *obj)
{
    p = ngx_copy_fix(p, "\"event_type\":\"publish\",\"input_id\":\"");
    p = (u_char *) ngx_escape_json(p, obj->input_id.data, obj->input_id.len);
    *p++ = '\"';

    return p;
}

static size_t
ngx_kmp_push_track_unpublish_json_get_size(ngx_kmp_push_track_t *obj)
{
    size_t  result =
        sizeof("\"event_type\":\"unpublish\",\"input_id\":\"") - 1 +
            obj->input_id.len + ngx_escape_json(NULL, obj->input_id.data,
            obj->input_id.len) +
        sizeof("\",\"reason\":\"") - 1 + obj->unpublish_reason.len +
            ngx_escape_json(NULL, obj->unpublish_reason.data,
            obj->unpublish_reason.len) +
        sizeof("\"") - 1;

    return result;
}

static u_char *
ngx_kmp_push_track_unpublish_json_write(u_char *p, ngx_kmp_push_track_t *obj)
{
    p = ngx_copy_fix(p, "\"event_type\":\"unpublish\",\"input_id\":\"");
    p = (u_char *) ngx_escape_json(p, obj->input_id.data, obj->input_id.len);
    p = ngx_copy_fix(p, "\",\"reason\":\"");
    p = (u_char *) ngx_escape_json(p, obj->unpublish_reason.data,
        obj->unpublish_reason.len);
    *p++ = '\"';

    return p;
}

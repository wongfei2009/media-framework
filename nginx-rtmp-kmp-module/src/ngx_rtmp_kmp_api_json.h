/* auto-generated by generate_json_header.py */

#ifndef ngx_copy_fix
#define ngx_copy_fix(dst, src)   ngx_copy(dst, (src), sizeof(src) - 1)
#endif

#ifndef ngx_copy_str
#define ngx_copy_str(dst, src)   ngx_copy(dst, (src).data, (src).len)
#endif

/* ngx_rtmp_kmp_api_stream_json writer */

static size_t
ngx_rtmp_kmp_api_stream_json_get_size(ngx_rtmp_kmp_stream_ctx_t *obj,
    ngx_rtmp_live_stream_t *stream)
{
    size_t  result;

    result =
        sizeof("{\"name\":\"") - 1 + obj->publish.name.len +
            ngx_escape_json(NULL, obj->publish.name.data,
            obj->publish.name.len) +
        sizeof("\",\"args\":\"") - 1 + obj->publish.args.len +
            ngx_escape_json(NULL, obj->publish.args.data,
            obj->publish.args.len) +
        sizeof("\",\"type\":\"") - 1 + obj->publish.type.len +
            ngx_escape_json(NULL, obj->publish.type.data,
            obj->publish.type.len) +
        sizeof("\",\"bw_in\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bytes_in\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bw_in_audio\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bytes_in_audio\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bw_in_video\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bytes_in_video\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bw_out\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bytes_out\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"uptime\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"tracks\":{") - 1 +
            ngx_rtmp_kmp_api_tracks_json_get_size(obj->tracks) +
        sizeof("}}") - 1;

    return result;
}


static u_char *
ngx_rtmp_kmp_api_stream_json_write(u_char *p, ngx_rtmp_kmp_stream_ctx_t *obj,
    ngx_rtmp_live_stream_t *stream)
{
    p = ngx_copy_fix(p, "{\"name\":\"");
    p = (u_char *) ngx_escape_json(p, obj->publish.name.data,
        obj->publish.name.len);
    p = ngx_copy_fix(p, "\",\"args\":\"");
    p = (u_char *) ngx_escape_json(p, obj->publish.args.data,
        obj->publish.args.len);
    p = ngx_copy_fix(p, "\",\"type\":\"");
    p = (u_char *) ngx_escape_json(p, obj->publish.type.data,
        obj->publish.type.len);
    p = ngx_copy_fix(p, "\",\"bw_in\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) (stream->bw_in.bandwidth * 8));
    p = ngx_copy_fix(p, ",\"bytes_in\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) stream->bw_in.bytes);
    p = ngx_copy_fix(p, ",\"bw_in_audio\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) (stream->bw_in_audio.bandwidth * 8));
    p = ngx_copy_fix(p, ",\"bytes_in_audio\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) stream->bw_in_audio.bytes);
    p = ngx_copy_fix(p, ",\"bw_in_video\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) (stream->bw_in_video.bandwidth * 8));
    p = ngx_copy_fix(p, ",\"bytes_in_video\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) stream->bw_in_video.bytes);
    p = ngx_copy_fix(p, ",\"bw_out\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) (stream->bw_out.bandwidth * 8));
    p = ngx_copy_fix(p, ",\"bytes_out\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) stream->bw_out.bytes);
    p = ngx_copy_fix(p, ",\"uptime\":");
    p = ngx_sprintf(p, "%i", (ngx_int_t) (ngx_current_msec - stream->epoch) /
        1000);
    p = ngx_copy_fix(p, ",\"tracks\":{");
    p = ngx_rtmp_kmp_api_tracks_json_write(p, obj->tracks);
    p = ngx_copy_fix(p, "}}");

    return p;
}


/* ngx_rtmp_kmp_api_session_json writer */

static size_t
ngx_rtmp_kmp_api_session_json_get_size(ngx_rtmp_kmp_ctx_t *obj)
{
    size_t               result;
    ngx_rtmp_session_t  *s;

    s = obj->s;
    result =
        sizeof("{\"flashver\":\"") - 1 + s->flashver.len +
            ngx_escape_json(NULL, s->flashver.data, s->flashver.len) +
        sizeof("\",\"swf_url\":\"") - 1 + s->swf_url.len +
            ngx_escape_json(NULL, s->swf_url.data, s->swf_url.len) +
        sizeof("\",\"tc_url\":\"") - 1 + s->tc_url.len + ngx_escape_json(NULL,
            s->tc_url.data, s->tc_url.len) +
        sizeof("\",\"page_url\":\"") - 1 + s->page_url.len +
            ngx_escape_json(NULL, s->page_url.data, s->page_url.len) +
        sizeof("\",\"type3_ext_ts\":\"") - 1 +
            ngx_rtmp_type3_ext_ts_str[s->type3_ext_ts].len +
        sizeof("\",\"remote_addr\":\"") - 1 + obj->remote_addr.len +
            ngx_escape_json(NULL, obj->remote_addr.data, obj->remote_addr.len)
            +
        sizeof("\",\"uptime\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"connection\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"streams\":[") - 1 +
            ngx_rtmp_kmp_api_streams_json_get_size(s) +
        sizeof("]}") - 1;

    return result;
}


static u_char *
ngx_rtmp_kmp_api_session_json_write(u_char *p, ngx_rtmp_kmp_ctx_t *obj)
{
    ngx_rtmp_session_t  *s;

    s = obj->s;
    p = ngx_copy_fix(p, "{\"flashver\":\"");
    p = (u_char *) ngx_escape_json(p, s->flashver.data, s->flashver.len);
    p = ngx_copy_fix(p, "\",\"swf_url\":\"");
    p = (u_char *) ngx_escape_json(p, s->swf_url.data, s->swf_url.len);
    p = ngx_copy_fix(p, "\",\"tc_url\":\"");
    p = (u_char *) ngx_escape_json(p, s->tc_url.data, s->tc_url.len);
    p = ngx_copy_fix(p, "\",\"page_url\":\"");
    p = (u_char *) ngx_escape_json(p, s->page_url.data, s->page_url.len);
    p = ngx_copy_fix(p, "\",\"type3_ext_ts\":\"");
    p = ngx_sprintf(p, "%V", &ngx_rtmp_type3_ext_ts_str[s->type3_ext_ts]);
    p = ngx_copy_fix(p, "\",\"remote_addr\":\"");
    p = (u_char *) ngx_escape_json(p, obj->remote_addr.data,
        obj->remote_addr.len);
    p = ngx_copy_fix(p, "\",\"uptime\":");
    p = ngx_sprintf(p, "%i", (ngx_int_t) (ngx_current_msec - s->epoch) / 1000);
    p = ngx_copy_fix(p, ",\"connection\":");
    p = ngx_sprintf(p, "%uA", (ngx_atomic_uint_t) s->connection->number);
    p = ngx_copy_fix(p, ",\"streams\":[");
    p = ngx_rtmp_kmp_api_streams_json_write(p, s);
    p = ngx_copy_fix(p, "]}");

    return p;
}


/* ngx_rtmp_kmp_api_application_json writer */

static size_t
ngx_rtmp_kmp_api_application_json_get_size(ngx_rtmp_core_app_conf_t *obj)
{
    size_t                    result;
    ngx_queue_t              *q;
    ngx_rtmp_kmp_ctx_t       *cur;
    ngx_rtmp_kmp_app_conf_t  *kacf;

    kacf = obj->app_conf[ngx_rtmp_kmp_module.ctx_index];
    if (kacf == NULL) {
        return 0;
    }

    result =
        sizeof("{\"name\":\"") - 1 + obj->name.len + ngx_escape_json(NULL,
            obj->name.data, obj->name.len) +
        sizeof("\",\"sessions\":[") - 1 +
        sizeof("]}") - 1;

    for (q = ngx_queue_head(&kacf->sessions);
        q != ngx_queue_sentinel(&kacf->sessions);
        q = ngx_queue_next(q))
    {
        cur = ngx_queue_data(q, ngx_rtmp_kmp_ctx_t, queue);
        result += ngx_rtmp_kmp_api_session_json_get_size(cur) + sizeof(",") -
            1;
    }

    return result;
}


static u_char *
ngx_rtmp_kmp_api_application_json_write(u_char *p, ngx_rtmp_core_app_conf_t
    *obj)
{
    ngx_queue_t              *q;
    ngx_rtmp_kmp_ctx_t       *cur;
    ngx_rtmp_kmp_app_conf_t  *kacf;

    kacf = obj->app_conf[ngx_rtmp_kmp_module.ctx_index];
    if (kacf == NULL) {
        return p;
    }

    p = ngx_copy_fix(p, "{\"name\":\"");
    p = (u_char *) ngx_escape_json(p, obj->name.data, obj->name.len);
    p = ngx_copy_fix(p, "\",\"sessions\":[");

    for (q = ngx_queue_head(&kacf->sessions);
        q != ngx_queue_sentinel(&kacf->sessions);
        q = ngx_queue_next(q))
    {
        cur = ngx_queue_data(q, ngx_rtmp_kmp_ctx_t, queue);

        if (p[-1] != '[') {
            *p++ = ',';
        }

        p = ngx_rtmp_kmp_api_session_json_write(p, cur);
    }

    p = ngx_copy_fix(p, "]}");

    return p;
}


/* ngx_rtmp_kmp_api_server_json writer */

static size_t
ngx_rtmp_kmp_api_server_json_get_size(ngx_rtmp_core_srv_conf_t *obj)
{
    size_t                     result;
    ngx_uint_t                 n;
    ngx_rtmp_core_app_conf_t  *cur;

    result =
        sizeof("{\"applications\":[") - 1 +
        sizeof("]}") - 1;

    for (n = 0; n < obj->applications.nelts; n++) {
        cur = ((ngx_rtmp_core_app_conf_t **) obj->applications.elts)[n];

        result += ngx_rtmp_kmp_api_application_json_get_size(cur) +
            sizeof(",") - 1;
    }

    return result;
}


static u_char *
ngx_rtmp_kmp_api_server_json_write(u_char *p, ngx_rtmp_core_srv_conf_t *obj)
{
    ngx_uint_t                 n;
    ngx_rtmp_core_app_conf_t  *cur;

    p = ngx_copy_fix(p, "{\"applications\":[");

    for (n = 0; n < obj->applications.nelts; n++) {
        cur = ((ngx_rtmp_core_app_conf_t **) obj->applications.elts)[n];

        if (p[-1] != '[') {
            *p++ = ',';
        }

        p = ngx_rtmp_kmp_api_application_json_write(p, cur);
    }

    p = ngx_copy_fix(p, "]}");

    return p;
}


/* ngx_rtmp_kmp_api_json writer */

static size_t
ngx_rtmp_kmp_api_json_get_size(void *obj)
{
    size_t                      result;
    ngx_uint_t                  n;
    ngx_rtmp_core_srv_conf_t   *cur;
    ngx_rtmp_core_main_conf_t  *cmcf;

    cmcf = ngx_rtmp_core_main_conf;
    result =
        sizeof("{\"version\":\"") - 1 +
            ngx_json_str_get_size(&ngx_rtmp_kmp_version) +
        sizeof("\",\"nginx_version\":\"") - 1 +
            ngx_json_str_get_size(&ngx_rtmp_kmp_nginx_version) +
        sizeof("\",\"rtmp_version\":\"") - 1 +
            ngx_json_str_get_size(&ngx_rtmp_kmp_rtmp_version) +
        sizeof("\",\"compiler\":\"") - 1 +
            ngx_json_str_get_size(&ngx_rtmp_kmp_compiler) +
        sizeof("\",\"built\":\"") - 1 +
            ngx_json_str_get_size(&ngx_rtmp_kmp_built) +
        sizeof("\",\"pid\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"uptime\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"naccepted\":") - 1 + NGX_INT_T_LEN +
        sizeof(",\"bw_in\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bytes_in\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bw_out\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"bytes_out\":") - 1 + NGX_INT64_LEN +
        sizeof(",\"servers\":[") - 1 +
        sizeof("]}") - 1;

    for (n = 0; n < cmcf->servers.nelts; n++) {
        cur = ((ngx_rtmp_core_srv_conf_t **) cmcf->servers.elts)[n];

        result += ngx_rtmp_kmp_api_server_json_get_size(cur) + sizeof(",") - 1;
    }

    return result;
}


static u_char *
ngx_rtmp_kmp_api_json_write(u_char *p, void *obj)
{
    ngx_uint_t                  n;
    ngx_rtmp_core_srv_conf_t   *cur;
    ngx_rtmp_core_main_conf_t  *cmcf;

    cmcf = ngx_rtmp_core_main_conf;
    p = ngx_copy_fix(p, "{\"version\":\"");
    p = ngx_json_str_write(p, &ngx_rtmp_kmp_version);
    p = ngx_copy_fix(p, "\",\"nginx_version\":\"");
    p = ngx_json_str_write(p, &ngx_rtmp_kmp_nginx_version);
    p = ngx_copy_fix(p, "\",\"rtmp_version\":\"");
    p = ngx_json_str_write(p, &ngx_rtmp_kmp_rtmp_version);
    p = ngx_copy_fix(p, "\",\"compiler\":\"");
    p = ngx_json_str_write(p, &ngx_rtmp_kmp_compiler);
    p = ngx_copy_fix(p, "\",\"built\":\"");
    p = ngx_json_str_write(p, &ngx_rtmp_kmp_built);
    p = ngx_copy_fix(p, "\",\"pid\":");
    p = ngx_sprintf(p, "%ui", (ngx_uint_t) ngx_getpid());
    p = ngx_copy_fix(p, ",\"uptime\":");
    p = ngx_sprintf(p, "%i", (ngx_int_t) (ngx_cached_time->sec -
        ngx_rtmp_kmp_start_time));
    p = ngx_copy_fix(p, ",\"naccepted\":");
    p = ngx_sprintf(p, "%ui", (ngx_uint_t) ngx_rtmp_naccepted);
    p = ngx_copy_fix(p, ",\"bw_in\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) (ngx_rtmp_bw_in.bandwidth * 8));
    p = ngx_copy_fix(p, ",\"bytes_in\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) ngx_rtmp_bw_in.bytes);
    p = ngx_copy_fix(p, ",\"bw_out\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) (ngx_rtmp_bw_out.bandwidth * 8));
    p = ngx_copy_fix(p, ",\"bytes_out\":");
    p = ngx_sprintf(p, "%uL", (uint64_t) ngx_rtmp_bw_out.bytes);
    p = ngx_copy_fix(p, ",\"servers\":[");

    for (n = 0; n < cmcf->servers.nelts; n++) {
        cur = ((ngx_rtmp_core_srv_conf_t **) cmcf->servers.elts)[n];

        if (p[-1] != '[') {
            *p++ = ',';
        }

        p = ngx_rtmp_kmp_api_server_json_write(p, cur);
    }

    p = ngx_copy_fix(p, "]}");

    return p;
}

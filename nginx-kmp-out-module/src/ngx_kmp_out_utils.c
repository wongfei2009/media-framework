#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http_call.h>
#include "ngx_kmp_out_utils.h"


#define NGX_HTTP_OK                        200


static ngx_str_t ngx_kmp_out_json_type = ngx_string("application/json");


ngx_chain_t *
ngx_kmp_out_alloc_chain_temp_buf(ngx_pool_t *pool, size_t size)
{
    ngx_buf_t    *b;
    ngx_chain_t  *cl;

    cl = ngx_alloc_chain_link(pool);
    if (cl == NULL) {
        ngx_log_error(NGX_LOG_NOTICE, pool->log, 0,
            "ngx_kmp_out_alloc_chain_temp_buf: ngx_alloc_chain_link failed");
        return NULL;
    }

    b = ngx_create_temp_buf(pool, size);
    if (b == NULL) {
        ngx_log_error(NGX_LOG_NOTICE, pool->log, 0,
            "ngx_kmp_out_alloc_chain_temp_buf: "
            "ngx_create_temp_buf failed, size: %uz", size);
        return NULL;
    }

    cl->buf = b;
    cl->next = NULL;

    return cl;
}


ngx_chain_t *
ngx_kmp_out_alloc_chain_buf(ngx_pool_t *pool, void *pos, void *last)
{
    ngx_buf_t    *b;
    ngx_chain_t  *cl;

    cl = ngx_alloc_chain_link(pool);
    if (cl == NULL) {
        ngx_log_error(NGX_LOG_NOTICE, pool->log, 0,
            "ngx_kmp_out_alloc_chain_buf: ngx_alloc_chain_link failed");
        return NULL;
    }

    b = ngx_calloc_buf(pool);
    if (b == NULL) {
        ngx_log_error(NGX_LOG_NOTICE, pool->log, 0,
            "ngx_kmp_out_alloc_chain_buf: ngx_calloc_buf failed");
        return NULL;
    }

    cl->buf = b;
    b->tag = (ngx_buf_tag_t) &ngx_kmp_out_alloc_chain_buf;
    b->temporary = 1;

    b->start = b->pos = pos;
    b->end = b->last = last;

    return cl;
}


#if 0
ngx_chain_t *
ngx_kmp_out_copy_chain(ngx_pool_t *pool, ngx_chain_t *src)
{
    size_t        size;
    u_char       *p;
    ngx_buf_t    *b;
    ngx_chain_t  *cl;
    ngx_chain_t  *cur;

    size = 0;
    for (cur = src; cur != NULL; cur = cur->next) {
        size += cur->buf->last - cur->buf->start;
    }

    cl = ngx_kmp_out_alloc_chain_temp_buf(pool, size);
    if (cl == NULL) {
        ngx_log_error(NGX_LOG_NOTICE, pool->log, 0,
            "ngx_kmp_out_copy_chain: alloc chain buf failed");
        return NULL;
    }

    b = cl->buf;
    p = b->last;
    for (cur = src; cur != NULL; cur = cur->next) {
        p = ngx_copy(p, cur->buf->start, cur->buf->last - cur->buf->start);
    }

    b->last = p;

    return cl;
}
#endif


ngx_chain_t *
ngx_kmp_out_format_json_http_request(ngx_pool_t *pool, ngx_str_t *host,
    ngx_str_t *uri, ngx_array_t *headers, ngx_chain_t *body)
{
    size_t         alloc_size;
    size_t         content_length;
    u_char        *p;
    ngx_buf_t     *b;
    ngx_str_t      buf;
    ngx_uint_t     i;
    ngx_chain_t   *cl;
    ngx_keyval_t  *kv;

    static const char  rq_tmpl[] = "POST %V HTTP/1.0\r\n"
        "Host: %V\r\n"
        "Content-Type: %V\r\n"
        "Connection: Close\r\n"
        "Content-Length: %uz\r\n";

    content_length = 0;
    for (cl = body; cl; cl = cl->next) {
        buf.data = cl->buf->pos;
        buf.len = cl->buf->last - cl->buf->pos;

        ngx_log_error(NGX_LOG_INFO, pool->log, 0,
            "ngx_kmp_out_format_json_http_request: pool: %p, body: %V",
            pool, &buf);

        content_length += buf.len;
    }

    alloc_size = sizeof(rq_tmpl) + uri->len + host->len +
        ngx_kmp_out_json_type.len + NGX_SIZE_T_LEN + sizeof(CRLF) - 1;

    if (headers) {
        kv = headers->elts;
        for (i = 0; i < headers->nelts; i++) {

            alloc_size += kv[i].key.len + sizeof(": ") - 1 + kv[i].value.len
                + sizeof(CRLF) - 1;
        }
    }

    cl = ngx_kmp_out_alloc_chain_temp_buf(pool, alloc_size);
    if (cl == NULL) {
        ngx_log_error(NGX_LOG_NOTICE, pool->log, 0,
            "ngx_kmp_out_format_json_http_request: "
            "ngx_kmp_out_alloc_chain_temp_buf failed");
        return NULL;
    }

    b = cl->buf;
    p = b->last;

    p = ngx_sprintf(p, rq_tmpl, uri, host, &ngx_kmp_out_json_type,
        content_length);

    if (headers) {
        kv = headers->elts;
        for (i = 0; i < headers->nelts; i++) {

            p = ngx_copy(p, kv[i].key.data, kv[i].key.len);
            *p++ = ':'; *p++ = ' ';

            p = ngx_copy(p, kv[i].value.data, kv[i].value.len);
            *p++ = CR; *p++ = LF;
        }
    }

    *p++ = CR; *p++ = LF;

    if ((size_t) (p - b->pos) > alloc_size) {
        ngx_log_error(NGX_LOG_ALERT, pool->log, 0,
            "ngx_kmp_out_format_json_http_request: "
            "result length %uz greater than allocated length %uz",
            (size_t) (p - b->pos), alloc_size);
        return NULL;
    }

    b->last = p;

    cl->next = body;

    return cl;
}


ngx_int_t
ngx_kmp_out_parse_json_response(ngx_pool_t *pool, ngx_log_t *log,
    ngx_uint_t code, ngx_str_t *content_type, ngx_buf_t *body,
    ngx_json_value_t *json)
{
    ngx_int_t   rc;
    ngx_uint_t  level;
    u_char      error[128];

    if (code != NGX_HTTP_OK) {
        level = (code >= NGX_HTTP_CALL_ERROR_COUNT) ? NGX_LOG_ERR :
            NGX_LOG_NOTICE;

        ngx_log_error(level, log, 0,
            "ngx_kmp_out_parse_json_response: invalid http status %ui", code);
        return NGX_ERROR;
    }

    if (content_type->len < ngx_kmp_out_json_type.len
        || ngx_strncasecmp(content_type->data,
            ngx_kmp_out_json_type.data,
            ngx_kmp_out_json_type.len)
        != 0)
    {
        ngx_log_error(NGX_LOG_ERR, log, 0,
            "ngx_kmp_out_parse_json_response: invalid content type %V",
            content_type);
        return NGX_ERROR;
    }

    if (body->last >= body->end) {
        ngx_log_error(NGX_LOG_ERR, log, 0,
            "ngx_kmp_out_parse_json_response: no room for null terminator");
        return NGX_ERROR;
    }

    *body->last = '\0';

    ngx_log_error(NGX_LOG_INFO, log, 0,
        "ngx_kmp_out_parse_json_response: pool: %p, body: %s",
        pool, body->pos);

    rc = ngx_json_parse(pool, body->pos, json, error, sizeof(error));
    if (rc != NGX_JSON_OK) {
        ngx_log_error(NGX_LOG_ERR, log, 0,
            "ngx_kmp_out_parse_json_response: ngx_json_parse failed %i, %s",
            rc, error);
        return NGX_ERROR;
    }

    if (json->type != NGX_JSON_OBJECT) {
        ngx_log_error(NGX_LOG_ERR, log, 0,
            "ngx_kmp_out_parse_json_response: "
            "invalid type %d, expected object",
            json->type);
        return NGX_ERROR;
    }

    return NGX_OK;
}


void
ngx_kmp_out_float_to_rational(double f, int64_t md, int64_t *num,
    int64_t *denom)
{
    /*  a: continued fraction coefficients. */
    int      i, neg = 0;
    int64_t  a, h[3] = { 0, 1, 0 }, k[3] = { 1, 0, 0 };
    int64_t  x, d, n = 1;

    if (md <= 1) {
        *denom = 1;
        *num = (int64_t) f;
        return;
    }

    if (f < 0) {
        neg = 1;
        f = -f;
    }

    while (f != (int64_t) f) {
        n <<= 1;
        if (!n) {
            *num = 0;
            *denom = 1;
            return;
        }

        f *= 2;
    }

    d = f;

    /* continued fraction and check denominator each step */
    for (i = 0; i < 64; i++) {
        a = d / n;
        if (i && !a) {
            break;
        }

        x = a;
        if (k[1] * a + k[0] >= md) {
            x = (md - k[0]) / k[1];
            if (x * 2 >= a || k[1] >= md) {
                i = 65;

            } else {
                break;
            }
        }

        h[2] = x * h[1] + h[0]; h[0] = h[1]; h[1] = h[2];
        k[2] = x * k[1] + k[0]; k[0] = k[1]; k[1] = k[2];

        x = d; d = n; n = x % n;
        if (!n) {
            break;
        }
    }

    *denom = k[1];
    *num = neg ? -h[1] : h[1];
}


static ngx_url_t *
ngx_kmp_out_parse_url(ngx_conf_t *cf, ngx_str_t *url)
{
    size_t      add;
    ngx_url_t  *u;

    u = ngx_pcalloc(cf->pool, sizeof(ngx_url_t));
    if (u == NULL) {
        return NULL;
    }

    add = 0;
    if (ngx_strncasecmp(url->data, (u_char *) "http://", 7) == 0) {
        add = 7;
    }

    u->url.len = url->len - add;
    u->url.data = url->data + add;
    u->default_port = 80;
    u->uri_part = 1;

    if (ngx_parse_url(cf->pool, u) != NGX_OK) {
        if (u->err) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                "%s in url \"%V\"", u->err, &u->url);
        }
        return NULL;
    }

    return u;
}


char *
ngx_kmp_out_url_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char  *p = conf;

    ngx_str_t   *value;
    ngx_url_t  **u;

    u = (ngx_url_t **) (p + cmd->offset);
    if (*u != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    value = cf->args->elts;

    *u = ngx_kmp_out_parse_url(cf, &value[1]);
    if (*u == NULL) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}
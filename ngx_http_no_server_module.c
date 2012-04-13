
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static ngx_http_output_header_filter_pt ngx_http_next_header_filter;

static ngx_int_t ngx_http_no_server_init(ngx_conf_t *cf);
static ngx_int_t ngx_http_no_server_header_filter(ngx_http_request_t *r);


static ngx_http_module_t  ngx_http_no_server_module_ctx = {
  NULL,                    /* preconfiguration */
  ngx_http_no_server_init, /* postconfiguration */

  NULL,                    /* create main configuration */
  NULL,                    /* init main configuration */

  NULL,                    /* create server configuration */
  NULL,                    /* merge server configuration */

  NULL,                    /* create location configuration */
  NULL                     /* merge location configuration */
};

ngx_module_t  ngx_http_no_server_module = {
  NGX_MODULE_V1,
  &ngx_http_no_server_module_ctx,  /* module context */
  NULL,                            /* module directives */
  NGX_HTTP_MODULE,                 /* module type */
  NULL,                            /* init master */
  NULL,                            /* init module */
  NULL,                            /* init process */
  NULL,                            /* init thread */
  NULL,                            /* exit thread */
  NULL,                            /* exit process */
  NULL,                            /* exit master */
  NGX_MODULE_V1_PADDING
};


static ngx_int_t ngx_http_no_server_init(ngx_conf_t *cf) {
  ngx_http_next_header_filter = ngx_http_top_header_filter;
  ngx_http_top_header_filter = ngx_http_no_server_header_filter;

  return NGX_OK;
}

static ngx_int_t ngx_http_no_server_header_filter(ngx_http_request_t *r) {
  ngx_table_elt_t* h = ngx_list_push(&r->headers_out.headers);

  if (h == NULL) {
    return NGX_HTTP_INTERNAL_SERVER_ERROR;
  }

  h->hash        = 0;
  h->key.len     = sizeof("Server") - 1;
  h->key.data    = (u_char*)"Server";
  h->value.len   = 0;
  h->value.data  = NULL;
  h->lowcase_key = (u_char*)"server";

  r->headers_out.server = h;

  return ngx_http_next_header_filter(r);
}


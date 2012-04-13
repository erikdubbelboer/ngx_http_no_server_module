
Simple module to strip the Server header from nginx responses.

Useful to save a bit of bandwidth when you run a server that serves hundreds of small requests per second.

To install add `--add-module=/path/to/ngx_http_no_server_module` to `./configure` when building nginx.

The module has no configuration and is always on.


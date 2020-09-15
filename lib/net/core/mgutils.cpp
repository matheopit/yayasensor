#include "mgutils.h"
#include <cstring>

 void mg_alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
  buf->base = (char*)malloc(suggested_size);
  buf->len = suggested_size;
  memset(buf->base,0,suggested_size);
}




#ifndef MG_UTILS_H
#define MG_UTILS_H

#include <exception>
#include  <string>
#include <uv.h>

#define DEFAULT_PORT 10200
#define DEFAULT_ADDR "0.0.0.0"
#define DEFAULT_SRV_ADDR "127.0.0.1"
#define logprint printf

struct MGErrorBase : public std::exception
{
    MGErrorBase(const char* message)
        :std::exception()
      ,m_message(message)
    {

    }
    const char * what () const throw ()
    {
        return m_message.c_str();
    }
private:
    std::string m_message;
};



void mg_alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);



#endif /*MG_UTILS_H */

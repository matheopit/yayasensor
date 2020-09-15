#ifndef MG_REMOTE_BUFFER_H_
#define MG_REMOTE_BUFFER_H_

/*
 * message = header(message len) + message
 * header = uint32_t
*/

#include <vector> 
#ifdef WIN32
#include "winstdint.h"
#else
#include <stdint.h>
#endif


#define MAXDATA 1024*1024*3
#define BUFFER_VERSION 0xFF

typedef uint32_t MGPacketHeader_t;

class IMGBufferClient;

enum TDecodeStep
{
    WAIT_HEADER
   , WAIT_BUFFER   
};

struct MGCurrentData
{
    MGCurrentData()
        :m_msglen(0)
        ,m_step(WAIT_HEADER) {}
        size_t m_msglen;
        TDecodeStep m_step;
        std::vector<char>m_WorkerBuffer;
};

class MGRemoteBuffer
{
private:
    MGRemoteBuffer(const MGRemoteBuffer&);
    MGRemoteBuffer& operator=(const MGRemoteBuffer&);
public:
    MGRemoteBuffer(IMGBufferClient*);
    virtual ~MGRemoteBuffer();
    bool decodeChunckData(const char* pzData,size_t nLen); 
    static bool createChunckData(const char* pzInputData, const size_t nInputLen, char** pzOutputData,uint32_t &nOutputLen);
protected:
    virtual void onTriggerCompleteData(const char* pzData,size_t nLen);
private:
    IMGBufferClient* m_bufferClient;
    MGCurrentData m_waitingData;
};

#endif /*MG_REMOTE_BUFFER_H_*/

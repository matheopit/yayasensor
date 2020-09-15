#include  "mgremotebuffer.h"
#include <cstring>
#include <memory>
#include "mgbufferclient.h"




MGRemoteBuffer::MGRemoteBuffer(IMGBufferClient* client)
    :m_bufferClient(client)
{

}


MGRemoteBuffer::~MGRemoteBuffer()
{

}



bool MGRemoteBuffer::decodeChunckData(const char* pzData,size_t nLen)
{
    std::copy(pzData,pzData + nLen,std::back_inserter(m_waitingData.m_WorkerBuffer));
    std::vector<char> & v = m_waitingData.m_WorkerBuffer;
    bool result = true;
    std::vector<char>::iterator itstart;
    std::vector<char>::iterator itend;
    while (true)
    {
       itstart = v.begin();
       itend = itstart;
       switch(m_waitingData.m_step)
       {
       case WAIT_HEADER:
       {
           if  (v.size() < sizeof (MGPacketHeader_t))
           {
              // printf("v[%d]\n",v.size());
               return true;
            }
           uint32_t len = 0;
           memcpy(&len, &v[0],sizeof(MGPacketHeader_t));
           if (len > MAXDATA)
           {
               v.clear();
               return false;
           }
           m_waitingData.m_msglen = len;
           itend += sizeof (MGPacketHeader_t);
           v.erase(itstart,itend);
           m_waitingData.m_step = WAIT_BUFFER;
       }
           break;
       case WAIT_BUFFER:
           //le message est complet
           if (m_waitingData.m_msglen <= v.size())
           {
               itend += m_waitingData.m_msglen;
               result = m_bufferClient->onTriggerCompleteData(&v[0], m_waitingData.m_msglen);
               v.erase(itstart,itend);
               m_waitingData.m_msglen = 0;
               m_waitingData.m_step = WAIT_HEADER;
           }
           else // Ok waiting for new data.
               return true;
           break;
       default:
           return true;
       }
   }
   return result;
}


bool MGRemoteBuffer::createChunckData(const char* pzInputData, const size_t nInputLen, char** pzOutputData,uint32_t &nOutputLen)
{
    if (nInputLen > 0 && pzInputData)
    {
        nOutputLen = nInputLen + sizeof(MGPacketHeader_t);
        *pzOutputData = (char *)malloc(nOutputLen);
        memset(*pzOutputData,0,nOutputLen);
        char* tmp = *pzOutputData;
        MGPacketHeader_t heads = nInputLen;
        memcpy(tmp,&heads,sizeof(MGPacketHeader_t));
        tmp += sizeof(MGPacketHeader_t);
        memcpy(tmp,pzInputData,nInputLen);
    }
    return false;
}


void MGRemoteBuffer::onTriggerCompleteData(const char* pzData,size_t nLen)
{
    m_bufferClient->onTriggerCompleteData(pzData,nLen);
}





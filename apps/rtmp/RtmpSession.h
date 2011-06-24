#ifndef _RtmpSession_h_
#define _RtmpSession_h_

#include "Rtmp.h"
#include "AmSession.h"

#include "librtmp/rtmp.h"

class RtmpAudio;
class RtmpConnection;

class RtmpSession 
  : public AmSession
{
  RtmpAudio*      rtmp_audio;

  RtmpConnection* rtmp_connection;
  AmMutex         m_rtmp_conn;

public:
  RtmpSession(RtmpConnection* c, unsigned int stream_id);
  ~RtmpSession();

  // @see AmSession
  void onSessionStart();
  void onBeforeDestroy();
  void onAudioEvent(AmAudioEvent* audio_ev);

  // forwards the packet the RtmpAudio
  void bufferPacket(const RTMPPacket& p);

  // sets the connection pointer
  void setConnectionPtr(RtmpConnection* c);
};

#endif
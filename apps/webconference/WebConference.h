/*
 * $Id: PinAuthConference.h 288 2007-03-28 16:32:02Z sayer $
 *
 * Copyright (C) 2007 iptego GmbH
 *
 * This file is part of sems, a free SIP media server.
 *
 * sems is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * For a license to use the sems software under conditions
 * other than those described here, or to purchase support for this
 * software, please contact iptel.org by e-mail at the following addresses:
 *    info@iptel.org
 *
 * sems is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef _WEBCONFERENCE_H_
#define _WEBCONFERENCE_H_


#include "RoomInfo.h"
#include "CallStats.h"
#include "AmApi.h"
#include "AmPromptCollection.h"
#include "AmRtpAudio.h" // playoutType

#include <map>
#include <string>
using std::map;
using std::string;

#include <fstream>
using std::ofstream;

#include <sys/types.h>
#include <regex.h>
#include <time.h>

class ConferenceStatus;
class ConferenceStatusContainer;

// configuration parameter names
#define ENTERING_CONFERENCE "entering_conference"
#define FIRST_PARTICIPANT   "first_participant"
#define JOIN_SOUND          "join_sound"
#define DROP_SOUND          "drop_sound"
#define ENTER_PIN           "enter_pin"
#define WRONG_PIN           "wrong_pin"

// default path for files
#define WEBCONF_ANNOUNCE_PATH "../apps/examples/webconference/"

class WebConferenceEvent : public AmEvent 
{
public:
  WebConferenceEvent(int id) : AmEvent(id) { }
  enum { Kick,
	 Mute,
	 Unmute 
  };
};

class WebConferenceFactory 
  : public AmSessionFactory,
    public AmDynInvokeFactory,
    public AmDynInvoke
{
  AmPromptCollection prompts;

  map<string, ConferenceRoom> rooms;
  AmMutex rooms_mut;

  // for DI 
  static WebConferenceFactory* _instance;
  bool configured;

  string getServerInfoString();
  string getRandomPin();
  /** returns NULL if adminpin wrong */
  ConferenceRoom* getRoom(const string& room, 
			  const string& adminpin);
  void postConfEvent(const AmArg& args, AmArg& ret,
		     int id, int mute);

  regex_t direct_room_re;
  bool use_direct_room;
  unsigned int direct_room_strip;

  ofstream feedback_file;
  void saveFeedback(const string& s);

  WCCCallStats* stats;

  string getAccessUri(const string& room);
  // for access of dialog to its url
  string getAdminpin(const string& room);

public:
  static string DigitsDir;
  static PlayoutType m_PlayoutType;
  static string urlbase;
  static string MasterPassword;

  WebConferenceFactory(const string& _app_name);
  AmSession* onInvite(const AmSipRequest&);
  AmSession* onInvite(const AmSipRequest& req,
		      AmArg& session_params);
  int onLoad();

  void newParticipant(const string& conf_id, 
		      const string& localtag, 
		      const string& number);
  void updateStatus(const string& conf_id, 
		    const string& localtag, 
		    ConferenceRoomParticipant::ParticipantStatus status,
		    const string& reason);
  
  void callStats(bool success, unsigned int connect_t);
  
  // DI API
  WebConferenceFactory* getInstance(){
    return _instance;
  }
  void invoke(const string& method, const AmArg& args, AmArg& ret);

  // DI functions
  void roomCreate(const AmArg& args, AmArg& ret);
  void roomInfo(const AmArg& args, AmArg& ret);
  void dialout(const AmArg& args, AmArg& ret);
  void kickout(const AmArg& args, AmArg& ret);
  void mute(const AmArg& args, AmArg& ret);
  void unmute(const AmArg& args, AmArg& ret);
  void serverInfo(const AmArg& args, AmArg& ret);
  void vqRoomFeedback(const AmArg& args, AmArg& ret);
  void vqCallFeedback(const AmArg& args, AmArg& ret);
  void vqConferenceFeedback(const AmArg& args, AmArg& ret);
  void resetFeedback(const AmArg& args, AmArg& ret);
  void flushFeedback(const AmArg& args, AmArg& ret);
  void getRoomPassword(const AmArg& args, AmArg& ret);
  void listRooms(const AmArg& args, AmArg& ret);
};


#endif
// Local Variables:
// mode:C++
// End:


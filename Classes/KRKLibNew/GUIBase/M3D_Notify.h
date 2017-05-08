//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Notify.h
//																	
// Description: basic class for notification between threads
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//

#ifndef M3D_NOTIFY
#define M3D_NOTIFY

#include <vector>
#include "CEGUI/CEGUIEventArgs.h"
#include "CEGUI/CEGUIEventSet.h"

namespace CEGUI
{

#define M3D_NOTIFY_TIMEOUT		5000

//! player Notify result data
typedef struct {
	int notify;
	int para1;
	int para2;
	std::string strparm1;
	std::string strparm2;
}M3D_Notify_t;


/*!
\brief
	ActionEventArgs class that is primarily used action start or end
*/
class NotifyEventArgs : public EventArgs
{
public:
	NotifyEventArgs(int para1, int para2) : 
			EventArgs(),
			d_para1(para1),
			d_para2(para2)
    {

	}

	NotifyEventArgs(int para1, int para2, std::string a, std::string b) : 
			EventArgs(),
			d_para1(para1),
			d_para2(para2)
    {
		d_strparm1 = a;
		d_strparm2 = b;
	}

	int d_para1;
	int	d_para2;
	std::string d_strparm1;
	std::string	d_strparm2;
};

class M3D_Notify
{
public:

	
	M3D_Notify(void);
		
	virtual ~M3D_Notify(void);

	/*!
	\brief
			multi-thread lock
	*/
	void lock(void);

	/*!
	\brief
			multi-thread unlock
	*/
	void unlock(void);
	
	/*!
	\brief
			push first notify to the end of list

	\param notify
			input notify
			
	\return
			nothing
	*/
	void pushNotify(M3D_Notify_t notify);
	
	/*!
	\brief
			push first notify to the end of list

	\param notifyId
			input notify id
	\param para1
			input parameter 1
	\param para2
			input parameter 2
			
	\return
			nothing
	*/
	void pushNotify(int notifyId, int para1, int para2);
	void pushNotify(int notifyId, int para1, int para2,std::string a,std::string b);
	
	/*!
	\brief
			pop first notify in list

	\param notify
			output notify
			
	\return
			true if found it
	*/
	bool popNotify(M3D_Notify_t& notify);
	
	/*!
	\brief
			query a special notify in list, find and pop it

	\param notify
			output notify
	\param notifyType
			input notifyType
			
	\return
			true if found it
	*/
	bool queryNotify(M3D_Notify_t& notify, int notifyType);
	
	/*!
	\brief
			wait a special notify in list, find and pop it
			call queryNotify in it

	\param notify
			output notify
	\param notifyType
			input notifyType
			
	\return
			true if found it
	*/
	bool waitNotify(M3D_Notify_t& notify, int notifyType);
	
	/*!
	\brief
			clean all notify in list
	*/
	void cleanNotify(void);

	/*!
	\brief
			set notify handle function
	*/
	virtual void setNotifyHandle(int notifyId, Event::Subscriber subscriber);
	
	/*!
	\brief
			del notify handle function
	*/
	virtual void delNotifyHandle(int notifyId);

	/*!
	\brief
			subscribe notify handle function
	*/
	void subscribeEvent(const String& name, Event::Subscriber subscriber)  {d_event.removeEvent(name); d_event.subscribeEvent(name, subscriber);}
	
	/*!
	\brief
			remove all subscribed events
	*/
	void removeAllEvents(void)  {d_event.removeAllEvents();}
	
	/*!
	\brief
			remove a special subscribed event
	*/
	void removeEvent(const String& name)  {d_event.removeEvent(name);}

	/*!
	\brief
			fire notify event
	*/
	void fireEvent(const String& name, NotifyEventArgs& args, const String& eventNamespace) {d_event.fireEvent(name, args, eventNamespace);}

	/*!
	\brief
			set synonize mode 
	*/
	void setSyncMode(bool setting) {syncNotify = setting;}

	bool isSyncMode(void) {return syncNotify;}

private:
	
	typedef std::vector<M3D_Notify_t> notifyList_t;
	notifyList_t d_notifyList;

	void* notifyMutex;

	//! synconize Notify
	bool syncNotify;

	//! cegui event object	
	EventSet d_event;
};

}

#endif

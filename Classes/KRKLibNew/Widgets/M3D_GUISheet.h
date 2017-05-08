//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_GuiSheet.cpp
//																	
// Description: GUI root window
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//
#ifndef _MULTAK_GUISHEET_
#define _MULTAK_GUISHEET_

#include "Window_2D.h"
#include "kkinput/kkinput.h"

namespace CEGUI
{

class M3D_GUISheet:public Window_2D
{
public:
	M3D_GUISheet(const String& type, const String& name);
	virtual ~M3D_GUISheet(void);

	static const String EventNamespace;				//!< Namespace for global events
	static const String WidgetTypeName;             //!< Window factory name
	
	Window_2D *getTopZoderWindow();

	void setOFNToKey(bool setting) {d_ofn_to_key = setting; for(unsigned char index = 0; index < MAX_OFN_DEV; index ++){ OFNReset(index);}}

	void setOFNMaxArea(int maxx, int maxy) {{d_ofn_max_x = maxx; d_ofn_max_y = maxy;}}

	void setOFNSense(float setting) {{d_ofn_sense= setting;};}
	
	void setOFNKeySense(float setting) {d_ofn_key_sense = setting;}
	
	bool injectOFNEvent(int dt, int dx, int dy, unsigned char event, unsigned char index);

private:

	bool OFNToKey(OFNEventArgs& args, int event, int para);

	void OFNReset(unsigned char index);

	unsigned long d_ofn_time[MAX_OFN_DEV];	// total delta time from touch on to touch off, (ms)
	int d_ofn_state[MAX_OFN_DEV];		//0: off, 1 on, 2 down
	
	int d_dxy[MAX_OFN_DEV][2];		// delta x,y from touch on to touch off

	int d_ofn_dx[MAX_OFN_DEV];		// total delta x from touch on to touch off
	int d_ofn_dy[MAX_OFN_DEV];		// total delta y from touch on to touch off
	unsigned long d_ofn_dt[MAX_OFN_DEV];	// total delta time from touch on to touch off, (ms)
	int d_ofn_touch[MAX_OFN_DEV];		//0: off, 1 on
	int d_ofn_key[MAX_OFN_DEV];		//0:up 1down

	int d_ofn_ds[MAX_OFN_DEV];
	int d_delta_ds[MAX_OFN_DEV];

	char		d_FirstRepeat;		// 1- before first key, 2-  first key to second key; 0- after 3'rd key

	short		d_last_dxy2[MAX_OFN_DEV][2];
	short		d_last_dxy[MAX_OFN_DEV][2];

	float		d_delta_dxy[MAX_OFN_DEV][2];
	float		d_delta_dsxy[MAX_OFN_DEV][2];    // * 100

	char		d_sending_fast_key[MAX_OFN_DEV];		// if speed > 30, then this = 1, if Speed < 10 2 times then this = 0; if touchoff then this = 1  //OFN_FAST_SPEED_MOVE_LIMIT
	char		d_sent_fast_key[MAX_OFN_DEV];		// if sent fast key, then no fast key when leave
	char		d_sent_fast_key2[MAX_OFN_DEV];		// if sent fast key, then no fast key when leave
	unsigned long	d_sent_fast_key_time[MAX_OFN_DEV];		// if sent fast key, then no fast key when leave
	unsigned long	d_last_event_time[MAX_OFN_DEV];		// if sent fast key, then no fast key when leave

	unsigned char	d_last_fast_direction;			// 0 - x, 1 - y

	unsigned long		d_lastofnTime[MAX_OFN_DEV];
	bool				d_ofn_to_key;		// 1: convert ofn event to keyboard event
	int					d_ofn_max_x;		// ofn maximum x
	int					d_ofn_max_y;		// ofn maximum y

	float				d_ofn_key_sense;// 0~1, 1 is maximum sensitive, only valid when d_ofn_to_key is true
	float				d_ofn_sense;// 0~1, 1 is maximum sensitive

	int					d_ofn_key_counter_x;
	int					d_ofn_key_counter_y;

	int 				d_ofn_lastTouch[MAX_OFN_DEV];
	int					d_ofn_lastKey[MAX_OFN_DEV];
	int					d_ofn_data_y_w[MAX_OFN_DEV];


};

}

#endif

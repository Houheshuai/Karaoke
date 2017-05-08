//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Req.cpp
//																	
// Description: basic class for data request
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//

#include "M3D_Req.h"

namespace CEGUI
{

//----------------------------------------------------------------------------//
M3D_Req::M3D_Req(void* para1, int para2)
{
}
	
//----------------------------------------------------------------------------//
M3D_Req::~M3D_Req(void)
{
}

//----------------------------------------------------------------------------//
int M3D_Req::reqInit(M3DReqCmd_t& cmd, int onePageItems)
{
	handle.reqCmd = cmd;
	handle.onePageItems = onePageItems;
	handle.totalItems = reqRec(0, -1);
	handle.curPage = 1;
	if (handle.onePageItems)
		handle.totalPage = (handle.totalItems+handle.onePageItems-1)/handle.onePageItems;
	else
	      handle.totalPage = 1;
	handle.curStartItem = 0;
	handle.reqCmd.itemIndex = 0;

	return handle.totalItems;
}

//----------------------------------------------------------------------------//
int M3D_Req::reqInit(M3DReqCmd_t& cmd)
{
	return reqInit(cmd, 1);
}

//----------------------------------------------------------------------------//
int M3D_Req::reqDeInit(void)
{
	return 0;
}

//----------------------------------------------------------------------------//
int M3D_Req::reqRec(int reqStart, int reqCount)
{
	return 0;
}

//----------------------------------------------------------------------------//
int M3D_Req::reqPage(int reqStart, int cursor)
{
	int ret = 0;
	
	if (reqStart >= 0) {
		if (handle.totalItems) {
			if (reqStart <= handle.totalItems-1) {
				ret = reqRec(reqStart,handle.onePageItems);
				handle.curPage = (cursor+handle.onePageItems)/handle.onePageItems;
			}
		}
		else {
			ret = reqRec(0,handle.onePageItems);
			handle.curPage = 0;
		}
	}
	else {
		if(handle.onePageItems+reqStart > 0) {
			ret = reqRec(0, handle.onePageItems);
			handle.curPage = (cursor+handle.onePageItems)/handle.onePageItems;
		}
	}
	return ret;
}

//----------------------------------------------------------------------------//
int M3D_Req::reqNextPage(void)
{
	int ret = 0;
	
	if (handle.curPage < (handle.totalItems+handle.onePageItems-1)/handle.onePageItems) {
		ret = reqRec(handle.curPage*handle.onePageItems,handle.onePageItems);
		handle.curStartItem = handle.curPage*handle.onePageItems;
		handle.curPage++;
	}

	return ret;
}

//----------------------------------------------------------------------------//
int M3D_Req::reqPrevPage(void)
{
	int ret = 0;
	
	if (handle.curPage > 1) {
		handle.curPage--;
		ret = reqRec((handle.curPage-1)*handle.onePageItems,handle.onePageItems);
		handle.curStartItem = (handle.curPage-1)*handle.onePageItems;
	}
	return ret;
}

}


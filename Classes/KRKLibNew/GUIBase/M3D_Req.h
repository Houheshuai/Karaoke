//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Req.h
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

#ifndef M3DREQ_H
#define M3DREQ_H

#include "M3D_Notify.h"

namespace CEGUI
{

#define M3DREQ_STRPARA_LEN		32

/*!
\brief
	request comand
	<type>& <subType> <ssType>define the command type
	<intPara> & <strPara[]> define the command parameters
*/
typedef struct {
	unsigned int  type;
	unsigned int  subType;
	unsigned int  ssType;
	unsigned int  intPara;
	unsigned int  cursor;
	unsigned int  itemIndex;		// set data from itemIndex
	char		  strPara[M3DREQ_STRPARA_LEN];
	
} M3DReqCmd_t;

/*!
\brief
	request result
	<Buffer> is the result data buffer, it must be deleted in destructor
	<para1> & <para2> & <para3> are some parameters to save result infomation, not data
*/
typedef struct {
	void* Buffer;
	int     para1;
	int     para2;
	int     para3;

} M3DReqResult_t;

/*!
\brief
	request handle
*/
class handleM3DRec
{
public:
    handleM3DRec()  
	{
		reqResult.Buffer = 0;
	}

	void setStrPara(char* str) {strncpy(reqCmd.strPara, str, sizeof(reqCmd.strPara)-1);}

	M3DReqCmd_t reqCmd;
	M3DReqResult_t reqResult;

	int totalItems;
	int onePageItems;
	int curPage;
	int totalPage;
	int curStartItem;
};

class M3D_Req : public M3D_Notify
{
public:

	M3D_Req(void* para1, int para2);
		
	virtual ~M3D_Req(void);

	/*!
	\brief
		M3D request interfaces

	*/
	virtual int reqInit(M3DReqCmd_t& cmd);
	virtual int reqInit(M3DReqCmd_t& cmd, int onePageItems);
	virtual int reqDeInit(void);
	virtual int reqRec(int reqStart, int reqCount);
	
	virtual void* getBindingRec(void) {return NULL;}
	virtual void* getBindingRec(int id) {return NULL;}
	virtual int getBindingRecLength(void) {return 0;}

	/*!
	\brief
		request record by page
	*/
	int reqPage(int reqStart, int cursor);
	int reqNextPage(void);
	int reqPrevPage(void);
	
	//! request command handle
	handleM3DRec handle;
	
private:

	
};

}

#endif

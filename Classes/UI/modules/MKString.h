/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKString.h
** Revision : 1.00											
**																	
** Description: 
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by ...
**
************************ HOWTO *******************************
** 
*/

#ifndef MKSTRING_H
#define MKSTRING_H

#include <stdlib.h>
#include <string>

namespace CEGUI
{
#ifndef _WIN32
extern "C" char * itoa(int i, char *a, int r);
#endif
class MKString {

public:
	
	MKString(void);

	virtual ~MKString(void);

	static int toInt(const std::string& str) {return atoi(str.c_str());}

	static std::string valueOf(int val) {char tmp[256]; itoa(val, tmp, 10); return std::string(tmp);}

};
}
#endif


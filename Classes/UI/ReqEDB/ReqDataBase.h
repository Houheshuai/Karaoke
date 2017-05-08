#ifndef _REQDATABASE_H
#define _REQDATABASE_H

//#include "../krklib/include/lib/edb/edb.h"
#include <string>
//#include <vector>

//using namespace std;

class ReqDataBase
{
	public:
		ReqDataBase();

        ~ReqDataBase();
		
		virtual int getLanguageSongQuantity(int lanId);
		virtual int reqLanguageList(void);
	private:	
};
#endif

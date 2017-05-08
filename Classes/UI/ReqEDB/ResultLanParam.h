#ifndef _RESULTLANPARAM_H
#define _RESULTLANPARAM_H

#include <string>
//#include <vector>

class ResultLanParam
{
	public:		
		
		ResultLanParam();
        ~ResultLanParam();

		void setLanguageNameEG(std::string lanname);
		std::string getLanguageNameEG(void);
		
		void setSongQuantity(int songnum);
		int getSongQuantity(void);
		
		void setLanguageType(int lantype);
		int getLanguageType(void);
		
		
	private:
		std::string languageNameEG;
		int songQuantity;
		int languageType;
};
#endif

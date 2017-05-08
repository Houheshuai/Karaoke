#include "ResultLanParam.h"


ResultLanParam::ResultLanParam()
{
	languageNameEG ="";
	songQuantity = 0;
	languageType = 0;
}
ResultLanParam::~ResultLanParam()
{

}
void ResultLanParam::setLanguageNameEG(std::string lanname)
{
	languageNameEG = lanname;
	return;
}
std::string ResultLanParam::getLanguageNameEG(void)
{
	return languageNameEG;
}

void ResultLanParam::setSongQuantity(int songnum)
{
	songQuantity = songnum;
	return;
}
int ResultLanParam::getSongQuantity(void)
{
	return songQuantity;
}
void ResultLanParam::setLanguageType(int lantype)
{
	languageType = lantype;
	return;
}

int ResultLanParam::getLanguageType(void)
{
	return languageType;
}




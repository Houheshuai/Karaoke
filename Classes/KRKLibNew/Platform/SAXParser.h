#ifndef __SAXPARSER_H__
#define __SAXPARSER_H__

#include "Platform/PlatformConfig.h"
//#include "Platform/Common.h"
#include <string>

typedef unsigned char XML_CHAR;

class SAXDelegator
{
public:
    virtual ~SAXDelegator() {}

    /**
     * @js NA
     * @lua NA
     */
    virtual void startElement(void *ctx, const char *name, const char **atts) = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void endElement(void *ctx, const char *name) = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void textHandler(void *ctx, const char *s, int len) = 0;
};

class SAXParser
{
    SAXDelegator*    _delegator;
public:
    /**
     * @js NA
     * @lua NA
     */
    SAXParser();
    /**
     * @js NA
     * @lua NA
     */
    ~SAXParser(void);
    /**
     * @js NA
     * @lua NA
     */
    bool init(const char *encoding);
    /**
     * @js NA
     * @lua NA
     */
    bool parse(const char* xmlData, size_t dataLength);
    /**
     * @js NA
     * @lua NA
     */
    bool parse(const std::string& filename);
    /**
     * @js NA
     * @lua NA
     */
    void setDelegator(SAXDelegator* delegator);
    /**
     * @js NA
     * @lua NA
     */
    static void startElement(void *ctx, const XML_CHAR *name, const XML_CHAR **atts);
    /**
     * @js NA
     * @lua NA
     */
    static void endElement(void *ctx, const XML_CHAR *name);
    /**
     * @js NA
     * @lua NA
     */
    static void textHandler(void *ctx, const XML_CHAR *name, int len);
};

#endif //__SAXPARSER_H__

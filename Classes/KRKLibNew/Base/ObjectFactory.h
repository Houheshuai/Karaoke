#ifndef __TRIGGERFACTORY_H__
#define __TRIGGERFACTORY_H__

#include <string>
#include <unordered_map>
#include <functional>
#include "Base/Ref.h"
#include "Base/Macros.h"


class ObjectFactory
{
public:
    typedef Ref* (*Instance)(void);
    typedef std::function<Ref* (void)> InstanceFunc;
    struct TInfo
    {
        TInfo(void);
        TInfo(const std::string& type, Instance ins = nullptr);
        TInfo(const std::string& type, InstanceFunc ins = nullptr);
        TInfo(const TInfo &t);
        ~TInfo(void);
        TInfo& operator= (const TInfo &t);
        std::string _class;
        Instance _fun;
        InstanceFunc _func;
    };
    typedef std::unordered_map<std::string, TInfo>  FactoryMap;

    static ObjectFactory* getInstance();
    static void destroyInstance();
    Ref* createObject(const std::string &name);

    void registerType(const TInfo &t);
    void removeAll();

protected:
    ObjectFactory(void);
    virtual ~ObjectFactory(void);
private:
    static ObjectFactory *_sharedFactory;
    FactoryMap _typeMap;
};


#endif

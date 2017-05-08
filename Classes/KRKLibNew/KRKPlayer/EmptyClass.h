#pragma once
#include <string>

//根据需求删除修改类名称

//用于拷贝文件，生成新的类，主要是在不继承的情况下，方便独立创建类文件
class EmptyClass
{
public:
	EmptyClass(std::string _className);
	~EmptyClass();

	void SetLog(int _logFlag);

	int			LogFlag;
	std::string MyClassName;
	static	int ReferenceTimes;
};

//单独一个实例的类
class EmptyClassSingleton
{ 
public: 
    static EmptyClassSingleton *GetSingleInstance() 
    { 
        if (p_instance_ == nullptr) { 
            static EmptyClassSingleton instance; 
            p_instance_ = &instance; 
        }
        return p_instance_; 
    } 

    void count_increase () {count_ ++;} 
    int count () const {return count_;} 

private: 
    EmptyClassSingleton ();
    ~EmptyClassSingleton ();

    static EmptyClassSingleton *p_instance_; 
    int count_; 
}; 

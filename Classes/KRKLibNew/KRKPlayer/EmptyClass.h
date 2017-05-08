#pragma once
#include <string>

//��������ɾ���޸�������

//���ڿ����ļ��������µ��࣬��Ҫ���ڲ��̳е�����£���������������ļ�
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

//����һ��ʵ������
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

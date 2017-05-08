//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Singleton.h
//																	
// Description: Singleton module template class
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//
#ifndef _M3D_SINGLETON_
#define _M3D_SINGLETON_

namespace CEGUI
{
template <typename T> class M3D_Singleton
{
public:
    static T* getSingletonPtr( void )
    {
		if (ms_Singleton == nullptr) { 
            static T instance; 
            ms_Singleton = &instance; 
        }
		return ms_Singleton;
	}

protected:
	M3D_Singleton( void ){}
	~M3D_Singleton( void ){}

private:
    static T* ms_Singleton;

    M3D_Singleton& operator=(const M3D_Singleton&) { return this; }
    M3D_Singleton(const M3D_Singleton&) {}
};

template <typename T>
T* M3D_Singleton<T>::ms_Singleton = nullptr;

}

#endif


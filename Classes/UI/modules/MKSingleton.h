//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : MKSingleton.h
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
#ifndef _MK_SINGLETON_
#define _MK_SINGLETON_

#include <cassert>
namespace CEGUI
{
template <typename T> class MKSingleton
{
protected:
    static
#ifdef __MINGW32__
    CEGUIEXPORT
#endif
    T* ms_Singleton;

public:
    MKSingleton( void )
    {
        assert( !ms_Singleton );
        ms_Singleton = static_cast<T*>(this);
    }
   ~MKSingleton( void )
        {  assert( ms_Singleton );  ms_Singleton = 0;  }
    static T& getSingleton( void )
        {  assert( ms_Singleton );  return ( *ms_Singleton );  }
    static T* getSingletonPtr( void )
        {  return ( ms_Singleton );  }

private:
    MKSingleton& operator=(const MKSingleton&) { return this; }
    MKSingleton(const MKSingleton&) {}
};
}
#endif


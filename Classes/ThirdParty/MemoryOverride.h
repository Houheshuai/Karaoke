#ifndef _MEMORY_Override_H
#define _MEMORY_Override_H

#include <new>

#ifndef _FILE_AND_LINE_
#define _FILE_AND_LINE_ __FILE__,__LINE__
#endif

namespace CEGUI
{

	template <class Type>
    Type* OP_NEW(const char *file, unsigned int line)
	{
		(void) file;
		(void) line;
		return new Type;
	}

	template <class Type, class P1>
	Type* OP_NEW_1(const char *file, unsigned int line, const P1 &p1)
	{
		(void) file;
		(void) line;
		return new Type(p1);
	}

	template <class Type, class P1, class P2>
	Type* OP_NEW_2(const char *file, unsigned int line, const P1 &p1, const P2 &p2)
	{
		(void) file;
		(void) line;
		return new Type(p1, p2);
	}

	template <class Type, class P1, class P2, class P3>
	Type* OP_NEW_3(const char *file, unsigned int line, const P1 &p1, const P2 &p2, const P3 &p3)
	{
		(void) file;
		(void) line;
		return new Type(p1, p2, p3);
	}

	template <class Type, class P1, class P2, class P3, class P4>
	Type* OP_NEW_4(const char *file, unsigned int line, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4)
	{
		(void) file;
		(void) line;
		return new Type(p1, p2, p3, p4);
	}


	template <class Type>
	Type* OP_NEW_ARRAY(const int count, const char *file, unsigned int line)
	{
		if (count==0)
			return 0;

		(void) file;
		(void) line;
		return new Type[count];
	}

	template <class Type>
	void OP_DELETE(Type *buff, const char *file, unsigned int line)
	{
		(void) file;
		(void) line;
		delete buff;
	}

	template <class Type>
	void OP_DELETE_ARRAY(Type *buff, const char *file, unsigned int line)
	{
		(void) file;
		(void) line;
		delete [] buff;
	}
}


#endif

/*!*********************************************************************************************************************
\file         PVRCore\RefCounted.h
\author       PowerVR by Imagination, Developer Technology Team
\copyright    Copyright (c) Imagination Technologies Limited.
\brief         A smart pointer implementation very close to the spec of std::shared_ptr but with some differences and tweaks to
              make it more suitable for the PowerVR Framework.
***********************************************************************************************************************/
#pragma once
#include "PVRCore/CoreIncludes.h"

#include <memory>
#include <type_traits>

namespace pvr {

/*!*********************************************************************************************************************
\brief    An interface that represents a block of memory that will be doing the bookkeeping for an object that will be Reference
          Counted. This bit of memory holds the reference counts.
***********************************************************************************************************************/
struct IRefCountEntry
{
	int32 count; //!< Number of total references for this object
	int32 weakcount; //!< Number of weak references for this object
	virtual void deleteEntry() = 0; //!< Will be overriden with the actual code required to delete the bookkeeping entry
	virtual void destroyObject() = 0; //!< Will be overriden with the actual code required to delete the object
	virtual ~IRefCountEntry() {} //!< Will be overriden with the actual code required to delete the object
	IRefCountEntry() : count(1), weakcount(0) {}
};

/*!*********************************************************************************************************************
\brief        DO NOT USE DIRECTLY. The RefCountedResource uses this class when required.
              An Intrusive Refcount entry stores the object on the same block of memory as the reference counts.
\tparam       MyClass_ The type of reference counted object.
\description  This class is used to store the generated object on the same block of memory as the reference counts bookkeeping
              giving much better memory coherency. It is created when the "construct" method is used to create a new object inside
              a smart pointer. This is a much better solution than creating the object yourself and then just wrapping the
			  pointer you have with a RefCountEntry, as if you use the intrusive class you save one level of indirection.
			  This class is used when the user does RefCountEntry<MyClass> entry; entry.construct(...);
***********************************************************************************************************************/
template<typename MyClass_>
struct RefCountEntryIntrusive : public IRefCountEntry
{
	union
	{
		double _alignment_; //!<Unused, value irrelevent. Used to 4-byte align the following byte array.
		char entry[sizeof(MyClass_)]; //!<Represents enough bytes of memory to store a MyClass_ object.
	};

	/*!*****************************************************************************************************************
	\brief       Construct a new RefCountEntryIntrusive and the contained object.  Parameterless constructor.
	\param[out]  pointee After returning, pointee will contain the address of the newly constructed MyClass_ object.
	\description This constructor is called when the user calls construct() with no arguments.
	             Uses MyClass_'s parameterless constructor. Creates the class in place on our block of memory.
	*******************************************************************************************************************/
	RefCountEntryIntrusive(MyClass_*& pointee)
	{
		pointee = new(entry) MyClass_();
	}

	/*!*****************************************************************************************************************
	\brief       Construct a new RefCountEntryIntrusive and the contained object.  One Parameter constructor.
	\param[out] pointee After returning, pointee will contain the address of the newly constructed object
	\tparam P1 The type of the first argument required for MyClass_ one parameter constructor.
	\param[in] p1 The parameter that will be passed as MyClass_'s constructor first argument
	\description This constructor is called when the user calls construct() with one argument.
	             Uses MyClass_'s one-parameter constructor. Creates the class in place on our block of memory.
	*******************************************************************************************************************/
	template<typename P1> RefCountEntryIntrusive(MyClass_*& pointee, P1&& p1)
	{
		pointee = new(entry)MyClass_(std::forward<P1>(p1));
	}

	/*!*****************************************************************************************************************
	\brief       Construct a new RefCountEntryIntrusive and the contained object.  Two Parameter constructor.
	\param[out] pointee After returning, pointee will contain the address of the newly constructed object
	\tparam P1 The type of the first argument required for MyClass_ two parameter constructor.
	\tparam P2 The type of the second argument required for MyClass_ two parameter constructor.
	\param[in] p1 The parameter that will be passed as MyClass_'s constructor first argument
	\param[in] p2 The parameter that will be passed as MyClass_'s constructor second argument
	\description This constructor is called when the user calls construct() with two arguments.
	             Uses MyClass_'s two-parameter constructor. Creates the class in place on our block of memory.
	******************************************************************************************************************/
	template<typename P1, typename P2> RefCountEntryIntrusive(MyClass_*& pointee, P1&& p1, P2&& p2)
	{
		pointee = new(entry)MyClass_(std::forward<P1>(p1), std::forward<P2>(p2));
	}
	/*!*****************************************************************************************************************
	\brief       Construct a new RefCountEntryIntrusive and the contained object.  Three Parameter constructor.
	\param[out] pointee After returning, pointee will contain the address of the newly constructed object
	\tparam P1 The type of the first argument required for MyClass_ two parameter constructor.
	\tparam P2 The type of the second argument required for MyClass_ two parameter constructor.
	\tparam P3 The type of the third argument required for MyClass_ three parameter constructor.
	\param[in] p1 The parameter that will be passed as MyClass_'s constructor first argument
	\param[in] p2 The parameter that will be passed as MyClass_'s constructor second argument
	\param[in] p3 The parameter that will be passed as MyClass_'s constructor third argument
	\description This constructor is called when the user calls construct() with three arguments.
	             Uses MyClass_'s three-parameter constructor. Creates the class in place on our block of memory.
	******************************************************************************************************************/
	template<typename P1, typename P2, typename P3> RefCountEntryIntrusive(MyClass_*& pointee, P1&& p1, P2&& p2, P3&& p3)
	{
		pointee = new(entry)MyClass_(std::forward<P1>(p1), std::forward<P2>(p2), std::forward<P3>(p3));
	}

	/*!*****************************************************************************************************************
	\brief       Construct a new RefCountEntryIntrusive and the contained object.  Four Parameter constructor.
	\param[out] pointee After returning, pointee will contain the address of the newly constructed object
	\tparam P1 The type of the first argument required for MyClass_ two parameter constructor.
	\tparam P2 The type of the second argument required for MyClass_ two parameter constructor.
	\tparam P3 The type of the third argument required for MyClass_ three parameter constructor.
	\tparam P4 The type of the fourth argument required for MyClass_ fourth parameter constructor.
	\param[in] p1 The parameter that will be passed as MyClass_'s constructor first argument
	\param[in] p2 The parameter that will be passed as MyClass_'s constructor second argument
	\param[in] p3 The parameter that will be passed as MyClass_'s constructor third argument
	\param[in] p4 The parameter that will be passed as MyClass_'s constructor fourth argument
	\description This constructor is called when the user calls construct() with four arguments.
	             Uses MyClass_'s four-parameter constructor. Creates the class in place on our block of memory.
	******************************************************************************************************************/
	template<typename P1, typename P2, typename P3, typename P4> RefCountEntryIntrusive(MyClass_*& pointee, P1&& p1, P2&& p2, P3&& p3,
	        P4&& p4)
	{
		pointee = new(entry)MyClass_(std::forward<P1>(p1), std::forward<P2>(p2), std::forward<P3>(p3), std::forward<P4>(p4));
	}

	/*!*****************************************************************************************************************
	\brief       Construct a new RefCountEntryIntrusive and the contained object.  Five Parameter constructor.
	\param[out] pointee After returning, pointee will contain the address of the newly constructed object
	\tparam P1 The type of the first argument required for MyClass_ two parameter constructor.
	\tparam P2 The type of the second argument required for MyClass_ two parameter constructor.
	\tparam P3 The type of the third argument required for MyClass_ three parameter constructor.
	\tparam P4 The type of the fourth argument required for MyClass_ four parameter constructor.
	\tparam P4 The type of the fifth argument required for MyClass_ five parameter constructor.
	\param[in] p1 The parameter that will be passed as MyClass_'s constructor first argument
	\param[in] p2 The parameter that will be passed as MyClass_'s constructor second argument
	\param[in] p3 The parameter that will be passed as MyClass_'s constructor third argument
	\param[in] p4 The parameter that will be passed as MyClass_'s constructor fourth argument
	\param[in] p5 The parameter that will be passed as MyClass_'s constructor fifth argument
	\description This constructor is called when the user calls construct() with five arguments.
	             Uses MyClass_'s five-parameter constructor. Creates the class in place on our block of memory.
	******************************************************************************************************************/
	template<typename P1, typename P2, typename P3, typename P4, typename P5> RefCountEntryIntrusive(MyClass_*& pointee, P1&& p1,
	        P2&& p2, P3&& p3, P4&& p4, P5&& p5)
	{
		pointee = new(entry)MyClass_(std::forward<P1>(p1), std::forward<P2>(p2), std::forward<P3>(p3), std::forward<P4>(p4),
		                             std::forward<P5>(p5));
	}

	/*!*****************************************************************************************************************
	\brief       Destroys the RefcountEntryIntrusive object (entry and counters). Called when all references
	             (count + weak count) are  0. It assumes the object has already been destroyed - so it will NOT destroy
				 the object properly - only free its memory!!! destroyObject must be explicitly called otherwise
				 undefined behaviour occurs by freeing the memory of a live object!
	******************************************************************************************************************/
	void deleteEntry()
	{
		delete this;
	}

	/*!*****************************************************************************************************************
	\brief       Destroys the the held object. Called when all strong references are dead (count is zero).
	******************************************************************************************************************/
	void destroyObject()
	{
		((MyClass_*)entry)->~MyClass_();
	}
};

/*!*********************************************************************************************************************
\brief        DO NOT USE DIRECTLY. The RefCountedResource uses this class when required.
              A "simple" Refcount entry keeps a user-provided pointer to the object together with the reference counts.
\tparam       MyClass_ The type of the pointer kept.
\description  This class is used to store a user-provided pointer with the reference counts bookkeeping. This class is used when
              instead of calling "RefCountedResource::construct", the user provides a pointer to his object directly. This is
			  worse than construct because it has worse memory coherency (the object lives "far" from the refcount information).
			  The best solution is to use "construct", which creates a new object on a RefCountEntryIntrusive.
			  On destruction, calls "delete" on the pointer.
***********************************************************************************************************************/
template<typename MyClass_>
struct RefCountEntry : public IRefCountEntry
{
	MyClass_* ptr; //!<Pointer to the object
	RefCountEntry() : ptr(NULL) { }
	RefCountEntry(MyClass_* ptr) : ptr(ptr) { }
	void deleteEntry() { delete this; }
	void destroyObject() { delete ptr; }
};

/*!*********************************************************************************************************************
\brief        DO NOT USE DIRECTLY. The RefCountedResource follows this class.
\tparam       MyClass_ The type of the pointer kept.
\description  This class stores a pointer alias to the object to avoid the double-indirection of the RefCountEntry.
              Broken off to make specialising for the MyClass_ = void easier.
***********************************************************************************************************************/
template<typename MyClass_>
class Dereferenceable
{
protected:
	MyClass_* pointee;
	Dereferenceable(const MyClass_ * pointee)
	{
		this->pointee = const_cast<MyClass_*>(pointee);
	}

public:
	MyClass_& operator*() { return *pointee; }
	const MyClass_& operator*() const
	{
		return *pointee;
	}

	MyClass_* operator->()
	{
		PVR_ASSERT(pointee != 0 && "Dereferencing NULL pointer");
		return pointee;
	}
	const MyClass_* operator->() const
	{
		PVR_ASSERT(pointee != 0 && "Dereferencing NULL pointer");
		return pointee;
	}

};

//!\cond NO_DOXYGEN
template<>
class Dereferenceable<void>
{
protected:
	Dereferenceable(void* pointee) : pointee(pointee) {}
	void* pointee;
};


template<typename MyClass_>
struct RefcountEntryHolder
{
protected:

	//Create a new intrusive refcount entry, and on it, construct a new object with its zero-parameter constructor.
	void construct(MyClass_*& pointee)
	{
		RefCountEntryIntrusive<MyClass_>* ptr = new RefCountEntryIntrusive<MyClass_>(pointee);
		refCountEntry = ptr;
	}
	//Create a new intrusive refcount entry, and on it, construct a new object with its one-parameter constructor.
	template <typename P1> void construct(MyClass_*& pointee, P1&& p1)
	{
		RefCountEntryIntrusive<MyClass_>* ptr = new RefCountEntryIntrusive<MyClass_>(pointee, p1);
		refCountEntry = ptr;
	}
	//Create an new intrusive refcount entry, and on it, construct a new object with its two-parameter constructor.
	template <typename P1, typename P2> void construct(MyClass_*& pointee, P1&& p1, P2&& p2)
	{
		RefCountEntryIntrusive<MyClass_>* ptr = new RefCountEntryIntrusive<MyClass_>(pointee, p1, p2);
		refCountEntry = ptr;
	}
	//Create an new intrusive refcount entry, and on it, construct a new object with its three-parameter constructor.
	template <typename P1, typename P2, typename P3> void construct(MyClass_*& pointee, P1&& p1, P2&& p2, P3&& p3)
	{
		RefCountEntryIntrusive<MyClass_>* ptr = new RefCountEntryIntrusive<MyClass_>(pointee, p1, p2, p3);
		refCountEntry = ptr;
	}
	//Create an new intrusive refcount entry, and on it, construct a new object with its four-parameter constructor.
	template <typename P1, typename P2, typename P3, typename P4> void construct(MyClass_*& pointee, P1&& p1, P2&& p2, P3&& p3,
	        P4&& p4)
	{
		RefCountEntryIntrusive<MyClass_>* ptr = new RefCountEntryIntrusive<MyClass_>(pointee, p1, p2, p3, p4);
		refCountEntry = ptr;
	}
	//Create an new intrusive refcount entry, and on it, construct a new object with its five-parameter constructor.
	template <typename P1, typename P2, typename P3, typename P4, typename P5> void construct(MyClass_*& pointee, P1&& p1, P2&& p2,
	        P3&& p3, P4&& p4, P5&& p5)
	{
		RefCountEntryIntrusive<MyClass_>* ptr = new RefCountEntryIntrusive<MyClass_>(pointee, p1, p2, p3, p4, p5);
		refCountEntry = ptr;
	}
	//Holding the actual entry (pointers, objects and everything). Use directly in the subclass.
	IRefCountEntry* refCountEntry;

	//Create this entry with an already constructed reference-counted entry.
	RefcountEntryHolder(IRefCountEntry* refCountEntry) : refCountEntry(refCountEntry) {}
};

template<>
struct RefcountEntryHolder<void>
{
protected:
	IRefCountEntry* refCountEntry;
	RefcountEntryHolder(IRefCountEntry* refCountEntry) : refCountEntry(refCountEntry) {}
};
//!\endcond

template<typename MyClass_> class RefCountedWeakReference;


/*!*********************************************************************************************************************
\brief        Reference counted smart pointer. It can be used very similarly to the C++11 shared_ptr, but with some differences.
\description  This reference counted smart resource will keep track of how many references to a specific object exist, and
              release it when this is zero. Use its .construct(...) method overloads to efficiently construct an object together
			  with its ref-counting bookkeeping information. If this is not practical, you can also assign an already created
			  pointer to it, as long as it is safe to call "delete" on it.
			  Copy construction, move and assignment all work as expected and can freely be used.
			  It can very easily be used polymorphically.
\tparam       MyClass_ The type of object held. If .construct(...) is called, this is the type of the object that will be created.
***********************************************************************************************************************/
template<typename MyClass_>
class RefCountedResource : public Dereferenceable<MyClass_>, public RefcountEntryHolder<MyClass_>
{
	template<typename> friend class RefCountedResource;
	template<typename> friend class RefCountedWeakReference;
public:
	/*!*********************************************************************************************************************
	\brief   Type of the object that this object contains. Can be a superclass of the actual type of the object.
	***********************************************************************************************************************/
	typedef MyClass_ ElementType;

	/*!*********************************************************************************************************************
	\return True if this object contains a reference to a non-null object (is safely dereferenceable).
	        Equivalent to !isNull().
	***********************************************************************************************************************/
	bool isValid() const { return RefcountEntryHolder<MyClass_>::refCountEntry != NULL && RefcountEntryHolder<MyClass_>::refCountEntry->count > 0; }

	/*!*********************************************************************************************************************
	\return True if this object does not contain a reference to a non-null object (is not safely dereferenceable).
	        Equivalent to !isValid().
	***********************************************************************************************************************/
	bool isNull() const { return RefcountEntryHolder<MyClass_>::refCountEntry == NULL || RefcountEntryHolder<MyClass_>::refCountEntry->count == 0; }

	/*!*********************************************************************************************************************
	\brief    Get a raw pointer to the pointed-to object.
	\return   A raw pointer to the pointed-to object.
	***********************************************************************************************************************/
	MyClass_* get() { return Dereferenceable<MyClass_>::pointee; }

	/*!*********************************************************************************************************************
	\brief    Get a const raw pointer to the pointed-to object.
	\return   A const raw pointer to the pointed-to object.
	***********************************************************************************************************************/
	const MyClass_* get() const { return Dereferenceable<MyClass_>::pointee; }

	/*!*********************************************************************************************************************
	\brief    Swap the contents of this RefCountedResource object with another RefCountedResource object of the same type.
	***********************************************************************************************************************/
	void swap(RefCountedResource& rhs)
	{
		IRefCountEntry* tmpRefCountEntry = RefcountEntryHolder<MyClass_>::refCountEntry;
		RefcountEntryHolder<MyClass_>::refCountEntry = rhs.refCountEntry;
		rhs.refCountEntry = tmpRefCountEntry;
		MyClass_ * tmpPointee = Dereferenceable<MyClass_>::pointee;
		Dereferenceable<MyClass_>::pointee = rhs.pointee;
		rhs.pointee = tmpPointee;
	}

	/*!*********************************************************************************************************************
	\brief    Default constructor. Points to NULL.
	***********************************************************************************************************************/
	RefCountedResource() : Dereferenceable<MyClass_>(NULL), RefcountEntryHolder<MyClass_>(0) { }

	/*!*********************************************************************************************************************
	\brief    Copy constructor. Increments reference count.
	***********************************************************************************************************************/
	RefCountedResource(const RefCountedResource& rhs) : Dereferenceable<MyClass_>(rhs), RefcountEntryHolder<MyClass_>(rhs)
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { ++(RefcountEntryHolder<MyClass_>::refCountEntry->count); }
	}

	/*!*********************************************************************************************************************
	\brief    Wrap an already existing object with a RefCountedResource.
	\tparam   MyPointer_ the type of the class pointed to by the pointer. May be a subclass of MyClass_.
	\param    ref The pointer to wrap into the RefCountedResource. Will be deleted when refcount reaches zero.
	\brief    Wrap an already existing object with a RefCountedResource. Will call delete on a MyPointer_ type when the reference
	          count reaches zero. MyPointer_ may be MyClass_ or a subclass of MyClass_. delete MyPointer_ will happen, not MyClass_.
	***********************************************************************************************************************/
	template<typename MyPointer_>
	explicit RefCountedResource(MyPointer_* ref) : Dereferenceable<MyClass_>(ref), RefcountEntryHolder<MyClass_>(new RefCountEntry<MyPointer_>(ref))
	{
		RefcountEntryHolder<MyClass_>::refCountEntry->count = 1;
	}

	/*!*********************************************************************************************************************
	\brief       Copy Assignment operator. Increments reference count.
	\description "this" (the left-hand-side of the operator) object will be released (if not NULL, reference count will be
	             decreased as normal and, if zero, the object will be deleted). Reference count of the right-hand-side object
				 will be increased and this RefCountedResource will be pointing to it.
	***********************************************************************************************************************/
	RefCountedResource& operator=(RefCountedResource rhs) { swap(rhs); return *this; }

	/*!*********************************************************************************************************************
	\brief       Implicit Copy Conversion constructor.
	\description 	A RefCountedResource is implicitly convertible to any type that its current ElementType is implicitly convertible
				 to. For example, a pointer to a subclass is implicitly convertible to a pointer to superclass.
				 Reference counting keeps working normally on the original object regardless of the type of the pointer.
	\param rhs   The object to convert
	\description The last (unnamed) parameter of this function is required for template argument matching (SFINAE) and is not used.
	***********************************************************************************************************************/
	template<class OldType_>
	RefCountedResource(const RefCountedResource<OldType_>& rhs,
	                   typename std::enable_if<std::is_convertible<OldType_*, MyClass_*>::value, void*>::type* = 0)
		: Dereferenceable<MyClass_>(rhs.pointee), RefcountEntryHolder<MyClass_>(rhs.refCountEntry)
	{
		//Compile-time check: are these types compatible?
		OldType_* checkMe = static_cast<OldType_*>(Dereferenceable<MyClass_>::pointee);
		(void)checkMe;
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { ++(RefcountEntryHolder<MyClass_>::refCountEntry->count); }
	}

	/*!*********************************************************************************************************************
	\brief       Explicit Copy Conversion constructor.
	\description A RefCountedResource is explicitly convertible to any type that its current ElementType is explicitly convertible to.
	             For example, a pointer to void is explicitly convertible to a pointer to any class.
				 Conversion used is static_cast.
				 Reference counting keeps working normally on the original object regardless of the type of the pointer.
	\param rhs   The object to convert
	\description The last (unnamed) parameter of this function is required for template argument matching (SFINAE) and is not used.
	***********************************************************************************************************************/
	template<class OldType_>
	explicit RefCountedResource(const RefCountedResource<OldType_>& rhs,
	                            typename std::enable_if < !std::is_convertible<OldType_*, MyClass_*>::value, void* >::type* = 0)
		: Dereferenceable<MyClass_>(static_cast<MyClass_* >(rhs.pointee)), RefcountEntryHolder<MyClass_>(rhs.refCountEntry)
	{
		//Compile-time check: are these types compatible?
		OldType_* checkMe = static_cast<MyClass_*>(Dereferenceable<MyClass_>::pointee);
		(void)checkMe;
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { ++(RefcountEntryHolder<MyClass_>::refCountEntry->count); }
	}

	/*!*********************************************************************************************************************
	\brief       Destructor. Releases the object (decreases reference count and deletes it if zero).
	***********************************************************************************************************************/
	virtual ~RefCountedResource() { release(); }

	/*!*********************************************************************************************************************
	\brief       Tests equality of the pointers of two compatible RefCountedResource. NULL tests equal to NULL.
	***********************************************************************************************************************/
	bool operator==(const RefCountedResource& rhs) const
	{
		return get() == rhs.get();
	}

	/*!*********************************************************************************************************************
	\brief       Decrements reference count. If it is the last pointer, destroys the pointed-to object. Else, abandons it and
	             resets to nothing. Equivalent to reset(NULL).
	***********************************************************************************************************************/
	void release()
	{
		releaseOne();
		RefcountEntryHolder<MyClass_>::refCountEntry = 0;
		Dereferenceable<MyClass_>::pointee = 0;
	}

	/*!*********************************************************************************************************************
	\brief       Decrements reference count. If it is the last pointer, destroys the pointed-to object. Else, abandons it. Then,
	             wraps the provided pointer and points to it. Equivalent to destroying the original smart pointer and creating a
				 new one.
	\tparam MyPointer_ The type of the new pointer to wrap. Must be implicitly convertible to MyClass_.
	\param ref   The new pointer to wrap.
	***********************************************************************************************************************/
	template<typename MyPointer_>
	void reset(MyPointer_* ref)
	{
		release();
		RefcountEntryHolder<MyClass_>::refCountEntry = new RefCountEntry<MyPointer_>(ref);
		Dereferenceable<MyClass_>::pointee = ref;
	}

	/*!*********************************************************************************************************************
	\brief       Decrements reference count. If it is the last pointer, destroys the pointed-to object. Else, abandons it. Then,
	             resets to NULL.
	***********************************************************************************************************************/
	void reset()
	{
		release();
	}

	/*!*********************************************************************************************************************
	\brief      -- Use this method to construct a new instance of ElementType using its default constructor, and use
	            reference counting with it. ---   PARAMETERLESS CONSTRUCTOR OVERLOAD
	\description Use this method or its overloads to create a new object in the most efficient way possible and wrap it in a
	            RefCountedResource object. Use this whenever possible instead of wrapping a user-provided pointer in order to get
				the best memory locality, as this method will create both the object and the necessary reference counters in one
				block of memory.
				If an object is already owned by this object, it will first be properly released before constructing the new one.
	***********************************************************************************************************************/
	void construct()
	{
		release();
		RefcountEntryHolder<MyClass_>::construct(Dereferenceable<MyClass_>::pointee);
	}

	/*!*********************************************************************************************************************
	\brief      -- Use this method to construct a new instance of ElementType using its one-parameter constructor, and use
	            reference counting with it. ---   ONE ARGUMENT CONSTRUCTOR OVERLOAD
	\description Use this method or its overloads to create a new object in the most efficient way possible and wrap it in a
	            RefCountedResource object. Use this whenever possible instead of wrapping a user-provided pointer in order to get
				the best memory locality, as this method will create both the object and the necessary reference counters in one
				block of memory.
				If an object is already owned by this object, it will first be properly released before constructing the new one.
	\tparam     ParamType  The type of the argument accepted by MyClass_'s constructor
	\param      param  The argument that will be forwarded to MyClass_'s constructor
	***********************************************************************************************************************/
	template <typename ParamType>
	void construct(ParamType&& param)
	{
		release();
		RefcountEntryHolder<MyClass_>::construct(Dereferenceable<MyClass_>::pointee, std::forward<ParamType>(param));
	}


	/*!*********************************************************************************************************************
	\brief      -- Use this method to construct a new instance of ElementType using its two-parameter constructor, and use
	            reference counting with it. ---   TWO-ARGUMENT CONSTRUCTOR OVERLOAD
	\description Use this method or its overloads to create a new object in the most efficient way possible and wrap it in a
	            RefCountedResource object. Use this whenever possible instead of wrapping a user-provided pointer in order to get
				the best memory locality, as this method will create both the object and the necessary reference counters in one
				block of memory.
				If an object is already owned by this object, it will first be properly released before constructing the new one.
	\tparam     ParamType1  The type of the first argument accepted by MyClass_'s constructor
	\param      param1  The argument that will be forwarded to MyClass_'s constructor as the first argument
	\tparam     ParamType2  The type of the second argument accepted by MyClass_'s constructor
	\param      param2  The argument that will be forwarded to MyClass_'s constructor as the second argument
	***********************************************************************************************************************/
	template <typename ParamType1, typename ParamType2>
	void construct(ParamType1&& param1, ParamType2&& param2)
	{
		release();
		RefcountEntryHolder<MyClass_>::construct(Dereferenceable<MyClass_>::pointee, std::forward<ParamType1>(param1),
		        std::forward<ParamType2>(param2));
	}

	/*!*********************************************************************************************************************
	\brief      -- Use this method to construct a new instance of ElementType using its three-parameter constructor, and use
	            reference counting with it. ---   THREE-ARGUMENT CONSTRUCTOR OVERLOAD
	\description Use this method or its overloads to create a new object in the most efficient way possible and wrap it in a
	            RefCountedResource object. Use this whenever possible instead of wrapping a user-provided pointer in order to get
				the best memory locality, as this method will create both the object and the necessary reference counters in one
				block of memory.
				If an object is already owned by this object, it will first be properly released before constructing the new one.
	\tparam     ParamType1  The type of the first argument accepted by MyClass_'s constructor
	\param      param1  The argument that will be forwarded to MyClass_'s constructor as the first argument
	\tparam     ParamType2  The type of the second argument accepted by MyClass_'s constructor
	\param      param2  The argument that will be forwarded to MyClass_'s constructor as the second argument
	\tparam     ParamType3  The type of the third argument accepted by MyClass_'s constructor
	\param      param3  The argument that will be forwarded to MyClass_'s constructor as the third argument
	***********************************************************************************************************************/
	template <typename ParamType1, typename ParamType2, typename ParamType3>
	void construct(ParamType1&& param1, ParamType2&& param2, ParamType3&& param3)
	{
		release();
		RefcountEntryHolder<MyClass_>::construct(Dereferenceable<MyClass_>::pointee, std::forward<ParamType1>(param1),
		        std::forward<ParamType2>(param2), std::forward<ParamType3>(param3));
	}

	/*!*********************************************************************************************************************
	\brief      -- Use this method to construct a new instance of ElementType using its four-parameter constructor, and use
	            reference counting with it. ---   FOUR-ARGUMENT CONSTRUCTOR OVERLOAD
	\descriptionUse this method or its overloads to create a new object in the most efficient way possible and wrap it in a
	            RefCountedResource object. Use this whenever possible instead of wrapping a user-provided pointer in order to get
				the best memory locality, as this method will create both the object and the necessary reference counters in one
				block of memory.
				If an object is already owned by this object, it will first be properly released before constructing the new one.
	\tparam     ParamType1  The type of the first argument accepted by MyClass_'s constructor
	\param      param1  The argument that will be forwarded to MyClass_'s constructor as the first argument
	\tparam     ParamType2  The type of the second argument accepted by MyClass_'s constructor
	\param      param2  The argument that will be forwarded to MyClass_'s constructor as the second argument
	\tparam     ParamType3  The type of the third argument accepted by MyClass_'s constructor
	\param      param3  The argument that will be forwarded to MyClass_'s constructor as the third argument
	\tparam     ParamType4  The type of the fourth argument accepted by MyClass_'s constructor
	\param      param4  The argument that will be forwarded to MyClass_'s constructor as the fourth argument
	***********************************************************************************************************************/
	template <typename ParamType1, typename ParamType2, typename ParamType3, typename ParamType4>
	void construct(ParamType1&& param1, ParamType2&& param2, ParamType3&& param3, ParamType4&& param4)
	{
		release();
		RefcountEntryHolder<MyClass_>::construct(Dereferenceable<MyClass_>::pointee, std::forward<ParamType1>(param1),
		        std::forward<ParamType2>(param2), std::forward<ParamType3>(param3), std::forward<ParamType4>(param4));
	}

	/*!*********************************************************************************************************************
	\brief      -- Use this method to construct a new instance of ElementType using its FIVE-parameter constructor, and use
	            reference counting with it. ---   FIVE-ARGUMENT CONSTRUCTOR OVERLOAD
	\descriptionUse this method or its overloads to create a new object in the most efficient way possible and wrap it in a
	            RefCountedResource object. Use this whenever possible instead of wrapping a user-provided pointer in order to get
				the best memory locality, as this method will create both the object and the necessary reference counters in one
				block of memory.
				If an object is already owned by this object, it will first be properly released before constructing the new one.
	\tparam     ParamType1  The type of the first argument accepted by MyClass_'s constructor
	\param      param1  The argument that will be forwarded to MyClass_'s constructor as the first argument
	\tparam     ParamType2  The type of the second argument accepted by MyClass_'s constructor
	\param      param2  The argument that will be forwarded to MyClass_'s constructor as the second argument
	\tparam     ParamType3  The type of the third argument accepted by MyClass_'s constructor
	\param      param3  The argument that will be forwarded to MyClass_'s constructor as the third argument
	\tparam     ParamType4  The type of the fourth argument accepted by MyClass_'s constructor
	\param      param4  The argument that will be forwarded to MyClass_'s constructor as the fourth argument
	\tparam     ParamType5  The type of the fifth argument accepted by MyClass_'s constructor
	\param      param5  The argument that will be forwarded to MyClass_'s constructor as the fifth argument
	***********************************************************************************************************************/
	template <typename ParamType1, typename ParamType2, typename ParamType3, typename ParamType4, typename ParamType5>
	void construct(ParamType1&& param1, ParamType2&& param2, ParamType3&& param3, ParamType4&& param4, ParamType5&& param5)
	{
		release();
		RefcountEntryHolder<MyClass_>::construct(Dereferenceable<MyClass_>::pointee, std::forward<ParamType1>(param1),
		        std::forward<ParamType2>(param2), std::forward<ParamType3>(param3), std::forward<ParamType4>(param4),
		        std::forward<ParamType5>(param5));
	}
private:
	void retainOne()
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { RefcountEntryHolder<MyClass_>::refCountEntry->count++; }
	}

	void releaseOne()
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry)
		{
#ifdef DEBUG
			if (RefcountEntryHolder<MyClass_>::refCountEntry->count == 0) //SANITY CHECK - should never happen!
			{
				PVR_ASSERT(0 && "POSSIBLE BUG - Refcount entry count is zero but a strong reference to it was still live");
				if (RefcountEntryHolder<MyClass_>::refCountEntry->weakcount == 0)
				{
					RefcountEntryHolder<MyClass_>::refCountEntry->deleteEntry();
				}
				RefcountEntryHolder<MyClass_>::refCountEntry = 0;
				Dereferenceable<MyClass_>::pointee = 0;
			}
			else
#endif
			{
				if (--(RefcountEntryHolder<MyClass_>::refCountEntry->count) == 0)
				{
					RefcountEntryHolder<MyClass_>::refCountEntry->destroyObject();
					if (RefcountEntryHolder<MyClass_>::refCountEntry->weakcount == 0)
					{
						RefcountEntryHolder<MyClass_>::refCountEntry->deleteEntry();
					}
					RefcountEntryHolder<MyClass_>::refCountEntry = 0;
					Dereferenceable<MyClass_>::pointee = 0;
				}
			}
		}
	}
	template <typename OriginalType>
	RefCountedResource(IRefCountEntry* entry, OriginalType* pointee)
		: RefcountEntryHolder<MyClass_>(entry), Dereferenceable<MyClass_>(static_cast<MyClass_* >(pointee))
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry)
		{
			++(RefcountEntryHolder<MyClass_>::refCountEntry->count);
		}
	}
	template<typename PointeeType>
	void resetEntry(IRefCountEntry* entry, PointeeType* pointee)
	{
		release();
		RefcountEntryHolder<MyClass_>::refCountEntry = entry;
		++(entry->count);
	}
};


/*!*********************************************************************************************************************
\brief      A RefCountedWeakReference is a "Weak Reference" to a Reference counted object.
\description Weak references are the same as a normal RefCountedResource with a few key differences:
            1) They cannot keep the object alive. If an object only has weak references to it, it is destroyed.
			2) You cannot construct an object on a weak reference.
			Weak references are used to avoid Cyclic Dependencies which would sometimes make objects undeleteable and hanging
			even when no application references exist to them (If "A" holds a reference to "B" and "B" holds a reference to
			"A" then even when the user abandons all references to A and B the objects will be dangling in memory). In those
			cases one side must hold a weak reference to the other ("A" holds a reference to "B" and "B" holds a weak
			reference to "A", then when the last reference to "A" is abandoned from the application, "A" will be deleted,
			freeing the reference to "B" and allowing it to be deleted.
			Can only be created from an already existing RefCountedResource or another RefCountedWeakReference.
\tparam     MyClass_  The type of the element that this RefCountedWeakReference points to. Can be polymorphic.
***********************************************************************************************************************/
template<typename MyClass_>
class RefCountedWeakReference : public Dereferenceable<MyClass_>, public RefcountEntryHolder<MyClass_>
{
	template<typename> friend class RefCountedResource;
	template<typename> friend class RefCountedWeakReference;
public:
	typedef MyClass_ ElementType; //!< The type of the element pointed to. Can be polymorphic.

	/*!*********************************************************************************************************************
	\brief     Test if this reference points to a valid object.
	\return    True if this reference points to a valid object.
	***********************************************************************************************************************/
	bool isValid() const { return RefcountEntryHolder<MyClass_>::refCountEntry != NULL && RefcountEntryHolder<MyClass_>::refCountEntry->count > 0; }

	/*!*********************************************************************************************************************
	\brief     Test if this reference does not point to a valid object.
	\return    True if this reference does not points to a valid object.
	***********************************************************************************************************************/
	bool isNull() const { return RefcountEntryHolder<MyClass_>::refCountEntry == NULL || RefcountEntryHolder<MyClass_>::refCountEntry->count == 0; }

	/*!*********************************************************************************************************************
	\brief     Get a raw pointer to the pointed-to object.
	\return    Get a raw pointer of MyClass_* type to the pointed-to object.
	***********************************************************************************************************************/
	MyClass_* get() { return Dereferenceable<MyClass_>::pointee; }

	/*!*********************************************************************************************************************
	\brief     Get a const raw pointer to the pointed-to object.
	\return    Get a const raw pointer of MyClass_* type to the pointed-to object.
	***********************************************************************************************************************/
	const MyClass_* get() const { return Dereferenceable<MyClass_>::pointee; }

	void swap(RefCountedWeakReference& rhs)
	{
		IRefCountEntry* tmpRefCountEntry = RefcountEntryHolder<MyClass_>::refCountEntry;
		RefcountEntryHolder<MyClass_>::refCountEntry = rhs.refCountEntry;
		rhs.refCountEntry = tmpRefCountEntry;
		MyClass_ * tmpPointee = Dereferenceable<MyClass_>::pointee;
		Dereferenceable<MyClass_>::pointee = rhs.pointee;
		rhs.pointee = tmpPointee;
	}

	/*!*********************************************************************************************************************
	\brief     Default constructor. Constructed object points to NULL.
	***********************************************************************************************************************/
	RefCountedWeakReference() : Dereferenceable<MyClass_>(NULL), RefcountEntryHolder<MyClass_>(0) { }

	/*!*********************************************************************************************************************
	\brief     Copy constructor. Implements normal reference counting (increases Weak reference count).
	***********************************************************************************************************************/
	RefCountedWeakReference(const RefCountedWeakReference& rhs) : Dereferenceable<MyClass_>(rhs), RefcountEntryHolder<MyClass_>(rhs)
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { ++(RefcountEntryHolder<MyClass_>::refCountEntry->weakcount); }
	}

	/*!*********************************************************************************************************************
	\brief     Copy conversion constructor from Normal (non-weak) reference. Implements normal reference counting (increases
	           Weak reference count).
	***********************************************************************************************************************/
	RefCountedWeakReference(const RefCountedResource<MyClass_>& rhs) : Dereferenceable<MyClass_>(rhs), RefcountEntryHolder<MyClass_>(rhs)
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { ++(RefcountEntryHolder<MyClass_>::refCountEntry->weakcount); }
	}

	/*!*********************************************************************************************************************
	\brief     Copy assignment operator. Implements normal reference counting (increases Weak reference count).
	***********************************************************************************************************************/
	RefCountedWeakReference& operator=(RefCountedWeakReference rhs) { swap(rhs); return *this; }

	/*!*********************************************************************************************************************
	\brief     Implicit Copy Conversion operator. Converts to this type any RefCountedWeakReference to a type that is implicitly
	           convertible to MyClass_.
	\tparam OldType_ The type that the right hand side wraps. Must be implicitly convertible to MyType_
	\param     rhs The object to convert
	\description The last (unnamed) parameter of this function is required for template argument matching (SFINAE) and is not used.
	***********************************************************************************************************************/
	template<class OldType_>
	RefCountedWeakReference(const RefCountedWeakReference<OldType_>& rhs,
	                        typename std::enable_if<std::is_convertible<OldType_*, MyClass_*>::value, void*>::type* = 0)
		: RefcountEntryHolder<MyClass_>(rhs.refCountEntry), Dereferenceable<MyClass_>(rhs.pointee)
	{
		//Compile-time check: are these types compatible?
		OldType_* checkMe = static_cast<OldType_*>(Dereferenceable<MyClass_>::pointee);
		(void)checkMe;
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { ++(RefcountEntryHolder<MyClass_>::refCountEntry->weakcount); }
	}

	/*!*********************************************************************************************************************
	\brief     Explicit Copy Conversion operator. Will converts to this type any RefCountedWeakReference to a type that is
	           explicitly convertible to MyClass_.
	\tparam OldType_ The type that the right hand side wraps. Must be explicitly convertible (static_cast) to MyType_
	\param     rhs The object to convert
	\description The last (unnamed) parameter of this function is required for template argument matching (SFINAE) and is not used.
	***********************************************************************************************************************/
	template<class OldType_>
	explicit RefCountedWeakReference(const RefCountedWeakReference<OldType_>& rhs,
	                                 typename std::enable_if < !std::is_convertible<OldType_*, MyClass_*>::value, void* >::type* = 0)
		: RefcountEntryHolder<MyClass_>(rhs.refCountEntry), Dereferenceable<MyClass_>((MyClass_*)(rhs.pointee))
	{
		//Compile-time check: are these types compatible?
		OldType_* checkMe = static_cast<MyClass_*>(Dereferenceable<MyClass_>::pointee);
		(void)checkMe;
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { ++(RefcountEntryHolder<MyClass_>::refCountEntry->weakcount); }
	}

	/*!*********************************************************************************************************************
	\brief   Destructor. Reduces weak references by one, freeing the bookkeeping block if total references reach 0.
	***********************************************************************************************************************/
	virtual ~RefCountedWeakReference() { release(); }

	/*!*********************************************************************************************************************
	\brief   Tests equality of pointers. NULL tests to NULL.
	***********************************************************************************************************************/
	bool operator==(const RefCountedWeakReference& rhs) const
	{
		return get() == rhs.get();
	}

	/*!*********************************************************************************************************************
	\brief   Decrements weak reference count. If it is the last pointer, the object must have already been destroyed, but it
	         destroys the reference counts block. Then, points to NULL.
	***********************************************************************************************************************/
	void release()
	{
		releaseOne();
		RefcountEntryHolder<MyClass_>::refCountEntry = 0;
		Dereferenceable<MyClass_>::pointee = 0;
	}

	/*!*********************************************************************************************************************
	\brief   Decrements weak reference count. If it is the last pointer, the object must have already been destroyed, but it
	         destroys the reference counts block. Then, points to NULL.
	***********************************************************************************************************************/
	void reset()
	{
		release();
	}

private:
	void retainOne()
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry) { RefcountEntryHolder<MyClass_>::refCountEntry->weakcount++; }
	}

	void releaseOne()
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry)
		{
#ifdef DEBUG
			if ((RefcountEntryHolder<MyClass_>::refCountEntry->count == 0)
			        && (RefcountEntryHolder<MyClass_>::refCountEntry->weakcount == 0)) //SANITY CHECK - should never happen!
			{
				PVR_ASSERT(0 && "POSSIBLE BUG - Refcount entry is zero but a weak reference to it still existed.");
				RefcountEntryHolder<MyClass_>::refCountEntry->deleteEntry();
				RefcountEntryHolder<MyClass_>::refCountEntry = 0;
				Dereferenceable<MyClass_>::pointee = 0;
			}
			else
#endif
			{
				if (--(RefcountEntryHolder<MyClass_>::refCountEntry->weakcount) == 0
				        && (RefcountEntryHolder<MyClass_>::refCountEntry->count == 0))
				{
					RefcountEntryHolder<MyClass_>::refCountEntry->deleteEntry();
					RefcountEntryHolder<MyClass_>::refCountEntry = 0;
					Dereferenceable<MyClass_>::pointee = 0;
				}
			}
		}
	}

	template <typename OriginalType>
	RefCountedWeakReference(IRefCountEntry* entry, OriginalType* pointee)
		: RefcountEntryHolder<MyClass_>(entry), Dereferenceable<MyClass_>(static_cast<MyClass_* >(pointee))
	{
		if (RefcountEntryHolder<MyClass_>::refCountEntry)
		{
			++(RefcountEntryHolder<MyClass_>::refCountEntry->weakcount);
		}
	}
	template<typename PointeeType>
	void resetEntry(IRefCountEntry* entry, PointeeType* pointee)
	{
		release();
		RefcountEntryHolder<MyClass_>::refCountEntry = entry;
		++(entry->weakcount);
	}
};

//!\cond NO_DOXYGEN
template<typename T>
struct IsRefCountedType
{
	template<typename U, void(U::*)()> struct SFINAE {};
	template<typename U> static char Test(SFINAE<U, &U::construct >*);
	template<typename U> static int Test(...);
	enum { value = sizeof(Test<T>(0)) == sizeof(char) };
};
}
//!\endcond
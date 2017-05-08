/**
 @file
 based on Chipmunk cpArray.
 Array is a faster alternative to NSMutableArray, it does pretty much the
 same thing (stores NSObjects and retains/releases them appropriately). It's
 faster because:
 - it uses a plain C interface so it doesn't incur Objective-c messaging overhead
 - it assumes you know what you're doing, so it doesn't spend time on safety checks
 (index out of bounds, required capacity etc.)
 - comparisons are done using pointer equality instead of isEqual

 There are 2 kind of functions:
 - Array functions that manipulates objective-c objects (retain and release are performed)
 - CArray functions that manipulates values like if they were standard C structures (no retain/release is performed)
 */

#ifndef C_ARRAY_H
#define C_ARRAY_H

#include "Base/Macros.h"
#include "Base/Ref.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Easy integration
#define ARRAYDATA_FOREACH(__array__, __object__)															\
__object__=__array__->arr[0]; for(long i=0, num=__array__->num; i<num; i++, __object__=__array__->arr[i])	\


typedef struct _Array {
	long num, max;
	Ref** arr;
} Array;

/** Allocates and initializes a new array with specified capacity */
Array* ArrayNew(long capacity);

/** Frees array after removing all remaining objects. Silently ignores nil arr. */
void ArrayFree(Array*& arr);

/** Doubles array capacity */
void ArrayDoubleCapacity(Array *arr);

/** Increases array capacity such that max >= num + extra. */
void ArrayEnsureExtraCapacity(Array *arr, long extra);

/** shrinks the array so the memory footprint corresponds with the number of items */
void ArrayShrink(Array *arr);

/** Returns index of first ourrence of object, NSNotFound if object not found. */
long ArrayGetIndexOfObject(Array *arr, Ref* object);

/** Returns a Boolean value that indicates whether object is present in array. */
bool ArrayContainsObject(Array *arr, Ref* object);

/** Appends an object. Behavior undefined if array doesn't have enough capacity. */
void ArrayAppendObject(Array *arr, Ref* object);

/** Appends an object. Capacity of arr is increased if needed. */
void ArrayAppendObjectWithResize(Array *arr, Ref* object);

/** Appends objects from plusArr to arr. 
 Behavior undefined if arr doesn't have enough capacity. */
void ArrayAppendArray(Array *arr, Array *plusArr);

/** Appends objects from plusArr to arr. Capacity of arr is increased if needed. */
void ArrayAppendArrayWithResize(Array *arr, Array *plusArr);

/** Inserts an object at index */
void ArrayInsertObjectAtIndex(Array *arr, Ref* object, long index);

/** Swaps two objects */
void ArraySwapObjectsAtIndexes(Array *arr, long index1, long index2);

/** Removes all objects from arr */
void ArrayRemoveAllObjects(Array *arr);

/** Removes object at specified index and pushes back all subsequent objects.
 Behavior undefined if index outside [0, num-1]. */
void ArrayRemoveObjectAtIndex(Array *arr, long index, bool releaseObj = true);

/** Removes object at specified index and fills the gap with the last object,
 thereby avoiding the need to push back subsequent objects.
 Behavior undefined if index outside [0, num-1]. */
void ArrayFastRemoveObjectAtIndex(Array *arr, long index);

void ArrayFastRemoveObject(Array *arr, Ref* object);

/** Searches for the first ourrence of object and removes it. If object is not
 found the function has no effect. */
void ArrayRemoveObject(Array *arr, Ref* object, bool releaseObj = true);

/** Removes from arr all objects in minusArr. For each object in minusArr, the
 first matching instance in arr will be removed. */
void ArrayRemoveArray(Array *arr, Array *minusArr);

/** Removes from arr all objects in minusArr. For each object in minusArr, all
 matching instances in arr will be removed. */
void ArrayFullRemoveArray(Array *arr, Array *minusArr);

// 
// // CArray for Values (c structures)

typedef struct _CArray {
    long num, max;
    void** arr;
} CArray;

/** Allocates and initializes a new C array with specified capacity */
CArray* CArrayNew(long capacity);

/** Frees C array after removing all remaining values. Silently ignores nil arr. */
void CArrayFree(CArray *arr);

/** Doubles C array capacity */
void CArrayDoubleCapacity(CArray *arr);

/** Increases array capacity such that max >= num + extra. */
void CArrayEnsureExtraCapacity(CArray *arr, long extra);

/** Returns index of first ourrence of value, NSNotFound if value not found. */
long CArrayGetIndexOfValue(CArray *arr, void* value);

/** Returns a Boolean value that indicates whether value is present in the C array. */
bool CArrayContainsValue(CArray *arr, void* value);

/** Inserts a value at a certain position. Behavior undefined if array doesn't have enough capacity */
void CArrayInsertValueAtIndex( CArray *arr, void* value, long index);

/** Appends an value. Behavior undefined if array doesn't have enough capacity. */
void CArrayAppendValue(CArray *arr, void* value);

/** Appends an value. Capacity of arr is increased if needed. */
void CArrayAppendValueWithResize(CArray *arr, void* value);

/** Appends values from plusArr to arr. Behavior undefined if arr doesn't have
 enough capacity. */
void CArrayAppendArray(CArray *arr, CArray *plusArr);

/** Appends values from plusArr to arr. Capacity of arr is increased if needed. */
void CArrayAppendArrayWithResize(CArray *arr, CArray *plusArr);

/** Removes all values from arr */
void CArrayRemoveAllValues(CArray *arr);

/** Removes value at specified index and pushes back all subsequent values.
 Behavior undefined if index outside [0, num-1].
 @since v0.99.4
 */
void CArrayRemoveValueAtIndex(CArray *arr, long index);

/** Removes value at specified index and fills the gap with the last value,
 thereby avoiding the need to push back subsequent values.
 Behavior undefined if index outside [0, num-1].
 @since v0.99.4
 */
void CArrayFastRemoveValueAtIndex(CArray *arr, long index);

/** Searches for the first ourrence of value and removes it. If value is not found the function has no effect.
 @since v0.99.4
 */
void CArrayRemoveValue(CArray *arr, void* value);

/** Removes from arr all values in minusArr. For each Value in minusArr, the first matching instance in arr will be removed.
 @since v0.99.4
 */
void CArrayRemoveArray(CArray *arr, CArray *minusArr);

/** Removes from arr all values in minusArr. For each value in minusArr, all matching instances in arr will be removed.
 @since v0.99.4
 */
void CArrayFullRemoveArray(CArray *arr, CArray *minusArr);


#endif // C_ARRAY_H

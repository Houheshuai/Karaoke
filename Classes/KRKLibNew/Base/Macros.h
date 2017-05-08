#ifndef __BASE_CCMACROS_H__
#define __BASE_CCMACROS_H__

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX


#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

#define RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

#define REPEAT_FOREVER (UINT_MAX -1)
#define kRepeatForever REPEAT_FOREVER


#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

#ifndef DBL_EPSILON
#define DBL_EPSILON     2.2204460492503131e-016
#endif // DBL_EPSILON


#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) || (defined(__clang__) && (__clang_major__ >= 3)) || (_MSC_VER >= 1800)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete; \
    TypeName &operator =(const TypeName &) = delete;
#else
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &); \
    TypeName &operator =(const TypeName &);
#endif

#if !defined(REQUIRES_NULL_TERMINATION)
    #if defined(__APPLE__) && (__APPLE__ >= 5549)
        #define REQUIRES_NULL_TERMINATION __attribute__((sentinel(0,1)))
    #elif defined(__GNUC__)
        #define REQUIRES_NULL_TERMINATION __attribute__((sentinel))
    #else
        #define REQUIRES_NULL_TERMINATION
    #endif
#endif

/** @def CONTENT_SCALE_FACTOR
On Mac it returns 1;
On iPhone it returns 2 if RetinaDisplay is On. Otherwise it returns 1
*/
#define CONTENT_SCALE_FACTOR()	1

/****************************/
/** RETINA DISPLAY ENABLED **/
/****************************/

/** @def RECT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define RECT_PIXELS_TO_POINTS(__rect_in_pixels__)                                                                        \
    Rect( (__rect_in_pixels__).origin.x / CONTENT_SCALE_FACTOR(), (__rect_in_pixels__).origin.y / CONTENT_SCALE_FACTOR(),    \
            (__rect_in_pixels__).size.width / CONTENT_SCALE_FACTOR(), (__rect_in_pixels__).size.height / CONTENT_SCALE_FACTOR() )

/** @def RECT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define RECT_POINTS_TO_PIXELS(__rect_in_points_points__)                                                                        \
    Rect( (__rect_in_points_points__).origin.x * CONTENT_SCALE_FACTOR(), (__rect_in_points_points__).origin.y * CONTENT_SCALE_FACTOR(),    \
            (__rect_in_points_points__).size.width * CONTENT_SCALE_FACTOR(), (__rect_in_points_points__).size.height * CONTENT_SCALE_FACTOR() )

/** @def POINT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define POINT_PIXELS_TO_POINTS(__pixels__)                                                                        \
Vec2( (__pixels__).x / CONTENT_SCALE_FACTOR(), (__pixels__).y / CONTENT_SCALE_FACTOR())

/** @def POINT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define POINT_POINTS_TO_PIXELS(__points__)                                                                        \
Vec2( (__points__).x * CONTENT_SCALE_FACTOR(), (__points__).y * CONTENT_SCALE_FACTOR())

/** @def POINT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define SIZE_PIXELS_TO_POINTS(__size_in_pixels__)                                                                        \
Size( (__size_in_pixels__).width / CONTENT_SCALE_FACTOR(), (__size_in_pixels__).height / CONTENT_SCALE_FACTOR())

/** @def POINT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define SIZE_POINTS_TO_PIXELS(__size_in_points__)                                                                        \
Size( (__size_in_points__).width * CONTENT_SCALE_FACTOR(), (__size_in_points__).height * CONTENT_SCALE_FACTOR())


/**
Helper macros which converts 4-byte little/big endian 
integral number to the machine native number representation
 
It should work same as apples CFSwapInt32LittleToHost(..)
*/

/// when define returns true it means that our architecture uses big endian
#define MK_HOST_IS_BIG_ENDIAN (bool)(*(unsigned short *)"\0\xff" < 0x100) 
#define MK_SWAP32(i)  ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define MK_SWAP16(i)  ((i & 0x00ff) << 8 | (i &0xff00) >> 8)   
#define MK_SWAP_INT32_LITTLE_TO_HOST(i) ((MK_HOST_IS_BIG_ENDIAN == true)? MK_SWAP32(i) : (i) )
#define MK_SWAP_INT16_LITTLE_TO_HOST(i) ((MK_HOST_IS_BIG_ENDIAN == true)? MK_SWAP16(i) : (i) )
#define MK_SWAP_INT32_BIG_TO_HOST(i)    ((MK_HOST_IS_BIG_ENDIAN == true)? (i) : MK_SWAP32(i) )
#define MK_SWAP_INT16_BIG_TO_HOST(i)    ((MK_HOST_IS_BIG_ENDIAN == true)? (i):  MK_SWAP16(i) )

#if !defined(_DEBUG)
#define CHECK_GL_ERROR_DEBUG()
#else
#define CHECK_GL_ERROR_DEBUG() \
    do { \
        GLenum __error = glGetError(); \
        if(__error) { \
			pvr::Log(pvr::Log.Error, "OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (false)
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)           do { if(p) { delete (p); (p) = nullptr; } } while(0)
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#endif

#define SAFE_RELEASE(p)          do { if(p) { p->release();  } } while(0)
#define SAFE_RELEASE_NULL(p)     do { if(p) { p->release(); (p) = nullptr; } } while(0)
#define SAFE_RETAIN(p)           do { if(p) { (p)->retain(); } } while(0)
#define BREAK_IF(cond)			 if(cond) break
//工具类函数
//图片是否是2的幂次方
extern int NextPOT(int x);
extern double M_atof(const char* str);

#define UNUSED_PARAM(unusedparam) (void)unusedparam

#define INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(__drawcalls__, __vertices__) \
    do {                                                                \
        Renderer *__renderer__ = Director::getInstance()->getRenderer();     \
        __renderer__->addDrawnBatches(__drawcalls__);                   \
        __renderer__->addDrawnVertices(__vertices__);                   \
    } while(0)



// new callbacks based on C++11
#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

/** @def CREATE_FUNC(__TYPE__)
 * Define a create function for a specific type, such as Layer.
 *
 * @param __TYPE__  class type to add create(), such as Layer.
 */
#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}



#endif // __BASE_MACROS_H__

#ifndef FACTORY_MODE_H
#define FACTORY_MODE_H

#ifdef __cplusplus
extern "C" {
#endif
struct tagListInfo;
typedef struct tagListInfo* FM_Handle;
extern FM_Handle FM_init(const char* fileName);
extern const char* FM_getValue(const char* tag, FM_Handle handle);
extern void FM_deinit(FM_Handle handle);
#ifdef __cplusplus
}
#endif

#endif
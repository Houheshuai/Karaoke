#ifndef __FILEUTILS_ANDROID_H__
#define __FILEUTILS_ANDROID_H__

#include "Platform/PlatformConfig.h"
#if TARGET_PLATFORM == PLATFORM_ANDROID

#include "Platform/FileUtils.h"
#include "Platform/PlatformMacros.h"
#include "Base/Types.h"
#include <string>
#include <vector>
#include "jni.h"
#include "android/asset_manager.h"

//! @brief  Helper class to handle file operations
class FileUtilsAndroid : public FileUtils
{
    friend class FileUtils;
public:
    FileUtilsAndroid();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~FileUtilsAndroid();

    static void setassetmanager(AAssetManager* a);
    static AAssetManager* getAssetManager() { return assetmanager; }

    /* override functions */
    bool init();

    virtual std::string getNewFilename(const std::string &filename) const override;

    /**
     *  Gets string from a file.
     */
    virtual std::string getStringFromFile(const std::string& filename) override;
    
    /**
     *  Creates binary data from a file.
     *  @return A data object.
     */
    virtual Data getDataFromFile(const std::string& filename) override;

    virtual std::string getWritablePath() const;
    virtual bool isAbsolutePath(const std::string& strPath) const;
    
private:
    virtual bool isFileExistInternal(const std::string& strFilePath) const override;
    virtual bool isDirectoryExistInternal(const std::string& dirPath) const override;
    Data getData(const std::string& filename, bool forString);

    static AAssetManager* assetmanager;
};

#endif // TARGET_PLATFORM == PLATFORM_ANDROID

#endif // __FILEUTILS_ANDROID_H__

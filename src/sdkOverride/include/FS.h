#ifndef FS_H
#define FS_H

#include <memory>
#include <Arduino.h>

#include <fstream>

class SDClass;

namespace fs {

class File;
class Dir;
class FS;

template <typename Tfs>
bool mount(Tfs& fs, const char* mountPoint);

enum SeekMode {
    SeekSet = 0,
    SeekCur = 1,
    SeekEnd = 2
};

class File : public Stream
{
public:
    virtual ~File() {}

    File(const char* path, const char* mode);

    // Print methods:
    size_t write(uint8_t) override;
    size_t write(const uint8_t *buf, size_t size) override;

    // Stream methods:
    int available() override;
    int read() override;
    int peek() override;
    void flush() override;
    size_t readBytes(char *buffer, size_t length)  override {
        return read((uint8_t*)buffer, length);
    }
    size_t read(uint8_t* buf, size_t size);
    bool seek(uint32_t pos, SeekMode mode);
    bool seek(uint32_t pos) {
        return seek(pos, SeekSet);
    }
    size_t position() const;
    size_t size() const;
    void close();
    operator bool() const;
    const char* name() const;
    const char* fullName() const; // Includes path
    bool truncate(uint32_t size);

    bool isFile() const;
    bool isDirectory() const;

    // Arduino "class SD" methods for compatibility
    template<typename T> size_t write(T &src){
      uint8_t obuf[256];
      size_t doneLen = 0;
      size_t sentLen;
      int i;

      while (src.available() > sizeof(obuf)){
        src.read(obuf, sizeof(obuf));
        sentLen = write(obuf, sizeof(obuf));
        doneLen = doneLen + sentLen;
        if(sentLen != sizeof(obuf)){
          return doneLen;
        }
      }

      size_t leftLen = src.available();
      src.read(obuf, leftLen);
      sentLen = write(obuf, leftLen);
      doneLen = doneLen + sentLen;
      return doneLen;
    }
    using Print::write;

    void rewindDirectory();
    File openNextFile();

    String readString() override;

protected:
    // Arduino SD class emulation
    std::shared_ptr<Dir> _fakeDir;
    FS                  *_baseFS;

    std::shared_ptr<std::ifstream> inStream_;
    std::shared_ptr<std::ofstream> outStream_;

    uint64_t inFileSize_ = 0;
};

class Dir {
public:
    Dir(): _baseFS(nullptr) { }

    File openFile(const char* mode);

    String fileName();
    size_t fileSize();
    bool isFile() const;
    bool isDirectory() const;

    bool next();
    bool rewind();

protected:
    FS       *_baseFS;
};

struct FSInfo {
    size_t totalBytes;
    size_t usedBytes;
    size_t blockSize;
    size_t pageSize;
    size_t maxOpenFiles;
    size_t maxPathLength;
};

class FSConfig
{
public:
    FSConfig(bool autoFormat = true) {
        _type = FSConfig::fsid::FSId;
	_autoFormat = autoFormat;
    }

    enum fsid { FSId = 0x00000000 };
    FSConfig setAutoFormat(bool val = true) {
        _autoFormat = val;
        return *this;
    }

    uint32_t _type;
    bool     _autoFormat;
};

class SPIFFSConfig : public FSConfig
{
public:
    SPIFFSConfig(bool autoFormat = true) {
        _type = SPIFFSConfig::fsid::FSId;
	_autoFormat = autoFormat;
    }
    enum fsid { FSId = 0x53504946 };
};

class FS
{
public:
    FS() {}

    bool setConfig(const FSConfig &cfg);

    bool begin();
    void end();

    bool format();
    bool info(FSInfo& info);

    File open(const char* path, const char* mode);
    File open(const String& path, const char* mode);

    bool exists(const char* path);
    bool exists(const String& path);

    Dir openDir(const char* path);
    Dir openDir(const String& path);

    bool remove(const char* path);
    bool remove(const String& path);

    bool rename(const char* pathFrom, const char* pathTo);
    bool rename(const String& pathFrom, const String& pathTo);

    bool mkdir(const char* path);
    bool mkdir(const String& path);

    bool rmdir(const char* path);
    bool rmdir(const String& path);

    bool gc();
};

} // namespace fs

#ifndef FS_NO_GLOBALS
using fs::FS;
using fs::File;
using fs::Dir;
using fs::SeekMode;
using fs::SeekSet;
using fs::SeekCur;
using fs::SeekEnd;
using fs::FSInfo;
using fs::FSConfig;
#endif //FS_NO_GLOBALS

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SPIFFS)
extern fs::FS SPIFFS;
#endif

#endif //FS_H

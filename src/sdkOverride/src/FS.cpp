#include "FS.h"
#include <fstream>
#include <string>

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SPIFFS)
fs::FS SPIFFS;
#endif

static const std::string rootFsPath = ".";///rootfs/";

namespace fs {

File::File(const char* path, const char* mode) {
    if (mode[0] == 'r') {
        auto sMode = std::ios_base::in | ( mode[1] == 'b' ? std::ios_base::binary : (std::ios_base::openmode)0);
        inStream_ = std::make_shared<std::ifstream>(rootFsPath + path, sMode | std::ios_base::ate);
        inFileSize_ = (inStream_ && inStream_->is_open()) ? (uint64_t)inStream_->tellg() : 0;
        if (inStream_ && inStream_->is_open())
            inStream_->seekg(0);
    } else if (mode[0] == 'w') {
        auto sMode = std::ios_base::out | ( mode[1] == 'b' ? std::ios_base::binary : (std::ios_base::openmode)0);
        outStream_ = std::make_shared<std::ofstream>(rootFsPath + path, sMode);
    } else {
        throw "Invalid file open mode";
    }
}

File::operator bool() const {
    return (inStream_ && inStream_->is_open()) || (outStream_ && outStream_->is_open());
}

int File::available() {
    if (!inStream_ || !inStream_->is_open())
        return 0;
    return inFileSize_ - inStream_->tellg();
}

int File::read() {
    if (!inStream_ || !inStream_->is_open())
        throw "file is not opened for read!";
    return inStream_->get();
}

int File::peek() {
    if (!inStream_ || !inStream_->is_open())
        throw "file is not opened for read!";
    return inStream_->peek();
}

size_t File::write(uint8_t c) {
    if (!outStream_ || !outStream_->is_open())
        throw "file is not opened for write!";
    outStream_->put(c);
    return 1;
}

size_t File::write(const uint8_t *buf, size_t size) {
    if (!outStream_ || !outStream_->is_open())
        throw "file is not opened for write!";
    outStream_->write((const char*)buf, size);
    return size;
}

void File::flush()  {
    fflush(nullptr);
}

size_t File::read(uint8_t* buf, size_t size) {
    throw "not implemented";
    return 0;
}

bool File::seek(uint32_t pos, SeekMode mode) {
    throw "not implemented";
    return 0;
}

size_t File::position() const {
    throw "not implemented";
    return 0;
}

size_t File::size() const {
    throw "not implemented";
    return 0;
}

const char* File::name() const {
    throw "not implemented";
    return 0;
}

const char* File::fullName() const {
    throw "not implemented";
    return 0;
}

bool File::truncate(uint32_t size) {
    throw "not implemented";
    return false;
}

bool File::isFile() const {
    return true;
}

bool File::isDirectory() const {
    return false;
}

void File::close() {
    inStream_.reset();
    outStream_.reset();
}

void File::rewindDirectory() {
    throw "not implemented";
}

File File::openNextFile() {
    throw "not implemented";
    return File("invalid", "invalid");
}

String File::readString() {
    throw "not implemented";
    return "";
}

// --------------------- FS ------------------------------

File FS::open(const char* path, const char* mode) {
    return File(path, mode);
}

File FS::open(const String& path, const char* mode) {
    return open(path.c_str(), mode);
}

void FS::end() {
}

bool FS::begin() {
    return true;
}

} // namespace fs

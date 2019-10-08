#include "FS.h"
#include <fstream>

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SPIFFS)
fs::FS SPIFFS;
#endif

namespace fs {

File::File(const char* path, const char* mode) {
    if (mode[0] == 'r') {
        auto sMode = std::ios_base::in | ( mode[1] == 'b' ? std::ios_base::binary : (std::ios_base::openmode)0);
        inStream_ = std::make_shared<std::ifstream>(path, sMode);
    } else if (mode[0] == 'w') {
        auto sMode = std::ios_base::out | ( mode[1] == 'b' ? std::ios_base::binary : (std::ios_base::openmode)0);
        outStream_ = std::make_shared<std::ofstream>(path, sMode);
    } else {
        throw "Invalid file open mode";
    }
}

File::operator bool() const {
    return inStream_->is_open() || outStream_->is_open();
}

File FS::open(const char* path, const char* mode) {
    return File(path, mode);
}

void File::close() {
    inStream_.reset();
    outStream_.reset();
}

File FS::open(const String& path, const char* mode) {
    return open(path.c_str(), mode);
}

void FS::end() {
}

} // namespace fs

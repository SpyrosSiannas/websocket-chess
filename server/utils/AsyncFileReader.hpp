#ifndef ASYNC_FILE_READER_H
#define ASYNC_FILE_READER_H

#include "Loop.h"
#include <fstream>
#include <string>

namespace server {
namespace utils {
class AsyncFileReader final {
public:
  AsyncFileReader(std::string filename) : _filename{filename} {
    _inputStream.open(filename, std::ios::binary);

    _inputStream.seekg(0, std::ios::end);
    _filesize = _inputStream.tellg();
    // Allocate 1MB of cache
    _cache.resize(1024 * 1024);

    _inputStream.seekg(0, std::ios::beg);
    _inputStream.read(_cache.data(), _cache.length());
    _cacheOffset = 0;
    _cacheFull = true;
  }

private:
  std::ifstream _inputStream;
  std::string _filename;
  std::string _cache;
  unsigned int _filesize;
  unsigned int _cacheOffset;
  bool _cacheFull{false};
  uWS::Loop *_eventLoop{uWS::Loop::get()};
};

} // namespace utils
} // namespace server
#endif // ASYNC_FILE_READER_H

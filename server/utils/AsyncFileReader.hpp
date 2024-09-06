#ifndef ASYNC_FILE_READER_H
#define ASYNC_FILE_READER_H

#include <fstream>
#include <string>
#include <future>

namespace server {
namespace utils {
class AsyncFileReader final {
public:
  AsyncFileReader(std::string filename) : _filename{filename} {
    _inputStream.open(filename, std::ios::binary);

    _inputStream.seekg(0, std::ios::end);
    _filesize = _inputStream.tellg();

    _inputStream.seekg(0, std::ios::beg);
    _inputStream.read(_cache, _cacheSize);
    _cachedOffset = 0;
    _cacheFull = true;
  }

  std::string_view peekCache(int offset) {
    bool fitsInCache = (offset - _cachedOffset) < _cacheSize;
    if (_cacheFull && offset >= _cachedOffset && fitsInCache) {
        int chunkSize = std::min<int>(_filesize - offset, _cacheSize - offset + _cachedOffset);
        return std::string_view(_cache + offset - _cachedOffset, chunkSize);
    } else {
        return std::string_view(nullptr, 0);
    }
  }

  void request(unsigned int offset, std::function<void(std::string_view)>&& callback) {
    if (!_cacheFull) {
      return;
    }

    return (void)std::async(std::launch::async, [this, callback, offset]() {
      if (!_inputStream.good()) {
        _inputStream.close();
        _inputStream.open(_filename, std::ios::binary);
      }

      if (_cachedOffset != offset) {
        _cacheFull = false;
        _inputStream.seekg(offset, _inputStream.beg);
        _inputStream.read(_cache, _cacheSize);
        _cachedOffset = offset;
        _cacheFull = true;
      }

      int chunkSize{std::min<int>(_cacheSize, _filesize - offset)};

      callback(std::string_view(_cache, chunkSize));
    });
  }
  bool isCacheFull() {return _cacheFull;}
  bool isStreamOpen() {return _inputStream.is_open();}
  unsigned int getFileSize() {return _filesize;}

private:
  std::ifstream _inputStream;
  std::string _filename;
  static constexpr unsigned int _cacheSize{1024*1024};
  char _cache[_cacheSize];
  unsigned int _filesize;
  unsigned int _cachedOffset;
  bool _cacheFull{false};
};

} // namespace utils
} // namespace server
#endif // ASYNC_FILE_READER_H

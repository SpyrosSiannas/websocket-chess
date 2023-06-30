#ifndef ASYNC_FILE_STREAMER_H
#define ASYNC_FILE_STREAMER_H

#include "AsyncFileReader.hpp"
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <HttpResponse.h>

namespace server {
namespace utils {
class AsyncFileStreamer {
public:
	AsyncFileStreamer(std::string rootDir) : _rootDir{rootDir} {
		initReaders(rootDir);
	}

	void initReaders(std::string root) {
		for(auto &p : std::filesystem::recursive_directory_iterator(root)) {
			std::string pathStr{p.path().string()};
            std::string url{pathStr.substr(root.length())};
            if (url == "/index.html") {
                url = "/";
            }
            asyncFileReaders.insert(std::make_pair(url,
			                                       std::make_unique<server::utils::AsyncFileReader>(pathStr)));
        }
	}

	template <bool SSL>
    void streamFile(uWS::HttpResponse<SSL> *res, std::string_view url) {
        const auto& it = asyncFileReaders.find(std::string(url));
        if (it == asyncFileReaders.end()) {
            auto filelist = getFiles();
            std::cout << "Did not find file: " << url << std::endl;
            std::cout << "Available Files:\n";
            for (auto& file : filelist) {
                std::cout << file << std::endl;
            }
            res->end();
        } else {
            streamFile(res, it->second);
        }
    }

	std::vector<std::string> getFiles() {
		std::vector<std::string> keys;
		for (auto& it : asyncFileReaders) {
			keys.emplace_back(std::string(it.first));
		}
		return keys;
	};

private:
	template <bool SSL>
    void streamFile(uWS::HttpResponse<SSL> *res, std::unique_ptr<server::utils::AsyncFileReader>& asyncFileReader) {
		std::string_view chunk = asyncFileReader->peekCache(res->getWriteOffset());
		if (!chunk.length() || res->tryEnd(chunk, asyncFileReader->getFileSize()).first) {
			if (chunk.length() < asyncFileReader->getFileSize()) {
				asyncFileReader->request(res->getWriteOffset(), [this, res, &asyncFileReader](std::string_view chunk) {
				if (!chunk.length()) {
					// todo: make sure to check for is_closed internally after all callbacks!
						res->close();
					} else {
						streamFile(res, asyncFileReader);
					}
				});
			}
		} else {
            res->onWritable([this, res, &asyncFileReader](int offset) {
				streamFile(res, asyncFileReader);
                return false;
            })->onAborted([]() {
                std::cout << "ABORTED!" << std::endl;
            });
		}
	}

private:
	std::string _rootDir;
	std::unordered_map<std::string, std::unique_ptr<server::utils::AsyncFileReader>> asyncFileReaders;
};

} // namespace utils
} // namespace server

#endif

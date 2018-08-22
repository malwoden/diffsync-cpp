#include "AsyncHasher.h"

namespace diffsync {

std::vector<std::tuple<uint32_t, std::vector<unsigned char>>>
asyncStrongAndWeakHash(const fs::path& filePath, uint32_t blockSize) {
    return asyncHash<std::tuple<uint32_t, std::vector<unsigned char>>>(filePath, blockSize,
        [] (const auto& data) {
            return std::make_tuple(diffsync::weakHash(data), diffsync::strongHash(data));
        } );
}

}

#pragma once

#include <unordered_map>
#include <tuple>
#include <experimental/filesystem>

#include "DiffSync.h"
#include "delta.pb.h"

namespace diffsync {

namespace fs = std::experimental::filesystem;

Delta
calculateDelta(const fs::path& file, uint32_t blocksize,
    std::unordered_map<WeakHash, std::tuple<StrongHash, uint32_t>> hashes);

void
applyDelta(const Delta& delta, const fs::path& oldFile,
    const fs::path& newFilePath, uint32_t blocksize);

} // namespace diffsync

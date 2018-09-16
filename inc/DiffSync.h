#pragma once

#include <string>
#include <vector>
#include <cstdint>

// Common definitions for the diffsync lib

namespace diffsync {

typedef uint32_t WeakHash;
typedef std::vector<unsigned char> StrongHash;
typedef std::tuple<WeakHash, StrongHash> HashPair;
typedef std::vector<HashPair> Hashes;

} // namespace diffsync
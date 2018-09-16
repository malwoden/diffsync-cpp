#pragma once

#include <string>
#include <vector>
#include <cstdint>

// Common definitions for the diffsync lib

namespace diffsync {

typedef uint32_t WeakHash;
typedef std::vector<unsigned char> StrongHash;
typedef std::tuple<WeakHash, StrongHash> HashPair;

// TODO: there is a problem with this as it doesn't allow for weak hash collisions.
//       each weak has can have 1..* associated strong hashes
typedef std::vector<HashPair> Hashes;

} // namespace diffsync
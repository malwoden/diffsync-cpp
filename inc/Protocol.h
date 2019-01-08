#pragma once

#include "block_hash.pb.h"

#include "DiffSync.h"

namespace diffsync {

BlockHashes encode(const HashVector& hashes);

} // namespace diffsync
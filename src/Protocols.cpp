#include "Protocol.h"


namespace diffsync{

BlockHashes encode(const Hashes& hashes) {
    BlockHashes blockHashes;
    int blockIndex = 0;

    for(auto&&[weak, strong] : hashes) {
        BlockHash* blockHash = blockHashes.add_hash();
        blockHash->set_block_index(blockIndex++);
        blockHash->set_strong_hash(&strong[0], strong.size());
        blockHash->set_weak_hash(weak);
    }

    return blockHashes;
}

} // namespace diffsync
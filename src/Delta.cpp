#include "Delta.h"

#include "Hashes.h"
#include "Files.h"
#include "delta.pb.h"

namespace diffsync {

Delta
calculateDelta(const fs::path& file, uint32_t blocksize,
    std::unordered_map<WeakHash, std::tuple<StrongHash, uint32_t>> hashes) {

    Delta delta;
    uint32_t offset = 0;
    std::vector<unsigned char> rawBytes;

    // A bad implementation follows:
    // 2. memory inefficient due to file load. Memmapping might be better
    // 3. Delta can be huge for very different files, which protocol buffers are not built for
    std::vector<unsigned char> fileBytes = readFile(file);
    bool blockFound = false;
    WeakHash weak = 0;

    while (true) {
        uint32_t end = std::min(static_cast<uint32_t>(fileBytes.size()), offset + blocksize);
        auto data = std::vector<unsigned char>(fileBytes.begin() + offset, fileBytes.begin() + end);
        if (data.size() == 0) {
            break;
        }

        if (blockFound || offset == 0) {
            weak = weakHash(data);
        } else {
            weak = rollWeakHash(weak, fileBytes[offset - 1], data.back());
        }
        blockFound = false;

        auto weakHashMatch = hashes.find(weak);
        if (weakHashMatch != hashes.end()) {
            auto[strong, index] = weakHashMatch->second;

            if (strong == strongHash(data)) {
                // 'flush' out any uncommitted raw bytes to the delta
                if (rawBytes.size() > 0) {
                    delta.add_changes()->set_raw_bytes(&rawBytes[0], rawBytes.size());
                    rawBytes.clear();
                }

                delta.add_changes()->set_block_reference(index);
                blockFound = true;
            }
        }

        if (data.size() < blocksize) {
            // this is the last block of data
            // capture any remaining unmatched block data before we add it as the final raw byte change
            if (!blockFound) {
                rawBytes.insert(rawBytes.end(), data.begin(), data.end());
            }

            if (rawBytes.size() > 0) {
                delta.add_changes()->set_raw_bytes(&rawBytes[0], rawBytes.size());
                rawBytes.clear();
            }
            break;
        }

        if (!blockFound) {
            rawBytes.push_back(data[0]);
        }

        offset += blockFound ? blocksize : 1;
    }

    return delta;
}

void
applyDelta(const Delta& delta, const fs::path& oldFile,
    const fs::path& newFilePath, uint32_t blocksize) {

    std::fstream output(newFilePath, std::ios::out | std::ios::trunc | std::ios::binary);
    if (output) {
        for (int i = 0; i < delta.changes_size(); i++) {
            const Change& change = delta.changes(i);

            if (change.Op_case() == Change::kBlockReference) {
                auto data = readBlock(oldFile, blocksize, change.block_reference() * blocksize);
                output.write(reinterpret_cast<char*>(&data[0]), data.size());
            } else if (change.Op_case() == Change::kRawBytes) {
                output.write(change.raw_bytes().data(), change.raw_bytes().size());
            }
        }
    }
}

} // namespace diffsync

#include <iostream>
#include <fstream>

#include "block_hash.pb.h"
#include "AsyncHasher.h"
#include "Protocol.h"

namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 3) {
        std::cerr << "Run like ./diffsyncrunner inputFile outputFile";
        return -1;
    }

    fs::path path(argv[1]);
    auto hashes = diffsync::asyncStrongAndWeakHash(path, 4096);

    BlockHashes blockHashes = diffsync::encode(hashes);

    std::cout << "Block count " << blockHashes.hash_size() << std::endl;

    std::fstream output(argv[2], std::ios::out | std::ios::trunc | std::ios::binary);
    if (!blockHashes.SerializeToOstream(&output)) {
      std::cerr << "Failed to write block hashes" << std::endl;
      return -1;
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
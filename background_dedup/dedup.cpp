#include <string>
#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <pHash.h>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    std::map<ulong64, std::vector<std::string> *> hash_list;

    ulong64 hash = 0;
    int status = 0;
#ifdef DEBUG
    int count = 0;
#endif

    std::string directory = argv[1];
    for (const auto & entry : fs::directory_iterator(directory)) {
#ifdef DEBUG
        count++;
        if (count > 10)
            break;
#endif
        status = ph_dct_imagehash(entry.path().c_str(), hash);
        if (status < 0) {
            std::cout << "ERROR: ph_dct_imagehash: " << status << std::endl;
            return 1;
        }
        auto hash_vec = hash_list.find(hash);
        if (hash_vec != hash_list.end()) {
            hash_vec->second->push_back(entry.path().filename().string());
        } else {
            auto temp = new std::vector<std::string>();
            temp->push_back(entry.path().filename().string());
            hash_list[hash] = temp;
        }
    }
    for (const auto & entry : hash_list) {
        if (entry.second->size() > 1) {
            std::cout << std::setw(20) << entry.first << ": ";
            bool first = true;
            for (const auto & item : *entry.second) {
                if (!first) {
                    std::cout << ", ";
                } else {
                    first = false;
                }
                std::cout << item;
            }
            std::cout << std::endl;
        }
    }
    return 0;
}

#include "../header/dir_holder.hpp"

// Static instance initialization
DirHolder * DirHolder::instance = nullptr;
const FlagHolder* DirHolder::holder = nullptr;

void DirHolder::loadFiles(void) {
    if (!this->holder->getRecursive()) {
        for (auto & entry : fs::directory_iterator(this->getPath())) {
            this->files.push_back(entry);
        }
    } else {
        for (auto & entry : fs::recursive_directory_iterator(this->getPath())) {
            this->files.push_back(entry);
        }
    }
}

void DirHolder::init(void) {
    this->folderPath = this->holder->getPath();

    // Safety check for the directory
    if (!fs::is_directory(this->folderPath)) {
        std::cout << "[-] The provided path ('" << this->folderPath << "') is not a directory!" << std::endl;
        std::exit(1);
    }

    this->loadFiles();
}

const DirHolder * DirHolder::getInstance(const FlagHolder * holder) {

    if (instance == nullptr) {
        instance = new DirHolder();
        instance->holder = holder;
        instance->init();
    }

    return instance;
}

void DirHolder::listFiles(void) const {
    for (auto & entry : this->files) {
        std::string file_name = entry.path().filename().string();

        if (!this->holder->getShowAll() && file_name[0] == '.') {
            continue;
        }

        std::cout << " ⇢ " << file_name << (entry.is_directory() ? "/ 🗁 " : "") << std::endl;
    }
}
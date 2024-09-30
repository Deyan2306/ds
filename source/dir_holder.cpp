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

// The main function that list files and determines the way that they should be listed
void DirHolder::listFiles(void) const {
    for (auto & entry : this->files) {
        std::string file_name = entry.name;

        if (!this->holder->getShowAll() && file_name[0] == '.') {
            continue;
        }

        if (this->holder->getLongInfo()) {
            std::cout << " [" << entry.getPermissionsString() << "] " 
                << entry.fileStat.st_nlink << std::setw(2) << " " 
                << (entry.pw ? entry.pw->pw_name : "unknown") << "/" 
                << (entry.gr ? entry.gr->gr_name : "unknown") << " "
                << std::setw( this->holder->getHumanReadable() ? 3 : 10 ) << (this->holder->getHumanReadable() 
                    ? (DirHolder::calculateByteFormat(entry.fileStat.st_size)) 
                    : (std::to_string(entry.fileStat.st_size))) << " "
                << "\t" << entry.mod_time << " ⇝ " 
                << file_name << (entry.isPath ? "/ 🗁 " : "") << std::endl;
     
        } else {
            std::cout << " ⇢ " << file_name << (entry.isPath ? "/ 🗁 " : "") << std::endl;
        }
    }
}

// @returns - string
// Formats bytes in a human readable way
std::string DirHolder::calculateByteFormat(unsigned long long bytes) {

    // Predefined byte formats (bigger ones would most probably overflow...)
    const unsigned long long KB = 1024;            // Kilobyte
    const unsigned long long MB = KB * 1024;       // Megabyte
    const unsigned long long GB = MB * 1024;       // Gigabyte
    const unsigned long long TB = GB * 1024;       // Terabyte (It will overflow) / TODO: Fix it

    // Holders
    double convertedValue;
    std::string unit;

    // Self explanitory..
    if (bytes >= TB) {
        convertedValue = static_cast<double>(bytes) / TB;
        unit = "TB";
    } else if (bytes >= GB) {
        convertedValue = static_cast<double>(bytes) / GB;
        unit = "GB";
    } else if (bytes >= MB) {
        convertedValue = static_cast<double>(bytes) / MB;
        unit = "MB";
    } else if (bytes >= KB) {
        convertedValue = static_cast<double>(bytes) / KB;
        unit = "KB";
    } else {
        convertedValue = static_cast<double>(bytes);
        unit = "B";
    }

    // Using stream to produce the formatted output 
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << convertedValue << " " << unit;

    return oss.str();
}
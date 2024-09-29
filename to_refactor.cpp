#include <boost/filesystem.hpp>

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

#include <iomanip>

#include <sstream>

#include <string>

#include "header/flag_holder.hpp"

namespace fs = boost::filesystem;

/**
 * `-r` for recursive call
 * `-a` for all
 * `-l` to list all 
 * 
 * ToDo's
 * 1. sorting?
 * 2. human readable formats
 * 3. refactoring...
 * 4. colors! 
 *
*/

void print_file_info(const fs::directory_entry & entry) {
    struct stat fileStat;

    if (stat(entry.path().c_str(), &fileStat) == 0) {
        // Permissions
        std::cout << "[";
        std::cout << ((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        std::cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        std::cout << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        std::cout << ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        std::cout << ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        std::cout << ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        std::cout << ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        std::cout << ((fileStat.st_mode & S_IROTH) ? "r" : "-");
        std::cout << ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        std::cout << ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        std::cout << "] ";

        // Number of links
        std::cout << std::setw(2) << fileStat.st_nlink << " ";

        // Group and owner
        struct passwd * pw = getpwuid(fileStat.st_uid);
        struct group  * gr = getgrgid(fileStat.st_gid);

        std::cout << std::setw(8) << (pw ? pw->pw_name : "unknown") << " ";
        std::cout << std::setw(8) << (gr ? gr->gr_name : "unknown") << " ";

        // Size (right-aligned)
        std::cout << std::setw(10) << fileStat.st_size << " ";

        // Last modification time (strip newline)
        char* mod_time = std::ctime(&fileStat.st_mtime);
        if (mod_time[strlen(mod_time) - 1] == '\n') {
            mod_time[strlen(mod_time) - 1] = '\0';  // Remove newline
        }
        std::cout << mod_time << " ";

        // File name
        std::cout << entry.path().filename().string() << std::endl;
    }
}

void list_directory_recursive(const fs::path & folder_path) {
    for (auto& entry : fs::recursive_directory_iterator(folder_path)) {
        std::cout << entry.path().filename().string() << std::endl;
    }
}

int main(int argc, char* argv[]) {

    const FlagHolder * holder = FlagHolder::getInstance(argc, argv);
    

    if (holder->contains("help")) {
        std::cout << holder->getDescription() << std::endl;
        return 0;
    }

    fs::path folder_path = holder->getPath();

    // Check if the directory is a path
    if (!fs::is_directory(folder_path)) {
        std::cerr << "[-] Error: " << folder_path << " is not a directory." << std::endl;
        return 1;
    }

    // Iterate the directory
    if (holder->getRecursive()) {
        list_directory_recursive(folder_path);
    } else {
        for (auto & entry : fs::directory_iterator(folder_path)) {
           std::string filename_path = entry.path().filename().string();
            if (!holder->getShowAll() && filename_path[0] == '.') {
                continue;
            }   

            if (holder->getLongInfo()) {
                print_file_info(entry);
            } else {
                if (entry.is_directory()) {

                }

                std::cout << " ⇢ " << filename_path << (entry.is_directory() ? "/ 🗁 " : "") << std::endl;
            }   
        }   
    }
    
    return 0;
}
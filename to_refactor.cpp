#include <boost/filesystem.hpp>


#include "header/flag_holder.hpp"
#include "header/dir_holder.hpp"


void print_file_info(const fs::directory_entry & entry) {
    struct stat fileStat;

    if (stat(entry.path().c_str(), &fileStat) == 0) {
        // Permissions
        std::cout << "[";
        
        std::cout << "] ";

        // Number of links
        std::cout << std::setw(2) << fileStat.st_nlink << " ";

        // Group and owner
        struct passwd * pw = getpwuid(fileStat.st_uid);
        struct group  * gr = getgrgid(fileStat.st_gid);

        std::cout << std::setw(8) << (pw ? pw->pw_name : "unknown") << " ";
        std::cout << std::setw(8) << (gr ? gr->gr_name : "unknown") << " ";
        // ==

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

int main(int argc, char* argv[]) {

    const FlagHolder * holder = FlagHolder::getInstance(argc, argv);
    const DirHolder * dir = DirHolder::getInstance(holder); 
    
    dir->listFiles();

    return 0;
}
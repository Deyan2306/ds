#include "../header/dir_file.hpp"

DirFile::DirFile(const fs::directory_entry & _entry) : entry(_entry) {
    this->name = entry.path().filename().string();
    
    if (this->entry.is_directory()) {
        this->isPath = true;
    }

    this->init();

}

void DirFile::init(void) {
    if (stat(this->entry.path().c_str(), &fileStat) == 0) {

        // Get the Group and Owner information
        this->pw = getpwuid(fileStat.st_uid);
        this->gr = getgrgid(fileStat.st_gid);

        // Get the modification time
        this->mod_time = std::ctime(&fileStat.st_mtime);

        // @attention
        // `mod_time` puts a newline character, so for formatting reasons we replace it with return char
        if (mod_time[strlen(mod_time) - 1] == '\n') {
            mod_time[strlen(mod_time) - 1] = '\0';
        }
    }
}

std::string DirFile::getPermissionsString(void) const {
    std::stringstream out;

    out << ((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    out << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    out << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    out << ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    out << ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    out << ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    out << ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    out << ((fileStat.st_mode & S_IROTH) ? "r" : "-");
    out << ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    out << ((fileStat.st_mode & S_IXOTH) ? "x" : "-");

    return out.str();
}
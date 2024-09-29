#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

#include <iostream>
#include <string>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

void print_file_info(const fs::directory_entry & entry) {
    struct stat fileStat;
    if (stat(entry.path().c_str(), &fileStat) == 0) {
        // Права
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

        // Брой линкове
        std::cout << " " << fileStat.st_nlink;

        // Собственик и група
        struct passwd *pw = getpwuid(fileStat.st_uid);
        struct group  *gr = getgrgid(fileStat.st_gid);
        std::cout << " " << (pw ? pw->pw_name : "unknown");
        std::cout << " " << (gr ? gr->gr_name : "unknown");

        // Размер
        std::cout << " " << fileStat.st_size;

        // Време на последна модификация
        std::cout << " " << std::ctime(&fileStat.st_mtime);

        // Име на файла
        std::cout << " " << entry.path().filename().string() << std::endl;
    }

}

int main(int argc, char* argv[]) {

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("path,p", po::value<std::string>()->default_value("."), "path to directory")
        ("all,a", "show the hidden files too")
        ("long,l", "pring long information about the files");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    fs::path folder_path(vm["path"].as<std::string>());

    // Check if the directory is a path
    if (!fs::is_directory(folder_path)) {
        std::cerr << "[-] Error: " << folder_path << " is not a directory." << std::endl;
        return 1;
    }

    bool show_all = vm.count("all");
    bool long_info = vm.count("long");

    // Iterate the directory
    for (auto & entry : fs::directory_iterator(folder_path)) {
        std::string filename_path = entry.path().filename().string();
        if (!show_all && filename_path[0] == '.') {
            continue;
        }

        if (long_info) {
            print_file_info(entry);
        } else {
            std::cout << filename_path << std::endl;
        }   
    }

    return 0;
}
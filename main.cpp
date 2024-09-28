#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <string>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        std::cerr << "[-] Error: You must provide a folder path!" << std::endl;
        return 1;
    }

    fs::path folder_path(argv[1]);

    // Check if the directory is a path
    if (!fs::is_directory(folder_path)) {
        std::cerr << "[-] Error: " << folder_path << " is not a directory." << std::endl;
        return 1;
    }

    // Iterate the directory
    for (auto & entry : fs::directory_iterator(folder_path)) {
        std::cout << entry.path().string() << std::endl;
    }

    return 0;
}
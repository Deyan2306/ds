#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <string>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("path,p", po::value<std::string>()->default_value("."), "path to directory");

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

    // Iterate the directory
    for (auto & entry : fs::directory_iterator(folder_path)) {
        std::cout << entry.path().string() << std::endl;
    }

    return 0;
}
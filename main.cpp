#include "header/dir_holder.hpp"

int main(int argc, char* argv[]) {

    const FlagHolder * holder = FlagHolder::getInstance(argc, argv);
    const DirHolder * dir = DirHolder::getInstance(holder); 
    
    dir->listFiles();

    return 0;
}
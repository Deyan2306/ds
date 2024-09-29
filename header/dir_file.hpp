#ifndef _DIR_FILE_H_
#define _DIR_FILE_H_

#include "imports.hpp"

class DirFile {

    public:
        struct stat fileStat;

        struct passwd * pw; // File owner
        struct group * gr;  // File group 

        char * mod_time;

        bool isPath = false;

        std::string name;
        fs::directory_entry entry;

        void init(void);

        std::string getPermissionsString(void) const;

        DirFile(const fs::directory_entry & _entry);

};

#endif
#ifndef _DIR_FILE_H_
#define _DIR_FILE_H_

#include "imports.hpp"

// TODO: No getters?
class DirFile {

    private:
        bool isPath = false;

    public:
        struct stat fileStat;

        struct passwd * pw; // File owner
        struct group * gr;  // File group 

        char * mod_time;

        std::string name;
        fs::directory_entry entry;

        void init(void);
        std::string getPermissionsString(void) const;

        // Constructors and Destructors
        DirFile(const fs::directory_entry & _entry);

        // Accessors
        bool isDirectory(void) const { return this->isPath; }

};

#endif
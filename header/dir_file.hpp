#ifndef _DIR_FILE_H_
#define _DIR_FILE_H_

#include "imports.hpp"

// TODO: No getters?
class DirFile {

    private:
        // Reformat the code so it uses some encapsulation

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

        // Constructors and Destructors
        DirFile(const fs::directory_entry & _entry);

};

#endif
#ifndef _DIR_HOLDER_H_
#define _DIR_HOLDER_H_

#include <boost/filesystem.hpp>

#include <vector>

#include "flag_holder.hpp"

namespace fs = boost::filesystem;

class DirHolder {

    private:
        static DirHolder * instance;
        static const FlagHolder * holder;

        // Path
        fs::path folderPath;
        std::vector<fs::directory_entry> files;

        DirHolder() { }

        void init(void);
        void loadFiles(void);

    public:
        // No need for copy constructor as this class is `Singleton`
        DirHolder(const DirHolder & other) = delete;

        // Accessors
        static const DirHolder * getInstance(const FlagHolder * holder);

        const fs::path & getPath(void) const { return folderPath; }
        
        void listFiles(void) const;


};

#endif
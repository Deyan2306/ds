#ifndef _FLAG_HOLDER_H_
#define _FLAG_HOLDER_H_

#include "dir_file.hpp"

class FlagHolder {

    private:
        static FlagHolder * instance;

        // Private constructor for easy instance initialization
        FlagHolder(int argc, char * argv[]) 
            :   argc(argc), 
                argv(argv), 
                desc("Allowed options") {
            // == Description options
            desc.add_options()
                ("help,h", "produce help message")
                ("path,p", po::value<std::string>()->default_value("."), "path to directory")
                ("all,a", "show the hidden files too")
                ("long,l", "pring long information about the files")
                ("recursive,r", "recursive iteration over the folder");
        }

        // Arguments
        int argc;
        char ** argv;

        // Initializors
        void init(void);
        void setFlagValues(void);

        // == Programming Options (specific) ==
        static po::variables_map vm;
        po::options_description desc;

        // Flag Options
        bool show_all;
        bool long_info;
        bool recursive;

        std::string path;

    public:
        // @attention 
        // Constructor has been removed since this is a `Singleton`
        FlagHolder(const FlagHolder & copy) = delete;

        // Holder accessors
        static const FlagHolder * getInstance(int argc, char * argv[]);
        static bool contains(const std::string & value);

        // Flag accessors
        bool getShowAll(void)   const  { return show_all;  }
        bool getLongInfo(void)  const  { return long_info; }
        bool getRecursive(void) const  { return recursive; }

        std::string getPath(void) const { return path;  }

        const po::options_description getDescription(void) const { return desc; }

};

#endif
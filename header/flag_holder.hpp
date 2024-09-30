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
                ("recursive,r", "recursive iteration over the folder")
                ("human_readable,m", "get a human-readable form of the size string")
                ("directories_only,d", "display only the directories")
                ("no_icons,x", "do not display icons for the directories");
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

        bool human_readable;
        bool directories_only;
        bool no_icons;

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
        bool getNoIcons(void)   const  { return no_icons;  }

        bool getHumanReadable(void)     const { return human_readable; }
        bool getDirectoriesOnly(void)   const { return directories_only; }

        std::string getPath(void) const { return path;  }

        const po::options_description getDescription(void) const { return desc; }

};

#endif
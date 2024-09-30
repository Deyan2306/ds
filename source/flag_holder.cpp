#include "../header/flag_holder.hpp"

// Static instance initialization
FlagHolder * FlagHolder::instance = nullptr;
po::variables_map FlagHolder::vm;

void FlagHolder::setFlagValues(void) {
    this->show_all = this->contains("all");
    this->long_info = this->contains("long");
    this->recursive = this->contains("recursive");
    this->human_readable = this->contains("human_readable");
    this->directories_only = this->contains("directories_only");
    this->no_icons = this->contains("no_icons");
}

void FlagHolder::init(void) {
    // Parse the argumets
    po::store(po::parse_command_line(this->argc, this->argv, this->desc), this->vm);
    po::notify(this->vm);

    // @attention
    // There is no need to keep initializing or running the program after the help command..
    if (this->contains("help")) {
        std::cout << this->desc << std::endl;
        std::exit(0);
    }

    // Set flag values
    this->setFlagValues();

    // Set path value
    this->path = this->vm["path"].as<std::string>();
}

const FlagHolder * FlagHolder::getInstance(int argc, char * argv[]) {

    // Safety check (init if there is no instance)
    if (instance == nullptr) {
        instance = new FlagHolder(argc, argv);
        instance->init();
    } 
    
    return instance;
}

bool FlagHolder::contains(const std::string & value) {
    return vm.count(value);
}

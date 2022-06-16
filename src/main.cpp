#include <iostream>
#include <cstring>
#include "zeta.h"

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Usage: zeta <command>" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(!strcmp(argv[1], "--help")){
        std::cout << "Usage: zeta [--help] [--version] [init [language]] [build] [clean]" << std::endl;
        return 0;
    } else if (!strcmp(argv[1], "--version")){
        std::cout << "Zeta C/C++ Helper Tool\nVersion: 0.0.1" << std::endl;
        return 0;
    } else if (!strcmp(argv[1], "init")){
        if(argc < 4){
            std::cout << "Usage: zeta init <name> <language>" << std::endl;
            exit(EXIT_FAILURE);
        }
        zeta::init(argv[2], argv[3]);
    } else if (!strcmp(argv[1], "build")){
        zeta::build();
    } else if (!strcmp(argv[1], "clean")){
        zeta::clean();
    } else {
        std::cout << "Usage: zeta [--help] [--version] [init [language]] [build] [clean]" << std::endl;
    }
    return 0;
}
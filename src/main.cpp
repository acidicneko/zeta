#include <iostream>
#include <fstream>
#include <cstring>
#include "utils.h"
#include "zeta.h"

void help(){
    std::cout << "Usage: zeta\n" 
              << "--help: prints this menu\n"
              << "--version: prints version info\n"
              << "init [target] [language]: initialise zeta for this directory\n"
              << "build: build givn project\n"
              << "clean: clean target and object files\n"
              << "all: clean and build project\n"
              << "update: get the latest release of Zeta\n"
              << "stat: print workspace information" << std::endl;
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Usage: zeta <command>" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(!strcmp(argv[1], "--help")){
        help();
        return 0;
    } else if (!strcmp(argv[1], "--version")){
        std::cout << "Zeta C/C++ Helper Tool\nVersion: 1.4.0\n";
        std::string last_commit_loc = GetEnv("HOME") + "/.config/zeta/last_commit";
        if(!fileExist(last_commit_loc)){
            std::cout << "Failed to retrieve commit ID." << std::endl;
        } else {
            std::ifstream last_commit(last_commit_loc);
            std::string content;
            std::getline(last_commit, content);
            last_commit.close();
            replace(content, "LAST_HASH=", "");
            std::cout << "Commit ID: " << content << std::endl;
        }
        std::cout << "Distributed under GNU GPLv3\n"
                  << "Copyright Ayush Yadav(acidicneko) 2022"<< std::endl;
        return 0;
    } else if (!strcmp(argv[1], "init")){
        if(argc < 4){
            std::cout << "Usage: zeta init <name> <language>" << std::endl;
            exit(EXIT_FAILURE);
        }
        zeta::init(argv[2], argv[3], false);
    } else if (!strcmp(argv[1], "force-init")){
        if(argc < 4){
            std::cout << "Usage: zeta force-init <name> <language>" << std::endl;
            exit(EXIT_FAILURE);
        }
        zeta::init(argv[2], argv[3], true);
    } else if (!strcmp(argv[1], "build")){
        zeta::build();
    } else if (!strcmp(argv[1], "clean")){
        zeta::clean();
    } else if (!strcmp(argv[1], "stat")){
        zeta::stat();
    } else if (!strcmp(argv[1], "all")){
        std::cout << "Cleaning and Building..." << std::endl;
        zeta::clean();
        zeta::build();
    } else if(!strcmp(argv[1], "update")){
        zeta::update();
    } else {
        std::cout << "unknown command: " << argv[1] << std::endl;
        help();
    }
    return 0;
}
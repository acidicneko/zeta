#include "zeta.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "utils.h"
#include "ini.h"

void zeta::init(std::string name, std::string language, bool force) {
    if (fileExist(".zeta/config.ini")){
        std::cout << "Zeta has already been initialized!" << std::endl;
        return;
    } else if(fileExist("Makefile") && force == false){
        std::cout << "Makefile already exists." << std::endl
                    << "Are you sure if this folder is empty?" << std::endl;
        std::cout << "\nZeta has been initialized forcefully." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Initializing Zeta...\n" << std::endl;
    std::cout << "Target: " << name << std::endl;
    std::cout << "Language: " << language << std::endl;
    Execute("mkdir .zeta");
    Execute("touch .zeta/config.ini");
    mINI::INIFile file(".zeta/config.ini");
    mINI::INIStructure ini;
    ini["general"]["language"] = language;
    ini["general"]["build"] = "make";
    ini["general"]["clean"] = "make clean";
    ini["general"]["target"] = name;
    file.generate(ini);
    zeta::initGit();
    if(!force){
        Execute("mkdir -p src/include");
        Execute("mkdir build");
        std::cout << "Writing Makefile..." << std::endl;
        zeta::writeMakefile(name);
        std::cout << "\nZeta has been initialized." << std::endl;
    }
}

void zeta::writeMakefile(std::string target){
    mINI::INIFile file(".zeta/config.ini");
    mINI::INIStructure ini;
    file.read(ini);
    std::cout << "Looking for Makefile templates for: " << ini["general"]["language"] << std::endl;
    std::string home = GetEnv("HOME");
    std::string templatePath = home + "/.config/zeta/templates/" + ini["general"]["language"] + "-Makefile";
    if(!fileExist(templatePath)){
        std::cout << "Could not find template file for " << ini["general"]["language"] 
                    << "\nInitialisation failed. Exiting..." << std::endl;
        Execute("rm -rf .zeta");
        Execute("rm -rf build");
        Execute("rm -rf src");
        exit(EXIT_FAILURE);
    }
    Execute("cp " + templatePath + " ./Makefile");
    std::ifstream makefileIn("Makefile");
    std::string makefileContent = getfile(makefileIn);
    makefileIn.close();
    replace(makefileContent, "target", target);
    std::ofstream makefileOut("Makefile");
    makefileOut << makefileContent;
    makefileOut.close();
}

void zeta::build(){
    zeta::checkInit();
    std::cout << "Building..." << std::endl;
    mINI::INIFile file(".zeta/config.ini");
    mINI::INIStructure ini;
    file.read(ini);
    Execute(ini["general"]["build"]);
}

void zeta::clean(){
    zeta::checkInit();
    std::cout << "Cleaning..." << std::endl;
    mINI::INIFile file(".zeta/config.ini");
    mINI::INIStructure ini;
    file.read(ini);
    Execute(ini["general"]["clean"]);
}

void zeta::stat(){
    zeta::checkInit();
    mINI::INIFile file(".zeta/config.ini");
    mINI::INIStructure ini;
    file.read(ini);
    std::cout << "Target Name: " << ini["general"]["target"] << "\n"
              << "Language: " << ini["general"]["language"] << "\n"
              << "Build: " << ini["general"]["build"] << "\n"
              << "Clean: " << ini["general"]["clean"] << std::endl;
}

void zeta::initGit(){
    if (folderExist(".git/")){
        std::cout << "Git has already been initialised." << std::endl;
        return;
    }
    std::string choice;
    std::cout << "Initialize git?[y/n]: ";
    std::cin >> choice;
    if(choice == "y"){
        Execute("git init");
    } else {
        return;
    }
}

void zeta::checkInit(){
    if(!fileExist(".zeta/config.ini")){
        std::cout << "Zeta hasn't been initialized for current directory." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void zeta::update(){
    std::string updateScript = GetEnv("HOME") + "/.config/zeta/update.sh";
    if(!fileExist(updateScript)){
        std::cout << "Update script not found.\n"
                  << "Script Location: " << updateScript
                  << "\nGrab the script from https://github.com/acidicneko/zeta/blob/main/assets/update.sh"
                  << std::endl; 
        exit(EXIT_FAILURE);
    }
    Execute(updateScript);
}
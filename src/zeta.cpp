#include "zeta.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "utils.h"
#include "ini.h"

void zeta::init(std::string name, std::string language) {
    if (fileExist(".zeta/config.ini")){
        std::cout << "Zeta has already been initialised!" << std::endl;
        return;
    } else if(fileExist("Makefile")){
        std::cout << "Makefile already exists." << std::endl
                    << "Are you sure if this folder is empty?" << std::endl;
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

    Execute("mkdir -p src/include");
    Execute("mkdir build");
    std::cout << "Writing Makefile..." << std::endl;
    zeta::writeMakefile(name);
    std::cout << "\nZeta has been initialized." << std::endl;
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
    std::cout << "Building..." << std::endl;
    Execute("make");
}

void zeta::clean(){
    std::cout << "Cleaning..." << std::endl;
    Execute("make clean");
}
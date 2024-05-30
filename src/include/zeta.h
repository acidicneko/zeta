#pragma once

#include <string>

namespace zeta {
    void init(std::string name, std::string language, bool force);
    void writeMakefile(std::string target);
    void build();
    void clean();
    void stat();
    void initGit();
    void checkInit();
}
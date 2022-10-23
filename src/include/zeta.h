#pragma once

#include <string>

namespace zeta {
    void init(std::string name, std::string language);
    void writeMakefile(std::string target);
    void build();
    void clean();
    void stat();
    void checkInit();
}
#include <Utilities/FileSystem.h>
#include "FileSystem.h"

std::string FileSystem::get_file_content(const char *filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if(in)
    {
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();
        return(contents.str());
    }
    else
    {
        throw(errno);
    }
}
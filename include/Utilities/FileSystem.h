#ifndef __FILESYSTEM_H__
    #define __FILESYSTEM_H__

    #include <fstream>
    #include <sstream>
    #include <string>

    class FileSystem
    {
        public:
            static std::string get_file_content(const char* filename);
    };
#endif
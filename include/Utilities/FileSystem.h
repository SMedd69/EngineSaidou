#ifndef __FILESYSTEM_H__
    #define __FILESYSTEM_H__

    #include <fstream>
    #include <sstream>
    #include <ImGUI/ImGuiFileDialog.h>
    #include <string>

    class FileSystem
    {
        public:
            static std::string get_file_content(std::string filename);

            static std::string OpenFile();
            static std::string SaveFile();
    };
#endif
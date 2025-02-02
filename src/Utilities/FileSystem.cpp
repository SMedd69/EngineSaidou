#include <Utilities/FileSystem.h>
#include "FileSystem.h"

std::string FileSystem::get_file_content(std::string filename)
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

std::string FileSystem::OpenFile()
{
    std::string filePath;

    ImGuiFileDialog::Instance()->OpenDialog("ChooseFile", "Open file", ".lua,.py");
    if(ImGuiFileDialog::Instance()->Display("ChooseFile"))
    {
        if(ImGuiFileDialog::Instance()->IsOk())
        {
            filePath = ImGuiFileDialog::Instance()->GetFilePathName();
        }
        ImGuiFileDialog::Instance()->Close();
    }

    return filePath;
}

std::string FileSystem::SaveFile()
{
    std::string filePath;

    ImGuiFileDialog::Instance()->OpenDialog("SaveFile", "Enregistrer sous..", ".lua,.py");
    if(ImGuiFileDialog::Instance()->Display("SaveFile"))
    {
        if(ImGuiFileDialog::Instance()->IsOk())
        {
            filePath = ImGuiFileDialog::Instance()->GetFilePathName();
        }
        ImGuiFileDialog::Instance()->Close();
    }

    return filePath;
}

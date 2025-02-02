#ifndef SCRIPT_EDITOR_H
#define SCRIPT_EDITOR_H

#include "TextEditor.h"
#include <Utilities/FileSystem.h>
#include <string>

class ScriptEditor {
public:
    TextEditor editor;
    std::string currentFile;

    ScriptEditor();
    void Render();
};

#endif
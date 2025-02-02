#include "ScriptEditor.h"
#include "imgui.h"
#include <fstream>
#include <iostream>

ScriptEditor::ScriptEditor() {
    editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua()); // Coloration syntaxique Lua
}

void ScriptEditor::Render() {
    ImGui::Begin("Éditeur de Code");

    // Boutons : Ouvrir et Enregistrer
    if (ImGui::Button("Ouvrir")) {
        std::string filePath = FileSystem::OpenFile();
        if (!filePath.empty()) {
            std::ifstream file(filePath);
            if (file.is_open()) {
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                editor.SetText(content);
                currentFile = filePath;
                file.close();
            }
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Enregistrer")) {
        if (currentFile.empty()) {
            currentFile = FileSystem::SaveFile();
        }
        if (!currentFile.empty()) {
            std::ofstream file(currentFile);
            if (file.is_open()) {
                file << editor.GetText();
                file.close();
            }
        }
    }

    ImGui::SameLine();
    
    // Bouton Exécuter
    if (ImGui::Button("Exécuter")) {
        std::string script = editor.GetText();
        // ScriptingEngine::ExecuteLuaScript(script);
        std::cout << script << std::endl;
    }

    ImGui::SameLine();

    // Bouton Exécuter Python
    if (ImGui::Button("Exécuter Python")) {
        std::string script = editor.GetText();
        std::cout << script << std::endl;
        // PythonBindings::ExecutePythonScript(script);
    }

    // Affichage de l'éditeur de texte
    editor.Render("TextEditor");

    ImGui::End();
}

#include "TextEditor.h"
#include "imgui.h"
#include <iostream>

class ScriptEditor {
public:
    TextEditor editor;

    ScriptEditor() {
        editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua()); // Syntaxe pour Lua
        editor.SetText("-- Écrivez votre script ici\nprint('Hello from Lua!')");
    }

    void Render() {
        ImGui::Begin("Éditeur de Code");

        // Ajoute un bouton pour exécuter le script
        if (ImGui::Button("Exécuter")) {
            std::string script = editor.GetText();
            std::cout << "Script exécuté : \n" << script << std::endl;
            // Ici, appelez votre moteur de script pour exécuter le code Lua/Python
        }

        // Afficher l'éditeur de texte
        editor.Render("TextEditor");

        ImGui::End();
    }
};

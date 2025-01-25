#ifndef COLOR_H
#define COLOR_H

#include <Math/Vector4.h>

class Color {
public:
    Vector4 color;

    // Constructeurs
    Color(float r, float g, float b, float a = 1.0f) : color(Vector4(r, g, b, a)) {}

    // Méthode statique pour des couleurs prédéfinies
    static Color Red() { return Color(1.0f, 0.0f, 0.0f); }
    static Color Green() { return Color(0.0f, 1.0f, 0.0f); }
    static Color Blue() { return Color(0.0f, 0.0f, 1.0f); }
    static Color Yellow() { return Color(1.0f, 1.0f, 0.0f); }
    static Color Cyan() { return Color(0.0f, 1.0f, 1.0f); }
    static Color Magenta() { return Color(1.0f, 0.0f, 1.0f); }
    static Color White() { return Color(1.0f, 1.0f, 1.0f); }
    static Color Black() { return Color(0.0f, 0.0f, 0.0f); }
    static Color Gray() { return Color(0.5f, 0.5f, 0.5f); }
    static Color Orange() { return Color(1.0f, 0.65f, 0.0f); }
    static Color Lavender() { return Color(0.9f, 0.88f, 0.98f); }
    static Color Mint() { return Color(0.88f, 0.95f, 0.88f); }
    static Color Beige() { return Color(0.96f, 0.94f, 0.88f); }
    static Color SkyBlue() { return Color(0.53f, 0.81f, 0.98f); }

    // Conversion en Vector4
    Vector4 ToVector4() const {
        return color;
    }

    // Méthode pour accéder aux composantes
    float GetR() const { return color.m_x; }
    float GetG() const { return color.m_y; }
    float GetB() const { return color.m_z; }
    float GetA() const { return color.m_w; }
};

#endif // COLOR_H

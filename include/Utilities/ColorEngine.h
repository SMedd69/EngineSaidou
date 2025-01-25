#ifndef COLOR_H
#define COLOR_H

#include <Math/Vector4.h>

class ColorEngine {
public:
    Vector4 color;

    // Constructeurs
    ColorEngine(float r, float g, float b, float a = 1.0f) : color(Vector4(r, g, b, a)) {}

    // Méthode statique pour des couleurs prédéfinies
    static ColorEngine Red() { return ColorEngine(1.0f, 0.0f, 0.0f); }
    static ColorEngine Green() { return ColorEngine(0.0f, 1.0f, 0.0f); }
    static ColorEngine Blue() { return ColorEngine(0.0f, 0.0f, 1.0f); }
    static ColorEngine Yellow() { return ColorEngine(1.0f, 1.0f, 0.0f); }
    static ColorEngine Cyan() { return ColorEngine(0.0f, 1.0f, 1.0f); }
    static ColorEngine Magenta() { return ColorEngine(1.0f, 0.0f, 1.0f); }
    static ColorEngine White() { return ColorEngine(1.0f, 1.0f, 1.0f); }
    static ColorEngine Black() { return ColorEngine(0.0f, 0.0f, 0.0f); }
    static ColorEngine Gray() { return ColorEngine(0.5f, 0.5f, 0.5f); }
    static ColorEngine Orange() { return ColorEngine(1.0f, 0.65f, 0.0f); }
    static ColorEngine Lavender() { return ColorEngine(0.9f, 0.88f, 0.98f); }
    static ColorEngine Mint() { return ColorEngine(0.88f, 0.95f, 0.88f); }
    static ColorEngine Beige() { return ColorEngine(0.96f, 0.94f, 0.88f); }
    static ColorEngine SkyBlue() { return ColorEngine(0.53f, 0.81f, 0.98f); }

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

#include <Math/Mathf.h>

const float Mathf::PI = 3.14159265358979323846f;
const float Mathf::RadToDeg = 57.2957795131f;
const float Mathf::DegToRad = 0.01745329252f;
const float Mathf::Epsilon7 = 1e-7f;
const float Mathf::Epsilon8 = 1e-8f;

float Mathf::Clamp(float value, float min, float max)
{
	if (value <= min)
		value = min;

	if (value >= max)
		value = max;

	return value;
}

// Loops the value t, so that it is never larger than length and never smaller than 0.
float Mathf::Repeat(float t, float length)
{
	return Clamp(t - std::floorf(t / length) * length, 0.0f, length);
}

float Mathf::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

// PingPongs the value t, so that it is never larger than length and never smaller than 0.
float Mathf::PingPong(float t, float length)
{
	t = Repeat(t, length * 2.0f);
	return length - std::abs(t - length);
}

float Mathf::PerlinNoise(float x, float y)
{
	int X = (int)std::floor(x) & 255;
	int Y = (int)std::floor(y) & 255;

	x -= std::floor(x);
	y -= std::floor(y);

	float u = Fade(x);
	float v = Fade(y);

	static const int permutation[] = { 151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
                      140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
                      247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
                       57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
                       74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
                       60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
                       65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
                      200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
                       52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
                      207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
                      119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
                      129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
                      218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
                       81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
                      184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
                      222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180 };

	// Définir p
	static int p[512];

	for (int i = 0; i < 256; i++)
	{
		p[i] = permutation[i];
		p[i + 256] = permutation[i];
	}
	

	int A = p[X] + Y;
	int AA = p[A];
	int AB = p[A + 1];
	int B = p[X + 1] + Y;
	int BA = p[B];
	int BB = p[B + 1];

	return Lerp(v, Lerp(u, Grad(p[AA], x, y), Grad(p[BA], x - 1, y)), Lerp(u, Grad(p[AB], x, y - 1), Grad(p[BB], x - 1, y - 1)));
}

float Mathf::Grad(int hash, float x, float y)
{
	int h = hash & 7;
	float u = h < 4 ? x : y;
	float v = h < 4 ? y : x;

	return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v);
}

float Mathf::Fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}
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

	// Définir p
	int p[512];

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
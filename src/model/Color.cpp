#include "Color.hpp"


using namespace gen;



Color::Color(int red, int green, int blue, int alpha)
	: red(red), green(green), blue(blue), alpha(alpha)
{}

void Color::copyFrom(std::unique_ptr<Color> other)
{
	red = other->red;
	green = other->green;
	blue = other->blue;
	alpha = other->alpha;
}
	

std::unique_ptr<Color> Color::newColor(float red, float green, float blue, float alpha)
{
	return std::make_unique<Color>(red, green, blue, alpha);
}

Color Color::emptyColor() {
	return {0, 0, 0, 0};
}
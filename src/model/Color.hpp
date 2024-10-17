#pragma once

#include <memory>



namespace gen
{

	class Color
	{
	public:
		float red, green, blue, alpha;

		Color(int, int, int, int);
		void copyFrom(std::unique_ptr<Color>);
		
		static std::unique_ptr<Color> newColor(float, float, float, float);
		static Color emptyColor();
	};

	

}
#pragma once

#include "Model.h"
#include "Color.hpp"



namespace gen
{

	class ColoredModel : public Model
	{
	private:
		Color color;

		static ColoredModel models[5];
		static unsigned int lastFreeIndex;

		ColoredModel();

	public:
		void addColor(std::unique_ptr<Color>);
		Color* getColor();

		static ColoredModel* newModel(std::unique_ptr<Transform>, std::unique_ptr<Mesh>, std::unique_ptr<Color>);
		static ColoredModel* modelsArray();
		static unsigned int modelsCount();

	};

}
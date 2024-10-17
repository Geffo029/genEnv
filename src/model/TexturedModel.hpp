#pragma once

#include "Model.h"
#include "Texture.h"



namespace gen
{

	class TexturedModel : public Model
	{
	private:
		Texture texture;

		static TexturedModel models[5];
		static unsigned int lastFreeIndex;

		TexturedModel();

	public:
		void addTexture(std::unique_ptr<Texture>);
		Texture* getTexture();

		static TexturedModel* newModel(std::unique_ptr<Transform>, std::unique_ptr<Mesh>, std::unique_ptr<Texture>);
		static TexturedModel* modelsArray();
		static unsigned int modelsCount();

	};

}
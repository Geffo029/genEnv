#pragma once

#include "components/Mesh.h"
#include "components/Texture.h"
#include "components/Transform.h"
#include <memory>



namespace gen
{


	class GuiElement
	{
	
	private:
		bool empty;
		Transform transform; //TODO: cambiare in GuiTransform (x,y - x,y,z,w - x,y)
		Mesh mesh;
		Texture texture;

		static GuiElement elementsQueue[5];
		static unsigned int lastFreeIndex;

		GuiElement();

	public:
		static GuiElement* newGuiElement(std::unique_ptr<Transform>, std::unique_ptr<Mesh>, std::unique_ptr<Texture>);
		static GuiElement* getElementsQueue();
		static unsigned int getElementsCount();

	};


}
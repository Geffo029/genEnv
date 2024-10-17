#pragma once

#include <vector>



namespace gen
{


	class Entity
	{
	
	private:
		int ID;
		unsigned int modelIndex; // TODO: cambiare i Component in un generico array di component. Ma il Model è solo un indice quindi como far?? 

		std::vector<int> components;

		static Entity entityArray[5];
		static unsigned int lastFreeIndex;

		Entity(int);

	public:
		Entity* newEntity();
		template <typename Type, typename... Args> Type* addComponent(Args&&...);
	};


}

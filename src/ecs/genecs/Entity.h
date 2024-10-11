#pragma once
#include "Model.h"


namespace gen {


	class Entity {
	private:
		unsigned int ID;
		unsigned int modelIndex; // TODO: cambiare i Component in un generico array di component. Ma il Model è solo un indice quindi como far?? 
	
	public:
		// Entity(Moed);
		void addModel();
	};


} // namespace gen

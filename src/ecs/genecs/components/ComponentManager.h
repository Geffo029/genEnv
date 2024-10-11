#pragma once
#include "Model.h"
#include "VAO.h" //TODO: teribbile non dovrebbe essere così forse


namespace gen {
	

	class ComponentManager {
	private:
	public:
		ComponentManager(/* args */);

		Model createModel(Transform&&, Mesh&&);
	};

	Model ComponentManager::createModel(Transform&& transform, Mesh&& mesh) {
		
	}
	
	ComponentManager::ComponentManager(/* args */)
	{
	}

	// namespace ComponentManager {
		
	// 	Model newModel(VAO);

	// } // namespace ComponentManager



} // namespace gen

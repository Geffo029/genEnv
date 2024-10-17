#include "Entity.h"
#include <utility>
#include <memory>


using namespace gen;


Entity* Entity::newEntity()
{
	Entity *currentEntity = &entityArray[lastFreeIndex];
	lastFreeIndex++;
	return currentEntity;
}

template <typename Type, typename... Args> Type* Entity::addComponent(Args&&... args) {
	Type *component = new Type() ;
	std::unique_ptr<Type> cacca = std::make_unique<Type>(std::forward<Args>(args)...);
	return component;
}
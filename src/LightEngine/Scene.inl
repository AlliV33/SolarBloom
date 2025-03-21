	#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"

template<typename T>
T* Scene::CreateEntity(sf::Vector2f size, const sf::Color& color, int mDrawPriority)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->Initialize(size, color, mDrawPriority);
	
	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}
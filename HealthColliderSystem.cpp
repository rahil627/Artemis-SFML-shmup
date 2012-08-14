#include "HealthColliderSystem.h"

HealthColliderSystem::HealthColliderSystem()
{
}

HealthColliderSystem::~HealthColliderSystem()
{
}

void HealthColliderSystem::initialize()
{
	this->colliderMapper.init(*world);
	this->healthMapper.init(*world);
}

void HealthColliderSystem::processEntity(artemis::Entity& e)
{
	ColliderComponent& collider = *colliderMapper.get(e);
	
	if(collider.contact == nullptr) return; // Screw you, I'm going home.
	
	if(collider.collidionsId == ColliderComponent::BULLET){
		artemis::Entity& collidedEnt = *collider.contact;
		
		//deal damage here
		
		collidedEnt.remove();
	}
	
	
} 


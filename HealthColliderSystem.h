#ifndef HEALTHCOLLIDERSYSTEM_H
#define HEALTHCOLLIDERSYSTEM_H

#include "EntityProcessingSystem.h" // Base class: EntityProcessingSystem.h
#include "ComponentMapper.h"
#include "HealthComponent.h"
#include "ColliderSystem.h"

class HealthColliderSystem : public artemis::EntityProcessingSystem
{
private:
	artemis::ComponentMapper<HealthComponent> healthMapper;
	artemis::ComponentMapper<ColliderComponent> colliderMapper;
protected:
	 
	virtual void processEntity(artemis::Entity& e);
	virtual void initialize();
	
public:
	HealthColliderSystem();
	virtual ~HealthColliderSystem();

};

#endif // HEALTHCOLLIDERSYSTEM_H

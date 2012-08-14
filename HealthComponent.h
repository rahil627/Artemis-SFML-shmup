#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "Component.h"

class HealthComponent : public artemis::Component{
	
public:

	int health;
	int maxHealth;
	
	HealthComponent(int health, int maxHealth){
		this->health = health;
		this->maxHealth = maxHealth;
	}
};

#endif
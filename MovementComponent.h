#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "Component.h"

class MovementComponent : public artemis::Component{
public:
	float velocityX;
	float velocityY;
	
	MovementComponent(float velocityX, float velocityY){
		this->velocityX = velocityX;
		this->velocityY = velocityY;
	}
};

class PositionComponent : public artemis::Component{
	
	
public:
	float posX;
	float posY;
	PositionComponent(float posX, float posY){
		this->posX = posX;
		this->posY = posY;
	}
};


#endif // $(Guard token)

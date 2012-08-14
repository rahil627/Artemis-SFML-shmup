#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "Component.h"
#include "Vector2D.h"

class VelocityComponent : public artemis::Component{
public:
	
	Vector2D velocity;
	
	VelocityComponent(float velocityX, float velocityY)  
	: velocity(velocityX,velocityY){}
};

class PositionComponent : public artemis::Component{
	
	
public:
	
	Vector2D position;
	
	PositionComponent(float posX, float posY) 
	: position(posX,posY){}
};


#endif // $(Guard token)

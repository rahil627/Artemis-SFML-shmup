#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H


#include "EntityProcessingSystem.h"
#include "MovementComponent.h"
#include "ComponentMapper.h"
#include <stdlib.h>//needs these three lines


class MovementSystem : public artemis::EntityProcessingSystem {

	private:
		artemis::ComponentMapper<VelocityComponent>  velocityMapper;
		artemis::ComponentMapper<PositionComponent>  positionMapper;

	public:
		MovementSystem() {
			setComponentTypes<VelocityComponent,PositionComponent>();
		};

		virtual void begin(){
			//system("cls");
			//std::cout << "Starting MovementSystem======================" <<  std::endl; 
		}

		virtual void end(){
				
			//std::cout << "Ending MovementSystem======================" <<  std::endl;
		}

		virtual void initialize() {
			velocityMapper.init(*world);
			positionMapper.init(*world);
		};

		virtual void processEntity(artemis::Entity &e) {
			
			PositionComponent & p = *positionMapper.get(e);
			VelocityComponent & v = *velocityMapper.get(e);

			p.position.x += v.velocity.x * world->getDelta();
			p.position.y += v.velocity.y * world->getDelta();
			
		};
};


#endif // $(Guard token)

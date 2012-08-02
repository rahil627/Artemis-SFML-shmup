#ifndef SPRITE_SYSTEM_H
#define SPRITE_SYSTEM_H

#include "EntityProcessingSystem.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include <SFML/Window.hpp>
#include "Entity.h"


class SpriteSystem : public artemis::EntityProcessingSystem {

	private:
		sf::RenderWindow * rWindow;
		artemis::ComponentMapper<SpriteComponent> spriteMapper;
		artemis::ComponentMapper<PositionComponent>  positionMapper;

	public:
		SpriteSystem(sf::RenderWindow& renderWindow) {
			rWindow = &renderWindow;
			setComponentTypes<SpriteComponent,PositionComponent>();
		};

		virtual void begin() {
			//system("cls");
			//std::cout << "Starting Starting Sprite Render======================" <<  std::endl;
		}

		virtual void end() {

			//std::cout << "Ending Ending Sprite Render======================" <<  std::endl;
		}

		virtual void initialize() {
			spriteMapper.init(*world);
			positionMapper.init(*world);
		};

		virtual void processEntity(artemis::Entity &e) {

			PositionComponent & p = *positionMapper.get(e);
			sf::Sprite & s = spriteMapper.get(e)->sprite;
			
			s.setPosition(p.posX,p.posY);
			rWindow->draw(s);
			
			if(s.getPosition().x > 900 || s.getPosition().y > 900) {
				e.remove();
			}
			
		};
};

#endif // $(Guard token)

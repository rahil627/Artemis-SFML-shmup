#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SystemManager.h"
#include "World.h"
#include "EntityManager.h"
#include "MovementSystem.h"
#include "SpriteComponent.h"
#include "SpriteSystem.h"
#include "PlayerJoySystem.h"
#include "ColliderSystem.h"
#include "Entity.h"
#include "TextureManager.h"
#include "HealthComponent.h"
#include "HealthColliderSystem.h"
#include "EntityFactory.h"

int main(int argc, char **argv) {
	
	sf::RenderWindow window(sf::VideoMode(800, 600,32), "Artemis Power");
	TextureManager tx;
	TextureManager::getInstance().addSearchPath("assets/");
	
	artemis::World * world  = new artemis::World();
	artemis::SystemManager * sm = world->getSystemManager();
	//artemis::EntityManager * em = world->getEntityManager();
	
	MovementSystem 		 &movsys 		= (MovementSystem&)		 sm->setSystem(new MovementSystem());
	SpriteSystem 		 &spritesys 	= (SpriteSystem&)		 sm->setSystem(new SpriteSystem(window));
	PlayerJoySystem 	 &playerJoy 	= (PlayerJoySystem&)	 sm->setSystem(new PlayerJoySystem());
	ColliderSystem 		 &collider 		= (ColliderSystem&)		 sm->setSystem(new ColliderSystem(800,600,100));
	HealthColliderSystem &healthCollider= (HealthColliderSystem&)sm->setSystem(new HealthColliderSystem());
	
	sm->initializeAll();
	
	for(int i=0; i< 2; i++)
	{
		EntityFactory::Instance()->createPlayer(*world,i);
	}
	
	sf::Clock deltaClock;
	sf::Time dt;

	window.setFramerateLimit(60);
	
	// Start the game loop
	while (window.isOpen()) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
			//break;
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		world->loopStart();
		playerJoy.process();
		movsys.process();
		collider.process();
		healthCollider.process();
		
		window.clear();
		spritesys.process();
		window.display();
		
		world->setDelta(deltaClock.restart().asSeconds());
	}

	delete world;
	return EXIT_SUCCESS;
}

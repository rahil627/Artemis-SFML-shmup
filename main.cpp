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


int main(int argc, char **argv) {
	
	sf::RenderWindow window(sf::VideoMode(800, 600,32), "Artemis Power");
	TextureManager tx;
	TextureManager::getInstance().addSearchPath("assets/");
	
	artemis::World * world  = new artemis::World();
	artemis::SystemManager * sm = world->getSystemManager();
	//artemis::EntityManager * em = world->getEntityManager();
	
	MovementSystem 	& movsys 	= *(MovementSystem*)	sm->setSystem(new MovementSystem());
	SpriteSystem 	& spritesys = *(SpriteSystem*)		sm->setSystem(new SpriteSystem(window));
	PlayerJoySystem & playerJoy = *(PlayerJoySystem*)	sm->setSystem(new PlayerJoySystem());
	ColliderSystem 	& collider 	= *(ColliderSystem*)	sm->setSystem(new ColliderSystem(800,600,100));
	
	sm->initializeAll();
	
	artemis::Entity * player;
	for(int i=0; i< 1; i++)
	{
		
		player = &world->createEntity(); 
		player->addComponent(new SpriteComponent(TextureManager::getInstance().getTexture("player.png")));
		player->addComponent(new MovementComponent(0,0));
		player->addComponent(new PositionComponent(rand() % 800,rand() % 600));
		player->addComponent(new PlayerJoyComponent(3,i));
		player->addComponent(new ColliderComponent(100, 100,1,1));
		player->refresh();
		world->getGroupManager()->set("HUMAN", *player);
		
	}

	sf::Clock deltaClock;
	sf::Time dt;

	window.setFramerateLimit(60);

	
	// Start the game loop
	while (window.isOpen()) {
	//while (true) {
		
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
		// Clear screen
		window.clear();
		//updateSpriteSystem
		spritesys.process();
		// Update the window
		window.display();
		
		world->setDelta(deltaClock.restart().asSeconds());
		//world->setDelta(0.016);
	}


	delete world;
	return EXIT_SUCCESS;
}

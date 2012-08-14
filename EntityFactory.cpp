#include "EntityFactory.h"
#include <Entity.h>
#include <World.h>
#include  "SpriteComponent.h"
#include  "MovementComponent.h"
#include  "PlayerJoySystem.h"
#include  "ColliderSystem.h"
#include  "HealthComponent.h"

EntityFactory* EntityFactory::ms_instance = 0;

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

EntityFactory* EntityFactory::Instance()
{
	if (ms_instance == 0) {
		ms_instance = new EntityFactory();
	}
	return ms_instance;
}

void EntityFactory::Release()
{
	if (ms_instance) {
		delete ms_instance;
	}
	ms_instance = 0;
}


artemis::Entity& EntityFactory::createPlayer(artemis::World& world, int playerNumber)
{
		artemis::Entity& player = world.createEntity(); 
		player.addComponent(new SpriteComponent(TextureManager::getInstance().getTexture("player.png")));
		player.addComponent(new VelocityComponent(0,0));
		player.addComponent(new PositionComponent(rand() % 800,rand() % 600));
		player.addComponent(new PlayerJoyComponent(3,playerNumber));
		player.addComponent(new ColliderComponent(100, 100,ColliderComponent::NONE,playerNumber));
		player.addComponent(new HealthComponent(100,100));
		player.refresh();
		world.getGroupManager()->set("HUMAN", player);
		return player;
}



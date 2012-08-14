#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

namespace artemis{
class Entity;
class World;
};

class EntityFactory
{
	static EntityFactory* ms_instance;

private:
	EntityFactory(const EntityFactory& rhs);
	EntityFactory& operator=(const EntityFactory& rhs);

public:
	static EntityFactory* Instance();
	static void Release();
	
	artemis::Entity& createPlayer(artemis::World& world, int playerNumber);

private:
	EntityFactory();
	~EntityFactory();

};

#endif // ENTITYFACTORY_H

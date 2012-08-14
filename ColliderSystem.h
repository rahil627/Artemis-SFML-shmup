#ifndef COLL_SYS_H
#define COLL_SYS_H

#include "EntityProcessingSystem.h"
#include "Component.h"
#include "Entity.h"
#include "MovementComponent.h"
#include "ComponentMapper.h"




/**
 * 
 */
class ColliderComponent : public artemis::Component{
	
public:
	
	enum CollisionObjectType : int{
	NONE = 0,
	HUMAN,
	BULLET
};
	
	int width,height,collidionsId,objectId;
	artemis::Entity* contact;
	
	ColliderComponent(int width, int height,int collidionsId, int objectId){
		this->width = width;
		this->height = height;
		this->collidionsId = collidionsId;
		this->objectId = objectId;
	}
	
	virtual ~ColliderComponent(){
		
	}
	
};

/*class CollisionPolicy{
public:
   void addRule(const int id1,const int id2){
	   
   }
   
   bool checkPolicy(const int id1,const int id2){
	   
   }
	
};*/



class ColliderSystem : public artemis::EntityProcessingSystem
{
private:
	artemis::ComponentMapper<PositionComponent> posMapper;
	artemis::ComponentMapper<ColliderComponent> collMapper;
	
	artemis::Bag<artemis::Bag<artemis::Entity*>*> * collisionBuckets;
	
	int cellXCount;
	int cellYCount;
	int cellSize;
	
public:
	ColliderSystem(int width, int height, int cellSize) {
		setComponentTypes<ColliderComponent,PositionComponent>();
		
		this->cellSize = cellSize;
		cellXCount = width/cellSize;
		cellYCount = height/cellSize;
		
		collisionBuckets = new artemis::Bag<artemis::Bag<artemis::Entity*>*>(cellYCount * cellXCount);
		
		for(int i=0; i<collisionBuckets->getCapacity(); i++)
		{
			collisionBuckets->set(i,new artemis::Bag<artemis::Entity*>());
		}

	}
	~ColliderSystem(){
		
		for(int i=0; i<collisionBuckets->getCapacity(); i++)
		{
			delete collisionBuckets->get(i);
		}
		
		delete collisionBuckets;
	}
	virtual void initialize(){
		posMapper.init(*world);
		collMapper.init(*world);
	}
	
	virtual void processEntity(artemis::Entity& e)
	{
		
	}
	
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*>& bag)
	{
		creatCollisionBuckets(bag);
		
		for(int i=0; i< collisionBuckets->getCapacity(); i++)
		{
			artemis::Bag<artemis::Entity*> * bucket = collisionBuckets->get(i);
			if(bucket->isEmpty() || bucket->getCount() == 1) continue;
			
			for(int j=0; j < bucket->getCount(); j++)
			{
				artemis::Entity& ej = *bucket->get(j);
				for(int k=j+1; k < bucket->getCount(); k++)
				{
					//Do collision action
					artemis::Entity& ek = *bucket->get(k);
					
					//Check collision policy
					
					if(collMapper.get(ej)->objectId == collMapper.get(ek)->objectId) 
						   continue;
						   
					if(intersects(ej,ek)){
						collMapper.get(ej)->contact = &ek;
						collMapper.get(ek)->contact = &ej;
					}
				}
			}
		}
	}
	
	void creatCollisionBuckets(artemis::ImmutableBag<artemis::Entity*>& bag){
		
		int i=0;
		for(i =0; i< collisionBuckets->getCapacity(); i++)
		{
			collisionBuckets->get(i)->clear();
		}
		
		for(i=0; i<bag.getCount(); i++)
		{
			int bucketX = (int)posMapper.get(*bag.get(i))->position.x / cellSize;
			int bucketY = (int)posMapper.get(*bag.get(i))->position.y / cellSize;
			
			int index = (bucketY * cellXCount) + bucketX;
			
			if(bucketX > 0 && bucketX < cellXCount && bucketY > 0 && bucketY < cellYCount){
				
				collisionBuckets->get(index)->add(bag.get(i));
				//std::cout << "Adding to bucket[" << bucketX << "][" <<bucketY << "]\n"; 
			}
			
			
		}

		
	}
	
	bool intersects(artemis::Entity& first, artemis::Entity& second){

		
		ColliderComponent & col1 = *collMapper.get(first);
		ColliderComponent & col2 = *collMapper.get(second);
		
		int posX1 = (int)posMapper.get(first)->position.x - col1.width*0.5f;
		int posY1 = (int)posMapper.get(first)->position.y - col1.height*0.5f;
		
		int posX2 = (int)posMapper.get(second)->position.x - col2.width*0.5f;
		int posY2 = (int)posMapper.get(second)->position.y - col2.height*0.5f;
		
		
		if(posX1 + col1.width < posX2) return false;
		if(posX1 > posX2 + col2.width) return false;
		if(posY1 + col1.height < posY2) return false;
		if(posY1 > posY2 + col2.height) return false;
		
		return true;
		
	}
	
};
#endif // $(Guard token)

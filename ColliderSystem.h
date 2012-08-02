#ifndef COLL_SYS_H
#define COLL_SYS_H


#include "GroupManager.h"
#include "EntityProcessingSystem.h"
#include "Component.h"
#include "Entity.h"
#include "MovementComponent.h"
#include "ComponentMapper.h"
#include <vector>
class ColliderComponent : public artemis::Component{
	
	public:
	int width,height,collidionsId,objectId;
	
	ColliderComponent(int width, int height,int collidionsId, int objectId){
		this->width = width;
		this->height = height;
		this->collidionsId = collidionsId;
		this->objectId = objectId;
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
	
	//std::vector<std::vector<artemis::Entity*> > collisionLists;
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
				artemis::Entity ej = *bucket->get(j);
				for(int k=j+1; k < bucket->getCount(); k++)
				{
					artemis::Entity ek = *bucket->get(k);
					if(collMapper.get(ej)->collidionsId == collMapper.get(ek)->collidionsId || 
					collMapper.get(ej)->objectId < 5) 
						   continue;
					if(intersects(ej,ek)){
						std::cout << "hit";
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
			int bucketX = (int)posMapper.get(*bag.get(i))->posX / cellSize;
			int bucketY = (int)posMapper.get(*bag.get(i))->posY / cellSize;
			
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
		
		int posX1 = (int)posMapper.get(first)->posX - col1.width*0.5f;
		int posY1 = (int)posMapper.get(first)->posY - col1.height*0.5f;
		
		int posX2 = (int)posMapper.get(second)->posX - col2.width*0.5f;
		int posY2 = (int)posMapper.get(second)->posY - col2.height*0.5f;
		
		
		if(posX1 + col1.width < posX2) return false;
		if(posX1 > posX2 + col2.width) return false;
		if(posY1 + col1.height < posY2) return false;
		if(posY1 > posY2 + col2.height) return false;
		
		return true;
		
	}
	
};
#endif // $(Guard token)

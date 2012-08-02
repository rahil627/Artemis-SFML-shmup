#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "InputEvent.h"
#include <SFML/Graphics.hpp>
#include "Event.h"


namespace st{
	namespace gameobject{
		
		class Player : public sf::Sprite, public st::input::IJoyListener, public st::event::IEventListener{
		private:
			static sf::Texture * img;
		
			sf::Vector2f velocity;
			
			float speed;
			st::event::EventDispatcher dispatcher;
			float fireRate;
			float fireCounter;
			bool isShooting;
			bool isSlowingTime;
			float powerBoost;
			bool powerShotReady;
			
		public:
			
			sf::Vector2f shootingDir;
		
			Player();
			virtual void onJoyData(st::input::JoyData &evt);
			virtual void update(float dt);
			virtual void shoot(float dt);
			virtual void slowDown();
			
			virtual void addEventListener(const std::string &type, st::event::function listener, int priority = 0);
			virtual void removeEventListener(const std::string &type, st::event::function listener);
			
		};
	};
};

#endif 

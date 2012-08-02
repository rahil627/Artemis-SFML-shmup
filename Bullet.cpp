#include "Bullet.h"
#include <iostream>
#include <math.h>
namespace st {
	namespace gameobject {
		
		Bullet::Bullet() {
		
		isActive = false;
			if(!img) {
				img = new sf::Texture();
				img->loadFromFile("assets/bullet.png");
				
			}
			
			//t
			this->setTexture(*img);
			std::cout << this->getTexture()->getSize().x << "\n";
			std::cout << this->getTexture()->getSize().y << "\n";
			
			setOrigin((img->getSize().x * 0.5f), (img->getSize().y* 0.5f));
			
#ifdef _DEBUG
		
			if(!img)std::cout << "Image couldn't be loaded :  BULLET";

#endif

			speed = 1000;
		};

		void Bullet::update(float dt) {

			move((dVector * (speed * dt)));
		};

		sf::Texture * Bullet::img;
	};
};

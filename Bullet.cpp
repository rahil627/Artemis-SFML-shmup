#include "Bullet.h"
#include <iostream>

namespace st {
	namespace gameobject {
		Bullet::Bullet() {
			if(!img) {
				img = new sf::Texture();
				img->loadFromFile("assets/bullet.png");
			}

			this->setTexture(*img);
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

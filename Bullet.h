#ifndef _BULLET_H
#define _BULLET_H

#include <SFML/Graphics.hpp>
namespace st {
	namespace gameobject {
		class Bullet : public sf::Sprite {

			private:
				static sf::Texture * img;
			public:
				bool isActive;
				float speed;
				sf::Vector2f dVector;
				Bullet();
				void update(float dt);
		};
	};
};
#endif

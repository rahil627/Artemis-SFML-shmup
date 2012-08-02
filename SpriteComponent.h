#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "SFML/graphics.hpp"
#include "Component.h"

class SpriteComponent : public artemis::Component{
public:
	sf::Sprite sprite;

	SpriteComponent(sf::Texture& texture){
		sprite.setTexture(texture);
		
		 sf::Vector2f c(texture.getSize().x/2,texture.getSize().y/2);
		sprite.setOrigin(c);
	}
};

#endif // $(Guard token)

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <SFML/Graphics.hpp>
namespace st{
	namespace management{
		namespace collision{
			//=============================================================================
			inline bool spriteOverlaps(const sf::Sprite &sp, const sf::Sprite &otherSp);
			inline bool rectOverlaps(const sf::Rect<float> rect, const sf::Rect<float> otherRect);
			//=============================================================================
		};
	};
};

#endif 
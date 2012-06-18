
#include "Collision.h"

namespace st {
	namespace management {
		namespace collision {
			//=============================================================================
			bool spriteOverlaps(const sf::Sprite &sp, const sf::Sprite &otherSp)
			{
				return sp.getGlobalBounds().intersects(otherSp.getGlobalBounds());
			}
			//=============================================================================

			//=============================================================================
			bool rectOverlaps(const sf::Rect<float> &rect, const sf::Rect<float> &otherRect)
			{
				return rect.intersects(otherRect);

			}
			//=============================================================================
		};
	};
};

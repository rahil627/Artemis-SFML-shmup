#ifndef __SHOOT_EVEN__H_
#define __SHOOT_EVEN__H_

#include "Event.h"
namespace st {
	namespace event {

		class ShootEvent : public Event {
			public:
				ShootEvent(const std::string type) : Event(type){}
	
				sf::Vector2f position;
				sf::Vector2f direction;
				bool powerShot;
				unsigned int familyID;
		};

	};
};
#endif // $(Guard token)

#include "ObjectHandlers.h"

namespace st {
	namespace objecthandlers {
		void processBullet( ObjectPool<Bullet> &bulletPool, std::list<Bullet*> &bulletList, float dt ) {

			std::list<Bullet*>::iterator it;
			Bullet * b;

			it = bulletList.begin();

			while( it != bulletList.end() ) {

				b = *it;
				b->update( dt );

				if( b->getPosition().x > 800 ) {

					it = bulletList.erase( it );
					bulletPool.resturnResource( b );
				} else
					++it;
			}
		}
	};
};

#ifndef _HOBJECTHANDLERS_H
#define _HOBJECTHANDLERS_H

#include "ObjectPool.h"
#include "Bullet.h"
#include <list>

using namespace st::gameobject;
using namespace st::management;

namespace st {
	namespace objecthandlers {
		void processBullet(ObjectPool<Bullet> &bulletPool, std::list<Bullet*> &bulletList, float dt);

	};
};
#endif

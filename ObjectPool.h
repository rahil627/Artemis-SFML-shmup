#ifndef _OBJECTPOOL_H_
#define _OBJECTPOOL_H_

#include <list>

namespace st{
	namespace management{
		template <class T> class ObjectPool{
			
		private:
			std::list<T*> resources;
		public:
			
			T * getResource(){
				
				if(resources.empty())
				{
					return new T();
				}
				else{
					T * resource  = resources.front();
					resources.pop_front();
					return resource;
				}
				
			}
			
			void resturnResource(T* object)
			{
				resources.push_back(object);
				//std::cout << "Pool size is now : " << resources.size() << std::endl;
			}
			
		};
	};
};

#endif 
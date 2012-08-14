#ifndef _EVENT_H
#define _EVENT_H

#include <map>
#include <list>
#include <string>

namespace st{
	namespace event{
		
		//======================================================================================
		class Event{
		public:
			Event(const std::string &type):
			type(type){};
			
			const std::string type;
		};
		
		typedef void (*function)(const Event &);
		//======================================================================================
		
		class IEventListener{
			virtual void addEventListener(const std::string &type, function listener, int priority = 0) = 0;
			virtual void removeEventListener(const std::string &type, function listener) = 0;
		};
		
		class EventDispatcher{
		public:
		
			EventDispatcher(){};
			/**
			 * 
			 * 
			 **/
			void addEventListener(const std::string &type, function listener, int priority = 0){
				eventHandlerList[type][priority].push_back(listener);
			}
			/**
			 * 
			 * 
			 **/
			void removeEventListener(const std::string &type, function listener){
				if(!hasEventListener(type))
					return;
					
				std::map<int, std::list<function> > &allFunctions = eventHandlerList[type];
				std::map<int, std::list<function > >::iterator it;
				it=allFunctions.begin();
				
				while(it != allFunctions.end())
				{
					it->second.remove(listener);
					
						if (it->second.empty()) { allFunctions.erase(it++); }
						else                    { ++it;                     }
				}
				
				if(allFunctions.empty())
					eventHandlerList.erase(type);
			}
			/**
			 * 
			 * 
			 **/
			bool hasEventListener(const std::string &type){
				return (eventHandlerList.find(type)) != eventHandlerList.end();
			}
			
			/**
			 * 
			 * 
			 **/
			void dispatchEvent(const Event &event){
				
				if(!hasEventListener(event.type))
					return;
					
					
					//A reference to keep code clean.
					std::map<int, std::list<function> > &allFunctions = eventHandlerList[event.type];
		
					
					for(std::map<int, std::list<function > >::reverse_iterator i=allFunctions.rbegin(); i!=allFunctions.rend(); ++i){
						std::list<function > &funclist = i->second;
						
						for(std::list<function>::iterator f = funclist.begin(); f!=funclist.end(); ++f){
							(*f)(event);
						}
						//Call function
						//(*i)(event);
					}
			}
			
		private:
			std::map<const std::string, std::map<int, std::list<function> > > eventHandlerList;
			
			EventDispatcher(EventDispatcher const&);              // Don't Implement
			void operator=(EventDispatcher const&);
		};
		
}
}

#endif 

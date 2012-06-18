#ifndef _INPUTEVENT_
#define _INPUTEVENT_

#include <vector>
#include "InputEvent.h"

namespace st{
	namespace input{

		enum Buttons{
			A = 0,
			B = 1,
			X = 2,
			Y = 3, 
			L = 4, 
			R = 5, 
			BACK = 6, 
			START = 7, 
			LS = 8, 
			RS = 9
		};
		
		typedef struct JoyEvent{
			
			float dt;
			
			float axisX; 
			float axisY;		
			
			bool buttonA;
			bool buttonB;
			bool buttonX;
			bool buttonY;
			bool buttonL;
			bool buttonLS;
			bool buttonR;
			bool buttonRS;
			bool buttonStart;
			bool buttonBack;
			
		}JoyEvent;
		
		//=======================================================
		class IJoyListener{
			
		public:
			virtual void onJoyEvent(JoyEvent evt) = 0; 
			
		};
		//=======================================================
		class JoyInput{
			
		public:
			JoyInput();
			void registerObject(st::input::IJoyListener* listener, unsigned int id);
			void deRegisterObject(st::input::IJoyListener* listener, unsigned int id);
			void update(float dt);
			
		private:
			std::vector<IJoyListener*> controllerID;
			
		protected:
			
		};

	};
};

#endif

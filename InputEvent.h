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
			Back = 6, 
			START = 7, 
			LS = 8, 
			RS = 9
		};
		
		typedef struct JoyData{
			
			float LSAxisX; 
			float LSAxisY;	
			float RSAxisX; 
			float RSAxisY;	

			int povX;
			int povY;
			
			bool A;
			bool B;
			bool X;
			bool Y;
			bool L;
			bool LS;
			bool R;
			bool RS;
			
			bool Start;
			bool Back;
			
			bool actionA;
			bool actionB;
			bool actionX;
			bool actionY;
			bool actionL;
			bool actionLS;
			bool actionR;
			bool actionRS;
			
			bool actionStart;
			bool actionBack;
			
			
		}JoyData;
		
		//=======================================================
		class IJoyListener{
			
		public:
			virtual void onJoyData(JoyData &evt) = 0; 
			
		};
		//=======================================================
		class JoyInput{
			
		public:
			JoyInput();
			~JoyInput();
			void registerObject(st::input::IJoyListener* listener, unsigned int id);
			void deRegisterObject(st::input::IJoyListener* listener, unsigned int id);
			void initData(JoyData& data);
			void update();
			
		private:
			IJoyListener *controllerID[4];
			JoyData previousState[4];
			JoyData padData[4];
			
		protected:
			
		};

	};
};

#endif

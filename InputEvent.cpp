#include "InputEvent.h"
#include <SFML/Window.hpp>
#include <iostream>
namespace st{
	namespace input{
		
		JoyInput::JoyInput(){
			
			for(size_t i=0; i<4; i++)
			{
				controllerID[i] = 0;
				initData(previousState[i]);
				initData(padData[i]);
			}

		}
		
		JoyInput::~JoyInput(){
			
			for (unsigned int i = 0; i < 4; i++)
			{
				//Set to null. Object should delete themselves.
				controllerID[i] = 0;
			}
			delete [] previousState;
			
		}
		
		void JoyInput::initData(JoyData& data){
			
			data.A = false;
			data.B = false;
			data.X = false;
			data.Y = false;
			data.L = false;
			data.R = false;
			data.LS = false;
			data.RS = false;
			data.Start = false;
			data.Back = false;
			
			data.actionA = false;
			data.actionB = false;
			data.actionX = false;
			data.actionY = false;
			data.actionL = false;
			data.actionR = false;
			data.actionLS = false;
			data.actionRS = false;
			data.actionStart = false;
			data.actionBack = false;
			
		}
		
		void JoyInput::deRegisterObject(st::input::IJoyListener * listener, unsigned int id){
			controllerID[id] = 0;
		}
		
		void JoyInput::registerObject(st::input::IJoyListener * listener, unsigned int id){
			controllerID[id] = listener;
		}
		
		void JoyInput::update(){
			
			
			for(unsigned int i=0; i< 4; i++)
			{
				
				if(controllerID[i] == 0) return;
				st::input::JoyData &data = padData[i];
				st::input::JoyData &prev = previousState[i];
				
				data.LSAxisX = sf::Joystick::getAxisPosition(i,sf::Joystick::X);
				data.LSAxisY = sf::Joystick::getAxisPosition(i,sf::Joystick::Y);
				data.RSAxisX = sf::Joystick::getAxisPosition(i,sf::Joystick::U);
				data.RSAxisY = sf::Joystick::getAxisPosition(i,sf::Joystick::R);
				data.povX  = sf::Joystick::getAxisPosition(i,sf::Joystick::PovX);
				data.povY  = sf::Joystick::getAxisPosition(i,sf::Joystick::PovY);
				
				data.actionA = data.A = sf::Joystick::isButtonPressed(i,st::input::A);
				if(prev.A) data.actionA = false; 
				data.actionB = data.B = sf::Joystick::isButtonPressed(i,st::input::B);
				if(prev.B) data.actionB = false; 
				data.actionX = data.X = sf::Joystick::isButtonPressed(i,st::input::X);
				if(prev.X) data.actionX = false; 
				data.actionY = data.Y = sf::Joystick::isButtonPressed(i,st::input::Y); 
				if(prev.Y) data.actionY = false; 
				data.actionL = data.L = sf::Joystick::isButtonPressed(i,st::input::L); 
				if(prev.L) data.actionL = false; 
				data.actionR = data.R = sf::Joystick::isButtonPressed(i,st::input::R); 
				if(prev.R) data.actionR = false; 
				data.actionStart = data.Start = sf::Joystick::isButtonPressed(i,st::input::START);
				if(prev.Start) data.actionStart = false; 
				data.actionBack = data.Back = sf::Joystick::isButtonPressed(i,st::input::Back);
				if(prev.Back) data.actionBack = false; 
				data.actionLS = data.LS = sf::Joystick::isButtonPressed(i,st::input::LS);
				if(prev.LS) data.actionLS = false; 
				data.actionRS = data.RS = sf::Joystick::isButtonPressed(i,st::input::RS);
				if(prev.RS) data.actionRS = false; 
				//etc etc
				previousState[i] = padData[i];
				controllerID[i]->onJoyData(data);
				
			}
		}
	}
}
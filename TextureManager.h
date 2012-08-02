#ifndef TEXTR_MANAGER_H
#define TEXTR_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class TextureManager{
	
public:
	static TextureManager& getInstance(){
      return *instance;  
	}
	
	sf::Texture& getTexture(std::string name);
	void addSearchPath(std::string path);
	TextureManager();
	~TextureManager();
private:
	static TextureManager * instance;
	
	std::unordered_map<std::string, sf::Texture*> texturemap;
	std::vector<std::string> pathlist;
	sf::Texture* defaultTexture;
};

#endif //end gaurd
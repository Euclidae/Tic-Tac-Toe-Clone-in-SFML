#include "AssetManager.hpp"
#include <iostream>
namespace Deus {
	void AssetManager::LoadTexture(std::string name, std::string fileName) {
		sf::Texture tex;

		if (tex.loadFromFile(fileName)) {
			this->_textures[name] = tex;
		}
	}

	sf::Texture& AssetManager::GetTexture(std::string name) {
		if (_textures.find(name) != _textures.end()) {
			return _textures.at(name);
		}
		else {
			std::cout << "Not found" << std::endl;
		}
	}
	
	
	void AssetManager::LoadFont(std::string name, std::string fileName) {
		sf::Font font;

		if (font.loadFromFile(fileName)) {
			this->_fonts[name] = font;
		}
	}

	sf::Font& AssetManager::GetFont(std::string name) {
		if (_fonts.find(name) != _fonts.end()) {
			return _fonts.at(name);
		}
		else {
			std::cout << "Not found" << std::endl;
		}
	}
}


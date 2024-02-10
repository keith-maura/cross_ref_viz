#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Bible.hpp"

int main(int argc, char* argv[]) {
	// Initialize string object for reading in files
	std::string line;
	// Create Bible object
	Bible bible;
	// File name and file object for cross references
	std::string cross_refs = "Cross_refs.csv";
        std::ifstream file(cross_refs);
        // Ignore first line
        std::getline(file, line);
        if(file.is_open()) {
		// Add cross references as Arc objects reading in line by line
                while (std::getline(file, line)) {
                        bible.AddArc(line);
                }
                file.close();
        }
	// Display error if file couldn't open
        else {
                std:: cout << "Cannot open file" << std::endl;
        }

	// Create window
	sf::RenderWindow window(sf::VideoMode(bible.refs->at(0).width, bible.refs->at(0).height), "Cross References");

	// Boolean if image has been saved
	bool saved = false;

	// Infinite loop while window is open, wait for close input and continuously draw visualization
	while (window.isOpen()) {
		// Clear window
		window.clear();

		// Check for close input
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Draw Bible
		bible.Render(window);

		// Display window
		window.display();

		// If image not yet saved, save and change saved to true
		if (!saved) {
			sf::Texture texture;
			if (!texture.create(bible.refs->at(0).width, bible.refs->at(0).height)) {
				std::cout << "Error - could not create texture" << std::endl;
			}
			texture.update(window);
			sf::Image capture = texture.copyToImage();
			capture.saveToFile("Cross_refs.jpg");
			saved = true;
		}
	}

return 0;

}

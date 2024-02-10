#include "Bible.hpp"
#include "Chapter.hpp"
#include "Arc.hpp"

#include <iostream>


// Constructor
Bible::Bible() {
	// Initialize vector to hold cross reference Arc objects
	refs = new std::vector<Arc>;
}

// Default destructor
Bible::~Bible() {
}

// Function to make Arc from a string input
Arc Bible::MakeArcFromLine(std::string line) {
	// Index of comma in input, declare vector of strings to hold data
        std::size_t comma = line.find(",");
        std::vector<std::string> vals;
	// While comma index is not out of bounds
        while (comma != std::string::npos) {
		// Add substring from 0 to comma to vals vector
                vals.push_back(line.substr(0, comma));
		// Update line to start after comma
                line = line.substr(comma + 1);
		// Find index of next comma
                comma = line.find(",");
        }
	// Construct from and to Chapter objects from vals vector
	Chapter* from = new Chapter(std::stoi(vals.at(3)), vals.at(0), std::stoi(vals.at(1)), std::stoi(vals.at(2)));
	Chapter* to = new Chapter(std::stoi(vals.at(8)), vals.at(5), std::stoi(vals.at(6)), std::stoi(vals.at(7)));
	// Return Arc object with the two Chapter objects
	return Arc{from, to};
}

// Add an Arc object to Bible given a string input
void Bible::AddArc(std::string line) {
	// Call MakeArcFromLine on input and add to refs vector
	refs->push_back(MakeArcFromLine(line));
}


// Render Bible on given window
void Bible::Render(sf::RenderWindow& window) {
	// Draw all cross reference Arc objects
	for (int i = 0; i < refs->size(); i++) {
		Arc a = refs->at(i);
		a.DrawArc(window);
	}
	
	// Draw horizontal white line to represent x-axis of all chapters
	sf::RectangleShape line(sf::Vector2f(refs->at(0).width - refs->at(0).offset * 2, 2));
	line.setPosition(sf::Vector2f(refs->at(0).offset, refs->at(0).height/2 - 1));
	
	window.draw(line);
}



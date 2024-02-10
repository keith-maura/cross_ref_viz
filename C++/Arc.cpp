#include "Arc.hpp"

// Constructor, take in Chapter reference is from and Chapter reference is to
Arc::Arc(Chapter* from_c, Chapter* to_c) {
	from = from_c;
	to = to_c;
}

// Destructor, default
Arc::~Arc() {
}

// Function to get a point on the arc
// Input: x_center - the center of the circle the arc is for, along the x axis
// 	  y_center - the center of the circle the arc is for, along the y axis
// 	  radius - the radius of the circle
// 	  numSides - the number of line segments to make up the arc
// 	  pointNumber - the side number being constructed
// 	  forward - true if the cross reference moves forward in the Bible (a book has a cross reference to a book that occurs later in the Bible)
// Output: sf::Vector2f with (x, y) for point on arc
sf::Vector2f Arc::GetArcPoint(float x_center, float y_center, float radius, int numSides, int pointNumber, bool forward) {
	// Calculate the left edge of the arc along the x axis
	float x_left = x_center - radius;
	// Find the radius squared
	float r2 = radius * radius;
	// x steps will be the length of the arc along the x axis divided by the number of sides
	float x_step = radius * 2.0f/(float)numSides;
	// x is the left edge + the step size * the step number
	float x = x_left + x_step * (float)pointNumber;
	// If cross reference moves forward, draw arc above center line
	if (forward) {
		// Using formula for a circle:(x-x_center)^2 + (y-y_center)^2 = r^2
		// Return only top half of the arc, which is subtracting sqrt value from y_center
		float y = y_center - (sqrt(r2 - (x - x_center)*(x - x_center))) * scale;
		// Multiply x by scale and offset by offset value
		return sf::Vector2f(x * scale + offset, y);
	}
	// Otherwise cross reference moves backward, draw arc below the center line
	// Same calculation for if forward is true, but instead add sqrt value to y_center for bottom half of arc
	float y = y_center + (sqrt(r2 - (x - x_center) * (x - x_center))) * scale;
	// Multiply x by scale and offset by offset value
	return sf::Vector2f(x * scale + offset, y);
	
}

// Function to draw an arc
// Input: x_center - the center of the circle the arc is for, along the x axis
//        y_center - the center of the circle the arc is for, along the y axis
//        radius - the radius of the circle
//        numSides - the number of line segments to make up the arc
//        forward - true if the cross reference moves forward in the Bible (a book has a cross reference to a book that occurs later in the Bible)
//        color - the color for the arc
// Output: ConvexShape for arc
sf::ConvexShape Arc::MakeArc(float x_center, float y_center, float radius, int numSides, bool forward, sf::Color color) {
	// Declare arc shape
	sf::ConvexShape arc;
	// Set point count
	arc.setPointCount(numSides+1);
	// Iterate through all points
	for (int i = 0; i <= numSides; i++) {
		// Set point on arc to value calculated by GetArcPoint
		arc.setPoint(i, GetArcPoint(x_center, y_center, radius, numSides, i, forward));
	}
	// No fill
	arc.setFillColor(sf::Color::Transparent);
	// Set outline to given color
	arc.setOutlineColor(color);
	// Set outline thickness to 1
	arc.setOutlineThickness(1);
	return arc;
};


// Function to draw the given arc
void Arc::DrawArc(sf::RenderWindow& window) {
	// Declare color
	sf::Color color;
	// If chapter for destination of cross reference is 929 or higher, it's New Testament, set to blue
	if (to->chapter_bible >= 929) {
		color = sf::Color(0, 0, 255, 25);
	}
	// Otherwise destination of cross reference is Old Testament, set to red
	else {
		color = sf::Color (255, 0, 0, 25);
	}
	// If chapter for destination comes later in the Bible than chapter for origin
	if (from->chapter_bible < to->chapter_bible) {
		// Calculate radius
		float radius = ((float)to->chapter_bible - (float)from->chapter_bible)/2.0f;
		// Set number of sides to 100
		int numSides = 100;
		// Call MakeArc to create arc
		sf::ConvexShape circle = MakeArc(from->chapter_bible + radius, height/2, radius, numSides, true, color);
		// Draw on window
		window.draw(circle);
	}
	// Otherwise chapter for destination comes earlier in the Bible than chapter for origin
	else {
		// Calcuate radius
		float radius = ((float)from->chapter_bible - (float)to->chapter_bible)/2.0f;
		// Set number of sides to 100
                int numSides = 100;
		// Call MakeArc to create arc
                sf::ConvexShape circle = MakeArc(to->chapter_bible + radius, height/2, radius, numSides, false, color);
		// Draw on window
		window.draw(circle);
	}
}

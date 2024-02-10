
# Biblical Cross References
## Description:
Early iteration with a small subset of data:





<img src="https://user-images.githubusercontent.com/71294657/205728916-437c45be-bc9f-43cf-b9cd-eea7621b357b.jpg" alt="cross_refs_early" width="400"/>

Final visualization in C++:




<img src="https://user-images.githubusercontent.com/71294657/205728921-93c1d5ab-fb95-4341-90d8-b2a4e42936c9.jpg" alt="cross_refs_final" width="400"/>

## Description

My project is a visualization of cross references in the Bible. A cross reference is when one verse references or presents a similar idea to a verse elsewhere in the Bible. My visualization consists of a horizontal white line to represent all chapters of the Bible chronologically with arcs connecting all cross references; arc endpoints are located on the white line corresponding to its cross reference chapters. References "forward" are above the line and refences "backward" are below the line. Red arcs are for references to the Old Testament, and blue arcs are for references to the New Testament. For an example consider Genesis 1:1 with cross reference to Revelation 4:11. Revelation 4:11 is the 'to' reference and is a New Testament book; and it's located after Genesis in the Bible, so the arc for this reference is placed above the white line and is blue. Some 3500+ cross references are visualized by my program.

## Resources

Inspiration:
* https://www.pdviz.com/bible-cross-references-visualization
* https://www.markmeynell.net/2010/01/08/a-stunning-visualization-of-the-bibles-63779-cross-references/

Cross Reference Data:
* https://github.com/scrollmapper/bible_databases/ (I used their .txt file with cross references and cleaned in Python to make .csv file for this C++ project)

Coding resources:
* https://www.sfml-dev.org/documentation/2.5.1/
* https://cplusplus.com/reference/

## How to Compile and Run

Clone GitHub repository to local machine. The necessary .csv data file is included here and will automatically be read in by the program; no arguments are needed when running the program. Ensure that SFML is installed on the machine. Navigate to `part1` folder.

- Compile with: `g++ ./src/*.cpp -o prog -I./include -lsfml-graphics -lsfml-window -lsfml-system`
- Run with: `./prog`

Running the program will open a window with the visualization and also saves the image as 'Cross_refs.jpg'.


## Design

Classes:
* Chapter
  * Represents a chapter in the Bible. Does not have any member functions but simply holds the following data: chapter number in the entire Bible, name of the book of the Bible the chapter is in, number of the book of the Bible the chapter is in, chapter number within book of the Bible.
* Arc
  * Represents a cross reference in the Bible. Holds pointers to two Chapters, the 'from' and 'to' chapters of the cross reference. Also holds width, height, scale, and offset constant variables for window size and scaling. Member functions create the semicircle shape of the arc and display the arc.
* Bible
  * Represents the entire Bible. Holds pointer to Arcs. Member functions create an Arc from an input line from the .csv data file, add an Arc to the Bible from said input line, and render all Arcs in the Bible.

## Technical Challenge

The most technically challenging aspect of this project was rendering semicircle shapes for each arc. The SFML library has a class for circles, but I could not find a function in that class to render only part of the circle - the top or bottom half in my case - or a different class for an arc or semicircle. The solution I came up with is to create a convex shape, which connects manually defined points. I used the mathematical formula for a circle to calculate points along the arc, and added those to a convex shape which renders a half circle using the following two functions:

MakeArc outputs a convex shape. Its inputs are:
* float x_center: the center of the arc - halfway between the input and output chapters
* float y_center: the bottom of the arc if it's above the white line, or top if it's below the white line
* float radius: the radius of the arc, half of the numerical difference between the two chapters
* int numSides: the number of sides for the arc to have; the more sides, the more smooth the arc appears
* bool forward: true if the 'to' chapter occurs later in the Bible than the 'from' chapter; the arc is located above the white line if forward is true
* Color color: the color of the arc; red will be input if 'to' is in the Old Testament and blue will be input if 'to' is in the New Testament; alpha is set to 25 for a neat visual effect showing where cross references are more concentrated.
This function declares a convex shape with numSides + 1 (extra side for line connecting endpoints). It calls helper GetArcPoint to calculate all arc points and adds them to the convex shape. It sets fill to transparent, outline to color with thickness of 1 and returns the shape.

The function GetArcPoint is a helper for MakeArc that outputs an (x, y) vector for a given point on the arc. Its inputs are:
* float x_center, float y_center, float radius, int numSides: all the same as in MakeArc
* bool forward: same as in MakeArc; y is subtracted from y_center if forward is true to be above the white line, it's added to y_center if forward is false to be below the white line
* int pointNumber: the point on the arc being calculated (1st point, 2nd, ...)
x_step is calculated to be the diameter of the circle divided by the number of sides; this is interpolated to find the x value. y is calculated using the formula for a circle and is added or subtracted from y_center depending on the variable forward. Values are scaled using scale variable and x is offset to be centered in screen using offset variable. A vector with the scaled and correctly positioned (x, y) values is returned.

## Results

The final visualization turned out exactly how I had hoped and is beautiful to look at; such a visualization spurs fascination and awe of how interconnected the Bible is. This program also saves a .jpg of the result; in future weeks after the course I am planning to edit my code to render a higher resolution version of this image to get printed and hang on my wall.
## Inspiration:
* https://www.pdviz.com/bible-cross-references-visualization
* https://www.markmeynell.net/2010/01/08/a-stunning-visualization-of-the-bibles-63779-cross-references/
## Data source:
* https://github.com/scrollmapper/bible_databases/

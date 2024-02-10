
# Biblical Cross References
## Description:
Early iteration with a small subset of data:





<img src="https://user-images.githubusercontent.com/71294657/205728916-437c45be-bc9f-43cf-b9cd-eea7621b357b.jpg" alt="cross_refs_early" width="400"/>

Final visualization in C++:




<img src="https://user-images.githubusercontent.com/71294657/205728921-93c1d5ab-fb95-4341-90d8-b2a4e42936c9.jpg" alt="cross_refs_final" width="400"/>

Final visualization in Java:




https://github.com/keith-maura/cross_ref_viz/blob/main/java_cross_refs_light.png

## Description

For this project I created a visualization to illustrate cross references in the Bible. A cross reference is when one verse references or presents an idea connected to a verse elsewhere in the Bible. Components are a horizontal center line, vertical chapter lines, and arcs.

The horizontal center line serves as a "timeline" or table of contents. The left endpoint is the beginning of the Bible and the right endopoint is the end.

Vertical lines mark the beginning of a book. There is a vertical line marking Genesis 1, Exodus 1, Leviticus 1, ..., Revelation 1. (Note that vertical lines were implemented on only in Java updates of the visualization)

Arcs represent cross references. Each endpoint corresponds to the location of the reference. Forward references (i.e. a reference from an earlier page to a later page) are above the center line, while references backwards are below the center line. Color indicates the destination of the reference as follows: red refers to an Old Testament reference, blue indicates a New Testament reference, and green indicates a reference within a book. Consider the example of a reference from Genesis 1:1 to Revelation 4:11. Revelation 4:11 is the 'to' reference and is a New Testament book. It's located after Genesis in the Bible, so the arc is placed above the center line and colored blue.

## Design

Classes:
* Chapter
  * Represents a chapter in the Bible. Holds the following data: chapter number in the entire Bible, name of the book of the Bible the chapter is in
* Arc
  * Represents a cross reference in the Bible. Has the following attributes: 'from' and 'to' chapters, 'from' and 'to' book numbers
* Bible
  * Represents the entire Bible. Attribues are width of image, scale factor (to adjust image resolution desires), ArrayList of Arcs, ArrayList of Chapters
  * Member methods include adding an Arc and adding a Chapter
* Run
  * Contains methods for main functionality: choose color based on Arc specifications, make and save visualization, draw horizontal line, draw chatper start lines, draw all arcs

## Data Files
### Input Data Source
* https://github.com/scrollmapper/bible_databases/
  * This GitHub repository contains biblical data pulled from openbible.info which compiles data from various sources. A field entitled 'votes' indicates how many reports there are of each reference. More votes means that a reference is more commonly used in Bible reading.
### Cleaned Data Files
The above file was cleaned via Python to extract chapter names and numbers into a .csv format. 
* Bible_books.csv: Data for all chapters in the Bible. Each row of data has the name of the book, the book number, the chapter within the book, and the chapter number within the entire Bible
* Cross_refs_all.csv: All cross reference data. Each row of data consists of the 'from' and 'to' book names and numbers, chapter number within book and within the entire Bible, and verse number.

## Iterations

This project was initially created for a class in C++ literacy and coded in C++ using the SFML library for visualization. I found many limitations using SFML; for example, there was no existance of a function to draw arcs, only entire circles, so I coded a function to manually draw arcs from many small line segments. This was very computationally heavy to find the (x, y) values of all points along each arc, and output a somewhat low-resolution image. I used the 'votes' field from my input data file to select the top 3500 cross references. Following the wrap-up of the course I implemented my code in Java using more sophisticated image libraries, namely Swing, in order to draw arcs much more easily and to allow for higher resolution image outputs. I also lowered the opacity of each arc object and used all cross references from my input file, nearly 350,000, to illustrate more even data. Using this new program I created an high-resulution output that was printed on a large canvas and used as a wedding gift!


## Resources

Inspiration:
* https://www.pdviz.com/bible-cross-references-visualization
* https://www.markmeynell.net/2010/01/08/a-stunning-visualization-of-the-bibles-63779-cross-references/

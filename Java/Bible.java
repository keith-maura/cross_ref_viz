import java.util.ArrayList;

public class Bible {
  // Width of window, scale,
  public final int width = 1225 * 10;
  public final int scale = 10;
  // Arc scale factor; 1 makes the final vis a circle
  public final double arc_height = 1;
  // Offset (for empty space on sides)
  public final int offset = (width - (1189 * (int)scale)) / 2;
  // List of all cross references
  public ArrayList<Arc> arcs;
  // List of first chapters in books
  public ArrayList<Chapter> chapters;

  // Constructor
  public Bible(){
    arcs = new ArrayList<Arc>();
    chapters = new ArrayList<Chapter>();
  }

  // Add a cross reference to list of cross references from a String input
  public void addArc(String line) {
    // Split line by comma
    String[] split_line = line.split(",");
    // Get data for Arc object
    int from_chapter_bible = Integer.parseInt(split_line[3]);
    int from_book_number = Integer.parseInt(split_line[1]);
    int to_chapter_bible = Integer.parseInt(split_line[8]);
    int to_book_number = Integer.parseInt(split_line[6]);
    // Create Arc object and add to list
    arcs.add(new Arc(from_chapter_bible, from_book_number, to_chapter_bible, to_book_number));
  }

  // Add a cross reference to list of cross references from a String input
  public void addChapter(String line) {
    // Split line by comma
    String[] split_line = line.split(",");
    // Get data for Chapter object
    int chapter_in_bible = Integer.parseInt(split_line[0]);
    String book_name = split_line[1];
    int chapter_in_book = Integer.parseInt(split_line[3]);
    // Save chapter if it's the first in its book
    if (chapter_in_book == 1) {
      chapters.add(new Chapter(chapter_in_bible, book_name));
    }
  }
}
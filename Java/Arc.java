public class Arc {

  // To and from data for chapter number in entire Bible and book number in Bible
  public int from_chapter_bible;
  public int from_book_number;
  public int to_chapter_bible;
  public int to_book_number;

  // Constructor
  public Arc(int from_chapter_bible, int from_book_number, int to_chapter_bible,
      int to_book_number) {
    this.from_chapter_bible = from_chapter_bible;
    this.from_book_number = from_book_number;
    this.to_chapter_bible = to_chapter_bible;
    this.to_book_number = to_book_number;
  }
}
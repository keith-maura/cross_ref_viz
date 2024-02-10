import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import java.awt.*;
import javax.imageio.ImageIO;
import javax.swing.*;

// Class for visualization
public class Run extends JFrame {

  public Run() throws FileNotFoundException {
    // A dummy window
    setTitle("Cross Refs");
    setSize(200, 200);
    setVisible(true);
    setDefaultCloseOperation(EXIT_ON_CLOSE);
  }

  // Determine color for arc
  public Color chooseColor(int from_book, int to_chapter, int to_book) {
    // Green if within same book
    if (from_book == to_book) {
      return new Color(0, 255, 0, 13);
    }
    // Blue if to New Testament
    else if (to_chapter >= 929) {
      return new Color(0, 0, 255, 13);
    }
    // Red if to Old Testament
    else {
      return new Color(255, 0, 0, 13);
    }
  }

  // Makes and saves png of visualization
  public void paint(Graphics g)
  {
    try {
      Bible bible = new Bible();
      String line;
      Scanner sc_refs = new Scanner(new File(
          "Cross_refs_all.csv"));
      // Ignore headers
      line = sc_refs.nextLine();
      // Read through remaining lines, add cross references to Bible object
      while (sc_refs.hasNextLine()) {
        line = sc_refs.nextLine();
        bible.addArc(line);
      }
      sc_refs.close();

      Scanner sc_ch = new Scanner(new File(
          "Bible_books.csv"));
      // Ignore headers
      line = sc_ch.nextLine();
      while (sc_ch.hasNextLine()) {
        line = sc_ch.nextLine();
        bible.addChapter(line);
      }
      sc_ch.close();

      // Create image
      BufferedImage image = new BufferedImage((int)(bible.width * 1.15), (int)(bible.width*1.15), BufferedImage.TYPE_INT_RGB);
      // Create graphics
      g = image.createGraphics();
      g.setColor(new Color(248, 240, 227));
      g.fillRect ( 0, 0, (int)(bible.width * 1.15), (int)(bible.width * 1.15));

      // Draw arc for each cross reference
      for (Arc a : bible.arcs) {
        int diameter = Math.abs(a.from_chapter_bible - a.to_chapter_bible);
        Color color = chooseColor(a.from_book_number, a.to_chapter_bible, a.to_book_number);
        g.setColor(color);
        // Only draw if diameter is at least 5
        if (diameter >= 10) {
          // Forward reference
          if (a.from_chapter_bible < a.to_chapter_bible) {
            g.drawArc(
                a.from_chapter_bible * bible.scale + bible.offset + (int) (bible.width * .075),
                (int)(bible.width * (1.15/2)) - (int)(diameter * bible.scale * bible.arc_height/2), diameter * bible.scale,
                (int) (diameter * bible.scale * bible.arc_height), 0, 180);
          }
          // Backward reference
          else {
            g.drawArc(a.to_chapter_bible * bible.scale + bible.offset + (int) (bible.width * .075),
                (int)(bible.width * (1.15/2)) - (int)(diameter * bible.scale * bible.arc_height/2), diameter * bible.scale,
                (int) (diameter * bible.scale * bible.arc_height), 180, 180);
          }
        }
      }
      // Draw horizontal line in middle for chapter line
      g.setColor(new Color(171,126,76));

      //int stagger = 50;
      // Draw vertical lines for each chapter
      for (Chapter c : bible.chapters) {
        /*
        if (stagger > 450) {
          stagger = 50;
        }
        */

        g.fillRect(c.chapter_number * bible.scale + bible.offset + (int)(bible.width * .075), 0, 2, (int)(bible.width * 1.15));
        /*
        Font font = new Font(null, Font.PLAIN, 30);
        AffineTransform affineTransform = new AffineTransform();
        affineTransform.rotate(Math.toRadians(270), 0, 0);
        Font rotatedFont = font.deriveFont(affineTransform);
        g.setFont(rotatedFont);
        g.drawString(c.book_name, c.chapter_number * bible.scale + bible.offset, bible.width);// - stagger);
        stagger += 200;
        */
      }
      // End of Bible line
      g.fillRect(1189 * bible.scale + bible.offset + (int)(bible.width * .075), 0, 4, (int)(bible.width * 1.15));


      // Horizontal middle line
      //g.fillRect(bible.offset + (int)(bible.width * .075), (int)(bible.width * (1.15/2)) - 5, 1189 * bible.scale, 10);
      // Same image
      ImageIO.write(image, "png", new File("Cross_refs_master.png"));
      System.out.println("Image saved");
      }
    catch (IOException e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) throws IOException {
    // Make Run object; it automatically calls paint method, and I don't know how to make an image
    // and save otherwise so I made it this way
    Run run = new Run();
  }
}

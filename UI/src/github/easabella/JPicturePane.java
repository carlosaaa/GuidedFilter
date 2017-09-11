package github.easabella;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.io.File;


class MyPanel extends JPanel {
    Image image = null;

    public void paintComponent(Graphics g) {
        super.paintComponent(g);


        try {
            if (image == null) {
                //   image = ImageIO.read(new File("D:\\zsfwork\\SHOW\\flower_nl.jpg"));
                image = ImageIO.read(new File("E:\\git_image\\bmp\\big.bmp"));
            }

            int w = getWidth();
            int h = getHeight();

            int iw = image.getWidth(null);
            int ih = image.getHeight(null);

            if (iw > w) {
                iw = w;
                ih = h*iw/w;
            } else if (ih > h) {
                ih = h;
                iw = w*ih/h;
            }

            g.drawImage(image, 0, 0, iw, ih, null);


        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}

/**
 * Created by Easabella.
 */
public class JPicturePane extends JScrollPane {

    MyPanel panel = new MyPanel();

    public JPicturePane() {
        super(VERTICAL_SCROLLBAR_ALWAYS, HORIZONTAL_SCROLLBAR_ALWAYS);
        setViewportView(panel);
    }

}

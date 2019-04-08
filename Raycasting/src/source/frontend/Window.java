package source.frontend;

import javax.swing.*;
import java.awt.*;

public class Window extends Canvas{
    JFrame jFrame;

    public Window(int width, int height, String title){
        Dimension dimension = new Dimension(width, height);
        setPreferredSize(dimension);
        setMaximumSize(dimension);
        setMinimumSize(dimension);

        jFrame = new JFrame();
        jFrame.add(this);
        jFrame.pack();
        jFrame.setResizable(false);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jFrame.setTitle(title);
        jFrame.setLocationRelativeTo(null);
        jFrame.setVisible(true);
    }
}

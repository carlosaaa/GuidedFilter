package github.easabella;

import javax.swing.*;
import java.util.logging.Level;
import java.util.logging.Logger;

class Main {

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }

        SwingUtilities.invokeLater(MyFrame::new);
    }
}


package github.easabella;

import javax.swing.*;
import java.awt.*;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.logging.Level;
import java.util.logging.Logger;

class Main extends JFrame {

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }

        SwingUtilities.invokeLater(() -> new Main().setVisible(true));
    }

    private Main() {
        this.setTitle("Java Class Viewer");
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        centerJFrame();
        this.createMenu();
        this.setVisible(true);
    }

    private void centerJFrame() {
        // Set main window size
        final Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
        this.setSize(
                (int) (d.getWidth() * 0.7),
                (int) (d.getHeight() * 0.7));

        // Center the main window
        this.setLocationRelativeTo(null);
    }

    private void createMenu() {
        final JMenuBar menuBar = new JMenuBar();
        this.setJMenuBar(menuBar);

        // File
        final JMenu menuFile = new JMenu("File");
        menuFile.setMnemonic(KeyEvent.VK_F);
        menuBar.add(menuFile);

        // File --> Open
        final JMenuItem menuItem_FileOpen = new JMenuItem("Open...", UIManager.getIcon("FileView.directoryIcon"));
        menuItem_FileOpen.setMnemonic(KeyEvent.VK_O);
        menuItem_FileOpen.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_O,
                InputEvent.CTRL_MASK));
        menuItem_FileOpen.addActionListener(e -> {
            //menu_FileOpen();
        });
        menuFile.add(menuItem_FileOpen);

        // File --> Close
        final JMenuItem menuItem_FileClose = new JMenuItem("Close");
        menuItem_FileClose.setMnemonic(KeyEvent.VK_C);
        menuItem_FileClose.addActionListener(e -> {
            //menu_FileClose();
        });
        menuFile.add(menuItem_FileClose);

        //
        //menuFile.addSeparator();
        // File --> Recent Files
        //JMenu menu_FileRecentFile = new JMenu("Recent Files");
        //menu_FileRecentFile.setMnemonic(KeyEvent.VK_R);
        //menuFile.add(menu_FileRecentFile);
        //
        menuFile.addSeparator();

        // File --> Exit
        final JMenuItem menuItem_FileExit = new JMenuItem("Exit", UIManager.getIcon("Table.ascendingSortIcon"));
        menuItem_FileExit.setMnemonic(KeyEvent.VK_X);
        menuItem_FileExit.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_X,
                InputEvent.ALT_MASK));
        menuItem_FileExit.addActionListener(e -> System.exit(0));
        menuFile.add(menuItem_FileExit);

        // Help
        final JMenu menuHelp = new JMenu("Help");
        menuFile.setMnemonic(KeyEvent.VK_H);
        menuBar.add(menuHelp);

        // Help --> Homepage
        final JMenuItem menuItem_HelpHomepage = new JMenuItem("Homepage");
        menuItem_HelpHomepage.setMnemonic(KeyEvent.VK_P);
        menuItem_HelpHomepage.addActionListener(e -> menu_HelpHomepage());

        menuHelp.add(menuItem_HelpHomepage);

        // Help --> About
        final JMenuItem menuItem_HelpAbout = new JMenuItem("About");
        menuItem_HelpAbout.setMnemonic(KeyEvent.VK_A);
        menuItem_HelpAbout.addActionListener(e ->  menu_HelpAbout());
        menuHelp.add(menuItem_HelpAbout);

    }

    private void menu_HelpAbout() {
        final JDialogAbout about = new JDialogAbout(this, "About");
        about.setLocationRelativeTo(this);
        about.setVisible(true);
    }

    private void menu_HelpHomepage() {
        try {
            Desktop.getDesktop().browse(new URI("https://github.com/amosshi/freeinternals/"));
        } catch (URISyntaxException | IOException ex) {
            JOptionPane.showMessageDialog(
                    this,
                    ex.getMessage(),
                    this.getTitle(),
                    JOptionPane.WARNING_MESSAGE);
        }
    }
}

package github.easabella;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

class MyFrame extends JFrame {

    private JPicturePane panelPic1 = new JPicturePane();
    private JPicturePane panelPic2 = new JPicturePane();

    public MyFrame() {
        this.setTitle("Guide Filter UI");
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        centerJFrame();
        this.createMenu();

        JPanel panelMain = new JPanel();
        panelMain.setLayout(new BorderLayout());
        getContentPane().add(panelMain);

        JPanel panelPic = new JPanel();
        panelPic.setLayout(new GridLayout(1,2));
        panelMain.add(panelPic, BorderLayout.CENTER);

       // panelPic1.setBorder(new LineBorder(Color.RED, 10));
       // panelPic2.setBorder(new LineBorder(Color.GREEN, 10));


        panelPic.add(panelPic1);
        panelPic.add(panelPic2);

        JPanel panelBtn = new JPanel(new GridLayout(1, 10));
        for (int i = 0; i < 10; i++) {

            panelBtn.add(new JButton(Integer.toString(i)));

        }

        panelMain.add(panelBtn, BorderLayout.SOUTH);

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

        {
            // File
            final JMenu menuFile = new JMenu("File");
            menuFile.setMnemonic(KeyEvent.VK_F);
            menuBar.add(menuFile);

            {
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
            }

            // Help
            final JMenu menuHelp = new JMenu("Help");
            menuFile.setMnemonic(KeyEvent.VK_H);
            menuBar.add(menuHelp);

            {
                // Help --> Homepage
                final JMenuItem menuItem_HelpHomepage = new JMenuItem("Homepage");
                menuItem_HelpHomepage.setMnemonic(KeyEvent.VK_P);
                menuItem_HelpHomepage.addActionListener(e -> menu_HelpHomepage());
                menuHelp.add(menuItem_HelpHomepage);

                // Help --> About
                final JMenuItem menuItem_HelpAbout = new JMenuItem("About");
                menuItem_HelpAbout.setMnemonic(KeyEvent.VK_A);
                menuItem_HelpAbout.addActionListener(e -> menu_HelpAbout());
                menuHelp.add(menuItem_HelpAbout);
            }
        }
    }

    private void menu_HelpAbout() {
        final JDialogAbout about = new JDialogAbout(this, "About");
        about.setLocationRelativeTo(this);
        about.setVisible(true);
    }

    private void menu_HelpHomepage() {
        try {
            Desktop.getDesktop().browse(new URI("https://github.com/easabella/GuidedFilter"));
        } catch (URISyntaxException | IOException ex) {
            JOptionPane.showMessageDialog(
                    this,
                    ex.getMessage(),
                    this.getTitle(),
                    JOptionPane.WARNING_MESSAGE);
        }
    }
}

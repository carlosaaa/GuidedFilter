package github.easabella;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.logging.Level;
import java.util.logging.Logger;

class JLabelHyperLink extends JLabel {

    private static final long serialVersionUID = 4876543219876500000L;

    private final String text;
    private final String url;
    private boolean isSupported;

    /**
     * Create a new Hyper Link enabled JLabel.
     *
     * @param text Text of the label
     * @param url Target URL
     */
    public JLabelHyperLink(final String text, final String url) {
        this.text = text;
        this.url = url;

        try {
            this.isSupported = Desktop.isDesktopSupported() && Desktop.getDesktop().isSupported(Desktop.Action.BROWSE);
        } catch (Exception e) {
            this.isSupported = false;
        }

        this.setText(false);
        this.addMouseListener(new MouseAdapter() {

            @Override
            public void mouseEntered(final MouseEvent e) {
                setText(isSupported);
                if (isSupported) {
                    setCursor(new Cursor(Cursor.HAND_CURSOR));
                }
            }

            @Override
            public void mouseExited(final MouseEvent e) {
                setText(false);
            }

            @Override
            public void mouseClicked(final MouseEvent e) {
                try {
                    Desktop.getDesktop().browse(
                            new java.net.URI(JLabelHyperLink.this.url));
                } catch (Exception ex) {
                    Logger.getLogger(JLabelHyperLink.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
    }

    private void setText(final boolean b) {
        if (!b) {
            setText("<html><font color=blue><u>" + text);
        } else {
            setText("<html><font color=red><u>" + text);
        }
    }
}


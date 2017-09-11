package github.easabella;


import javax.swing.*;
import java.awt.*;


class JDialogAbout extends JDialog {

    private static final long serialVersionUID = 4876543219876500000L;

    public JDialogAbout(final Frame owner, final String title) {
        super(owner, title);
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setModal(true);

        this.initComponents();
        this.pack();
        this.setResizable(false);
    }

    private void initComponents() {
        this.setLayout(new FlowLayout());

        final JButton buttonClose = new JButton("Close");
        buttonClose.addActionListener(e -> buttonOK_Clicked());

//      Lay out the labels from top to bottom.
        final JPanel listPane = new JPanel();
        listPane.setLayout(new BoxLayout(listPane, BoxLayout.PAGE_AXIS));

        final JLabel label = new JLabel("Guilded Filter UI");
        label.setFont(new Font(Font.DIALOG, Font.BOLD, 20));

        listPane.add(label);
        listPane.add(Box.createRigidArea(new Dimension(0, 5)));
        listPane.add(new JLabelHyperLink(
                "111",
                "https://docs.oracle.com/javase/specs/jvms/se8/html/"));
        listPane.add(Box.createRigidArea(new Dimension(0, 5)));
        listPane.add(new JLabel("Author: Easabella"));
        listPane.add(Box.createRigidArea(new Dimension(0, 20)));
        listPane.add(new JLabelHyperLink(
                "222",
                "https://github.com/easabella/GuidedFilter"));
        listPane.add(Box.createRigidArea(new Dimension(0, 5)));
        listPane.add(new JLabel("333"));
        listPane.add(Box.createRigidArea(new Dimension(0, 5)));

        listPane.setBorder(//BorderFactory.createEmptyBorder(10, 10, 10, 10));
                BorderFactory.createLineBorder(Color.BLACK));

//      Lay out the buttons from left to right.
        final JPanel buttonPane = new JPanel();
        buttonPane.setLayout(new BoxLayout(buttonPane, BoxLayout.LINE_AXIS));
        buttonPane.setBorder(//BorderFactory.createEmptyBorder(0, 10, 10, 10));
                BorderFactory.createLineBorder(Color.RED));
        buttonPane.add(Box.createHorizontalGlue());
        buttonPane.add(buttonClose);

//      Put everything together, using the content pane's BorderLayout.
        final Container contentPane = this.getContentPane();
        contentPane.add(listPane, BorderLayout.NORTH);
        contentPane.add(buttonPane, BorderLayout.SOUTH);

    }

    private void buttonOK_Clicked() {
        this.setVisible(false);
    }
}


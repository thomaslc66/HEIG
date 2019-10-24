/**
 * @File        : GraphicInterface.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 19.03.2018
 *
 * @Goal        : Main user interface
 *
 * @Comment(s)  : -
 *
 * @See JFrame, Runnable, Displayer
 */

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class GraphicInterface extends JFrame implements Runnable, Displayer {

    /* Instance unique */
    private static GraphicInterface INSTANCE = null;
    private WindowsContent windowContent;
    private ArrayList<Form> forms;
    private Thread forever;
    private boolean isRunning;

    private GraphicInterface() {
        super();
        this.setResizable(true);
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        int size = 300;
        windowContent = new WindowsContent();
        windowContent.setPreferredSize(new Dimension(size,size));
        windowContent.setVisible(true);

        forms = new ArrayList<>();

        this.add(windowContent);

        pack();
        setVisible(true);

        forever = new Thread(this);
        isRunning = false;
    }

    /**
     * Start to move the forms
     */
    public void start() {
        isRunning = true;
        forever.start();
    }

    /**
     * Add form
     * @param form The form to add
     */
    public void addForm(Form form) {
        forms.add(form);
    }

    /**
     * Get the content width
     * @return The content Width
     */
    public int getWidth() {
        return windowContent.getHeight();
    }

    /**
     * Get the content Height
     * @return The content Height
     */
    public int getHeight() {
        return windowContent.getWidth();
    }

    /**
     * Get the Graphic2D
     * @return The Graphic2D
     */
    public Graphics2D getGraphics() {
        return (Graphics2D)super.getGraphics();
    }

    /**
     * Repaint the content
     */
    public void repaint() {
        windowContent.repaint();
    }

    /**
     * Set the window title
     * @param s The new title
     */
    public void setTitle(String s) {
        super.setTitle(s);
    }

    /**
     * Run the content
     */
    @Override
    public void run() {
        while (isRunning) {
            for (Form form : forms) {
                form.moveForm(windowContent.getWidth(), windowContent.getHeight());
            }

            windowContent.repaint();

            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Get a singleton of GraphicInterface
     * @return A singleton of GraphicInterface
     */
    public static GraphicInterface getInstance(){
        if(INSTANCE == null){
            INSTANCE = new GraphicInterface();
        }
        return INSTANCE;
    }

    class WindowsContent extends JPanel {

        /**
         * Paint all forms into the content
         * @param g The graphic to paint the forms
         */
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            for(Form form : forms){
                form.draw((Graphics2D)g);
            }
        }
    }
}

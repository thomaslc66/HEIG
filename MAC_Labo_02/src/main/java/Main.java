/**
 * @File        : Main.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 19.03.2018
 *
 * @Goal        : Main
 *
 * @Comment(s)  : -
 *
 */

import java.awt.*;

public class Main {
    private static GraphicInterface gui;
    private static final int NB_MAX_FORMS = 40;

    public static void main(String[] args){
        gui = GraphicInterface.getInstance();
        gui.setTitle("Bouncer");
        populateGui();
        gui.start();
    }

    /**
     * Populate the GraphicInterface with forms
     */
    private static void populateGui() {
        for(int i = 0; i < Utils.getRandomInt(NB_MAX_FORMS); ++i) {
            gui.addForm(new Circle(Color.yellow, gui.getWidth(), gui.getHeight()));
        }

        for(int i = 0; i < Utils.getRandomInt(NB_MAX_FORMS); ++i) {
            gui.addForm(new Square(Color.blue, gui.getWidth(), gui.getHeight()));
        }
    }
}

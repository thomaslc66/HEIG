/**
 * @File        : Displayer.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 19.03.2018
 *
 * @Goal        : Interface to define an Object than can be display
 *
 * @Comment(s)  : -
 *
 */

import java.awt.*;

public interface Displayer
{
    int getWidth();
    int getHeight();
    Graphics2D getGraphics();
    void repaint();
    void setTitle(String s);
}
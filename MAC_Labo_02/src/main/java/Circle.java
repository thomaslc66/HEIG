/**
 * @File        : Circle.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 19.03.2018
 *
 * @Goal        : Circle form
 *
 * @Comment(s)  : -
 *
 * @See Form
 */

import java.awt.*;

public class Circle extends Form {

    private int radius;

    public Circle(Color color, int widthLimit, int heightLimit){
        super(color, widthLimit, heightLimit);
        this.radius = Utils.getRandomInt(10, 50);
    }

    /**
     * Draw the form
     * @param g The graphic to draw the form
     */
    @Override
    public void draw(Graphics2D g) {
        super.draw(g);
        g.fillOval(super.getPosition().x,super.getPosition().y, radius, radius);
    }

    /**
     * Give the delta size to bounce correctly on the content
     * @return The delta size to bounce correctly on the content
     */
    @Override
    public int getDeltaSize() {
        return radius;
    }
}

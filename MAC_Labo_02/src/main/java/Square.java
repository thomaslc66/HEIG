/**
 * @File        : Square.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 19.03.2018
 *
 * @Goal        : Square form
 *
 * @Comment(s)  : -
 *
 * @See Form
 */

import java.awt.*;

public class Square extends Form {

    private int size;

    public Square(Color color, int widthLimit, int heightLimit){
        super(color, widthLimit, heightLimit);
        this.size = Utils.getRandomInt(10, 50);
    }

    /**
     * Draw the form
     * @param g The graphic to draw the form
     */
    @Override
    public void draw(Graphics2D g) {
        super.draw(g);
        g.fillRect(getPosition().x, getPosition().y, size, size);
    }

    /**
     * Give the delta size to bounce correctly on the content
     * @return The delta size to bounce correctly on the content
     */
    @Override
    public int getDeltaSize() {
        return size;
    }
}

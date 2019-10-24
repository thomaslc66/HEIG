/**
 * @File        : Form.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 19.03.2018
 *
 * @Goal        : Common form required
 *
 * @Comment(s)  : -
 *
 */

import java.awt.*;

public abstract class Form {

    private Color color;
    private Point position;
    private int dx;
    private int dy;

    Form(Color color, int widthLimit, int heightLimit){
        this.color = color;
        position = new Point(Utils.getRandomInt(widthLimit), Utils.getRandomInt(heightLimit));
        dx = Utils.getRandomOnePosNeg();
        dy = Utils.getRandomOnePosNeg();
    }

    /**
     * Draw the color of the form
     * @param g The graphic to draw the form
     */
    protected void draw(Graphics2D g) {
        g.setColor(color);
    }

    /**
     * Get the form position
     * @return The form position
     */
    protected Point getPosition() {
        return position;
    }

    /**
     * Move the form inside the content
     * @param widthLimit The content max width limit
     * @param heightLimit The content max height limit
     */
    public void moveForm(int widthLimit, int heightLimit) {
        if(position.x < 0) {
            dx = 1;
        }
        if(position.x + getDeltaSize() >= widthLimit) {
            dx = -1;
        }

        if(position.y < 0) {
            dy = 1;
        }
        if(position.y + getDeltaSize() >= heightLimit) {
            dy = -1;
        }

        position.x += dx;
        position.y += dy;
    }

    /**
     * Give the delta size to bounce correctly on the content
     * @return The delta size to bounce correctly on the content
     */
    public abstract int getDeltaSize();
}

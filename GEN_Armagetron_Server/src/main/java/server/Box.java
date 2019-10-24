/**
 * @project     : Argmagetron
 * @file        : Box.java
 * @author(s)   : Thomas Lechaire
 * @date        : 11.05.2017
 *
 * @brief        : Class Box contained in the GridGame
 */
package server;

import java.awt.*;

/**
 * @class Box
 */
class Box {

    /**
     * Attributes
     */
    private static final int IDWALL = 33333;
    private int id;
    private Color color;

    /**
     * Constructor
     */
    Box(){}


    /**
     * Constructor
     *
     * @param c Color of the Box
     */
    Box(Color c){
        this.color = c;
    }

    /**
     * Constructor
     *
     * @param id of the Box
     */
    Box(int id){
        this.id = id;
    }

    /**
     * @fn void setColor()
     *
     * @brief Set the color of the Box
     *
     * @author Thomas Lechaire
     *
     * @param c Color of the box
     */
    void setColor(Color c){
        this.color = c;
    }


    /**
     * @fn void setId()
     *
     * @brief Set the id of the Box
     *
     * @author Thomas Lechaire
     *
     * @param id of the box
     */
    void setId(int id){
        this.id = id;
    }

    /**
     * @fn void IsWall()
     *
     * @brief make the Box become a wall for others
     *
     * @author Thomas Lechaire
     */
    void isWall(){
        this.id = IDWALL;
    }

    /**
     * @fn int getId()
     *
     * @brief Get the id of the current Box
     *
     * @author Thomas Lechaire
     *
     * @return int equal to the Id of the Box
     *
     */
    int getId() {
        return id;
    }


    /**
     * @fn Color getColor()
     *
     * @brief get the Color assigned to the box
     *
     * @author Thomas Lechaire
     *
     * @return Color of the Box
     */
    Color getColor() {
        return color;
    }

    /**
     * @fn boolean isEmpty()
     *
     * @brief check if the box is empty or not
     *
     * @author Thomas Lechaire
     *
     * @return boolean True, the box is empty
     * @return boolean False, the box is not empty
     */
    boolean isEmpty(){
        return (this.id != IDWALL && this.color == null);
    }
}

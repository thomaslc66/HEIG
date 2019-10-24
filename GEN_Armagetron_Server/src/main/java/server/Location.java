/**
 * @project     : Argmagetron
 * @file        : Location.java
 * @author(s)   : Thomas Lechaire
 * @date        : 11.05.2017
 *
 * @brief       : Class Location use to set Starting location to player
 */


package server;

import java.awt.*;
import java.util.ArrayList;

/**
 * @class Location
 */
public class Location {

    /**
     * ArrayList of fixed position for the start of the 4 players
     */
    private final static ArrayList<Point> arrayList = new ArrayList<Point>(){{
        add(new Point(5,5));
        add(new Point(75,75));
        add(new Point(5,75));
        add(new Point(75,5));
    }};

    /**
     * Direction given to the for player at start point.
     */
    private final static short UP = 0;
    private final static short LEFT = 1;
    private final static short DOWN = 2;
    private final static short RIGHT = 3;
    private static short index = Player.UP;
    private short direction;
    private Point position;


    /**
     * Constructor
     */
    Location() {
        //Setting the direction
        switch (index){
            case 0:
                this.direction = DOWN;
                break;
            case 1:
                this.direction = UP;
                break;
            case 2:
                this.direction = LEFT;
                break;
            case 3:
                this.direction = RIGHT;
                break;
        }
        //setting the positions
        this.position = arrayList.get(index);
        if(index == 3){
            index = 0;
        }else{
            index++;
        }
    }

    /**
     * @fn short getDirection()
     *
     * @brief Get the direction
     *
     * @author Thomas Lechaire
     *
     * @return short of the direction
     */
    short getDirection() {
        return direction;
    }

    /**
     * @fn Point getPosition()
     *
     * @brief Get the position of the player
     *
     * @author Thomas Lechaire
     *
     * @return Point The position of the player
     */
    Point getPosition() {
        return position;
    }

}

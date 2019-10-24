/**
 * @project     : Argmagetron
 * @file        : Player.java
 * @author(s)   : Michael Brouchoud
 * @date        : 18.05.2017
 *
 * @brief        : Use to manage a player
 *
 */
package server;

import java.awt.*;
import java.util.UUID;

/**
 * @class Player
 */
class Player {
    private UUID uniqueId;
    private String username;
    private Point position;
    private Point lastPosition;
    private Color color;
    final static short UP = 0;
    final static short LEFT = 1;
    final static short DOWN = 2;
    final static short RIGHT = 3;
    private short direction;
    private boolean isAlive;

    /**
     * Constructor
     */
    Player() {
        this("test", Color.green);
    }

    /**
     * Constructor
     *
     * @param username The player's user name
     * @param color The player's color
     */
    Player(String username, Color color) {
        this(username, color, new Location());
    }

    /**
     * Constructor
     *
     * @param username The player's user name
     * @param color The player's color
     * @param location The player's first position
     */
    Player(String username, Color color, Location location) {
        this.username = username;
        this.uniqueId = UUID.randomUUID();
        this.color = color;

        //TODO Check that when the code is better
        this.position = location.getPosition();
        this.direction = location.getDirection();
        this.isAlive = true;
        this.lastPosition = position;
    }

    /**
     * @fn Point getPosition()
     *
     * @brief Return the player's position
     *
     * @author Michael Brouchoud
     *
     * @return Point The player's position
     */
    Point getPosition() {
        return position;
    }

    /**
     * @fn Point getLastPosition()
     *
     * @brief Return the player's last position
     *
     * @author Michael Brouchoud
     *
     * @return Point The player's last position
     */
    Point getLastPosition(){
        return lastPosition;
    }

    /**
     * @fn private void setLastPosition(Point p)
     *
     * @brief Set the last position of the player
     *
     * @author Michael Brouchoud
     *
     * @param p The last position to set
     */
    private void setLastPosition(Point p){
        this.lastPosition = new Point(p);
    }

    /**
     * @fn void setPosition(Point p)
     *
     * @brief Set the position of the player
     *
     * @author Michael Brouchoud
     *
     * @param p The position to set
     */
    void setPosition(Point p){
        this.position = new Point(p);
    }

    /**
     * @fn UUID getUniqueId()
     *
     * @brief Get the player's UUID
     *
     * @author Michael Brouchoud
     *
     * @return UUID the player's UUID
     */
    UUID getUniqueId() {
        return uniqueId;
    }

    /**
     * @fn String getUsername()
     *
     * @brief Get the player's username
     *
     * @author Michael Brouchoud
     *
     * @return String the player's username
     */
    String getUsername() {
        return username;
    }

    /**
     * @fn Color getColor()
     *
     * @brief Get the player's Color
     *
     * @author Michael Brouchoud
     *
     * @return Color the player's Color
     */
    Color getColor() {
        return color;
    }

    /**
     * @fn void turnLeft()
     *
     * @brief Set the direction of the player when turn left
     *
     * @author Michael Brouchoud
     */
    void turnLeft() {
        switch (direction) {
            case UP:
                direction = LEFT;
                break;
            case DOWN:
                direction = RIGHT;
                break;
            case LEFT:
                direction = DOWN;
                break;
            case RIGHT:
                direction = UP;
                break;
        }
    }

    /**
     * @fn void turnRight()
     *
     * @brief Set the direction of the player when turn right
     *
     * @author Michael Brouchoud
     */
    void turnRight() {
        switch (direction) {
            case LEFT:
                direction = UP;
                break;
            case RIGHT:
                direction = DOWN;
                break;
            case UP:
                direction = RIGHT;
                break;
            case DOWN:
                direction = LEFT;
                break;
        }
    }

    /**
     * @fn void updatePosition()
     *
     * @brief Update the player's position
     *
     * @author Michael Brouchoud
     */
    void updatePosition() {
        if(this.isAlive) {
            this.setLastPosition(position);
            switch (direction) {
                case LEFT:
                    --position.y;
                    break;
                case RIGHT:
                    ++position.y;
                    break;
                case UP:
                    --position.x;
                    break;
                case DOWN:
                    ++position.x;
                    break;

            }
        }
    }

    /**
     * @fn boolean isAlive()
     *
     * @brief Indicate if the player is alive
     *
     * @author Michael Brouchoud
     *
     * @return true the player is alive
     * @return false the player is dead
     */
    boolean isAlive() {
        return this.isAlive;
    }

    /**
     * @fn void die()
     *
     * @brief Kill the player
     *
     * @author Michael Brouchoud
     */
    void die() { this.isAlive = false; }
}

/**
 * @project     : Argmagetron
 * @file        : GameGrid.java
 * @author(s)   : Thomas Lechaire
 * @date        : 11.05.2017
 *
 * @brief        : class use to manage the GameGrid
 */

package server;

import java.awt.*;
import java.util.ArrayList;

/**
 * @class GameGrid
 */
class GameGrid {

    /**
     * attributes
     */
    private static final short WIDTH = 80;
    private static final short HIGH = 80;
    private static final int IDWALL = 33333;
    private ArrayList<ArrayList<Box>> gameGrid = new ArrayList<ArrayList<Box>>();

    /**
     * Constructor
     */
    GameGrid(){
        initGrid();
    }


    /**
     * @fn private void initGrid()
     *
     * @brief Initialisation of the GameGrid
     *
     * @author Thomas Lechaire
     */
    private void initGrid(){
        for (int i = 0; i < WIDTH; i++){
            ArrayList<Box> line = new ArrayList<Box>();
            for (int j = 0; j < HIGH; j++){
                line.add(new Box()); //case vide
            }
            gameGrid.add(line);
        }
    }

    /**
     * @fn void updateGameGrid(ArrayList<Player> players)
     *
     * @breif update the Game Grid and set box to wall after
     *         the passage of a player
     *
     * @author Thomas Lechaire
     *
     * @param players Array of Player
     */
    void updateGameGrid(ArrayList<Player> players){
        for (Player p : players){
            synchronized (p) {
                Point point = p.getPosition();
                if (checkDeath(p)) {
                    /* TODO if time remove the player form the list to send less data */
                    //players.remove(p);
                } else {
                    //The box became a wall
                    setBoxToWall(point);
                }
            }
        }
    }

    /**
     * @fn private void setBoxToWall(Point p)
     *
     * @brief Set the box like a wall
     *
     * @author Thomas Lechaire
     * @param p The position of the box to set
     */
    private void setBoxToWall(Point p){
        if(p.y >= 0 && p.x >= 0){
            gameGrid.get(p.x).get(p.y).isWall();
        }
    }

    /**
     * @fn Box getBox(Point p)
     *
     * @brief Get the Box corresponding to the Point
     *
     * @author Thomas Lechaire
     *
     * @param p The Point
     *
     * @return The Box corresponding to the Point
     */
    Box getBox(Point p){
        return gameGrid.get(p.x).get(p.y);
    }


    /**
     * @fn boolean checkDeath(Player player)
     *
     * @brief Check if the player will die
     *
     * @author Thomas Lechaire
     *
     * @param player The player to check
     *
     * @return True The player is Alive
     * @return False The player is dead
     */
    boolean checkDeath(Player player){
        //Point lastPosition = null;
        boolean isDead = false;

        /*** part to manage the grid limits ***/
        //if player goes up
        if(player.getPosition().y < 0){
            isDead = die(player, player.getLastPosition());
        }
        //if player goes down
        else if(player.getPosition().y >= gameGrid.size()){
            isDead = die(player, player.getLastPosition());
        }//if player goes right
        else if(player.getPosition().x >= gameGrid.size()){
            isDead = die(player, player.getLastPosition());
        }//if player goes left
        else if(player.getPosition().x < 0){
            isDead = die(player, player.getLastPosition());
        }
        /*** end of grid limit ***/
        else{
            //check if case is Not Empty.
            if(!getBox(player.getPosition()).isEmpty()){
                isDead = die(player, player.getLastPosition());
            }
        }

        return isDead;
    }

    /**
     * @fn private boolean die(Player player, Point lastPosition)
     *
     * @brief Kill the player
     *
     * @author Thomas Lechaire
     *
     * @param player The player to kill
     * @param lastPosition The player's last position
     *
     * @return True The player is Alive
     * @return False The player is dead
     */
    private boolean die(Player player, Point lastPosition) {
        player.setPosition(lastPosition);
        player.die();
        return true;
    }

    /**
     * @fn int getIdWall()
     *
     * @brief Get the id of the wall
     *
     * @author Thomas Lechaire
     * 
     * @return int The id of the wall
     */
    /* méthode pour le test*/
    int getIdWall(){
        return IDWALL;
    }

    /**
     * @fn short getWidth()
     *
     * @brief Get the grid's width
     *
     * @author Thomas Lechaire
     * 
     * @return short The grid's width
     */
    short getWidth() {
        return WIDTH;
    }

    /**
     * @fn short getHeight()
     *
     * @brief Get the grid's height
     *
     * @author Thomas Lechaire
     *
     * @return short The grid's height
     */
    short getHeight() {
        return HIGH;
    }
}

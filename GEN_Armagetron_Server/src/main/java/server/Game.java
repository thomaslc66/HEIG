/**
 * @project     : Argmagetron
 * @file        : Game.java
 * @author(s)   : Michael Brouchoud
 * @date        : 30.05.2017
 *
 * @brief        : Use to Manage the Game
 *
 */

package server;

import share.Util;

import java.util.ArrayList;
import java.util.Collections;
import java.util.UUID;

/**
 * @class Game
 */
class Game implements Runnable {
    private ArrayList<Player> players;
    private ArrayList<Player> finalPlayers;
    private Controller controller;
    private boolean isRunning;
    private Thread thread;
    private GameGrid gameGrid;
    static final short TIME_TO_WAIT_BEFORE_GAME_START = 5000;
    private static final short MAX_PLAYER = 4; //TODO A adpater pour la release
    private static final short GAME_SPEED = 100; //TODO A adpater pour la release

   /**
     * Constructor
     *
     * @param controller The game's controller
     */
    Game(Controller controller) {
        this.finalPlayers = new ArrayList<Player>();
        this.players = new ArrayList<Player>();
        this.controller = controller;
        this.isRunning = false;
        this.thread = new Thread(this);
        this.gameGrid = new GameGrid();
    }

    /**
     * @fn void add(Player player)
     *
     * @brief Add player to the game.
     *        and start the game if all players are connected
     *
     * @author Michael Brouchoud
     *
     * @param player The player to add
     */
    void add(Player player) {
        if(players.size() < MAX_PLAYER) {
            players.add(player);
            if(players.size() == MAX_PLAYER) {
                controller.startGame();
            }
        }
    }

    /**
     * @fn final ArrayList<Player> getPlayers()
     *
     * @brief Add player to the game.
     *        and start the game if all players are connected
     *
     * @author Michael Brouchoud
     *
     * @return ArrayList<Player> the game's players
     */
    final ArrayList<Player> getPlayers() {
        return this.players;
    }

    /**
     * @fn Player getPlayer(UUID uniqueId)
     *
     * @brief Return the player with the same UUID
     *
     * @author Michael Brouchoud
     *
     * @param uniqueId The player's UUID to find
     *
     * @return Player The player with the same UUID
     * @return null No player found
     */
    Player getPlayer(UUID uniqueId) {
        for(Player player : players) {
            if(player.getUniqueId().equals(uniqueId)) {
                return player;
            }
        }
        return null;
    }

    /**
     * @fn void start()
     *
     * @brief Start the game
     *
     * @author Michael Brouchoud
     */
    void start() {
        this.isRunning = true;
        thread.start();
    }

    /**
     * @fn void stop()
     *
     * @brief Stop the game
     *
     * @author Michael Brouchoud
     */
    void stop() {
        this.isRunning = false;
    }

    /**
     * @fn public void run()
     *
     * @brief Renew the game state and send to all clients the new game state
     *
     * @author Michael Brouchoud
     */
    public void run() {
        //Wait some seconds before to start the game
        try {
            Thread.sleep(TIME_TO_WAIT_BEFORE_GAME_START); //TODO A adpater pour la release (vitesse du jeu)
        } catch (InterruptedException e) {
            Util.print("Something interrupt the game : " + e);
            e.printStackTrace();
        }

        while (isRunning) {
            if(!isEndGame()) {
                this.updatePlayerPosition(); //TODO vider la liste des joueurs morts.
                this.gameGrid.updateGameGrid(players); //update de la position des joueurs sur la grille
                this.controller.sendGame(this.players);
                try {
                    Thread.sleep(GAME_SPEED);
                } catch (InterruptedException e) {
                    Util.print("Something interrupt the game : " + e);
                    e.printStackTrace();
                }
            }
            else {
                this.controller.endGame();
                this.controller.sendGame(this.finalPlayers); //Envoie la liste de tous les player dans l'ordre du premier mort au dernier
                this.controller.stopGame();
            }
        }
    }

    /**
     * @fn private boolean isEndGame()
     *
     * @brief Return if it is the end of the game
     *
     * @author Michael Brouchoud
     *
     * @return true it is the end of the game
     * @return false it is not the end of the game
     */
    private boolean isEndGame() {
        for(Player player : players) {
            if (!player.isAlive() && !finalPlayers.contains(player)){
                finalPlayers.add(player);
            }
        }
        if(finalPlayers.size() < MAX_PLAYER) {
            return false;
        }
        Collections.reverse(finalPlayers);
        return true;
    }

    /**
     * @fn private void updatePlayerPosition()
     *
     * @brief Update all players position
     *
     * @author Michael Brouchoud
     */
    private void updatePlayerPosition() {
        for(Player player : players) {
            player.updatePosition();
        }
    }

    /**
     * @fn public boolean isRunning()
     *
     * @brief Indicate if the game is running
     *
     * @author Michael Brouchoud
     *
     * @return true The game is running
     * @return true The game is not running
     */
    boolean isRunning() {
        return this.isRunning;
    }
}

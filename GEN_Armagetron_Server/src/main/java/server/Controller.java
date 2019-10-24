/**
 * @project     : Argmagetron
 * @file        : Controller.java
 * @author(s)   : Michael Brouchoud
 * @date        : 30.05.2017
 *
 * @brief        : Check all data between Game and Server
 *
 */
package server;

import data.*;
import share.Util;

import java.util.ArrayList;

/**
 * @class Controller
 */
class Controller {
    private Server server;
    private Game game;

    /**
     *
     * Constructor
     *
     * @param server The server to control
     */
    Controller(Server server) {
        this.newGame();
        this.server = server;
    }

    /**
     * @fn private void newGame()
     *
     * @brief Create a new Game
     *
     * @author Michael Brouchoud
     */
    private void newGame() {
        this.game = new Game(this);
    }

    /**
     * @fn void startGame()
     *
     * @brief Start a new game and notify all clients
     *
     * @author Michael Brouchoud
     */
    void startGame() {
        this.sendGame(this.game.getPlayers());
        this.server.broadcastClients(new GameStatData(GameStatData.START_GAME, Game.TIME_TO_WAIT_BEFORE_GAME_START));
        this.game.start();
    }

    /**
     * @fn void endGame()
     *
     * @brief End the game and notify all clients
     *
     * @author Michael Brouchoud
     */
    void endGame() {
        this.server.broadcastClients(new GameStatData(GameStatData.END_GAME, (short)0));
        this.stopGame();
    }

    /**
     * @fn void stopGame()
     *
     * @brief Stop the game
     *
     * @author Michael Brouchoud
     */
    void stopGame() {
        this.game.stop();
    }

    /**
     * @fn boolean processData(Object o, ClientThread clientThread)
     *
     * @brief Process the object received by the client
     *
     * @author Michael Brouchoud
     *
     * @param o The object to process
     * @param clientThread The client who sent the object
     *
     * @return true The data was proceed successfully
     * @return true The data was proceed not successfully
     */
    boolean processData(Object o, ClientThread clientThread) {
        if(o instanceof ConnectionData) {
            Util.print("Client connected.");
            clientThread.sendData(this.processConnection((ConnectionData) o));
            return true;
        }
        else if(o instanceof ClientStatData) {
            this.processClientStatData((ClientStatData) o, clientThread);
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * @fn private PlayerData processConnection(ConnectionData connectionData)
     *
     * @brief Process the ConnectionData
     *
     * @author Michael Brouchoud
     *
     * @param connectionData The ConnectionData to process
     *
     * @return PlayerData The client's player configuration
     */
    private PlayerData processConnection(ConnectionData connectionData) {
        Player player = new Player(connectionData.getUsername(), (connectionData.getColor()), new Location());
        this.addPlayer(player);
        return new PlayerData(player.getUniqueId(), player.getPosition(), player.getUsername(), player.getColor(), player.isAlive());
    }

    /**
     * @fn void addPlayer(Player player)
     *
     * @brief Add player to game
     *
     * @author Michael Brouchoud
     *
     * @param player The player to add
     */
    void addPlayer(Player player) {
        this.game.add(player);
    }

    /**
     * @fn private void processClientStatData(ClientStatData clientStatData, ClientThread clientThread)
     *
     * @brief Process the ConnectionData
     *
     * @author Michael Brouchoud
     *
     * @param clientStatData The ConnectionData to process
     * @param clientThread The client who sent the ConnectionData
     */
    private void processClientStatData(ClientStatData clientStatData, ClientThread clientThread) {
        switch (clientStatData.getType()) {
            case ClientStatData.TURN_LEFT:
                synchronized (this) {
                    Player player = this.game.getPlayer(clientStatData.getUniqueId());
                    if(player != null) {
                        player.turnLeft();
                    }
                }
                break;
            case ClientStatData.TURN_RIGHT:
                synchronized (this) {
                    Player player = this.game.getPlayer(clientStatData.getUniqueId());
                    if(player != null) {
                        player.turnRight();
                    }
                }
                break;
            case ClientStatData.LOGOUT:
                this.server.remove(clientThread);
                break;
        }
    }

    /**
     * @fn boolean sendGame(ArrayList<Player> players)
     *
     * @brief Send a GameData to all clients and indicate if it was send successfully
     *
     * @author Michael Brouchoud
     *
     * @param players The players to send with the game
     *
     * @return true The game is send
     * @return true The game is not send
     */
    boolean sendGame(ArrayList<Player> players) {
        boolean isGameSend = false;
        synchronized (this) {
            ArrayList<PlayerData> playersData = new ArrayList<PlayerData>();
            for (Player player : players) {
                playersData.add(new PlayerData(player.getUniqueId(), player.getPosition(), player.getUsername(), player.getColor(), player.isAlive()));
            }
            this.server.broadcastClients(new GameData(playersData));
            isGameSend = true;
        }
        return isGameSend;
    }

    /**
     * @fn boolean isRunning()
     *
     * @brief Indicate if the game is running
     *
     * @author Michael Brouchoud
     *
     * @return true The game is running
     * @return true The game is not running
     */
    boolean gameIsRunning() {
        return this.game.isRunning();
    }

    /**
     * @fn boolean isRunning()
     *
     * @brief Set the Game
     *
     * @author Michael Brouchoud
     *
     * @param game The game to set
     */
    void setGame(Game game) {
        this.game = game;
    }
}

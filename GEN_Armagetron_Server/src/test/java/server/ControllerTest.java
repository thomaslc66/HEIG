/**
 * @project     : Argmagetron
 * @file        : ControllerTest.java
 * @author(s)   : Michaël Brouchoud
 * @date        : 05.06.2017
 *
 * @brief        : Test the class ControllerTest
 */

package server;

import clientTest.Client;
import data.ClientStatData;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.UUID;

public class ControllerTest {
    private Controller controller;

    @Before
    public void beforeStart() {
        controller = new Controller(TestUtils.server);
        TestUtils.server.setController(controller);
        while (!controller.gameIsRunning()) {
            new Client("localhost", TestUtils.port);
        }
    }

    @Test
    public void startGame() throws Exception {
        Assert.assertTrue(controller.gameIsRunning());
    }

    @Test
    public void endGame() throws Exception {
        Controller controller = new Controller(TestUtils.server);
        controller.startGame();
        Assert.assertTrue(controller.gameIsRunning());

        controller.endGame();

        Assert.assertFalse(controller.gameIsRunning());
    }

    @Test
    public void processData() throws Exception {
        ClientThread clientThread = TestUtils.server.getClientThread(0);

        Player player = new Player();
        controller.addPlayer(player);
        Assert.assertTrue(controller.processData(new ClientStatData(ClientStatData.TURN_RIGHT, player.getUniqueId()), clientThread));
        Assert.assertTrue(controller.processData(new ClientStatData(ClientStatData.TURN_RIGHT, player.getUniqueId()), clientThread));
        Assert.assertTrue(controller.processData(new ClientStatData(ClientStatData.TURN_RIGHT, UUID.randomUUID()), clientThread));
        Assert.assertTrue(controller.processData(new ClientStatData(ClientStatData.LOGOUT, UUID.randomUUID()), clientThread));
    }

    @Test
    public void sendGame() throws Exception {
        ArrayList<Player> players = new ArrayList<Player>() {{
            add(new Player());
            add(new Player());
            add(new Player());
            add(new Player());
        }};

        Assert.assertTrue(controller.sendGame(players));
    }

    @Test
    public void canCreateController() throws Exception {
        Assert.assertNotNull(new Controller(TestUtils.server));
    }

}
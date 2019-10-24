package server;

import clientTest.Client;
import org.junit.Assert;
import org.junit.Test;

public class GameTest {
    @Test
    public void add() throws Exception {
        Controller controller = new Controller(TestUtils.server);
        Game game = new Game(controller);
        controller.setGame(game);
        TestUtils.server.setController(controller);
        int cpt = -1;
        while (!game.isRunning()) {
            new Client("localhost", TestUtils.port);
            cpt++;
        }
        Assert.assertEquals(game.getPlayers().size(), cpt);
    }

    @Test
    public void getPlayers() throws Exception {
        Game game = new Game(new Controller(TestUtils.server));
        Assert.assertNotNull(game.getPlayers());
    }

    @Test
    public void getPlayer() throws Exception {
        Controller controller = new Controller(TestUtils.server);
        Game game = new Game(controller);
        controller.setGame(game);
        TestUtils.server.setController(controller);
        while (!game.isRunning()) {
            new Client("localhost", TestUtils.port);
        }
        Assert.assertNotNull(game.getPlayer(game.getPlayers().get(0).getUniqueId()));
    }

    @Test
    public void startStopisRunning() throws Exception {
        Game game = new Game(new Controller(TestUtils.server));
        Assert.assertFalse(game.isRunning());

        game.start();

        Assert.assertTrue(game.isRunning());

        game.stop();

        Assert.assertFalse(game.isRunning());
    }

    @Test
    public void canCreateGame() throws Exception {
        Assert.assertNotNull(new Controller(TestUtils.server));
    }

}
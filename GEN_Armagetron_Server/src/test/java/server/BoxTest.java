/**
 * @project     : Argmagetron
 * @file        : BoxTest.java
 * @author(s)   : Michaël Brouchoud
 * @date        : 18.05.2017
 *
 * @brief        : Test the class Box
 */
package server;

import org.junit.Assert;
import org.junit.Test;
import share.Util;

import java.awt.*;
import java.util.UUID;

public class BoxTest {

    @Test
    public void getSetColor() throws Exception {
        Color color = Color.black;
        Box myBox = new Box(color);
        Assert.assertEquals(myBox.getColor(), color);

        color = Color.green;
        myBox.setColor(color);
        Assert.assertEquals(myBox.getColor(), color);
    }

    @Test
    public void getSetId() throws Exception {
        int id = Util.rand.nextInt();
        Box myBox = new Box(id);
        Assert.assertEquals(myBox.getId(), id);

        id = Util.rand.nextInt();
        myBox.setId(id);
        Assert.assertEquals(myBox.getId(), id);
    }

    @Test
    public void isEmpty() throws Exception {
        Assert.assertTrue(new Box().isEmpty());
        Assert.assertTrue(new Box(Util.rand.nextInt()).isEmpty());
        Assert.assertFalse(new Box(Color.cyan).isEmpty());
    }

    @Test
    public void canCreateBox() throws Exception {
        Assert.assertNotNull(new Box());
        Assert.assertNotNull(new Box(Color.black));
        Assert.assertNotNull(new Box(Util.rand.nextInt()));
    }

}
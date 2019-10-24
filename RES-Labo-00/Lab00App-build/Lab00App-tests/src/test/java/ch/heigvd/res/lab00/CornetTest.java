package ch.heigvd.res.lab00;

import org.junit.Assert;
import org.junit.Test;

public class CornetTest {
    @Test
    public void aCornetShouldMakepouet() {
        IInstrument cornet = new Cornet();
        String sound = cornet.play();
        Assert.assertEquals("pouet", sound);
    }

    @Test
    public void aCornetShouldNotBeMute() {
        IInstrument cornet = new Cornet();
        int clavierVolume = cornet.getSoundVolume();
        Assert.assertTrue(clavierVolume > 0);
    }

    @Test
    public void aCornetShouldBeGold() {
        IInstrument cornet = new Cornet();
        String color = cornet.getColor();
        Assert.assertEquals("gold", color);
    }

}

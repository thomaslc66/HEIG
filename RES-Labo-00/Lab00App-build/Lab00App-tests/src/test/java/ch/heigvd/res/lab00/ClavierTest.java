package ch.heigvd.res.lab00;

import org.junit.Assert;
import static org.junit.Assert.assertNotNull;
import org.junit.Test;

/**
 * @author Abass MAHDAVI
 */


public class ClavierTest {
  @Test
  public void thereShouldBeAClavierClass() {
    IInstrument clavier = new Clavier();
    assertNotNull(clavier);
  }
  
  @Test
  public void itShouldBePossibleToPlayAClavier() {
    IInstrument clavier = new Clavier();
    String sound = clavier.play();
    assertNotNull(sound);
  }
  
  @Test
  public void aClavierShouldMakeDayyyn() {
    IInstrument clavier = new Clavier();
    String sound = clavier.play();
    Assert.assertEquals("dayyyn", sound);
  }
  
  @Test
  public void aClavierShouldNotBeMute() {
    IInstrument clavier = new Clavier();
    int clavierVolume = clavier.getSoundVolume();
    Assert.assertTrue(clavierVolume > 0);
  }

  @Test
  public void aClavierShouldBeIvory() {
    IInstrument clavier = new Clavier();
    String color = clavier.getColor();
    Assert.assertEquals("ivory", color);
  }
}

package ch.heigvd.res.lab00;

import ch.heigvd.res.lab00.Application;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *       *** IMPORTANT WARNING : DO NOT EDIT THIS FILE ***
 * 
 * This file is used to specify what you have to implement. To check your work,
 * we will run our own copy of the automated tests. If you change this file,
 * then you will introduce a change of specification!!!
 * 
 * @author Olivier Liechti
 */
public class ApplicationTest {
  
  public ApplicationTest() {
  }
  
  @Test
  public void thereShouldBeAClassNamedApplication() {
    Application application = new Application();
    assertNotNull(application);
  }
  
  @Test
  public void thereShouldBeAGetterForMessage() {
    Application application = new Application();
    String message = application.getMessage();
    assertNotNull(message);
  }
  
  @Test
  public void theGetterForMessageShouldReturnTheCorrectValue() {
    String testValue = "does it work?";
    Application application = new Application(testValue);
    String message = application.getMessage();
    assertEquals(testValue, message);
  }

  @Test
  public void theDefaultValueForMessageShouldBeDefined() {
    Application application = new Application();
    String message = application.getMessage();
    assertEquals("HEIG-VD rocks!", message);
  }
  
  @Test
  public void thereShouldBeAMethodToAddIntegers() {
    Application application = new Application();
    int sum = application.add(40, 2);
    assertEquals(42, sum);
  }
  
}

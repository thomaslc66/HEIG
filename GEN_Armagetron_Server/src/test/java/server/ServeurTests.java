/**
 * @project     : Argmagetron
 * @file        : ServeurTests.java
 * @author(s)   : Thomas Léchaire
 * @date        : 01.06.2017
 *
 * @brief        : Class vérifiant les collisions sur le serveur
 */


package server;

import org.junit.Test;

import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

import static org.junit.Assert.*;

public class ServeurTests {

    @Test
    public void testCollision() throws Exception{

        GameGrid gameGrid = new GameGrid();
        Random r = new Random();
        //Ajout de mur aléatoirement
        int idWall = gameGrid.getIdWall();
        int width = gameGrid.getWidth();
        int heigh = gameGrid.getHeight();

        //génération aléatoires de mur sur la carte.
        for(int i = 0; i < heigh*100; i++){
            gameGrid.getBox(new Point(r.nextInt(width),r.nextInt(width))).setId(idWall);
        }


        Player p1 = new Player("Thomas", Color.RED);

        while(p1.isAlive()){
            gameGrid.checkDeath(p1);
            p1.setPosition(new Point(r.nextInt(width), r.nextInt(width)));
        }

        assertFalse(p1.isAlive());
    }


    @Test
    public void testBoxCollision() throws Exception{
        GameGrid g = new GameGrid();

        Player p1 = new Player("Michael", Color.black);
        Player p2 = new Player("Thomas", Color.GREEN);

        p1.setPosition(new Point(02,02));
        p2.setPosition(new Point(20,20));

        ArrayList<Player> p = new ArrayList<Player>();
        p.add(p1);
        p.add(p2);

        g.updateGameGrid(p);

        assertTrue(p1.isAlive());
        assertTrue(p2.isAlive());

        p1.setPosition(new Point(40,40));
        p2.setPosition(new Point(40,40));

        g.updateGameGrid(p);

        assertTrue(p1.isAlive()); //p1 passe avant sur la case et la transforme en mur
        assertFalse(p2.isAlive()); //p2 passe après et entre en collision avec le mur créé par p1


    }
}
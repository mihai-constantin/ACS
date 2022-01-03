package observers;

import entities.Hero;
import entities.Treasure;
import game.World;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;

import static game.World.*;

/**
 * Observer that prints the lore of a treasure when a hero discovers it.
 */
public class TreasureDiscoverer implements Observer {


    public void update(Observable o, Object arg) {
        // check if any hero is in an area containing a treasure
        // print some message
        // remove treasure from map and
        // add to specific hero's inventory

        World world = (World) o;
        ArrayList<Hero> party = world.getParty();
        ArrayList<Treasure> treasures = world.getTreasures();
        int[][] map = world.getMap();

        for (Hero hero : party) {
            for (Treasure treasure : treasures) {
                if (treasure.getPosx() == hero.getPosx() && treasure.getPosy() == hero.getPosy()) {
                    hero.collect(treasure);
                    System.out.println(hero);
                    map[hero.getPosx()][hero.getPosy()] = HERO_SPOT;
                    world.setMap(map);
                    world.removeTreasure(treasure);
                    break;
                }
            }
        }

    }
}

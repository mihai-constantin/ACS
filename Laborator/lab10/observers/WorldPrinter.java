package observers;

/**
 * Observer that prints the game's world (the map with all the treasures,
 * heroes, obstacles)
 */

import game.World;

import java.util.Observable;
import java.util.Observer;

import static game.World.*;

public class WorldPrinter implements Observer {

    @Override
    public void update(Observable o, Object arg) {
        // obtain the World's map, treasures and heroes
        // print the map
        // e.g.
        // 0  1  1  1  0
        // H  T  0  1  0
        // 0  0  T  0  0
        // 0  0  0  T  T
        // 0  T  0  0  0
        // T - treasure, H - hero, 1 - obstacle

        World world = (World) o;
        int[][] map = world.getMap();
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                if (map[i][j] == HERO_SPOT) {
                    System.out.print("H" + " ");
                } else {
                    if (map[i][j] == TREASURE_SPOT) {
                        System.out.print("T" + " ");
                    } else {
                        System.out.print(map[i][j] + " ");
                    }
                }
            }
            System.out.println();
        }
    }

}
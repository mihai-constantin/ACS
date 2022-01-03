package entities;

import java.util.ArrayList;
import java.util.List;

import game.World;

import static game.World.*;

public abstract class Hero {

    protected String name;
    protected List<Treasure> inventory;
    protected int posx, posy;

    /* Hero actions */
    public void move(Direction direction) {

        World world = World.getInstance();
        int[][] map = world.getMap();
        ArrayList<Hero> party = world.getParty();

        int initialPosx = posx;
        int initialPosy = posy;

        switch (direction) {
            case E:
                posy = (posy + 1) % World.MAP_SIZE;
                break;
            case W:
                posy = (posy + World.MAP_SIZE - 1) % World.MAP_SIZE;
                break;
            case S:
                posx = (posx + 1) % World.MAP_SIZE;
                break;
            case N:
                posx = (posx + World.MAP_SIZE - 1) % World.MAP_SIZE;
                break;
        }

        if (map[posx][posy] == OBSTACLE_SPOT) {
            System.out.println("Can't move there !");
            this.posx = initialPosx;
            this.posy = initialPosy;
            map[initialPosx][initialPosy] = HERO_SPOT;
        } else {
            map[posx][posy] = HERO_SPOT;

            int count = 0;
            for (Hero hero : party) {
                if (hero.getPosx() == initialPosx && hero.getPosy() == initialPosy) {
                    count++;
                }
            }
            if (count == 0) {
                map[initialPosx][initialPosy] = EMPTY_SPOT;
            } else {
                map[initialPosx][initialPosy] = HERO_SPOT;
            }
        }
        // the world must be informed in order to update its observers about this move
        world.update();
    }

    public void collect(Treasure treasure) {
        inventory.add(treasure);
    }

    public abstract void attack();

    /* Getters and setters */

    public void setInventory(List<Treasure> inventory) {
        this.inventory = inventory;
    }

    public int getPosy() {
        return posy;
    }

    public void setPosy(int posy) {
        this.posy = posy;
    }

    public int getPosx() {
        return posx;
    }

    public void setPosx(int posx) {
        this.posx = posx;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public enum Direction {
        S, N, E, W
    }

    public enum Type {
        WARRIOR, MAGE, PRIEST
    }

}



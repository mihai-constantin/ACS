package game;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Random;

import entities.Hero;
import entities.Treasure;
import factories.TreasureFactory;

public class World extends Observable {

    public static final int MAP_SIZE = 5;
    public static final int EMPTY_SPOT = 0;
    public static final int OBSTACLE_SPOT = 1;
    public static final int HERO_SPOT = 2;
    public static final int TREASURE_SPOT = 3;

    private ArrayList<Hero> party = new ArrayList<>();
    private ArrayList<Treasure> treasures = new ArrayList<>();
    private boolean adventureStarted = false;

    private int[][] map = new int[][]
            {
                    {0, 0, 1, 1, 0},
                    {0, 0, 0, 1, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 1, 0, 0},
                    {0, 0, 0, 0, 0}
            };

    private static World world = null;

    private World() {
    }

    public static World getInstance() {
        if (world == null)
            world = new World();
        return world;
    }

    public void update() {
        this.setChanged();
        this.notifyObservers();
    }

    public void populateTreasures(int numTreasures) {

        if (numTreasures > MAP_SIZE * MAP_SIZE) {
            System.err.println("Too many treasures");
            return;
        }

        Random generator = new Random();

        TreasureFactory treasureFactory = new TreasureFactory();
        for (int i = 0; i < numTreasures; i++) {
            Treasure treasure = treasureFactory.createTreasure();

            int px, py;
            do {
                px = generator.nextInt(MAP_SIZE);
                py = generator.nextInt(MAP_SIZE);
            } while (map[px][py] != EMPTY_SPOT);

            map[px][py] = TREASURE_SPOT;
            treasure.setPosx(px);
            treasure.setPosy(py);
            treasures.add(treasure);
        }
    }

    public void removeTreasure(Treasure t) {
        treasures.remove(t);
    }

    public ArrayList<Hero> getParty() {
        return party;
    }

    public ArrayList<Treasure> getTreasures() {
        return treasures;
    }


    public boolean isAdventureStarted() {
        return adventureStarted;
    }

    public void setAdventureStarted(boolean adventureStarted) {
        this.adventureStarted = adventureStarted;
    }

    public void setMap(int[][] map) {
        this.map = map;
    }

    public int[][] getMap() {
        return map;
    }
}
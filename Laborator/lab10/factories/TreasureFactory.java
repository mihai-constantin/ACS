package factories;

import java.util.Random;

import entities.Treasure;


/**
 * Builds random treasure objects. Hides the treasure creation mechanism using
 * a factory method.
 */
public class TreasureFactory {

    // ideas for treasure names and lore:
    private final String[] names = {"Sword of Justice",
            "Leg of St Andrew",
            "Rabbit's Foot",
            "5-leaf Clover",
            "Shield of the Wise"};

    private final String[] lore = {"it looks quite old",
            "you've heard of this before",
            "tales of this legendary item are told in each tavern"};

    public Treasure createTreasure() {
        Random generator = new Random();
        return new Treasure(names[generator.nextInt(names.length)],
                lore[generator.nextInt(lore.length)]);
    }
}
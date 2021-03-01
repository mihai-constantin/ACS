package game;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;


import entities.*;
import factories.HeroFactory;
import observers.WorldPrinter;
import observers.TreasureDiscoverer;

import static game.World.*;


public class Main {

    public static World world = World.getInstance();

    private static String helpMessage() {

        String s = "Commands:\n"
                + "\t start - starts an adventure, must be called after adding heroes\n"
                + "\t add <hero-type> <hero-name>\n"
                + "\t\t hero types: warrior, mage, priest (any case)\n"
                + "\t move <hero-name> <direction>\n"
                + "\t\t directions: right, left, up, down\n"
                + "\t stop - ends the program\n"
                + "\t help - prints this menu";

        return s;
    }


    public static void main(String[] args) {

        while (true) {
            System.out.println(">");
            Scanner sc = new Scanner(System.in);
            String cmd = sc.nextLine();
            String[] cmdTokens = cmd.split(" ");

            switch (cmdTokens[0]) {

                case "help":
                    System.out.println(Main.helpMessage());
                    break;

                case "add":
                    if (world.isAdventureStarted()) {
                        System.out.println("Adventure has already started..."
                                + "maybe next time!\n");
                        break;
                    }

                    if (cmdTokens.length < 3) {
                        System.out.println("Not enough parameters..!\n"
                                + Main.helpMessage());
                        break;
                    }

                    System.out.println("Adding " + cmdTokens[1]
                            + " named " + cmdTokens[2]
                            + " to the party.");

                    // check the hero's type and create the hero

                    Hero.Type heroType;

                    try {
                        heroType = Hero.Type.valueOf(cmdTokens[1].toUpperCase());

                        Hero hero = HeroFactory.createHero(heroType, cmdTokens[2]);
                        int[][] map = world.getMap();
                        Random generator = new Random();
                        int px, py;
                        do {
                            px = generator.nextInt(MAP_SIZE);
                            py = generator.nextInt(MAP_SIZE);
                        } while (map[px][py] == OBSTACLE_SPOT);

                        map[px][py] = HERO_SPOT;
                        hero.setPosx(px);
                        hero.setPosy(py);
                        hero.setInventory(new ArrayList<>());
                        world.setMap(map);
                        world.getParty().add(hero);

                        System.out.println("Party :" + world.getParty());
                    } catch (IllegalArgumentException ex) {
                        System.out.println("Wrong hero type! Try again...\n"
                                + "Possible hero types: warrior, mage, priest (any case)");
                    }

                    break;


                case "start":

                    if (!world.isAdventureStarted()) {
                        System.out.println("We're off on an adventure!");
                        world.setAdventureStarted(true);
                        world.populateTreasures(5);

                        // Add observers to the World
                        world.addObserver(new TreasureDiscoverer());
                        world.addObserver(new WorldPrinter());
                        // The game state must inform its observers
                        world.update();

                    }
                    break;

                case "move":

                    if (world.isAdventureStarted()) {

                        if (cmdTokens.length < 3) {
                            System.out.println("Not enough parameters..!\n"
                                    + Main.helpMessage());
                            break;
                        }

                        Hero.Direction dir = null;

                        switch (cmdTokens[2]) {
                            case "right":
                                dir = Hero.Direction.E;
                                break;
                            case "left":
                                dir = Hero.Direction.W;
                                break;
                            case "up":
                                dir = Hero.Direction.N;
                                break;
                            case "down":
                                dir = Hero.Direction.S;
                                break;
                            default:
                                System.out.println("Wrong direction! Try again...");
                        }

                        if (dir != null) {
                            for (Hero h : world.getParty()) {
                                if (h.getName().equals(cmdTokens[1])) {
                                    h.move(dir);
                                    System.out.println("Found hero " + h.getName());
                                }
                            }
                        }

                    } else {
                        System.out.println("First start the adventure, than move the heroes!");
                    }

                    break;

                case "stop":
                    if (world.isAdventureStarted()) {
                        System.out.println("Adventure ended");
                    }

                    sc.close();

                    System.exit(0);

                default:
                    System.out.println("try again...\n" + Main.helpMessage());
            }
        }
    }
}

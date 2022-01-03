package entities;


/**
 * Class representing a "treasure". The map contains treasures that the heroes
 * will collect.
 * <p>
 * The treasures have a special story(lore) associated with them.
 */
public class Treasure {

    protected String name;
    protected String lore;
    protected int posx, posy;

    public Treasure(String name, String lore) {
        this.name = name;
        this.lore = lore;
    }

    public int getPosx() {
        return posx;
    }

    public void setPosx(int posx) {
        this.posx = posx;
    }

    public int getPosy() {
        return posy;
    }

    public void setPosy(int posy) {
        this.posy = posy;
    }

    @Override
    public String toString() {
        return '\n' + "Treasure: "
                + "name='" + name + '\''
                + ", lore='" + lore + '\''
                + ", posx=" + posx
                + ", posy=" + posy;
    }
}

package entities;

//extra attribute: damage (aka strength)

public class Warrior extends Hero {

    @Override
    public void attack() {
        System.out.println("Warrior attacks!");
    }

    @Override
    public String toString() {
        return '\n' + "=====      Warrior      =====" + '\n'
                + "name='" + name + '\'' + '\n'
                + "inventory=" + inventory + '\n'
                + "Player's position: "
                + "(" + posx
                + " " + posy + ")";
    }
}

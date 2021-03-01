package entities;

//extra attribute: knowledge

public class Priest extends Hero {

    @Override
    public void attack() {
        System.out.println("Priest attacks!");
    }

    @Override
    public String toString() {
        return '\n' + "=====      Priest      =====" + '\n'
                + "name='" + name + '\'' + '\n'
                + "inventory=" + inventory + '\n'
                + "Player's position: "
                + "(" + posx
                + " " + posy + ")";
    }
}

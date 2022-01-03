package entities;

//additional attack: magicAttack

public class Mage extends Hero {

    @Override
    public void attack() {
        System.out.println("Mage attacks!");
    }

    @Override
    public String toString() {
        return '\n' + "=====      Mage      =====" + '\n'
                + "name='" + name + '\'' + '\n'
                + "inventory=" + inventory + '\n'
                + "Player's position: "
                + "(" + posx
                + " " + posy + ")";
    }
}
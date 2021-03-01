package factories;

import entities.Hero;
import entities.Mage;
import entities.Priest;
import entities.Warrior;

public class HeroFactory {

    /**
     * @param type the Hero type
     * @param name
     * @return
     */
    public static Hero createHero(Hero.Type type, String name) {
        switch (type) {
            case MAGE:
                Mage mage = new Mage();
                mage.setName(name);
                return mage;
            case PRIEST:
                Priest priest = new Priest();
                priest.setName(name);
                return priest;
            case WARRIOR:
                Warrior warrior = new Warrior();
                warrior.setName(name);
                return warrior;
        }
        throw new IllegalArgumentException("The hero type " + type +
                " does not exist.");
    }
}

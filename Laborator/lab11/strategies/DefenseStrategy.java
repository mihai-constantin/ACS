package strategies;

import entities.Hero;
import entities.Monster;
import entities.Treasure;

import java.util.List;

public class DefenseStrategy implements Strategy {

    Hero hero;

    public DefenseStrategy(Hero hero) {
        this.hero = hero;
    }

    @Override
    public void attack(Monster m) {

	    /*	Attack algorithm
			if hero type weapon found boost HP with treasure.getHpBoost() + hero.getBaseHpBoost()
				else boost HP with getBaseHpBoost()
			Do a basic attack on the monster -> hero.getBaseDamage()
			--> In order to find the weapon, iterate through the inventory of the hero.
	    */

        List<Treasure> inventory = hero.getInventory();
        Monster monster = hero.getTarget();

        boolean foundTreasure = false;
        if (inventory != null) {
            for (Treasure treasure : inventory) {
                if (treasure.getDamageType() == hero.getDamageType()) {
                    hero.setHP(hero.getHP() + hero.getBaseHpBoost() + treasure.getBoostHp());
                    monster.setHP(monster.getHP() - hero.getBaseDamage());
                    foundTreasure = true;
                    break;
                }
            }
        }

        if (!foundTreasure) {
            hero.setHP(hero.getHP() + hero.getBaseHpBoost());
            monster.setHP(monster.getHP() - hero.getBaseDamage());
        }
    }

}

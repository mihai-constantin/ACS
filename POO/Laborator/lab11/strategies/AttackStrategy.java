package strategies;

import entities.Hero;
import entities.Monster;
import entities.Treasure;
import game.GameState;

import java.util.List;

public class AttackStrategy implements Strategy {

    Hero hero;

    public AttackStrategy(Hero hero) {
        this.hero = hero;
    }

    @Override
    public void attack(Monster m) {

	    /*	Attack algorithm
			if hero type weapon found use it (x3 weapon damage)
				else if counter weapon found use it (x2 weapon damage)
				else basic attack (no bonus)
			--> In order to find the weapon, iterate through the inventory of the hero.
	    */

        List<Treasure> inventory = hero.getInventory();
        Monster monster = hero.getTarget();

        boolean foundTreasure = false;
        if (inventory != null) {
            for (Treasure treasure : inventory) {
                if (treasure.getDamageType() == hero.getDamageType()) {
                    monster.setHP(monster.getHP() - 3 * treasure.getDmg());
                    foundTreasure = true;
                    break;
                }
            }
        }

        if (!foundTreasure) {
            boolean foundMonster = false;
            if (inventory != null) {
                for (Treasure treasure : inventory) {
                    if (treasure.getDamageType() == monster.getWeakness()) {
                        monster.setHP(monster.getHP() - 2 * treasure.getDmg());
                        foundMonster = true;
                        break;
                    }
                }
            }

            if (!foundMonster) {
                monster.setHP(monster.getHP() - hero.getBaseDamage());
            }
        }
    }

}

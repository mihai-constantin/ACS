/**
 * @author Constantin Mihai, 321CD
 */

package player;

import main.Strategy;

import java.util.List;

public class Wizard extends Basic {

    public Wizard() {
        setName(Strategy.WIZARD);
    }

    /**
     * @param players    Players in the current game
     * @param idxSheriff Index for the current sheriff
     */

    @Override
    public void inspect(final List<Player> players, final int idxSheriff) {

        for (int i = 0; i < players.size(); i++) {
            if (!players.get(i).isSheriff() && players.get(i).isGivingBribe()) {
                basicInspection(players.get(i), players.get(idxSheriff));
            }
        }
    }

}

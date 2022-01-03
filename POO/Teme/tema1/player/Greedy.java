/**
 * @author Constantin Mihai, 321CD
 */

package player;

import main.Asset;
import main.Strategy;

import java.util.Collections;
import java.util.List;

public class Greedy extends Basic {

    public Greedy() {
        setName(Strategy.GREEDY);
    }

    /**
     * @param players    Players in the current game
     * @param idxSheriff Index for the current sheriff
     */

    @Override
    public void inspect(final List<Player> players, final int idxSheriff) {

        for (int i = 0; i < players.size(); i++) {

            if (!players.get(i).isSheriff()) {

                if (players.get(i).isGivingBribe()) {

                    int coinsSheriff = players.get(idxSheriff).getCoins();
                    int coinsMerchant = players.get(i).getCoins();

                    /* Sheriff takes the bribe */

                    int addCoins = players.get(i).getBribe();

                    players.get(i).setCoins(coinsMerchant - addCoins);
                    players.get(idxSheriff).setCoins(coinsSheriff + addCoins);

                    /* Add assert on stand */

                    for (Asset asset : players.get(i).getAssetsInBag()) {
                        int frequency = players.get(i).getAssetsOnMerchantStand().get(asset);
                        players.get(i).getAssetsOnMerchantStand().replace(asset, frequency + 1);
                    }

                } else {

                    basicInspection(players.get(i), players.get(idxSheriff));

                }
            }
        }
    }

    /**
     * Update bag for a greedy player.
     */

    @Override
    public void updateBag() {

        IllegalAssetComparator illegalAssetComparator = new IllegalAssetComparator();
        Collections.sort(getIllegalAssets(), illegalAssetComparator);

        if (getIllegalAssets() != null && getIllegalAssets().size() > 0) {
            getAssetsInBag().add(getIllegalAssets().get(0));
        }

    }
}

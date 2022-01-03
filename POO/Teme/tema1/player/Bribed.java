/**
 * @author Constantin Mihai, 321CD
 */

package player;

import java.util.Collections;

import main.Asset;
import main.Strategy;

public class Bribed extends Basic {

    public Bribed() {
        setName(Strategy.BRIBED);
    }

    public final Strategy selectStrategy() {

        Strategy strategy;
        int numberOfIllegalAssets = getIllegalAssets().size();

        if (numberOfIllegalAssets != 0) {

            int coins = getCoins();

            if (numberOfIllegalAssets <= 2) {

                final int bribe = 5;

                if (coins >= bribe) {
                    strategy = Strategy.BRIBED;
                    setGivingBribe(true);
                    setBribe(bribe);
                } else {
                    strategy = Strategy.BASIC;
                }

            } else {
                final int bribe = 10;

                if (coins >= bribe) {
                    strategy = Strategy.BRIBED;
                    setGivingBribe(true);
                    setBribe(bribe);
                } else {
                    strategy = Strategy.BASIC;
                }
            }
        } else {
            strategy = Strategy.BASIC;
        }

        return strategy;
    }

    /**
     * Insert the assets into bribed player.
     */

    @Override
    public void createBag() {

        init();

        Strategy strategy = selectStrategy();

        if (strategy == Strategy.BRIBED) {

            IllegalAssetComparator illegalAssetComparator = new IllegalAssetComparator();
            Collections.sort(getIllegalAssets(), illegalAssetComparator);

            for (int i = 0; i < Math.min(getIllegalAssets().size(), getNumberOfCards()); i++) {
                getAssetsInBag().add(getIllegalAssets().get(i));
            }

            setDeclaredType(Asset.APPLE);

        } else {

            pushInBag(); /* Basic player */
        }

    }
}

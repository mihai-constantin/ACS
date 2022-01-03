/**
 * @author Constantin Mihai, 321CD
 */

package player;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import main.Asset;
import main.Strategy;

public class Basic extends Player {

    private List<Asset> legalAssets;
    private List<Asset> illegalAssets;

    class LegalAssetComparator implements Comparator<Asset> {

        @Override
        public int compare(final Asset a1, final Asset a2) {
            if (a1.getFREQUENCY() == a2.getFREQUENCY()) {
                return a2.getProfit() - a1.getProfit();
            }
            return a2.getFREQUENCY() - a1.getFREQUENCY();
        }
    }

    class IllegalAssetComparator implements Comparator<Asset> {
        @Override
        public int compare(final Asset a1, final Asset a2) {
            return a2.getProfit() - a1.getProfit();
        }
    }

    public Basic() {
        setName(Strategy.BASIC);
    }

    /**
     * @return strategy of a player and his role
     */
    @Override
    public String toString() {
        Strategy nameStrategy = getName();
        return nameStrategy.name() + " " + getMerchant();
    }

    /**
     * @return the illegal assets that a player has in hand
     */

    public List<Asset> getIllegalAssets() {
        return illegalAssets;
    }

    /**
     * @return the legal assets that a player has in hand
     */

    public List<Asset> getLegalAssets() {
        return legalAssets;
    }

    /**
     * Initialize the stand for a player.
     */
    @Override
    public void createStandMap() {
        getAssetsOnMerchantStand().put(Asset.APPLE, 0);
        getAssetsOnMerchantStand().put(Asset.CHEESE, 0);
        getAssetsOnMerchantStand().put(Asset.BREAD, 0);
        getAssetsOnMerchantStand().put(Asset.CHICKEN, 0);
        getAssetsOnMerchantStand().put(Asset.SILK, 0);
        getAssetsOnMerchantStand().put(Asset.PEPPER, 0);
        getAssetsOnMerchantStand().put(Asset.BARREL, 0);

    }

    /**
     * Initialize the assets in hands for a player.
     */

    public void init() {

        legalAssets = new ArrayList<>();
        illegalAssets = new ArrayList<>();

        for (int i = 0; i < getNumberOfCards(); i++) {
            getAssetsInHand().get(i).setFREQUENCY(0);
        }

        for (int i = 0; i < getNumberOfCards(); i++) {
            int actualFrequency = getAssetsInHand().get(i).getFREQUENCY();
            getAssetsInHand().get(i).setFREQUENCY(actualFrequency + 1);
        }

        for (int i = 0; i < getNumberOfCards(); i++) {
            if (getAssetsInHand().get(i).getTYPE()) {
                legalAssets.add(getAssetsInHand().get(i));
            } else {
                illegalAssets.add(getAssetsInHand().get(i));
            }
        }
    }

    /**
     * Push the assets in bag for a basic player.
     */

    public void pushInBag() {

        if (legalAssets.size() == 0) {

            /* Only illegal assets */

            IllegalAssetComparator illegalAssetComparator = new IllegalAssetComparator();
            Collections.sort(illegalAssets, illegalAssetComparator);

            getAssetsInBag().add(illegalAssets.get(0));

            Asset.APPLE.setFREQUENCY(0);
            setDeclaredType(Asset.APPLE);

        } else {

            /* Some legal assets */

            LegalAssetComparator legalAssetComparator = new LegalAssetComparator();
            Collections.sort(legalAssets, legalAssetComparator);

            int minim = Math.min(getNumberOfCards() - 1, legalAssets.get(0).getFREQUENCY());

            for (int i = 0; i < minim; i++) {
                getAssetsInBag().add(legalAssets.get(0));
            }

            setDeclaredType(getAssetsInBag().get(0));
        }
    }

    /**
     * Create bag for a player.
     */

    @Override
    public void createBag() {

        init();
        pushInBag();
    }

    /**
     * Update bag for a greedy player.
     */

    @Override
    public void updateBag() {

    }

    /**
     * @param player  The player that is verified by the seriff
     * @param sheriff The current sheriff
     */

    public void basicInspection(final Player player, final Player sheriff) {
        int coinsSheriff = sheriff.getCoins();
        int coinsMerchant = player.getCoins();

        for (Asset asset : player.getAssetsInBag()) {
            asset.setFREQUENCY(0);
        }

        for (Asset asset : player.getAssetsInBag()) {
            int f = asset.getFREQUENCY();
            asset.setFREQUENCY(1 + f);
        }

        boolean liar = false;

        for (Asset asset : player.getAssetsInBag()) {

            if (!(asset == player.getDeclaredType())) {

                /* Merchant is a liar */

                coinsMerchant = player.getCoins();
                coinsSheriff = sheriff.getCoins();

                int decCoins = asset.getPENALTY();

                player.setCoins(coinsMerchant - decCoins);
                sheriff.setCoins(coinsSheriff + decCoins);

                if (player.getDeclaredType().getTYPE()) {

                    boolean ok = false;

                    for (int k = 0; k < player.getAssetsInBag().size(); k++) {

                        if (player.getAssetsInBag().get(k)
                                == player.getDeclaredType()) {
                            ok = true;
                            break;
                        }
                    }

                    if (ok) {

                        int frequency = player.getAssetsOnMerchantStand()
                                .get(player.getDeclaredType());

                        int newFrequency = frequency
                                + player.getDeclaredType().getFREQUENCY();

                        player.getAssetsOnMerchantStand()
                                .replace(player.getDeclaredType(), newFrequency);

                    }
                }

                liar = true;

            }
        }

        if (!liar) {

            /* Honest merchant */

            coinsMerchant = player.getCoins();
            coinsSheriff = sheriff.getCoins();

            int addCoins = player.getDeclaredType().getFREQUENCY()
                    * player.getDeclaredType().getPENALTY();

            player.setCoins(coinsMerchant + addCoins);
            sheriff.setCoins(coinsSheriff - addCoins);

            /* Add assert on stand */

            int currentFrequency = player.getAssetsOnMerchantStand()
                    .get(player.getDeclaredType());

            int newFrequency = currentFrequency
                    + player.getDeclaredType().getFREQUENCY();

            player.getAssetsOnMerchantStand()
                    .replace(player.getDeclaredType(), newFrequency);

        }
    }

    /**
     * @param players    Players in the current game
     * @param idxSheriff Index for the current sheriff
     */
    @Override
    public void inspect(final List<Player> players, final int idxSheriff) {

        for (int i = 0; i < players.size(); i++) {

            if (!players.get(i).isSheriff()) {
                basicInspection(players.get(i), players.get(idxSheriff));
            }
        }

    }

    /**
     * Print score for a player.
     */
    @Override
    public void printScore() {

        System.out.println(this.getName() + ": " + this.getCoins());
    }

    /**
     * Remove the assets that a player pushed in bag.
     */
    @Override
    public void removeAssetsInHand() {

        for (Asset asset : getAssetsInBag()) {

            for (int i = 0; i < getAssetsInHand().size(); i++) {
                if (getAssetsInHand().get(i).name().equals(asset.name())) {
                    getAssetsInHand().remove(i);
                    break;
                }
            }
        }
    }

}

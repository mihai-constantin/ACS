/**
 * @author Constantin Mihai, 321CD
 */

package player;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import main.Asset;
import main.Strategy;

public abstract class Player {

    private static final int NUMBER_OF_CARDS = 6;
    private int coins;
    private Strategy name;
    private boolean sheriff;
    private boolean givingBribe;
    private int bribe;
    private int merchant;

    private Asset declaredType;
    private List<Asset> assetsInHand = new ArrayList<>();
    private List<Asset> assetsInBag = new ArrayList<>();

    private Map<Asset, Integer> assetsOnMerchantStand = new HashMap<>();

    public static int getNumberOfCards() {
        return NUMBER_OF_CARDS;
    }

    /**
     * @return the number of coins for every player
     */
    public int getCoins() {
        return coins;
    }

    /**
     * @param coins Set the number of coins of a player to this value
     */
    public void setCoins(final int coins) {
        this.coins = coins;
    }

    /**
     * @return name's strategy for every player
     */

    public Strategy getName() {
        return name;
    }

    /**
     * @param name Set strategy of a player to this value
     */

    public void setName(final Strategy name) {
        this.name = name;
    }

    /**
     * @return bribe offered by a player
     */

    public int getBribe() {
        return bribe;
    }

    /**
     * @param bribe Set the bribe's player
     */
    public void setBribe(final int bribe) {
        this.bribe = bribe;
    }

    /**
     * @return if the player is or is not a sheriff
     */

    public boolean isSheriff() {
        return sheriff;
    }

    /**
     * @param sheriff Set the role of a player (sheriff or merchant)
     */

    public void setSheriff(final boolean sheriff) {
        this.sheriff = sheriff;
    }

    /**
     * @return if a player offers bribe to the sheriff
     */

    public boolean isGivingBribe() {
        return givingBribe;
    }

    /**
     * @param givingBribe Set if a player offers bribe to the sheriff
     */

    public void setGivingBribe(final boolean givingBribe) {
        this.givingBribe = givingBribe;
    }

    /**
     * @return the number of times when a player is a merchant
     */
    public int getMerchant() {
        return merchant;
    }

    /**
     * @param merchant Set the number of times when a player is a merchant
     */

    public void setMerchant(final int merchant) {
        this.merchant = merchant;
    }

    /**
     * @return the declared type of assets
     */
    public Asset getDeclaredType() {
        return declaredType;
    }

    /**
     * @param declaredType Set the declared type of assets
     */
    public void setDeclaredType(final Asset declaredType) {
        this.declaredType = declaredType;
    }

    /**
     * @return the assets that a player has in hands
     */
    public List<Asset> getAssetsInHand() {
        return assetsInHand;
    }

    /**
     * @return the assets that a player has in bag
     */

    public List<Asset> getAssetsInBag() {
        return assetsInBag;
    }

    /**
     * @param assetsInBag Set the assets that a player has in bag
     */

    public void setAssetsInBag(final List<Asset> assetsInBag) {
        this.assetsInBag = assetsInBag;
    }

    /**
     * @return the assets that a player has on stand
     */

    public Map<Asset, Integer> getAssetsOnMerchantStand() {
        return assetsOnMerchantStand;
    }

    public abstract void createBag();

    public abstract void updateBag();

    public abstract void createStandMap();

    public abstract void inspect(List<Player> players, int idxSheriff);

    public abstract void removeAssetsInHand();

    public abstract void printScore();

}

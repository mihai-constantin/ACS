/**
 * @author Constantin Mihai, 321CD
 */

package game;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import main.Asset;
import main.GameInput;
import player.Player;
import player.Basic;
import player.Greedy;
import player.Bribed;
import player.Wizard;

import static main.Asset.APPLE;
import static main.Asset.CHEESE;
import static main.Asset.BREAD;
import static main.Asset.CHICKEN;
import static main.Asset.SILK;
import static main.Asset.PEPPER;
import static main.Asset.BARREL;

public class Match extends GameInput {

    private final int numberOfRounds;
    static final int NUMBER_OF_CARDS = 6;
    private final int numberOfPlayers;
    private final List<Integer> mAssetOrder = getAssetIds();
    private final List<String> mPlayersOrder = getPlayerNames();
    private static List<Player> players;

    private static final int APPLE_KING_BONUS = 20;
    private static final int APPLE_QUEEN_BONUS = 10;

    private static final int CHEESE_KING_BONUS = 15;
    private static final int CHEESE_QUEEN_BONUS = 10;

    private static final int BREAD_KING_BONUS = 15;
    private static final int BREAD_QUEEN_BONUS = 10;

    private static final int CHICKEN_KING_BONUS = 10;
    private static final int CHICKEN_QUEEN_BONUS = 5;

    private static final int APPLE_ID = 0;
    private static final int CHEESE_ID = 1;
    private static final int BREAD_ID = 2;
    private static final int CHICKEN_ID = 3;
    private static final int SILK_ID = 10;
    private static final int PEPPER_ID = 11;
    private static final int BARREL_ID = 12;

    private Map<Integer, Asset> map = new HashMap<>();

    public Match(final List<Integer> assets, final List<String> players) {
        super(assets, players);
        numberOfRounds = 2 * mPlayersOrder.size();
        numberOfPlayers = mPlayersOrder.size();
        Match.players = new ArrayList<>();
    }

    public final void createMap() {
        map.put(APPLE_ID, APPLE);
        map.put(CHEESE_ID, CHEESE);
        map.put(BREAD_ID, BREAD);
        map.put(CHICKEN_ID, CHICKEN);
        map.put(SILK_ID, SILK);
        map.put(PEPPER_ID, PEPPER);
        map.put(BARREL_ID, BARREL);
    }

    public final void setFrequency() {
        APPLE.setFREQUENCY(0);
        CHEESE.setFREQUENCY(0);
        BREAD.setFREQUENCY(0);
        CHICKEN.setFREQUENCY(0);
        SILK.setFREQUENCY(0);
        PEPPER.setFREQUENCY(0);
        BARREL.setFREQUENCY(0);
    }

    class StandingsComparator implements Comparator<Player> {
        @Override
        public int compare(final Player p1, final Player p2) {
            return p2.getCoins() - p1.getCoins();
        }
    }

    public final void createPlayers() {
        for (int i = 0; i < numberOfPlayers; i++) {

            String typePlayer = mPlayersOrder.get(i);

            switch (typePlayer) {

                case "basic":
                    players.add(new Basic());
                    break;

                case "greedy":
                    players.add(new Greedy());
                    break;

                case "wizard":
                    players.add(new Wizard());
                    break;

                default:
                    players.add(new Bribed());
                    break;
            }
        }
    }

    public final void addProfitPerStand() {

        final int addCheese = 3;
        final int addChicken = 2;
        final int addBread = 2;

        for (int j = 0; j < numberOfPlayers; j++) {

            int addCoins = 0;

            for (Object key : players.get(j).getAssetsOnMerchantStand().keySet()) {
                Object value = players.get(j).getAssetsOnMerchantStand().get(key);

                Asset asset = (Asset) key;
                Integer integer = (Integer) value;

                /* Profit - Legal assets */
                if (asset.getTYPE()) {
                    addCoins = addCoins + asset.getProfit() * integer;
                }

                /* Profit - Illegal assets */
                if (integer > 0 && !asset.getTYPE()) {

                    int profit;

                    switch (asset) {
                        case SILK:
                            profit = SILK.getProfit() + addCheese * CHEESE.getProfit();
                            addCoins += integer * profit;
                            break;
                        case PEPPER:
                            profit = PEPPER.getProfit() + addChicken * CHICKEN.getProfit();
                            addCoins += integer * profit;
                            break;

                        default:
                            profit = Asset.BARREL.getProfit() + addBread * Asset.BREAD.getProfit();
                            addCoins += integer * profit;
                            break;
                    }
                }
            }

            int coins = players.get(j).getCoins();
            players.get(j).setCoins(coins + addCoins);

        }
    }

    public final void switchLegalAssets(final Asset legalAsset, final Player player) {
        int coins = player.getCoins();

        switch (legalAsset) {
            case APPLE:
                player.setCoins(coins + APPLE_KING_BONUS);
                break;

            case CHEESE:
                player.setCoins(coins + CHEESE_KING_BONUS);
                break;
            case BREAD:
                player.setCoins(coins + BREAD_KING_BONUS);
                break;

            default:
                player.setCoins(coins + CHICKEN_KING_BONUS);
                break;
        }
    }

    public final void bonusLegalAssets() {

        Asset[] legalAssets = {Asset.APPLE, CHEESE, Asset.BREAD, CHICKEN};

        for (Asset legalAsset : legalAssets) {

            int maxAssets = 0;

            for (int j = 0; j < numberOfPlayers; j++) {

                if (j == 0) {
                    maxAssets = players.get(j).getAssetsOnMerchantStand().get(legalAsset);
                } else {
                    if (maxAssets < players.get(j).getAssetsOnMerchantStand().get(legalAsset)) {
                        maxAssets = players.get(j).getAssetsOnMerchantStand().get(legalAsset);
                    }
                }
            }

            for (int j = 0; j < numberOfPlayers; j++) {
                if (players.get(j).getAssetsOnMerchantStand().get(legalAsset) == maxAssets) {

                    switchLegalAssets(legalAsset, players.get(j));
                }
            }

            for (int j = 0; j < numberOfPlayers; j++) {
                if (players.get(j).getAssetsOnMerchantStand().get(legalAsset) != maxAssets) {
                    int queen = players.get(j).getAssetsOnMerchantStand().get(legalAsset);

                    boolean secondMax = true;

                    for (int k = 0; k < numberOfPlayers; k++) {
                        Integer integer = players.get(k).getAssetsOnMerchantStand().get(legalAsset);
                        if (integer != maxAssets && integer > queen) {
                            secondMax = false;
                        }
                    }

                    int coins = players.get(j).getCoins();

                    if (secondMax) {
                        switch (legalAsset) {
                            case APPLE:
                                players.get(j).setCoins(coins + APPLE_QUEEN_BONUS);
                                break;

                            case CHEESE:
                                players.get(j).setCoins(coins + CHEESE_QUEEN_BONUS);
                                break;
                            case BREAD:
                                players.get(j).setCoins(coins + BREAD_QUEEN_BONUS);
                                break;

                            default:
                                players.get(j).setCoins(coins + CHICKEN_QUEEN_BONUS);
                                break;
                        }
                    }
                }
            }

        }
    }

    public final void bonusIllegalAssets() {
        for (int j = 0; j < numberOfPlayers; j++) {

            final int addCheese = 3;
            final int addChicken = 2;
            final int addBread = 2;

            int frequency;

            for (Object key : players.get(j).getAssetsOnMerchantStand().keySet()) {
                Object value = players.get(j).getAssetsOnMerchantStand().get(key);

                Asset asset = (Asset) key;
                Integer integer = (Integer) value;

                /* Illegal asset on stand */
                if (!asset.getTYPE()) {

                    int addFrequency;

                    switch (asset) {
                        case SILK:
                            addFrequency = addCheese * integer;
                            frequency = players.get(j).getAssetsOnMerchantStand().get(CHEESE);
                            players.get(j).getAssetsOnMerchantStand()
                                    .replace(CHEESE, frequency + addFrequency);
                            break;

                        case PEPPER:
                            addFrequency = addChicken * integer;
                            frequency = players.get(j).getAssetsOnMerchantStand().get(CHICKEN);
                            players.get(j).getAssetsOnMerchantStand()
                                    .replace(CHICKEN, frequency + addFrequency);
                            break;

                        default:
                            addFrequency = addBread * integer;
                            frequency = players.get(j).getAssetsOnMerchantStand().get(BREAD);
                            players.get(j).getAssetsOnMerchantStand()
                                    .replace(BREAD, frequency + addFrequency);
                            break;
                    }
                }
            }
        }
    }

    public final void printStandings() {
        List<Player> standings = new ArrayList<>();

        for (int j = 0; j < numberOfPlayers; j++) {
            standings.add(players.get(j));
        }

        StandingsComparator standingsComparator = new StandingsComparator();
        Collections.sort(standings, standingsComparator);

        for (int j = 0; j < numberOfPlayers; j++) {
            System.out.println(standings.get(j).getName() + ": " + standings.get(j).getCoins());
        }
    }

    public final void play() {

        createMap();

        createPlayers();

        /* Create a map for storing the assets on merchant's stand */
        final int initialCoins = 50;

        for (int j = 0; j < numberOfPlayers; j++) {
            players.get(j).createStandMap();
            players.get(j).setCoins(initialCoins);
        }

        /* Add the assets from mAssetOrder for every player */
        for (int j = 0; j < numberOfPlayers; j++) {
            for (int k = 0; k < NUMBER_OF_CARDS; k++) {
                players.get(j).getAssetsInHand().add(map.get(mAssetOrder.get(0)));
                mAssetOrder.remove(0);
            }
        }

        for (int i = 0; i < numberOfRounds; i++) {

            setFrequency();

            for (int j = 0; j < numberOfPlayers; j++) {
                players.get(j).setSheriff(false);
                players.get(j).setGivingBribe(false);
                players.get(j).setAssetsInBag(new ArrayList<>());
            }

            players.get(i % numberOfPlayers).setSheriff(true);

            int idxSheriff = 0;

            for (int j = 0; j < numberOfPlayers; j++) {

                if (!players.get(j).isSheriff()) {
                    players.get(j).setMerchant(players.get(j).getMerchant() + 1);

                    players.get(j).createBag();

                    if (players.get(j).getMerchant() % 2 == 0 && players.get(j) instanceof Greedy
                            && players.get(j).getAssetsInBag().size() < NUMBER_OF_CARDS - 1) {

                        players.get(j).updateBag();
                    }

                    players.get(j).removeAssetsInHand();

                } else {

                    idxSheriff = j;
                }

            }

            players.get(idxSheriff).inspect(players, idxSheriff);

            /* Add assets from input */
            for (int j = 0; j < numberOfPlayers; j++) {
                if (players.get(j).getAssetsInHand().size() != NUMBER_OF_CARDS) {
                    int length = players.get(j).getAssetsInHand().size();
                    for (int k = length; k < NUMBER_OF_CARDS; k++) {
                        players.get(j).getAssetsInHand().add(map.get(mAssetOrder.get(0)));
                        mAssetOrder.remove(0);
                    }
                }
            }
        }

        addProfitPerStand();

        bonusIllegalAssets();

        bonusLegalAssets(); /* Bonus King & Queen */

        printStandings();
    }

}

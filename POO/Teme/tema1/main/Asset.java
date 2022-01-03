/**
 * @author Constantin Mihai, 321CD
 */

package main;

/**
 * Enumerates the types of assets.
 * Asset.TYPE == true  -> Legal Asset
 * Asset.TYPE == false -> Illegal Asset
 */
public enum Asset {

    APPLE(2, 2, 0, true),
    CHEESE(3, 2, 0, true),
    BREAD(4, 2, 0, true),
    CHICKEN(4, 2, 0, true),
    SILK(9, 4, 0, false),
    PEPPER(8, 4, 0, false),
    BARREL(7, 4, 0, false);

    private final int profit;
    private final int penalty;
    private final boolean type;
    private int frequency;

    Asset(final int profit, final int penalty, final int frequency, final boolean type) {
        this.profit = profit;
        this.penalty = penalty;
        this.type = type;
        this.frequency = frequency;
    }

    public final int getProfit() {
        return profit;
    }

    public int getPENALTY() {
        return penalty;
    }

    public boolean getTYPE() {
        return type;
    }

    public void setFREQUENCY(final int newFrequency) {
        this.frequency = newFrequency;
    }

    public int getFREQUENCY() {
        return frequency;
    }


}

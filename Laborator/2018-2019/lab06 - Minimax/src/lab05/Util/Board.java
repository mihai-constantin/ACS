package lab05.Util;

/**
 * Created by mihai on 26.03.2017.
 */
public abstract class Board<Move, Player> implements IBoard<Move, Player> {
    private Player currentPlayer;

    public Board(Player player) {
        this.currentPlayer = player;
    }

    @Override
    public Player getCurrentPlayer() {
        return currentPlayer;
    }

    public void setCurrentPlayer(Player player) {
        this.currentPlayer = player;
    }
}

package lab05.Util;

import java.util.ArrayList;

/**
 * Created by mihai on 26.03.2017.
 */
public interface IBoard<Move, Player> {
    public ArrayList<Move> getMoves();
    public IBoard<Move, Player> makeMove(Move move);
    public Double evaluate();
    public Player getCurrentPlayer();
    public boolean isGameOver();
    public void setCurrentPlayer(Player player);
}

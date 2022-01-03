package lab05;

import lab05.AI.AICore;
import lab05.Game.TicTacToe.XOBoard;

/**
 * Created by mihai on 26.03.2017.
 */
public class Main {
    public static void main(String args[]) {
        AICore<Integer, Integer> AI = AICore.getInstance();
        System.out.println("Test 1");
        AI.playGame(new XOBoard(1), "Random", "Random");
        System.out.println("\nTest 2");
        AI.playGame(new XOBoard(1), "Minimax", "Random");
        System.out.println("\nTest 3");
        AI.playGame(new XOBoard(1), "Negamax", "Random");
        System.out.println("\nTest 4");
        AI.playGame(new XOBoard(1), "Minimax", "Negamax");
    }
}

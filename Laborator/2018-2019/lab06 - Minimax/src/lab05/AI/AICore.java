package lab05.AI;

import lab05.Util.Board;
import lab05.Util.IBoard;

import java.util.ArrayList;
import java.util.Random;

/**
 * Created by mihai on 26.03.2017.
 */
public class AICore<Move, Player> {
    class Pair {
        private Move move;
        private Double value;

        public Pair(Move move, Double value) {
            this.move = move;
            this.value = value;
        }

        public Move getMove() {
            return move;
        }

        public Double getValue() {
            return value;
        }
    }

    private static AICore instance = null;
    private static final int MAXDEPTH = 5;

    private AICore() {

    }

    public static AICore getInstance() {
        if (instance == null) {
            instance = new AICore();
        }
        return instance;
    }

    public Pair minimax(IBoard<Move, Player> board, Player player, int maxDepth, int currentDepth) {

        if (board.isGameOver() || currentDepth == maxDepth) {
            return new Pair(null, board.evaluate());
        }

        Move bestMove = null;
        Double bestScore;
        if ((board.getCurrentPlayer()).equals(player)) {
            bestScore = Double.MIN_VALUE;
        } else {
            bestScore = Double.MAX_VALUE;
        }

        for (Move move : board.getMoves()) {
            Board newBoard = (Board) board.makeMove(move);
            Pair pair = minimax(newBoard, player, maxDepth, currentDepth + 1);
            Double currentScore = -pair.value;
            if ((board.getCurrentPlayer()).equals(player)) {
                if (currentScore.compareTo(bestScore) > 0) {
                    bestScore = currentScore;
                    bestMove = move;
                }
            } else {
                if (currentScore.compareTo(bestScore) < 0) {
                    bestScore = currentScore;
                    bestMove = move;
                }
            }
        }

        return new Pair(bestMove, bestScore);
    }

    public Pair negamax(IBoard<Move, Player> board, int maxDepth, int currentDepth) {

        if (board.isGameOver() || currentDepth == maxDepth) {
            return new Pair(null, board.evaluate());
        }

        Move bestMove = null;
        Double bestScore = Double.MIN_VALUE;

        for (Move move : board.getMoves()) {
            Board newBoard = (Board) board.makeMove(move);

            Pair pair = negamax(newBoard, maxDepth, currentDepth + 1);
            Double currentScore = -pair.value;
            if (currentScore.compareTo(bestScore) <= 0) {
                bestScore = currentScore;
                bestMove = move;
            }
        }

        return new Pair(bestMove, bestScore);
    }

    public Pair abNegamax(IBoard<Move, Player> board, int maxDepth, int currentDepth, Double alpha, Double beta) {

        if (board.isGameOver() || currentDepth == maxDepth) {
            return new Pair(null, board.evaluate());
        }

        Move bestMove = null;
        Double bestScore = Double.MIN_VALUE;

        for (Move move : board.getMoves()) {
            Board newBoard = (Board) board.makeMove(move);

            Pair pair = abNegamax(newBoard, maxDepth, currentDepth + 1, -beta, -alpha);
            Double currentScore = -pair.value;
            if (currentScore.compareTo(alpha) <= 0) {
                bestScore = currentScore;
                bestMove = move;
                alpha = currentScore;
            }

            if (alpha.compareTo(beta) >= 0) {
                break;
            }
        }

        return new Pair(bestMove, bestScore);
    }

    public Move random(IBoard<Move, Player> board) {
        ArrayList<Move> moves = board.getMoves();
        Random randomGenerator = new Random();
        int randomInt = randomGenerator.nextInt(moves.size());
        return moves.get(randomInt);
    }

    public Move getBestMoves(String type, IBoard<Move, Player> board) {
        if (type.equals("Minimax")) {
            return minimax(board, board.getCurrentPlayer(), MAXDEPTH, 0).move;
        } else if (type.equals("Negamax")) {
            return negamax(board, MAXDEPTH, 0).move;
        } else if (type.equals("Alpha Beta Negamax")) {
            return abNegamax(board, MAXDEPTH, 0, Double.MIN_VALUE, Double.MAX_VALUE).move;
        } else if (type.equals("Random")) {
            return random(board);
        }
        return null;
    }

    public void playGame(IBoard<Move, Player> board, String strategy1, String strategy2) {
        System.out.println("Playerul " + board.getCurrentPlayer() + " foloseste strategia " + strategy1);
        System.out.println("Adversarul foloseste strategia " + strategy2);
        int k = 0;
        String strategy;
        while (!board.isGameOver()) {
            Move move;
            if (k % 2 == 0) {
                move = getBestMoves(strategy1, board);
                strategy = strategy1;
            } else {
                move = getBestMoves(strategy2, board);
                strategy = strategy2;
            }
            if (move == null) {
                System.out.println("Strategia " + strategy + " nu a fost implementata corect! :(");
                return;
            }
            board = board.makeMove(move);
            k++;
        }
        System.out.println(board);
    }

}

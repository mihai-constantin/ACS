package lab05.Game.TicTacToe;

import lab05.Util.Board;
import lab05.Util.IBoard;

import java.util.ArrayList;

/**
 * Created by mihai on 26.03.2017.
 */
public class XOBoard extends Board<Integer, Integer> {
    public int matrix[][];

    public XOBoard(Integer player) {
        super(player);
        this.matrix = new int[3][3];
    }

    @Override
    public ArrayList<Integer> getMoves() {
        ArrayList<Integer> result = new ArrayList<>();
        int k = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matrix[i][j] == 0) {
                    result.add(k);
                }
                k++;
            }
        }
        return result;
    }

    @Override
    public IBoard<Integer, Integer> makeMove(Integer integer) {
        XOBoard board = this.cloneBoard();
        board.matrix[integer / 3][integer % 3] = board.getCurrentPlayer();
        board.setCurrentPlayer(3 - board.getCurrentPlayer());
        return board;
    }

    @Override
    public Double evaluate() {
        int total = 0;
        int suma1, suma2;
        int i, j;
        for (i = 0; i < 3; i++) {
            suma1 = 0;
            suma2 = 0;
            for (j = 0; j < 3; j++) {
                if (matrix[i][j] == getCurrentPlayer()) {
                    suma1++;
                } else if (matrix[i][j] != 0) {
                    suma2++;
                } else {
                    total++;
                }
            }
            if (suma1 == 3) {
                return 1.0;
            } else if (suma2 == 3) {
                return -1.0;
            }
        }
        // Verific pe coloane
        int diagP1, diagP2, diagS1, diagS2;
        diagP1 = 0;
        diagP2 = 0;
        diagS1 = 0;
        diagS2 = 0;
        for (j = 0; j < 3; j++) {
            suma1 = 0;
            suma2 = 0;
            for (i = 0; i < 3; i++) {
                if (i == j) {
                    if (matrix[i][j] == getCurrentPlayer()) {
                        diagP1++;
                    } else if (matrix[i][j] != 0) {
                        diagP2++;
                    }
                }
                if (j == 3 - i) {
                    if (matrix[i][j] == getCurrentPlayer()) {
                        diagS1++;
                    } else if (matrix[i][j] != 0) {
                        diagS2++;
                    }
                }
                if (matrix[i][j] == getCurrentPlayer()) {
                    suma1++;
                } else if (matrix[i][j] != 0) {
                    suma2++;
                }
            }
            if (suma1 == 3) {
                return 1.0;
            } else if (suma2 == 3) {
                return -1.0;
            }
        }
        if (diagP1 == 3 || diagS1 == 3) {
            return 1.0;
        } else if (diagS2 == 3 || diagP2 == 3) {
            return -1.0;
        }
        if (total == 0) {
            return 0.5;
        }
        return 0.0;
    }

    @Override
    public boolean isGameOver() {
        return evaluate() != 0.0;
    }

    public XOBoard cloneBoard() {
        XOBoard board = new XOBoard(getCurrentPlayer());
        int result[][] = new int[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result[i][j] = matrix[i][j];
            }
        }
        board.matrix = result;
        return board;
    }

    public String toString() {
        String result = "";
        for (int i = 0; i < 3; i++) {
            result += "(";
            for (int j = 0; j < 3; j++) {
                if (matrix[i][j] == 0) {
                    result +=  " - ";
                } else if (matrix[i][j] == 1) {
                    result += " X ";
                } else {
                    result += " O ";
                }
            }
            result += ")\n";
        }
        result += "Player-ul care urmeaza sa mute este " + getCurrentPlayer();
        return result;
    }
}

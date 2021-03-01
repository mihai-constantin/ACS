package main;

import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    static int dim;
    static int matrix[][];
    static int ans;

    static int[] dlin = {-1, 0, 1, 0};
    static int[] dcol = {0, 1, 0, -1};

    public static void FILL(int x, int y) {

        if (x >= 0 && x <= dim - 1 && y >= 0 && y <= dim - 1) {
            if (matrix[x][y] == 1) {
                matrix[x][y] = 0;

                // parcurge vecinii nodului curent
                for (int k = 0; k < 4; k++) {
                    int x_nou = x + dlin[k];
                    int y_nou = y + dcol[k];

                    if (x_nou >= 0 && x_nou <= dim - 1 && y_nou >= 0 && y_nou <= dim - 1) {
                        if (matrix[x_nou][y_nou] == 1) {
                            FILL(x_nou, y_nou);
                        }
                    }

                }
            }
        }
    }

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */

        Scanner sc = new Scanner(System.in);

        dim = Integer.parseInt(sc.nextLine());

        matrix = new int[dim][dim];

        for (int i = 0; i < dim; i++) {
            String input = sc.nextLine();

            for (int j = 0; j < input.length(); j++) {

                if (input.charAt(j) == 'X') {
                    matrix[i][j] = 1;
                }
            }

        }

//        for (int i = 0; i < dim; i++) {
//            for (int j = 0; j < dim; j++) {
//                System.out.print(matrix[i][j] + " ");
//            }
//            System.out.println();
//        }

        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (matrix[i][j] == 1) {
                    FILL(i, j);
                    ans++;
                }

            }
        }

//        for (int i = 0; i < dim; i++) {
//            for (int j = 0; j < dim; j++) {
//                System.out.print(matrix[i][j] + " ");
//            }
//            System.out.println();
//        }

        System.out.println(ans);

    }
}
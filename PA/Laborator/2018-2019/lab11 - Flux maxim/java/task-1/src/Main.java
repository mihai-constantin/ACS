import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Main {
	static class Task {
		public static final String INPUT_FILE = "in";
		public static final String OUTPUT_FILE = "out";
		public static final int NMAX = 1005;

		int n;
		int m;

		@SuppressWarnings("unchecked")
		ArrayList<Integer> adj[] = new ArrayList[NMAX];
		int C[][];

		private void readInput() {
			try {
				Scanner sc = new Scanner(new BufferedReader(new FileReader(
								INPUT_FILE)));
				n = sc.nextInt();
				m = sc.nextInt();

				C = new int[n + 1][n + 1];
				for (int i = 1; i <= n; i++) {
					adj[i] = new ArrayList<>();
				}
				for (int i = 1; i <= m; i++) {
					int x, y, z;
					x = sc.nextInt();
					y = sc.nextInt();
					z = sc.nextInt();
					adj[x].add(y);
					adj[y].add(x);
					C[x][y] += z;
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(int result) {
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
								OUTPUT_FILE)));
				pw.printf("%d\n", result);
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private int getResult() {
			// TODO: Calculati fluxul maxim pe graful orientat dat.
			// Sursa este nodul 1.
			// Destinatia este nodul n.
			//
			// In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
			// arcelor, iar in C sunt stocate capacitatile arcelor.
			// De exemplu, un arc (x, y) de capacitate z va fi tinut astfel:
			// C[x][y] = z, adj[x] contine y, adj[y] contine x.
			int flow = 0;
			return flow;
		}

		public void solve() {
			readInput();
			writeOutput(getResult());
		}
	}

	public static void main(String[] args) {
		new Task().solve();
	}
}

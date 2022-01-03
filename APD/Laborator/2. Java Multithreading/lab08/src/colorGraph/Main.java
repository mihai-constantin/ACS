package colorGraph;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * @author cristian.chilipirea
 * 
 */

public class Main {
	static int N = 10;
	static int COLORS = 3;
	static int[][] graph = { { 0, 1 }, { 0, 4 }, { 0, 5 }, { 1, 0 }, { 1, 2 }, { 1, 6 }, { 2, 1 }, { 2, 3 }, { 2, 7 },
			{ 3, 2 }, { 3, 4 }, { 3, 8 }, { 4, 0 }, { 4, 3 }, { 4, 9 }, { 5, 0 }, { 5, 7 }, { 5, 8 }, { 6, 1 },
			{ 6, 8 }, { 6, 9 }, { 7, 2 }, { 7, 5 }, { 7, 9 }, { 8, 3 }, { 8, 5 }, { 8, 6 }, { 9, 4 }, { 9, 6 },
			{ 9, 7 } };

	static ExecutorService tpe = Executors.newFixedThreadPool(4);

	static void colorGraph(int[] colors, int step) {
		if (step == N) {
			printColors(colors);
			return;
		}

		// for the node at position step try all possible colors
		for (int i = 0; i < COLORS; i++) {
			int[] newColors = colors.clone();
			newColors[step] = i;
			if (verifyColors(newColors, step))
				colorGraph(newColors, step + 1);
		}
	}

	private static boolean verifyColors(int[] colors, int step) {
		for (int i = 0; i < step; i++) {
			if (colors[i] == colors[step] && isEdge(i, step))
				return false;
		}
		return true;
	}

	private static boolean isEdge(int a, int b) {
		for (int i = 0; i < graph.length; i++) {
			if (graph[i][0] == a && graph[i][1] == b)
				return true;
		}
		return false;
	}
	
	static void printColors(int[] colors) {
		String aux = "";
		for (int i = 0; i < colors.length; i++) {
			aux += colors[i] + " ";
		}
		System.out.println(aux);
	}

	public static void main(String[] args) {

//		colorGraph(colors, 0);
		int[] colors = new int[N];
		Main.tpe.submit(new Task(tpe, colors, 0));
	}
}

class Task implements Runnable {

	ExecutorService tpe;
	int[] colors;
	int step;

	public Task(ExecutorService tpe, int[] colors, int step) {
		this.tpe = tpe;
		this.colors = colors;
		this.step = step;
	}

	private static boolean isEdge(int a, int b) {
		for (int i = 0; i < Main.graph.length; i++) {
			if (Main.graph[i][0] == a && Main.graph[i][1] == b)
				return true;
		}
		return false;
	}

	private static boolean verifyColors(int[] colors, int step) {
		for (int i = 0; i < step; i++) {
			if (colors[i] == colors[step] && isEdge(i, step))
				return false;
		}
		return true;
	}

	@Override
	public void run() {

		if (step == Main.N) {
			Main.printColors(colors);
			tpe.shutdown();

			try {
				if(!tpe.awaitTermination(1, TimeUnit.SECONDS)) {
					tpe.shutdownNow();
				}
			} catch (InterruptedException e) {
				// e.printStackTrace();
			}
		}

		// for the node at position step try all possible colors
		for (int i = 0; i < Main.COLORS; i++) {
			int[] newColors = colors.clone();
			newColors[step] = i;
			if (verifyColors(newColors, step))
//				colorGraph(newColors, step + 1);

				tpe.submit(new Task(tpe, newColors, step + 1));
		}
	}
}
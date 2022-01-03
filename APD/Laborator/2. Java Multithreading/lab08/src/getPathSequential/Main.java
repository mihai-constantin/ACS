package getPathSequential;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * @author cristian.chilipirea
 * 
 */

public class Main {
	static int[][] graph = { { 0, 1 }, { 0, 4 }, { 0, 5 }, { 1, 0 }, { 1, 2 }, { 1, 6 }, { 2, 1 }, { 2, 3 }, { 2, 7 },
			{ 3, 2 }, { 3, 4 }, { 3, 8 }, { 4, 0 }, { 4, 3 }, { 4, 9 }, { 5, 0 }, { 5, 7 }, { 5, 8 }, { 6, 1 },
			{ 6, 8 }, { 6, 9 }, { 7, 2 }, { 7, 5 }, { 7, 9 }, { 8, 3 }, { 8, 5 }, { 8, 6 }, { 9, 4 }, { 9, 6 },
			{ 9, 7 } };

	static ExecutorService tpe = Executors.newFixedThreadPool(4);

	static void getPath(ArrayList<Integer> partialPath, int destination) {
		if (partialPath.get(partialPath.size() - 1) == destination) {
			System.out.println(partialPath);
			return;
		}

		// Try to add all possible next nodes that do not create a cycle.
		int lastNodeInPath = partialPath.get(partialPath.size() - 1);
		for (int i = 0; i < graph.length; i++) {
			if (graph[i][0] == lastNodeInPath) {
				if (partialPath.contains(graph[i][1]))
					continue;
				ArrayList<Integer> newPartialPath = (ArrayList<Integer>) partialPath.clone();
				newPartialPath.add(graph[i][1]);
				getPath(newPartialPath, destination);
			}
		}
	}

	public static void main(String[] args) {
		ArrayList<Integer> partialPath = new ArrayList<Integer>();
		// Get Path from 0 to 3. The path does not have to be shortest, but it
		// must not contain cycles.
//		getPath(partialPath, 3);
		partialPath.add(0);
		Main.tpe.submit(new Task(tpe, 3, partialPath));
	}
}

class Task implements Runnable {

	ExecutorService tpe;
	ArrayList<Integer> partialPath = new ArrayList<Integer>();
	int destination;

	public Task(ExecutorService tpe, int destination, ArrayList<Integer> partialPath) {
		this.tpe = tpe;
		this.destination = destination;
		this.partialPath = partialPath;
	}

	@Override
	public void run() {

		if (partialPath.get(partialPath.size() - 1) == destination) {

			System.out.println(partialPath);

			tpe.shutdown();

			try {
				if(!tpe.awaitTermination(1, TimeUnit.SECONDS)) {
					tpe.shutdownNow();
				}
			} catch (InterruptedException e) {
				// e.printStackTrace();
			}
		}

		// Try to add all possible next nodes that do not create a cycle.
		int lastNodeInPath = partialPath.get(partialPath.size() - 1);
		for (int i = 0; i < Main.graph.length; i++) {
			if (Main.graph[i][0] == lastNodeInPath) {
				if (partialPath.contains(Main.graph[i][1]))
					continue;
				ArrayList<Integer> newPartialPath = (ArrayList<Integer>) partialPath.clone();
				newPartialPath.add(Main.graph[i][1]);
//				getPath(newPartialPath, destination);
				tpe.submit(new Task(tpe, destination, newPartialPath));
			}
		}


	}
}

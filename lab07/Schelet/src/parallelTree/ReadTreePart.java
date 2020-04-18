package parallelTree;

import com.sun.source.tree.Tree;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.BrokenBarrierException;

/**
 * @author cristian.chilipirea
 *
 */
public class ReadTreePart implements Runnable {
	TreeNode tree;
	String fileName;

	public ReadTreePart(TreeNode tree, String fileName) {
		this.tree = tree;
		this.fileName = fileName;
	}

	@Override
	public void run() {
		try {
			BufferedReader br = new BufferedReader(new FileReader(this.fileName));
			String line;
			while ((line = br.readLine()) != null) {
				String tokens[] = line.split("\t");
				Integer to = Integer.valueOf(tokens[0]);
				Integer from = Integer.valueOf(tokens[1]);

				//TODO - obtine obiect parinte din "from"

				// -> busy wait in while
				// -> cat timp parinte == null, parinte = getNode(from);

				TreeNode parent;

				while((parent = tree.getNode(from)) == null);

				//TODO - adauga copil in parinte, plecand de la parinte si "to"

				// atentie! copil si parinte sunt de tip TreeNode

				synchronized (Main.class) {
					parent.addChild(new TreeNode(to));
				}
			}

			br.close();

		} catch (IOException e) {

		}

		try {
			// sincronizare
			Main.cyclicBarrier.await();
		} catch (InterruptedException | BrokenBarrierException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}
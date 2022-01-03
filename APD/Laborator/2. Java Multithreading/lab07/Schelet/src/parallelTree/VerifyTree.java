package parallelTree;

import java.util.concurrent.BrokenBarrierException;

/**
 * @author cristian.chilipirea
 *
 */
public class VerifyTree implements Runnable {
	TreeNode tree;

	public VerifyTree(TreeNode tree) {
		this.tree = tree;
	}

	boolean isCorrect(TreeNode tree) {
		if (tree == null)
			return true;
		if (tree.name >= 64)
			return true;
		if (tree.left == null)
			return false;
		if (tree.right == null)
			return false;
		boolean aux = ((tree.left.name + tree.right.name) == (tree.name * 4 + 1));
		return aux && isCorrect(tree.left) && isCorrect(tree.right);
	}

	@Override
	public void run() {

		try {
			Main.cyclicBarrier.await();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (BrokenBarrierException e) {
			e.printStackTrace();
		}

		if (isCorrect(tree))
			System.out.println("Correct");
		else
			System.out.println("Wrong");

	}
}

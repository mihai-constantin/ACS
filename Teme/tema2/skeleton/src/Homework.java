import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

/*
 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
 */

/**
 * Main class.
 */
public class Homework {

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	public static void main(String[] args) {
		if (args.length < 4) {
			System.out.println(
					"Usage: java Homework <galaxyInfoPath> <numberOfHashes> <numberOfHeadQuarters> <numberOfSpaceExplorers>");
			System.exit(1);
		}

		int numberOfHashes = Integer.parseInt(args[1]);
		int numberOfHeadQuarters = Integer.parseInt(args[2]);
		int numberOfSpaceExplorers = Integer.parseInt(args[3]);

		AtomicInteger hashesSolved = new AtomicInteger(0);
		CommunicationChannel channel = new CommunicationChannel();

		HeadQuarter headQuarters[] = new HeadQuarter[numberOfHeadQuarters];
		for (int i = 0; i < numberOfHeadQuarters; ++i) {
			headQuarters[i] = new HeadQuarter(args[0], numberOfSpaceExplorers, hashesSolved, channel);
			headQuarters[i].start();
		}

		Set<Integer> solved = new HashSet<>();
		SpaceExplorer spaceExplorers[] = new SpaceExplorer[numberOfSpaceExplorers];
		for (int i = 0; i < numberOfSpaceExplorers; ++i) {
			spaceExplorers[i] = new SpaceExplorer(numberOfHashes, solved, channel);
			spaceExplorers[i].start();
		}

		try {
			for (int i = 0; i < numberOfHeadQuarters; ++i) {
				headQuarters[i].join();
			}

			for (int i = 0; i < numberOfSpaceExplorers; ++i) {
				spaceExplorers[i].join();
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}

/*
 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
 */

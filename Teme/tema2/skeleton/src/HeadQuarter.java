import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

/*
 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
 */

/**
 * Class for a Federation HeadQuarter thread.
 */
public class HeadQuarter extends Thread {
	// test files
	private static String NODE_NAMES = "_data.txt";
	private static String ANSWER = "_answer.txt";
	private static String GRAPH = "_graph.txt";

	// helper message (used when a solar system has no parent - it is reachable from
	// the start)
	private static String NO_PARENT = "NO_PARENT";

	/**
	 * Message body that specifies the end of the list of unlocked adjacent solar
	 * systems sent by the headquarters to the space explorers.
	 */
	public static String END = "END";

	/**
	 * Message body that specifies the end of the program (sent to each space
	 * explorer).
	 */
	public static String EXIT = "EXIT";

	// map of the galaxy (represented as a graph)
	private ArrayList<String> solarSystemNames;
	private ArrayList<String> solarSystemDecodedFrequencies;
	private Integer numberOfSolarSystems;
	private boolean[][] adjacencyMatrix;

	// termination
	private Integer numberOfSpaceExplorers;
	private AtomicInteger decodedFrequencies;
	private static Set<String> decodedFrequenciesSet = new HashSet<String>();

	// communications
	private CommunicationChannel channel;

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Creates a {@code HeadQuarter} object.
	 * 
	 * @param galaxyInfoPath
	 *            path to the input (i.e., the folder containing the galaxy map and
	 *            the expected results)
	 * @param numberOfSpaceExplorers
	 *            number of space explorers
	 * @param decodedFrequencies
	 *            number of decoded frequencies (discovered solar systems)
	 * @param channel
	 *            communication channel between the space explorers and the
	 *            headquarters
	 */
	public HeadQuarter(String galaxyInfoPath, Integer numberOfSpaceExplorers, AtomicInteger decodedFrequencies,
			CommunicationChannel channel) {
		parseHashes(galaxyInfoPath);
		parseAnswers(galaxyInfoPath);
		parseAdjMatrix(galaxyInfoPath);

		this.numberOfSpaceExplorers = numberOfSpaceExplorers;
		this.decodedFrequencies = decodedFrequencies;
		this.channel = channel;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Parses the values to be decoded (hashed) by the space explorers.
	 * 
	 * @param testCase
	 *            path to the test case being tested
	 */
	private void parseHashes(String testCase) {
		solarSystemNames = new ArrayList<>();

		try (BufferedReader br = new BufferedReader(new FileReader(testCase + NODE_NAMES))) {
			for (String line; (line = br.readLine()) != null;) {
				solarSystemNames.add(line);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

		this.numberOfSolarSystems = solarSystemNames.size();
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Parses the decoded frequencies (i.e., hashed values).
	 * 
	 * @param testCase
	 *            path to the test case being tested
	 */
	private void parseAnswers(String testCase) {
		solarSystemDecodedFrequencies = new ArrayList<>();

		try (BufferedReader br = new BufferedReader(new FileReader(testCase + ANSWER))) {
			for (String line; (line = br.readLine()) != null;) {
				solarSystemDecodedFrequencies.add(line);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Parses the map of the galaxy (i.e., the graph adjacency matrix).
	 * 
	 * @param testCase
	 *            path to the test case being tested
	 */
	private void parseAdjMatrix(String testCase) {
		adjacencyMatrix = new boolean[numberOfSolarSystems][numberOfSolarSystems];

		AtomicInteger row = new AtomicInteger(0);
		AtomicInteger column = new AtomicInteger(0);

		try (BufferedReader br = new BufferedReader(new FileReader(testCase + GRAPH))) {
			for (String line; (line = br.readLine()) != null;) {
				String[] splitLine = line.split(", ");
				for (String s : splitLine) {
					adjacencyMatrix[row.getAndIncrement()][column.get()] = s.equals("1");
				}
				column.getAndIncrement();
				row.set(0);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	@Override
	public void run() {
		Message endMessage = new Message(-1, HeadQuarter.END);

		// put the initial solar systems (i.e., accessible from the start)
		List<Integer> rootNodes = getInitialSolarSystems();

		// send the initial solar systems to the space explorers
		for (Integer node : rootNodes) {
			channel.putMessageHeadQuarterChannel(new Message(-1, HeadQuarter.NO_PARENT));
			channel.putMessageHeadQuarterChannel(new Message(node, solarSystemNames.get(node)));
		}
		channel.putMessageHeadQuarterChannel(endMessage);

		while (true) {
			// if all the solar systems in the galaxy have been found, the program ends
			// successfully
			if (decodedFrequencies.get() == numberOfSolarSystems) {
				for (int i = 0; i < numberOfSpaceExplorers; ++i) {
					// each space explorer is notified that the discovery mission has completed
					channel.putMessageHeadQuarterChannel(new Message(-1, HeadQuarter.EXIT));
				}
				channel.putMessageHeadQuarterChannel(endMessage);

				System.out.println("All solar systems have been discovered! Headquarter quitting.");
				System.exit(0);
			}

			// random sleep (simulates periods when the HQ is busy and cannot decode the
			// frequencies for the space explorers)
			try {
				Thread.sleep((long) (Math.random() * 100));
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

			// wake up and take one message from the space explorers
			Message explorerMessage = channel.getMessageSpaceExplorerChannel();
			if (explorerMessage == null) {
				continue;
			}

			if (checkSpaceExplorerMessage(explorerMessage, rootNodes)) {
				// put all the neighboring (i.e., adjacent undiscovered) solar systems for
				// decoding
				Integer currentSolarSystem = explorerMessage.getCurrentSolarSystem();
				List<Integer> neighbors = getNeighbors(currentSolarSystem);

				// notify interested space explorers about the new undiscovered solar systems
				// (through the communication channel)
				for (Integer neigh : neighbors) {
					channel.putMessageHeadQuarterChannel(
							new Message(currentSolarSystem, solarSystemNames.get(currentSolarSystem)));
					channel.putMessageHeadQuarterChannel(new Message(neigh, solarSystemNames.get(neigh)));
				}
				channel.putMessageHeadQuarterChannel(endMessage);

				// add the new decoded frequency to the global set
				synchronized (decodedFrequenciesSet) {
					if (!decodedFrequenciesSet.contains(explorerMessage.getData())) {
						decodedFrequencies.getAndIncrement();
						decodedFrequenciesSet.add(explorerMessage.getData());
					}
				}
			} else {
				// if the message received from a space explorer is incorrect (i.e., the decoded
				// value or the previous solar system was wrong), the galaxy explodes and the
				// program ends with an error
				System.out.println("Received incorrect previous solar system or decoding! Galaxy exploded.");
				System.exit(1);
			}
		}
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Computes the initial solar systems (i.e., the ones reachable at the start of
	 * the simulation).
	 * 
	 * @return the list of initial solar systems
	 */
	private List<Integer> getInitialSolarSystems() {
		List<Integer> rootNodes = new ArrayList<>();
		boolean visited[] = new boolean[numberOfSolarSystems];

		for (int solarSystem = 0; solarSystem < numberOfSolarSystems; ++solarSystem) {
			if (!visited[solarSystem]) {
				visitSubTree(solarSystem, visited);
				rootNodes.add(solarSystem);
			}
		}
		return rootNodes;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Computes the neighbors of a solar system (i.e., other solar systems
	 * accessible through the discovered worm-holes).
	 * 
	 * @param solarSystem
	 *            current solar system
	 * @return list of accessible solar systems from the current one
	 */
	private List<Integer> getNeighbors(int solarSystem) {
		List<Integer> neighbours = new ArrayList<>();

		for (int j = 0; j < numberOfSolarSystems; ++j) {
			if (adjacencyMatrix[solarSystem][j])
				neighbours.add(j);
		}

		return neighbours;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Visits a sub-tree in a graph.
	 * 
	 * @param solarSystem
	 *            current solar system
	 * @param visited
	 *            list of visited nodes
	 */
	private void visitSubTree(int solarSystem, boolean visited[]) {
		LinkedList<Integer> queue = new LinkedList<>();
		visited[solarSystem] = true;
		queue.push(solarSystem);

		while (!queue.isEmpty()) {
			int current = queue.poll();
			List<Integer> neighbors = getNeighbors(current);
			for (Integer neigh : neighbors) {
				if (!visited[neigh]) {
					visited[neigh] = true;
					adjacencyMatrix[neigh][current] = false;
					queue.add(neigh);
				}
			}
		}
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Verifies if a message received from a space explorer is correct (the
	 * frequency was decoded correctly and the parent solar system - i.e., the one
	 * where the space explorer was coming from - is correct).
	 * 
	 * @param message
	 *            message to be verifies
	 * @param rootSolarSystems
	 *            list of root solar systems
	 * @return
	 */
	private boolean checkSpaceExplorerMessage(Message message, List<Integer> rootSolarSystems) {
		int parentNode = message.getParentSolarSystem();
		int currentNode = message.getCurrentSolarSystem();

		if (!rootSolarSystems.contains(currentNode) && !adjacencyMatrix[parentNode][currentNode])
			return false;

		return message.getData().equals(solarSystemDecodedFrequencies.get(message.getCurrentSolarSystem()));
	}
}

/*
 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
 */

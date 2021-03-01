import os
import sys
import argparse

import uuid

from igraph import Graph


def main(arguments):
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('-f', '--file',
                        help="Print testcase details in files starting with this suffix + (_graph.txt, _data.txt)",
                        required=False)
    parser.add_argument('-s', '--size', default=10,
                        help="Size of graph", required=False)
    parser.add_argument('-e', '--edges', default=9,
                        help="Number of edges", required=False)

    args = parser.parse_args(arguments)

    # generate graph
    g = Graph.Erdos_Renyi(n=int(args.size), m=int(
        args.edges), directed=False, loops=False)
    # g = Graph.Degree_Sequence([1, 3, 1, 1], method="vl")

    # print to file(s)
    if args.file:
        with open(args.file + '_graph.txt', 'w+') as f:
            for line in g.get_adjacency():
                print >> f, ', '.join(map(str, line))
        with open(args.file + '_data.txt', 'w+') as f:
            for _ in range(int(args.size)):
                print >> f, uuid.uuid4()
    else:
        for line in g.get_adjacency():
            print ', '.join(map(str, line))
        for _ in range(args.size):
            print uuid.uuid4()


if __name__ == '__main__':
    main(sys.argv[1:])

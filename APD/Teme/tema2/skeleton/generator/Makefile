.PHONY: all

all: run
# required dependencies for mac
generator-mac-deps:
	brew install cairo
	brew install py2cairo
	brew install igraph
	pip install python-igraph

# generate test case
# python generate_graph.py -h for details
# name of file should be a suffix, as the script generates two files
run:
	python generate_graph.py -f ../test_cases/test01 -s 100 -e 150

.PHONY: all

all: build

build: Main.java
	javac Main.java

# solves a test-case, given its prefix
# if 3rd argument given, prints the solution in the given file suffix (should be identical to the 1st param)
run: 
	time java Main ../test_cases/test01 100000 ../test_cases/test01

clean:
	rm *.class

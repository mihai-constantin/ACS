build:
	gcc -std=c9x TestStack.c -o TestStack -w
	gcc -std=c9x TestQueue.c -o TestQueue -w
	gcc -std=c9x Parantheses.c -o Parantheses -w
	gcc -std=c9x RadixSort.c -o RadixSort -lm -w
clean:
	rm TestStack TestQueue Parantheses RadixSort *~
runStack:	
	./TestStack
runQueue:	
	./TestQueue

runValgrindStack:
	valgrind ./TestStack
runValgrindQueue:
	valgrind ./TestQueue

runParantheses:	
	./Parantheses
runRadix:	
	./RadixSort	



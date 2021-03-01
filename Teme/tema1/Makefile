build:
	gcc tema1.c -o tema1

run: build
	./tema1

check-memory-leaks: build
	valgrind --leak-check=full -v ./tema1

clean:
	rm tema1 test_easy_0.txt test_easy_1.txt test_easy_2.txt test_medium_1.txt test_medium_2.txt test_complex_1.txt test_complex_2.txt
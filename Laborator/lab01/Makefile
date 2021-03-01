all: hello-world pi

hello-world: HelloWorld.c
	gcc -fopenmp $? -o $@ -Wall

pi: pi.c
	gcc $? -o $@ -Wall

pi2: pi2.c
	gcc -fopenmp $? -o $@ -Wall

pi3: pi3.c
	gcc -fopenmp $? -o $@ -Wall

pi4: pi4.c
	gcc -fopenmp $? -o $@ -Wall

pi5: pi5.c
	gcc -fopenmp $? -o $@ -Wall

demo: demo.c
	gcc -fopenmp $? -o $@ -Wall

.PHNOY: clean
clean:
	rm -f hello-world pi pi2 pi3 pi4 pi5 demo

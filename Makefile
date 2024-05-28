all: clasament

clasament: *.c
	gcc $^ -Wall -g -o clasament	
clean:
	rm -f clasament
	rm -f *.out
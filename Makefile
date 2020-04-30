clean:
	rm -f stack

stack:
	clang++ stack.cpp -o stack && ./stack

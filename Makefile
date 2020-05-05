clean:
	rm -f stack
	rm -f singlylinkedlist

stack:
	clang++ stack.cpp -o stack && ./stack

singlylinkedlist:
	clang++ singlylinkedlist.cpp -o singlylinkedlist && ./singlylinkedlist

clean:
	rm -f stack
	rm -f singlylinkedlist
	rm -f nodes

stack:
	clang++ stack.cpp -o stack && ./stack

singlylinkedlist:
	clang++ singlylinkedlist.cpp -o singlylinkedlist && ./singlylinkedlist

nodes:
	clang++ nodes.cpp -o nodes && ./nodes

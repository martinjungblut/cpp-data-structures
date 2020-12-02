clean:
	rm -f stack
	rm -f singlylinkedlist
	rm -f doublylinkedlist
	rm -f nodes

stack:
	clang++ -std=c++17 stack.cpp -o stack && ./stack

singlylinkedlist:
	clang++ -std=c++17 singlylinkedlist.cpp -o singlylinkedlist && ./singlylinkedlist

doublylinkedlist:
	clang++ -std=c++17 doublylinkedlist.cpp -o doublylinkedlist && ./doublylinkedlist

nodes:
	clang++ -std=c++17 nodes.cpp -o nodes && ./nodes

clean:
	rm -f stack
	rm -f singlylinkedlist
	rm -f doublylinkedlist
	rm -f nodes

stack:
	clear && make clean && clang++ -std=c++17 stack.cpp -o stack && ./stack -s --reporter=junit

singlylinkedlist:
	clear && make clean && clang++ -std=c++17 singlylinkedlist.cpp -o singlylinkedlist && ./singlylinkedlist -s --reporter=junit

doublylinkedlist:
	clear && make clean && clang++ -std=c++17 doublylinkedlist.cpp -o doublylinkedlist && ./doublylinkedlist -s --reporter=junit

nodes:
	clear && make clean && clang++ -std=c++17 nodes.cpp -o nodes && ./nodes -s --reporter=junit

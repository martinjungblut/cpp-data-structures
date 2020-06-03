clean:
	rm -f stack
	rm -f singlylinkedlist
	rm -f trackers

stack:
	clang++ stack.cpp -o stack && ./stack

singlylinkedlist:
	clang++ singlylinkedlist.cpp -o singlylinkedlist && ./singlylinkedlist

trackers:
	clang++ trackers.cpp -o trackers && ./trackers

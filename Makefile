ds: main.cpp
	g++ main.cpp -o ds -s -lboost_filesystem

clean:
	rm -rf ds
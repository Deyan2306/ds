ds: main.cpp
	g++ main.cpp -o ds -s -lboost_filesystem -lboost_program_options

clean:
	rm -rf ds
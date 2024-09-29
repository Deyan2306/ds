ds: main.cpp
	g++ to_refactor.cpp source/flag_holder.cpp source/dir_holder.cpp source/dir_file.cpp -o ds -s -lboost_filesystem -lboost_program_options

clean:
	rm -rf ds
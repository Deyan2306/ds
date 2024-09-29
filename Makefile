ds: main.cpp
	g++ main.cpp source/flag_holder.cpp source/dir_holder.cpp source/dir_file.cpp -o ds -s -lboost_filesystem -lboost_program_options

clean:
	rm -rf ds

install: ds
	install -Dm755 ds /usr/local/bin/ds

uninstall:
	rm -f /usr/local/bin/ds

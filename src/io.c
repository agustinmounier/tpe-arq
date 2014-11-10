#include "../include/io.h"
#include "../include/terminal.h"
#include "../include/common.h"

int write_io(int file_desc, char * buffer, int cant){
	
	int resp = -1;
	
	switch(file_desc){
		case STDOUT:
			resp = write_to_terminal(buffer, cant);
			break;
		case STDIN:
			resp = write_to_terminal_buffer(buffer, cant);
			break;
		case STDERR:
			resp = write_to_terminal(buffer, cant);
			break;
	}

	return resp;

}

int read_io(int file_desc, char * buffer, int cant){

	int resp = -1;
	
	switch(file_desc){

		case STDOUT:
			return 0;
		case STDIN:
			resp = read_from_terminal(buffer, cant);
			break;
		case STDERR:
			return 0;

	}

	return resp;

}

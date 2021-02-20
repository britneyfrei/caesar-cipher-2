// included header files
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// function prototype
void rotx(char *, char *);

// struct definition
struct entry {
	char message[16];
	char rotation[4];
};

int main(int argc, char **argv) {
	// check for correct number of arguments
	// if not, show error message and stop
	if (argc != 2) {
		printf("Usage: ./four <file>\n");
		return 1;
	}
	// initialize entries array of struct entry
	struct entry entries[8];
	// initialize buffer
	char buf[128];

	// call open() with filename given on command line and 0
	int fd = open(argv[1], 0);

	// call read() with file descriptor, buf and 128
	ssize_t file_length = read(fd, buf, 128);

	// parse buf and place messages and rotations into entries array
	int b = 0; // index of buf
	int e = 0; // index of entries
	int m = 0; // index of message
	int r = 0; // index of rotation
	// skip first line of file
	while (buf[b] != '\n') {
		b++;
	}
	// increment b to skip the newline char
	b++;
	// loop until end of file is reached
	for (b; b < file_length; b++) {
		// loop until comma is reached
		for (b; buf[b] != ','; b++) {
			// place each char in buf into the message array
			entries[e].message[m] = buf[b];
			m++;
		}
		// null terminate the message array
		entries[e].message[m] = '\0';
		// increment b to skip the newline char
		b++;
		// loop until newline is reached
		for (b; buf[b] != '\n'; b++) {
			// place each char in buf into the rotation array
			entries[e].rotation[r] = buf[b];
			r++;
		}
		// null terminate the rotation array
		entries[e].rotation[r] = '\0';
		// reset the message and rotation indices
		m = 0;
		r = 0;
		// use rotx() to decode messages in place
		rotx(entries[e].message, entries[e].rotation);
		// output message on single line
		// check if end of file is reached
		if (buf[b] == '\n' && buf[b+1] == '\0') {
			// print the last message with a newline after
			printf("%s\n", entries[e].message);
		}
		else {
			// print message with a space after
			printf("%s ", entries[e].message);
		}
		// increment index of entries
		e++;
	}
	// close the file
	close(fd);
	return 0;
}

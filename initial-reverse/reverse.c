#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/*
 * This program reverses input.
 * If called with 0 args it handles stdin.
 * If called with 1 args it reads from the file passed in and prints
 * to stdout.
 * If called with 2 args it reads from the file passed in and writes
 * to the second argument.
 */

struct text_line {
	char *line;
	struct text_line *next;
};



int
main(int argc, char *argv[])
{
	if (argc > 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}	

	size_t nbytes = 80;

	FILE *infile = stdin;
	FILE *outfile = stdout;

	if (argc > 1) {
		infile = fopen(argv[1], "r");
		if (infile == NULL) {
			fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[1]);
			exit(1);
		}
	}

	if (argc > 2) {
		outfile = fopen(argv[2], "w");
		if (outfile == NULL) {
			fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[2]);
			exit(1);
		}

		struct stat f1;
		struct stat f2;
		int res;
		res = fstat(fileno(infile), &f1);
		if (res != 0) {
			fprintf(stderr, "reverse: fstat error\n");
			exit(1);
		}
		
		res = fstat(fileno(outfile), &f2);
		if (res != 0) {
			fprintf(stderr, "reverse: fstat error\n");
			exit(1);
		}
		
		if (f1.st_ino == f2.st_ino) {
			fprintf(stderr, "reverse: input and output file must differ\n");
			exit(1);
		}
		
	}
		

	/* we always make the head the most recent node made
	 * because we are going to want to walk the list in
	 * reverse, a lot like a stack */
	struct text_line *head = malloc(sizeof(struct text_line));
	head->next = NULL;
	while (getline(&(head->line), &nbytes, infile) != -1) {
		struct text_line *p = malloc(sizeof(struct text_line));
		p->next = head;
		p->line = NULL;
		head = p;
	}

	struct text_line *curr = head;
	while (curr != NULL){
		fprintf(outfile, curr->line);
		struct text_line *tmp = curr->next;
		free(curr->line);
		free(curr);
		curr = tmp;
	}
		

	fclose(infile);
	fclose(outfile);
	return 0;
}

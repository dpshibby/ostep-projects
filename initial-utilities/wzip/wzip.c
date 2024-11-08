#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/*
 * This program takes a list of filenames as input and produces a
 * run-length encoding compression based on the given file. The
 * output is printed to stdout so must be redirected to a file
 * to be saved.
 */
int
main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}

	FILE *fp;

	int32_t inarow = 0;
	int ch;
	int last;

	for (int i = 1; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wzip: cannot open file \"%s\"\n", argv[i]);
			exit(1);
		}
		size_t res = fread(&last, sizeof(char), 1, fp);
		if (res != 1)
			continue;
		else
			inarow++;

		while (fread(&ch, sizeof(char), 1, fp)) {
			if (ch == last) {
				inarow++;
			} else {
				fwrite(&inarow, sizeof(int32_t), 1, stdout);
				fwrite(&last, sizeof(char), 1, stdout);
				inarow = 1;
				last = ch;
			}

		}
		fclose(fp);
	}
	/* final write out after all files are closed */
	if (inarow != 0) {
		fwrite(&inarow, sizeof(int32_t), 1, stdout);
		fwrite(&last, sizeof(char), 1, stdout);
	}




	return 0;
}

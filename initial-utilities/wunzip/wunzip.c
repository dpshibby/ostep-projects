#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/*
 * This program takes a list of filenames as input and produces a
 * run-length encoding decompression based on the given files. The
 * output is printed to stdout so must be redirected to a file
 * to be saved.
 */
int
main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}

	FILE *fp;

	int32_t repeats = 0;
	int ch;

	for (int i = 1; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wunzip: cannot open file \"%s\"\n", argv[i]);
			exit(1);
		}

		while (fread(&repeats, sizeof(int32_t), 1, fp)) {
			fread(&ch, sizeof(char), 1, fp);
			for (int j = 0; j < repeats; j++) {
				printf("%c", ch);
			}

		}
		fclose(fp);
	}




	return 0;
}

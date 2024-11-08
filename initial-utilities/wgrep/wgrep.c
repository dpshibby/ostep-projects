#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * This program takes as input a search term followed by one or
 * more file names and searches each file for the search term.
 * If it is found, the entire line on which it is found is
 * printed. If only a search term and no files are given, it
 * accepts input from stdin. It does not do anything fancy like
 * regexp searching.
 */
int
main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}

	FILE *fp;
	size_t nbytes = 80;
	char *buffer = malloc(nbytes + 1);

	if (argc == 2) {
		fp = stdin;
		while (getline(&buffer, &nbytes, fp) != -1) {
			if(strstr(buffer, argv[1]))
				printf("%s", buffer);
		}
		fclose(fp);
		exit(0);
	}
		
	for (int i = 2; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wgrep: cannot open file \"%s\"\n", argv[i]);
			exit(1);
		}

		while (getline(&buffer, &nbytes, fp) != -1) {
			if(strstr(buffer, argv[1]))
				printf("%s", buffer);
		}
		fclose(fp);
	}



	free(buffer);
	return 0;
}

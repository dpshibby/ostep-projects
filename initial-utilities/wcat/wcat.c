#include <stdlib.h>
#include <stdio.h>

/*
 * This program takes a list of files and prints them
 * in the order received. If it cannot open the next
 * file to be read, the program exits with an error.
 */
int
main(int argc, char *argv[])
{
	if (argc == 1)
		exit(0);

	FILE *fp;
	char buffer[81];

	for (int i = 1; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wcat: cannot open file \"%s\"\n", argv[i]);
			exit(1);
		}

		while (fgets(buffer, sizeof(buffer), fp) != NULL)
			printf("%s", buffer);

		fclose(fp);
	}

	return 0;
}

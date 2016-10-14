#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	int numLine = 0, numWord = 0, numByte = 0;
	char c, pre = ' ';
    	FILE *fp = fopen(argv[1], "r");
	while(1) {
		c = fgetc(fp);
		if(c == EOF)
			break;
		numByte++;
		if(isspace(pre) && !isspace(c))
			numWord++;
		pre = c;
		if(c == '\n')
			numLine++;
	}
	fclose(fp);
	printf("%d %d %d", numLine, numWord, numByte);
    return 0;
}

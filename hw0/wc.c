#include <stdio.h>

int main(int argc, char* argv[]) {
	unsigned int words, lines, characters;
	words = lines = characters = 0;
	char* filename = argv[1];
	FILE* file = fopen(filename, "r");
	char ch = fgetc(file), prech = 's';
	
	if(file == NULL) { // return if there is no such file
		printf("No such file\n");		
		return 0;
	}

	while((ch = fgetc(file)) != EOF) {
				
		characters += 1;		
		if(ch == '\n') { 
			lines += 1;
			words += 1; // maybe there is some optimal solution to count words
		}
		if(ch == ' ' && prech != ' ') {
			words += 1;
		}
		prech = ch;
	}
	printf("%u %u %u %s\n", lines, words, characters, filename);
}

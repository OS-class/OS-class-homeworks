#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printText();
    numberOfLines();

    return 0;
}

void printText(){
    FILE *file;
    file =fopen("/home/developer/Text Files/file.txt", "r");
    int count = 0;
    char buf[1000];
    char* str = NULL;

    while ((str = fgets(buf, 1000, file)) != NULL){
        printf("%s",str);
        count += strlen(str);
    }

    printf("\nNumber of characthers: %d", count);
}

void numberOfLines(){
    FILE *file;
    file =fopen("/home/developer/Text Files/file.txt", "r");

    char c;
    int lines = 0, words = 0;

    do {
      c = getc (file);
      if (c == '\n' && c != ' '){
          lines++;
        }
      if(c == ' ' || c == '\n'){
        words++;
      }
      } while (c != EOF);

    printf("\nNumber of lines: %d", lines);
    printf("\nNumber of words: %d\n", words);
}

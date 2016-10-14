#include <stdio.h>

int main(void)
{
  int word, newlines, charracter;
  int c;
char evvelki = ' ' ;

FILE *fp = fopen("/home/elish32/Documents/project/a.txt","r");


  word = 0;
  newlines = 0;
charracter = 0;

  do {
	++charracter;
       c = getc(fp);
	if(c != ' ' && evvelki == ' ' || c=='\n') {
          ++word;
      }
      
      if(c == '\n') {
         ++newlines;
      }
	evvelki = c;  
}
  while(c != EOF);

  printf("Charracter: %d\n Word: %d\n Lines: %d\n", charracter, (word-1), newlines);
  return 0;
}

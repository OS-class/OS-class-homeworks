+#include <stdio.h>
 +#include <stdlib.h> 
 +#include <ctype.h> 
 +
 +int main(int argc, char* argv[])
 +{
 +    unsigned long lCount, wCount , cCount; 
 +
 +    char* cFile = ""; 
 +    cFile = argv[1]; 
 +
 +    FILE* fPointer = NULL; 
 +    fPointer = fopen(cFile,"r"); 
 +
 +    char ch;
 +    char previous = ' '; 
 +
 +    cCount =0;
	  wCount = 0;
	  cFile = 0;
 +        
 +    
 +    while((ch = getc(fPointer)) != EOF) {
 +        cCount++; 
 
	 if(isspace(previous) && !isspace(ch))
 +            wCount++;
 +
 +
 +        if(ch == '\n')
 +            lCount++; 
 +
 +       
 +      
 +        
 +        previous = ch; 
 +    }
 +        
 +    printf("%ld %ld %ld %s\n", lCount, wCount, cCount, cFile); 
 +
 +    return 0;
 +}

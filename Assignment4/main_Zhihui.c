#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
//Fix me: Do the necessary change to make the implementation //case-insensitive  
   while (1) 
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '\''){
            if (length + 1 >= maxLength){
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            // store the read char one by one into the array
            word[length] = tolower(c);
            length++;
        }
        else if (length > 0 || c == EOF){
            break;
        }
    }
    if (length == 0){
        free(word);
        return NULL;
    }
    word[length] = '\0';
    /*
    int i;
    for(i=0;i<length;i++){
        printf("%c", word[i]);
    }
    printf("\n");
    */
    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    FILE *reader=fopen(fileName,"r");
    assert(reader!=NULL);

    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---
    // Be sure to free the word after you are done with it here.
    int *val;
    char *word = nextWord(reader);
    while (word != NULL) {
        val = hashMapGet(map, word);
        
        if (val == NULL) {              //not in map
            hashMapPut(map, word, 1);
        }
        else{                           //already in map
            hashMapPut(map, word, *val+1);
        }
        free(word);
        word = nextWord(reader);
        }
    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    fclose(reader);
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);

    return 0;
}

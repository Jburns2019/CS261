#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    char *word = nextWord(file);
    while (word != 0) {
        hashMapPut(map, word, 1);
        word = nextWord(file);
    }
}

int _findMin(int one, int two, int three) {
    int returnVal = one;

    if (two <= one && two <= three) {
        returnVal = two;
    } else if (three <= one && three <= two) {
        returnVal = three;
    }

    return returnVal;
}

int _getLavenshteinVal(char *dictionWord, char *word) {
    int n = strlen(dictionWord);
    int m = strlen(word);

    //Set up the array.
    int arr[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            arr[i][j] = 0;
        }
    }

    //the top and far left are just indexed.
    for (int i = 1; i <= n; i++) {
        arr[i][0] = i;
    }
    for (int j = 1; j <= m; j++) {
        arr[0][j] = j;
    }

    //set value based on which of sub, deletion, or insertion gives the smallest value.
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cost = ((int)dictionWord[i-1] - (int)word[j-1] == 0) ? 0 : 1;
//            if (cost == 0) {//testing
//                printf("(%c, %c) @ (%d, %d)\n", dictionWord[i-1], word[j-1], i, j);
//            }
            int min = _findMin(arr[i-1][j] + 1, arr[i][j-1] + 1, arr[i-1][j-1] + cost);
            arr[i][j] = min;
        }
    }

//    for (int i = 0; i <= n; i++) { testing
//        for (int j = 0; j <= m; j++) {
//            printf("[%d]", arr[i][j]);
//        }
//        printf("\n");
//    }

    return arr[n][m];
}

 void _lavenshteinMapVals(HashMap *map, HashMap *lMap, char **mapCollection, char *word) {
    for (int i = 0; i < map->size; i++) {
        hashMapPut(lMap, mapCollection[i], _getLavenshteinVal(mapCollection[i], word));
    }
}

int _arrayContains(int cap, char **arr, char *word) {
    int returnVal = 0;
    for (int i = 0; i < cap; i++) {
        if (strcmp(arr[i], word) == 0) {
            returnVal = 1;
        }
    }
    return returnVal;
}

char **_psuedoSortN(int num, char**lMapCollection, HashMap *lMap) {
    char **arr = (char **)malloc(num * sizeof(char *));
    for (int i = 0; i < num; i++) {
        int min = *hashMapGet(lMap, lMapCollection[0]);
        for (int j = 1; j < lMap->size; j++) {
            int newMin = *hashMapGet(lMap, lMapCollection[j]);
            if (newMin <= min && !_arrayContains(i, arr, lMapCollection[j])) {
                min = *hashMapGet(lMap, lMapCollection[j]);
                arr[i] = lMapCollection[j];
            }

        }
    }
    return arr;
}

char **_getWords(HashMap *map, char *word) {
    char **wordCollection = (char **)malloc(5 * sizeof(char *));
    HashMap *lMap = hashMapNew(map->capacity);
    _lavenshteinMapVals(map, lMap, mapCollection(map), word);
    char **arr = _psuedoSortN(5, mapCollection(lMap), lMap);
    for (int i = 0; i < 5; i++) {
        wordCollection[i] = arr[i];
    }
    return wordCollection;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv) {
    HashMap* map = hashMapNew(1000);

    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);

    fclose(file);

    char inputBuffer[256];
    int quit = 0;

    while (!quit) {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);

        int validInput = 1;
        for (int i = 0; i < strlen(inputBuffer); i++) {
            if (!isalpha(inputBuffer[i])) {
                validInput = 0;
                printf("The character |%c| is not allowed. Try again.\n", inputBuffer[i]);
            } else if (isupper(inputBuffer[i])) {
                inputBuffer[i] += 32;
            }
        }

        if (validInput) {
            if (hashMapContainsKey(map, inputBuffer)) {
                printf("The inputed word %s is spelled correctly.\n", inputBuffer);
          } else {
                printf("That word is not in the dictionary, here are the closest words:");
                char **words = _getWords(map, inputBuffer);
                for(int i = 0; i < 5; i++) {
                    if (i < 4) {
                        printf("%s, ", words[i]);
                    }
                    else {
                        printf("and %s.\n", words[i]);
                    }
                }
            }

            if (strcmp(inputBuffer, "quit") == 0) {
                quit = 1;
            }
        }


    }

    hashMapDelete(map);
    return 0;
}

/* CS261- Assignment 1A - Question 3
   Name: John Burns
   Date: 07/01/19
   Solution description: String operations.
*/

#include <stdio.h>
#include <stdlib.h>

int _isUpperCase(char ch) {
    int returnVal = 0;
    int val = (int)ch;
    if (val >= 65 && val <= 90) {
        returnVal = 1;
    }
    return returnVal;
}

int _isLowerCase(char ch) {
    int returnVal = 0;
    int val = (int)ch;
    if (val >= 97 && val <= 122) {
        returnVal = 1;
    }
    return returnVal;
}

int _isAlpha(char ch) {
    int returnVal = 0;
    int val = (int)ch;
    if ((val >= 65 && val <= 90) || (val >= 97 && val <= 122)) {
        returnVal = 1;
    }
    return returnVal;
}

int _isDigit(char ch) {
    int returnVal = 0;
    int val = (int)ch;
    if (val >= 48 && val <= 57) {
        returnVal = 1;
    }
    return returnVal;
}

char toUpperCase(char ch)
{
    char returnChar = ch;
    if (_isLowerCase(ch) == 1) {
        int val = (int)ch;
        val -= 32;
        returnChar = (char)val;
    }
    return returnChar;
}

char toLowerCase(char ch)
{
  char returnChar = ch;
    if (_isUpperCase(ch) == 1) {
        int val = (int)ch;
        val += 32;
        returnChar = (char)val;
    }
    return returnChar;
}

int stringLength(char s[])
{
    int length = 0;
    while (*(s + length) != '\0') {
        length += 1;
    }
   return length;
}


void camelCase(char* word) {
	int length = stringLength(word);
	int editLength = length;
	int begOfStr = 0;
	int j = 0;

	//make all letters lower case.
	for (int i = 0; i < length; i++) {
        word[i] = toLowerCase(word[i]);
    }

    //find out if the word is worth processing.
	int searchingForLetter = 1;
	int hasBeen_ = 0;
	int searchingForSecW = 1;
	int k = 0;
	while (searchingForSecW == 1 && k < length) {
        if (_isAlpha(word[k]) == 1 && searchingForLetter != 0) {
            begOfStr = k;
            searchingForLetter = 0;
        }
        if (searchingForLetter == 0 && _isAlpha(word[k]) == 0) {
                hasBeen_ = 1;
        }
        if (hasBeen_ == 1 && _isAlpha(word[k]) == 1) {
            searchingForSecW = 0;
        }
        k++;
	}

	if (searchingForSecW == 0) {
        //remove all weird symbols.
        for (int i = begOfStr; i < length; i++) {
            if (_isAlpha(word[i]) == 1 || word[i] == '_') {
                word[j] = word[i];
            }
            else if ((word[i] == ' ') || (_isAlpha(word[i]) == 0 && word[i] != '_')) {
                word[j] = '_';
            }
            j++;
        }
        editLength -= begOfStr;
        if (editLength < length) {
            word[editLength] = '\0';
            length = editLength;
            editLength = length;
        }

        //Make some upper case letters.
        hasBeen_ = 0;
        for (int i = 0; i < length; i++) {
            if (i > 0 && _isAlpha(word[i]) == 0) {
                hasBeen_ = 1;
            }
            if (hasBeen_ == 1 && _isAlpha(word[i]) == 1) {
                word[i] = toUpperCase(word[i]);
                hasBeen_ = 0;
            }
        }

        j = 0;
        editLength = 0;
        for (int i = 0; i < length; i++) {
            if (_isAlpha(word[i]) == 1) {
                    editLength++;
                word[j] = word[i];
                j++;
            }
        }
        if (editLength < length) {
            word[editLength] = '\0';
            length = editLength;
            editLength = length;
        }
	}
	else {
        printf("That is not a valid string for camelCasing. You must have a first and second word separated by a series of non letters.\n");
        word[0] = '\0';
	}
	return;
}

int main()
{
    printf("Enter the string:\n");
    char* str = (char *) malloc(100 * sizeof(char));
    gets(str);
    int length = stringLength(str);
    printf("%d\n", length);

	camelCase(str);
	length = stringLength(str);
	for (int i = 0; i < length; i++) {
        printf("%c", str[i]);
	}
	return 0;
}


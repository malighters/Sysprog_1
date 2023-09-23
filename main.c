#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 31
#define MAX_FILE_LENGTH 1000

struct Word {
    char word[MAX_WORD_LENGTH];
    int length;
};

int compareByLength(const void *a, const void *b) {
    struct Word *wordA = (struct Word *)a;
    struct Word *wordB = (struct Word *)b;
    return wordA->length - wordB->length;
}

int main() {
    printf("Lab task: sort words by their length\n");
    printf("Chernenko Yevhenii, TTP-32\n");

    char filename[100];
    printf("Enter file name: \n");
    scanf("%s", filename);

    FILE *file = fopen("D:\\adsa.txt", "r");
    if (file == NULL) {
        printf("An error occurred opening the file.\nThe file may not exist or you do not have permission to read it.\n"
               "Check if the file name is correct and try again.\n"
               "Example file name: name.txt\n");
        return 1;
    }

    struct Word words[MAX_FILE_LENGTH];
    int wordCounter = 0;

    char wordBuffer[MAX_WORD_LENGTH];
    int wordBufferIndex = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (!isalpha(c)) {
            if (wordBufferIndex > 0) {
                wordBuffer[wordBufferIndex] = '\0';

                bool isDuplicate = false;
                for (int i = 0; i < wordCounter; i++) {
                    if (strcmp(words[i].word, wordBuffer) == 0) {
                        isDuplicate = true;
                        break;
                    }
                }
                if (!isDuplicate) {
                    strcpy(words[wordCounter].word, wordBuffer);
                    words[wordCounter].length = 0;
                    for (int i = 0; wordBuffer[i] != '\0'; i++) {
                        if (isalpha(wordBuffer[i])) {
                            words[wordCounter].length++;
                        }
                    }
                    wordCounter++;
                }
                wordBufferIndex = 0;
            }
        } else {
            if (wordBufferIndex < 30) {
                wordBuffer[wordBufferIndex++] = c;
            }
        }
    }

    qsort(words, wordCounter, sizeof(struct Word), compareByLength);

    printf("Words without repetitions, sorted by increasing number of length:\n");
    for (int i = 0; i < wordCounter; i++) {
        printf("%s (%d letters)\n", words[i].word, words[i].length);
    }

    fclose(file);
    return 0;
}

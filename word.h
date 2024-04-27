#ifndef WORD_H
#define WORD_H

typedef struct Word
{
    char* english;
    char* korean;

} Word;

Word* getWord(const char* filename, int* size);
void saveWord(Word* words, int* size);
void printWords(Word* words, int size);
void freeWords(Word* words, int size);

#endif
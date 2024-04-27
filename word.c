#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"

#define _CRT_SECURE_NO_WORNINGS

Word* getWord(const char* filename, int* size)
{
    // 파일 열기
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        printf("파일 열기 실패: %s\n", filename);

    // 단어 개수 세기
    *size = 0;
    char line[50];
    while (fgets(line, sizeof(line), file))
        (*size)++;
    rewind(file);

    // 동적 할당
    Word* words = malloc(sizeof(Word) * (*size));
    if (words == NULL)
    {
        printf("메모리 할당 실패\n");
        fclose(file);
        exit(1);
    }

    // 파일 내용 읽어서 배열에 저장
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        char* english = strtok(line, " ");
        char* korean = strtok(NULL, "\n");

        words[i].english = malloc(strlen(english) + 1);
        words[i].korean = malloc(strlen(korean) + 1);

        strcpy(words[i].english, english);
        strcpy(words[i].korean, korean);

        i++;
    }

    fclose(file);
    return words;
}

void saveWord(Word* words, int* size)
{
    // 파일 열기
    FILE* file = fopen("wrong_words.txt", "w");
    if (file == NULL)
        printf("파일 열기 실패\n");

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s, %s\n", words[i].english, words[i].korean);
    }

    fclose(file);
}

void printWords(Word* words, int size)
{
    for (int i = 0; i < size; i++)
        printf("%s: %s\n", words[i].english, words[i].korean);
}

void freeWords(Word* words, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(words[i].english);
        free(words[i].korean);
    }
    free(words);
}
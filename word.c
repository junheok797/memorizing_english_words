#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"

Word* getWord(const char* filename, int* size)
{
    // ���� ����
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        printf("���� ���� ����: %s\n", filename);

    // �ܾ� ���� ����
    *size = 0;
    char line[50];
    while (fgets(line, sizeof(line), file))
        (*size)++;
    rewind(file);

    // ���� �Ҵ�
    Word* words = malloc(sizeof(Word) * (*size));
    if (words == NULL)
    {
        printf("�޸� �Ҵ� ����\n");
        fclose(file);
        exit(1);
    }

    // ���� ���� �о �迭�� ����
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "word.h"

int isGameOver(int*** life)
{
    if (***life == 0)
    {
        printf("------------------------------------------------------\n\n");
        printf("Game over!!!\n");
        return 0;
    }
    else
    {
        printf("<현재 목숨은 %d개 입니다.>\n\n", ***life);
    }
    return 1;
}

void printWord(char* word, int* accord, int length)
{
    printf("단어: ");
    for (int i = 0; i < length; i++)
    {
        if (accord[i] == 1)
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n");
}

int check(char* wordE, int* accord, int*** life, int length, int stage)
{
    char* answer = malloc(length);

    printf("Enter a letter: ");
    scanf("%s", answer);

    if (stage == 1)
    {
        for (int i = 0; i < length; i++)
            if (wordE[i] == answer[0])
                accord[i] = 1;
        printf("\n");
        free(answer);
        return 1;
    }
    else if (stage == 2)
    {
        if (strcmp(wordE, answer) == 0)
        {
            printf("\n");
            printf("------------------------------------------------------\n\n");
            printf("correct!! ");
            return 0;
        }
        else
        {
            printf("\n");
            if (***life != 1) printf("Wrong! Try again!\n");
            ***life = ***life - 1;
            return 1;
        }
    }
}

void stage1(char* word, int* accord, int length, int** life)
{
    int stage = 1;
    int repetition = 1;
    int boolean = 1;

    printf("---------------------- stage 1 -----------------------\n");
    printf("stage 1은 알파벳을 이용해 단어를 유추하는 단계입니다.\n\n");

    while ((repetition <= 3) && (boolean == 1))
    {
        printWord(word, accord, length);
        printf("알파벳을 입력해주세요.\n");
        boolean = check(word, accord, &life, length, stage);
        repetition++;
    }
}

void stage2(char* wordE, char* wordK, int* save, int length, int** life)
{
    int stage = 2;
    int boolean = 1;

    printf("---------------------- stage 2 -----------------------\n");
    printf("stage 2는 뜻을 보고 단어를 맞추는 단계입니다.\n\n");

    while (isGameOver(&life) && (boolean == 1))
    {
        printWord(wordE, save, length);
        printf("뜻 : %s\n", wordK);
        printf("단어를 입력해주세요.\n");
        boolean = check(wordE, save, &life, length, stage);
    }
}

void game(Word* words, int size, int* life)
{
    srand(time(NULL));
    int i = rand() % size;

    printf("%d", *life);

    unsigned int lengthE = strlen(words[i].english);
    unsigned int lengthK = strlen(words[i].korean);

    char* wordE = malloc(lengthE + 1);
    char* wordK = malloc(lengthK + 1);

    strcpy(wordE, words[i].english);
    strcpy(wordK, words[i].korean);

    int* accord = (int*)malloc(sizeof(int) * lengthE);
    memset(accord, 0, sizeof(int) * lengthE);

    printf("Welcom to Hangman!\n\n");

    stage1(wordE, accord, lengthE, &life);
    stage2(wordE, wordK, accord, lengthE, &life);

    free(wordE);
    free(wordK);
    free(accord);
}

int main()
{
    int life = 5;
    int size;
    const char* filename = "words.txt";

    Word* words = getWord(filename, &size);
    if (words == NULL) return 1;

    game(words, size, &life);

    //printWords(words, size);

    freeWords(words, size);
}
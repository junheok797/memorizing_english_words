#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "word.h"

#define _CRT_SECURE_NO_WORNINGS

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
        printf("<���� ����� %d�� �Դϴ�.>\n\n", ***life);
    }
    return 1;
}

void printWord(char* word, int* accord, int length)
{
    printf("�ܾ�: ");
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
    char* answer = malloc(length + 1);

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
            free(answer);
            return 0;
        }
        else
        {
            printf("\n");
            if (***life != 1) printf("Wrong! Try again!\n");
            ***life = ***life - 1;
            free(answer);
            return 1;
        }
    }
}

void stage1(char* word, int* accord, int length, int** life)
{
    int stage = 1;
    int repetition = 1;
    int boolean = 1;
    char* answer = malloc(length);

    printf("---------------------- stage 1 -----------------------\n");
    printf("stage 1�� ���ĺ��� �̿��� �ܾ �����ϴ� �ܰ��Դϴ�.\n\n");

    while ((repetition <= 4) && (boolean == 1))
    {
        printWord(word, accord, length);
        printf("���ĺ��� �Է����ּ���.\n");

        boolean = check(word, accord, &life, length, stage);
        repetition++;
    }
}

void stage2(char* wordE, char* wordK, int* save, int length, int** life)
{
    int stage = 2;
    int boolean = 1;

    printf("---------------------- stage 2 -----------------------\n");
    printf("stage 2�� ���� ���� �ܾ ���ߴ� �ܰ��Դϴ�.\n\n");

    while (isGameOver(&life) && (boolean == 1))
    {
        printWord(wordE, save, length);
        printf("�� : %s\n", wordK);
        printf("�ܾ �Է����ּ���.\n");
        boolean = check(wordE, save, &life, length, stage);
    }
}

void game(Word* words, int size, Word* wrong_words, int* num_wrong_words, int* life)
{
    srand(time(NULL));
    int i = rand() % size;
    int tmp_life = *life;

    unsigned int lengthE = strlen(words[i].english);
    unsigned int lengthK = strlen(words[i].korean);

    char* wordE = malloc(lengthE + 1);
    char* wordK = malloc(lengthK + 1);

    strcpy(wordE, words[i].english);
    strcpy(wordK, words[i].korean);

    int* accord = (int*)malloc(sizeof(int) * lengthE);
    memset(accord, 0, sizeof(int) * lengthE);

    stage1(wordE, accord, lengthE, &life);
    stage2(wordE, wordK, accord, lengthE, &life);

    if (tmp_life != *life)
    {
        strcpy(wrong_words[*num_wrong_words].english, wordE);
        strcpy(wrong_words[*num_wrong_words].korean, wordK);
        (*num_wrong_words)++;
    }

    free(wordE);
    free(wordK);
    free(accord);
}

int main()
{
    int life = 5;
    int size = 0;
    int count = 0;
    int num_wrong_words = 0;
    const char* filename = "words.txt";
    
    Word* words = getWord(filename, &size);
    if (words == NULL) return 1;

    Word* wrong_words = malloc(sizeof(Word) * size);

    printf("Welcom to Hangman!\n\n");

    while (life != 0 && count != size)
    {
        game(words, size, wrong_words, &num_wrong_words, &life);
        count++;

        if (life != 0)
        {
            int intention = 0;

            do
            {
                printf("�� �����Ͻðڽ��ϳ�? (1: ��, 2: �ƴϿ�) ");
                scanf("%d", &intention);

                if (intention == 1)
                {
                    printf("\n\n");
                    printf("=================== ���� �ܾ� �Դϴ� ===================\n\n");
                }
                else if (intention == 2)
                {
                    break;
                }
                else
                {
                    printf("�ɼǿ� �´� ���ڸ� �Է����ּ���!\n");
                    intention = 0;
                }
            } while (intention = 0);

            if (intention == 2) break;
        }
    }

    printf("================== ���α׷��� �����մϴ� ==================");
    saveWord(wrong_words, num_wrong_words);

    freeWords(wrong_words, size);
    freeWords(words, size);
}
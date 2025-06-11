#ifndef QUESTION_H
#define QUESTION_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LEN_TEXT 250

typedef struct {
    char question[300];       
    char answers[4][MAX_LEN_TEXT];    
    int correctAnswer;       
    int difficulty;          
} question;


void loadQuestions(question *questions, int count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Грешка при четене.");
        return;
    }

    fread(&count, sizeof(int), 1, file);
    fread(questions, sizeof(question), count, file);

    fclose(file);
}

void saveQuestions(question *questions, int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Грешка при запис.");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(questions, sizeof(question), count, file);

    fclose(file);
}

void addQuestionInteractive(question *questions, int count) {
    if (count >= 200) {
        printf("Достигнат е максимален брой въпроси.\n");
        return;
    }

    question *q = &questions[count];

    printf("Ваведете текст на въпроса:\n");
    fgets(q->question, MAX_LEN_TEXT, stdin);
    q->question[strcspn(q->question, "\n")] = 0;

    for (int i = 0; i < 4; i++) {
        printf("Отговор %d: ", i + 1);
        fgets(q->answers[i], MAX_LEN_TEXT, stdin);
        q->answers[i][strcspn(q->answers[i], "\n")] = 0;
    }

    printf("Номер на правилен отговор (1-4): ");
    scanf("%d", &q->correctAnswer);
    getchar();

    printf("Ниво на трудност (1-10): ");
    scanf("%d", &q->difficulty);
    getchar();

    count++;
    printf("Въпросът е добавен!\n");
}

void editQuestionInteractive(question *questions, int count) {
    if (count == 0) {
        printf("Няма въпроси.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, questions[i].question);
    }

    int index;
    printf("Избери номер на въпрос за редакция: ");
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > count) {
        printf("Невалиден номер.\n");
        return;
    }

    question *q = &questions[index - 1];

    printf("Нов въпрос:\n");
    char buffer[MAX_LEN_TEXT];
    fgets(buffer, MAX_LEN_TEXT, stdin);
    if (strcmp(buffer, "\n") != 0) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(q->question, buffer, MAX_LEN_TEXT);
    }

    for (int i = 0; i < 4; i++) {
        printf("Нов отговор %d: ", i + 1);
        fgets(buffer, MAX_LEN_TEXT, stdin);
        if (strcmp(buffer, "\n") != 0) {
            buffer[strcspn(buffer, "\n")] = 0;
            strncpy(q->answers[i], buffer, MAX_LEN_TEXT);
        }
    }

    printf("Нов номер на верния отговор (1-4): ");
    int correct;
    scanf("%d", &correct);
    getchar();
    if (correct >= 1 && correct <= 4)
        q->correctAnswer = correct;

    printf("Нова трудност (1-10): ");
    int diff;
    scanf("%d", &diff);
    getchar();
    if (diff >= 1 && diff <= 10)
        q->difficulty = diff;

    printf("Въпросът е редактиран!\n");
}
#endif
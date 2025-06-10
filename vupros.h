#ifndef QUESTION_H
#define QUESTION_H

#define MAX_LEN_TEXT 250

typedef struct {
    char question[300];       
    char answers[4][MAX_LEN_TEXT];    
    int correctAnswer;       
    int difficulty;          
} question;

void addQuestion(question *questions, int *questionCount);
void editQuestion(question *questions, int questionCount);
void saveQuestionsToFile(question *questions, int questionCount, const char *filename);
int loadQuestionsFromFile(question *questions, const char *filename);

#endif
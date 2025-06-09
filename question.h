#ifndef QUESTION_H
#define QUESTION_H

typedef struct {
    char question[200];       
    char answers[4][128];    
    int correctAnswer;       
    int difficulty;          
} question;

void addQuestion(question *questions, int *questionCount);
void editQuestion(question *questions, int questionCount);
void saveQuestionsToFile(question *questions, int questionCount, const char *filename);
int loadQuestionsFromFile(question *questions, const char *filename);

#endif
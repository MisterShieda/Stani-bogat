#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "vuprosi.h"
#include "crypt.h"

#define MAX_JOKERS 3

question questions[MAX_LEN_TEXT];

int used_5050 = 0, used_friend = 0, used_audience = 0;

void use_5050(question *q, int *mask) {
    int removed = 0;
    while (removed < 2) {
        int idx = rand() % 4;
        if (idx != q->correctAnswer && mask[idx]) {
            mask[idx] = 0;
            removed++;
        }
    }
}

int use_friend(question *q, int *mask) {
    int prob[] = {80, 60, 30};
    int difficulty = q->difficulty;
    int chance = difficulty <= 3 ? prob[0] : difficulty <= 6 ? prob[1] : prob[2];
    int r = rand() % 100;
    if (r < chance) return q->correctAnswer;
    while (1) {
        int i = rand() % 4;
        if (i != q->correctAnswer && mask[i]) return i;
    }
}

void use_audience(question *q, int *mask, int *votes) {
    int prob[] = {80, 60, 30};
    int difficulty = q->difficulty;
    int chance = difficulty <= 3 ? prob[0] : difficulty <= 6 ? prob[1] : prob[2];

    int remaining[4], count = 0;
    for (int i = 0; i < 4; i++) {
        if (mask[i]) remaining[count++] = i;
    }

    int correct_votes = rand() % (chance - 10) + 10 + (100 - chance);
    int others = 100 - correct_votes;
    int shuffle_votes[count];

    shuffle_votes[0] = correct_votes;
    for (int i = 1; i < count; i++) shuffle_votes[i] = rand() % (others / (count - 1));

    int sum = 0;
    for (int i = 1; i < count; i++) sum += shuffle_votes[i];
    shuffle_votes[0] += (others - sum);

    for (int i = 0; i < count; i++) votes[remaining[i]] = shuffle_votes[i];
}

void play_game(){
    srand(time(NULL));
    int score = 0, current_question = 0;
    int mask[4] = {1, 1, 1, 1};
    int votes[4] = {0, 0, 0, 0};

    while (current_question < 10) {
        question *q = &questions[current_question];
        printf("\nВъпрос %d: %s\n", current_question + 1, q->question);
        for (int i = 0; i < 4; i++) {
            if (mask[i]) printf("%d. %s\n", i + 1, q->answers[i]);
        }

        printf("Изберете отговор (1-4) или използвайте жокер:\n");
        printf("1. Отговор\n2. 50/50\n3. Помощ от приятел\n4. Гласуване на публиката\n5. Изход\n");

        int choice;
        scanf("%d", &choice); getchar();
            if (choice < 1 || choice > 5) {
            printf("Невалиден избор! Моля, изберете отново.\n");
            continue;
        }
        if (choice == 1) {
            printf("Моля, изберете отговор (1-4): ");
            continue;
        }

        if (choice == 5) break;
        if (choice < 1 || choice > 5) {
            printf("Невалиден избор! Моля, изберете отново.\n");
            continue;
        }

        if (choice == 2 && !used_5050) {
            use_5050(q, mask);
            used_5050 = 1;
            continue;
        } else if (choice == 3 && !used_friend) {
            int answer = use_friend(q, mask);
            printf("Помощ от приятел: Отговор %d\n", answer + 1);
            used_friend = 1;
            continue;
        } else if (choice == 4 && !used_audience) {
            use_audience(q, mask, votes);
            printf("Гласуване на публиката:\n");
            for (int i = 0; i < 4; i++) {
                if (mask[i]) printf("%d. %d%%\n", i + 1, votes[i]);
            }
            used_audience = 1;
            continue;
        }

        int answer;
        scanf("%d", &answer); getchar();
        answer--; 

        if (answer < 0 || answer > 3 || !mask[answer]) {
            printf("Невалиден отговор!\n");
            continue;
        }

        if (answer == q->correctAnswer) {
            printf("Правилен отговор!\n");
            score += q->difficulty;
        } else {
            printf("Грешен отговор! Правилният беше: %d. %s\n", q->correctAnswer + 1, q->answers[q->correctAnswer]);
            break;

        }
        current_question++;
        if (current_question % 5 == 0) {
            printf("Поздравления! Вашият текущ резултат е: %d\n", score);
            printf("Искате ли да продължите? (1 - Да, 0 - Не): ");
            int cont;
            scanf("%d", &cont); getchar();
            if (!cont) break;
        }   

        if (current_question == 10) {
            printf("Поздравления! Завършихте играта с резултат: %d\n", score);
            printf("Искате ли да започнете отначало? (1 - Да, 0 - Не): ");
            int cont;
            scanf("%d", &cont); getchar();
            if (!cont) break;
            current_question = 0;
            score = 0;
            used_5050 = 0;
            used_friend = 0;
            used_audience = 0;
            memset(mask, 1, sizeof(mask));
            memset(votes, 0, sizeof(votes));
        }

    
} }



int main() {
    const char* input = "vuprosi.txt";
    const char* encrypted = "vuprosi.enc";
    const char* decrypted = "decrypted.txt";

    int count = 3;
    loadQuestions(questions , count, input );
    

    int choice;
    do {
        printf("\n--- Menu ---\n");
        printf("1. New game\n2. Добави въпрос\n3. Редактирай въпрос\n4. Изход\n");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1: play_game(); break;
            case 2: addQuestionInteractive(questions, count); break;
            case 3: editQuestionInteractive(questions, count); break;
            case 4:
                saveQuestions(questions, count, input);
                remove(input);
                printf("Изход...\n");
                break;
        }
    } while (choice != 4);

    return 0;
}

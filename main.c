#include <stdio.h>
#include "crypt.h"

int main() {
    printf("\n Декриптиране на въпросите...");
    decrypt("vuprosi.txt");

    printf("\n Съдържание:");
    FILE* f = fopen("vuprosi.txt", "r");
    if (f) {
        char line[256];
        while (fgets(line, sizeof(line), f))
            printf("%s", line);
        fclose(f);
    }

    printf("\n Криптиране на файла...");
    encrypt("vuprosi.txt");

    

    printf("\n Готово.");
    return 0;
}
#include <stdio.h>
#include "crypt.h"

int main() {
    const char* input = "vuprosi.txt";
    const char* encrypted = "vuprosi.enc";
    const char* decrypted = "decrypted.txt";

    // Криптиране
    if (encrypt_file(input, encrypted) == 0) {
        printf("Файлът успешно е криптиран: %s\n", encrypted);
    } else {
        printf("Грешка при криптиране.\n");
        return 1;
    }

    // Декриптиране
    if (decrypt_file(encrypted, decrypted) == 0) {
        printf("Файлът успешно е декриптиран: %s\n", decrypted);
    } else {
        printf("Грешка при декриптиране.\n");
        return 1;
    }

    return 0;
}
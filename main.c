#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int file_exists(const char *filepath) {
    struct stat buffer;
    return (stat(filepath, &buffer) == 0);
}

int main(void) {
    const char *filepath = "C:/rarassword/data.rar";

    if (!file_exists(filepath)) {
        printf("The system cannot find the specified path: %s\n", filepath);
        return 1;
    }

    const char *start[] = {
            "a", "A", ""
    };

    const char *other[] = {
            ".", "@", "%", ".@", "@.", ""
    };

    const char *other2[] = {
            "1", "2", ""
    };

    const char *end[] = {
            "", "", ".", "@", "%", ".@", "@."
    };

    size_t numStart = sizeof(start) / sizeof(start[0]);
    size_t numOther = sizeof(other) / sizeof(other[0]);
    size_t numOther2 = sizeof(other2) / sizeof(other2[0]);
    size_t numEnd = sizeof(end) / sizeof(end[0]);

    int password_correct = 0;

    for (size_t i = 0; i < numStart && !password_correct; i++) {
        for (size_t j = 0; j < numOther && !password_correct; j++) {
            for (size_t k = 0; k < numOther2 && !password_correct; k++) {
                for (size_t l = 0; l < numEnd && !password_correct; l++) {
                    char pass[100];
                    snprintf(pass, sizeof(pass), "%s%s%s%s", start[i], other[j], other2[k], end[l]);

                    char command[500];
                    snprintf(command, sizeof(command), "unrar t -p\"%s\" \"%s\" 2>nul 1>nul", pass, filepath);

                    int return_var = system(command);

                    if (return_var == 0) {
                        printf("\033[32mPassword is correct: %s\033[0m\n", pass);
                        password_correct = 1;
                        break;
                    } else {
                        printf("\033[31mIncorrect password: %s\033[0m\n", pass);
                    }
                }
            }
        }
    }

    if (!password_correct) {
        printf("No valid password found for the file\n");
    }

    return 0;
}

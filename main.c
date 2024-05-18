#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int file_exists(const char *filepath) {
    struct stat buffer;
    return (stat(filepath, &buffer) == 0);
}

int main(void) {
    const char *filepath = "C:/Dev/www/rarassword/data.rar";

    if (!file_exists(filepath)) {
        printf("The system cannot find the specified path: %s\n", filepath);
        return 1;
    }

    const char *start[] = {
            "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve", "diez",
    };

    const char *other[] = {
            ".", "@", "%"
    };

    const char *other2[] = {
            "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
    };

    const char *end[] = {
            ".", "@", "%"
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

                    printf("Testing password: %s\n", pass);

                    char command[500];
                    snprintf(command, sizeof(command), "unrar t -p\"%s\" \"%s\"", pass, filepath);

                    printf("Executing command: %s\n", command);

                    int return_var = system(command);

                    if (return_var == 0) {
                        printf("Password is correct: %s\n", pass);
                        password_correct = 1;
                        break;
                    } else {
                        printf("Command returned error code: %d\n", return_var);
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

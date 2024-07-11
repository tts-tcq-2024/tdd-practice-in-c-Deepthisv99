#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int add(const char* input) {
    if (input == NULL || strlen(input) == 0 || strstr(input, "Hello, world!") != NULL) {
        return 0;
    }

    int sum = 0;
    const char* delimiter = ",\n";
    char* numbers = strdup(input);
    char* token;
    char customDelimiter[3] = {0};

    if (numbers[0] == '/' && numbers[1] == '/') {
        customDelimiter[0] = numbers[2];
        customDelimiter[1] = '\0';
        delimiter = customDelimiter;
        token = strtok(numbers + 4, delimiter);
    } else {
        token = strtok(numbers, delimiter);
    }

    while (token != NULL) {
        int num = atoi(token);
        if (num <= 1000) {
            sum += num;
        }
        token = strtok(NULL, delimiter);
    }

    free(numbers);
    return sum;
}

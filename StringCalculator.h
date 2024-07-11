#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Custom exception handling for negative numbers
void throw_negatives_exception(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

int add(const char* input) {
    if (input == NULL || strlen(input) == 0) {
        return 0;
    }

    int sum = 0;
    const char* delimiters = ",\n";
    char* numbers = strdup(input);
    char* token;
    char* negatives = (char*) malloc(sizeof(char) * strlen(input) * 2);
    negatives[0] = '\0';

    // Handling custom delimiters
    if (numbers[0] == '/' && numbers[1] == '/') {
        char* delimiter_end = strstr(numbers, "\n");
        if (delimiter_end) {
            size_t delimiter_length = delimiter_end - numbers - 2;
            char* custom_delimiter = (char*) malloc(delimiter_length + 1);
            strncpy(custom_delimiter, numbers + 2, delimiter_length);
            custom_delimiter[delimiter_length] = '\0';
            delimiters = custom_delimiter;
            token = strtok(numbers + 2 + delimiter_length + 1, delimiters);
        } else {
            token = strtok(numbers, delimiters);
        }
    } else {
        token = strtok(numbers, delimiters);
    }

    while (token != NULL) {
        int num = atoi(token);
        if (num < 0) {
            strcat(negatives, token);
            strcat(negatives, " ");
        } else if (num <= 1000) {
            sum += num;
        }
        token = strtok(NULL, delimiters);
    }

    if (strlen(negatives) > 0) {
        char error_message[256];
        sprintf(error_message, "negatives not allowed: %s", negatives);
        free(numbers);
        free(negatives);
        throw_negatives_exception(error_message);
    }

    free(numbers);
    free(negatives);
    return sum;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_SIZE 30
#define BIG_WORD_SIZE 1024
#define GRAM_SIZE 5000

struct n_gram_freq {
    char word1[WORD_SIZE];
    char word2[WORD_SIZE];
    int freq;
};

struct words_freq {
    char word[WORD_SIZE];
    int freq;
};

void read_n_grams(struct n_gram_freq *grams, int *n, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Error opening n-gram file");
        exit(1);
    }

    if (fscanf(f, "%d", n) != 1) *n = 0;

    if (*n > GRAM_SIZE) *n = GRAM_SIZE;

    for (int i = 0; i < *n; i++) {
        fscanf(f, "%29s %29s %d", grams[i].word1, grams[i].word2, &grams[i].freq);
    }
    fclose(f);
}


void read_words(struct words_freq *words, int *n, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Error opening words file");
        exit(1);
    }

    if (fscanf(f, "%d", n) != 1) *n = 0;

    if (*n > GRAM_SIZE) *n = GRAM_SIZE;

    for (int i = 0; i < *n; i++) {
        fscanf(f, "%29s %d", words[i].word, &words[i].freq);
    }
    fclose(f);
}


int get_word_freq(struct words_freq *words, int nr_words, const char *target) {
    for (int i = 0; i < nr_words; i++) {
        if (strcmp(words[i].word, target) == 0) {
            return words[i].freq;
        }
    }
    return 0; 
}


void get_best_word(struct n_gram_freq *grams, struct words_freq *words, 
                   int nr_grams, int nr_words, 
                   const char *current_word, char *result_buffer) {
    
    double max_ratio = -1.0;
    int found_candidate = 0;

    for (int i = 0; i < nr_grams; i++) {
        if (strcmp(grams[i].word1, current_word) == 0) {
            
            char *candidate_next = grams[i].word2;
            double a = (double)grams[i].freq;
            double b = (double)get_word_freq(words, nr_words, candidate_next);

            double ratio = 0.0;
            if (b > 0) {
                ratio = a / b;
            }

            if (ratio > max_ratio) {
                max_ratio = ratio;
                strcpy(result_buffer, candidate_next);
                found_candidate = 1;
            }
        }
    }
    if (!found_candidate) {
        result_buffer[0] = '\0';
    }
}


void extract_last_word(const char *sentence, char *buffer) {
    if (sentence == NULL || strlen(sentence) == 0) {
        buffer[0] = '\0';
        return;
    }
    
    
    char temp[BIG_WORD_SIZE];
    snprintf(temp, BIG_WORD_SIZE, "%s", sentence);

    char *token = strtok(temp, " ");
    char *last = token;

    while (token != NULL) {
        last = token;
        token = strtok(NULL, " ");
    }

    if (last) {
        strcpy(buffer, last);
    } else {
        buffer[0] = '\0';
    }
}

int main(int argc, char **argv) {
    
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <bigrams_file> <words_file> <start_sentence> <num_predictions>\n", argv[0]);
        return 1;
    }

    int nr_grams = 0, nr_words = 0;

    
    struct n_gram_freq *grams = calloc(GRAM_SIZE, sizeof(struct n_gram_freq));
    struct words_freq *words = calloc(GRAM_SIZE, sizeof(struct words_freq));
    
    if (!grams || !words) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    
    read_n_grams(grams, &nr_grams, argv[1]);
    read_words(words, &nr_words, argv[2]);

    int nr_predicted_words = atoi(argv[4]);
    if (nr_predicted_words <= 0) {
         printf("%s\n", argv[3]);
         free(grams);
         free(words);
         return 0;
    }

    char sentence[BIG_WORD_SIZE];
    snprintf(sentence, BIG_WORD_SIZE, "%s", argv[3]);
    char last_word[WORD_SIZE];
    extract_last_word(argv[3], last_word);
    char next_word[WORD_SIZE];
    for (int i = 0; i < nr_predicted_words; i++) {
        next_word[0] = '\0';
        get_best_word(grams, words, nr_grams, nr_words, last_word, next_word);
        if (next_word[0] == '\0') {
            break; 
        }
        strncat(sentence, " ", BIG_WORD_SIZE - strlen(sentence) - 1);
        strncat(sentence, next_word, BIG_WORD_SIZE - strlen(sentence) - 1);
        strcpy(last_word, next_word);
    }
    printf("%s\n", sentence);
    free(grams);
    free(words);
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BRIGHT_PATH "/sys/class/backlight/intel_backlight"
#define BRIGHT_FILE BRIGHT_PATH "/brightness"
#define MAX_BRIGHT_FILE BRIGHT_PATH "/max_brightness"
#define FORMAT "Current brightness: %d%%\n"

void delta(int max, int value, int delta) {
    FILE *bf = fopen(BRIGHT_FILE, "w");
    if (bf == NULL) {
        fprintf(stderr, "Can't open \"%s\".\n", BRIGHT_FILE);
        exit(1);
    }
    if (value + delta > max) {
        fprintf(bf, "%d", max);
    } else if (value + delta < 0) {
        fprintf(bf, "0");
    } else {
        fprintf(bf, "%d", value + delta);
    }
    fclose(bf);
}
void set(int value, int max) {
    FILE *bf = fopen(BRIGHT_FILE, "w");
    if (bf == NULL) {
        fprintf(stderr, "Can't open \"%s\".\n", BRIGHT_FILE);
        exit(1);
    }
    if (value > 0 && value <= max) {
        fprintf(bf, "%d", value);
    }
    fclose(bf);
}

int main(int argc, char *argv[]) {
    int opt, current, max, step, query = 0;
    FILE *bf = fopen(BRIGHT_FILE, "r");
    FILE *mbf = fopen(MAX_BRIGHT_FILE, "r");
    if (bf == NULL) {
        fprintf(stderr, "Can't open \"%s\".\n", BRIGHT_FILE);
        return 1;
    }
    if (mbf == NULL) {
        fprintf(stderr, "Can't open \"%s\".\n", MAX_BRIGHT_FILE);
        return 1;
    }
    fscanf(bf, "%d", &current);
    fscanf(mbf, "%d", &max);
    step = max / 20;
    fclose(bf);
    fclose(mbf);
    
    while ((opt = getopt(argc, argv, "idqmM")) != -1) {
        switch (opt) {
            case 'i': delta(max, current, step); break;
            case 'd': delta(max, current, -step); break;
            case 'q': query = 1; break;
            case 'm': set(step, max); break;
            case 'M': set(max, max); break;
            default: fprintf(stderr, "Usage %s [-idq]\n", argv[0]);
        }
    }
    if (query > 0) {
        printf(FORMAT, 100 * current / max);
    }
}

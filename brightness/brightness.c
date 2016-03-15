#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BRIGHT_PATH "/sys/class/backlight/intel_backlight"
#define BRIGHT_FILE BRIGHT_PATH "/brightness"
#define MAX_BRIGHT_FILE BRIGHT_PATH "/max_brightness"
#define FORMAT "Current brightness: %d%%\n"

void change(int max, int value, int change) {
    FILE *bf = fopen(BRIGHT_FILE, "w");
    if (bf == NULL) {
        fprintf(stderr, "Can't open \"%s\".\n", BRIGHT_FILE);
        exit(1);
    }
    if (value + change > max) {
        fprintf(bf, "%d", max);
    } else if (value + change < 0) {
        fprintf(bf, "0");
    } else {
        fprintf(bf, "%d", value + change);
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
    if (bf == NULL) {
        fprintf(stderr, "Can't open \"%s\".\n", MAX_BRIGHT_FILE);
        return 1;
    }
    fscanf(bf, "%d", &current);
    fscanf(mbf, "%d", &max);
    step = max / 20;
    fclose(bf);
    fclose(mbf);
    
    while ((opt = getopt(argc, argv, "idq")) != -1) {
        switch (opt) {
            case 'i': change(max, current, step); break;
            case 'd': change(max, current, -step); break;
            case 'q': query = 1; break;
            default: fprintf(stderr, "Usage %s [-idq]\n", argv[0]);
        }
    }
    if (query > 0) {
        printf(FORMAT, 100 * current / max);
    }
}

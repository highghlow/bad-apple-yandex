#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include "data.h"

char *cs[] = {"red", "green", "blue"};

unsigned long long milliseconds_since(struct timespec start) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    return (unsigned long long)(now.tv_sec - start.tv_sec) * 1000
         + (now.tv_nsec - start.tv_nsec) / 1000000;
}

int main(int argc, char *argv[]) {
        if (argc == 1) {
                printf("bapple <audio>\n");
                exit(1);
        }

        if (!fork()) {
                char *args[] = {"aplay", argv[1], "-r", "44100", "-f", "S16_LE", "-c", "2", NULL};
                execvp("aplay", args);
                exit(1);
        }

        size_t pos = 0;
        unsigned char a, b, c;
        FILE *f;
        char filename[45];
        char data[10];
        size_t last = 0;

        struct timespec start;
        clock_gettime(CLOCK_MONOTONIC, &start);
#define OFFSET 0
        while (1) {
                pos = milliseconds_since(start) / 100;
                if (last != pos) {
                        printf("%d\n", pos);
                        fflush(stdout);
                        last = pos;
                }
                pos += OFFSET;
                if (pos >= frames_len) {
                        break;
                }

                for (int c = 0; c < 3; c++) {
                        for (int r = 0; r < 3; r++) {
                                sprintf(filename, "/sys/class/leds/micro:%s:ring%d/brightness", cs[c], r+1);
                                f = fopen(filename, "wb");
                                sprintf(data, "%d\n", frames[pos][r]);
                                fwrite(data, strlen(data), 1, f);
                                fclose(f);
                        }
                }
                usleep(10);
        }

        wait(NULL);
}

#include "cachelab.h"
#include "stdio.h"
#include "stdlib.h"

int s, E, b, verbose = 0;
int hits = 0, misses = 0, evictions = 0;
char * t;
typedef struct{
    int valid;
    int tag;
    int block_offset;
} line;
typedef struct{
    line* lines;
} set;

//
int parseArgs(int argc, char * argv[])
{
    printf("argc:%d\n", argc);
    int i = 1;
    while (i < argc) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'h':
                    printf("help\n");
                    return 0;
                case 'v':
                    verbose = 1;
                    printf("verbose=%d\t", verbose);
                    break;
                case 's':
                    i++;
                    s = atoi(argv[i]);
                    printf("s=%d\t", s);
                    break;
                case 'E':
                    i++;
                    E = atoi(argv[i]);
                    printf("E=%d\t", E);
                    break;
                case 'b':
                    i++;
                    b = atoi(argv[i]);
                    printf("b=%d\t", b);
                    break;
                case 't':
                    i++;
                    t = argv[i];
                    printf("t=%s", t);
                    break;
                default:
                    printf("\nargs are error");
                    return 0;
            }
            i++;
        }
    }
    printf("\n");
    return 0;
}

//
int parseTrace() {
    FILE *file = fopen(t, "r");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // read one line
        if (line[0] != ' ') continue;
        char oprand = line[1];
        if (oprand == 'L') {

        } else if (oprand == 'S') {

        } else if (oprand == 'M') {

        }
        // printf("%s", line);
    }
    fclose(file);
    return 0;
}

int getTag(int address) {
    return address >> (b + s);
}
int getSet(int address) {
    return (address >> b) & ~(~0 << s);
}
int getOffset(int address) {
    return address & (~(~0 << b));
}

int main(int argc, char* argv[]) {
    parseArgs(argc, argv);
    parseTrace();
    printSummary(0, 0, 0);
}

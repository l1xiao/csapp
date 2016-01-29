#include "cachelab.h"
#include "stdio.h"
#include "stdlib.h"
int parseArgs(int argc, char* argv[]);
void init();
int parseTrace(char* line);
void find(void* addr, int size);
long getTag(void* address);
int getSet(void* address);
int count = 0;
long long int address = 0;
int s, E, b, verbose = 0;
int hits = 0, misses = 0, evictions = 0;
char * t;
int timestamp;
typedef struct {
    int* valid;
    int* tag;
    int* timestamp;
} cache;
cache* sets;

int parseArgs(int argc, char * argv[]) {
    int i = 1;
    while (i < argc) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'h':
                    return 0;
                case 'v':
                    verbose = 1;
                    break;
                case 's':
                    i++;
                    s = atoi(argv[i]);
                    break;
                case 'E':
                    i++;
                    E = atoi(argv[i]);
                    break;
                case 'b':
                    i++;
                    b = atoi(argv[i]);
                    break;
                case 't':
                    i++;
                    t = argv[i];
                    break;
                default:
                    return 0;
            }
            i++;
        }
    }
    return 0;
}
void init() {
    int S = 1 << s;
    sets = (cache*)malloc(sizeof(cache) * S);
    for (int i = 0; i < S; i++) {
        sets[i].valid = (int*)malloc(sizeof(int) * E);
        sets[i].tag = (int*)malloc(sizeof(int) * E);
        sets[i].timestamp = (int*)malloc(sizeof(int) * E);
        for (int j = 0; j < E; j++) {
            sets[i].valid[j] = 0;
            sets[i].tag[j] = 0;
            sets[i].timestamp[j] = 0;
        }
    }
}
int parseTrace(char* line) {
    // read one line
    char oprand;
    void* addr;
    int size;
    sscanf(line, " %c %p,%d", &oprand, &addr, &size);
    if (verbose) {
        printf("%d:%c %llx,%d ", count, oprand, (long long int)addr, size);
    }
    find(addr, size);
    if (oprand == 'M') {
        find(addr, size);
    }
    if (verbose) printf("\n");
    return 0;
}
void find(void* addr, int size) {
    int index = getSet(addr);
    address = (long long int) addr;
    int tag = getTag(addr);
    int evict = 100000000, tag_index = 0;
    int flag = 0;
    int empty = -1;
    for (int i = 0; i < E; i++) {
        if (sets[index].tag[i] == tag && sets[index].valid[i] == 1) {
            flag = 1;
            tag_index = i;
            break;
        }
        empty = sets[index].valid[i] == 1 ? empty : i;
        if (evict > sets[index].timestamp[i]) {
            evict = sets[index].timestamp[i];
            tag_index = i;
        }
    }

    if (flag == 1) {
        hits++;
        // put the block
        if (verbose) printf("hit ");
        sets[index].timestamp[tag_index] = timestamp;
    } else {
        misses++;
        if (verbose) printf("miss ");
        // eviction
        if (empty == -1) {
            // put in oldest block
            if (verbose) printf("eviction ");
            sets[index].tag[tag_index] = tag;
            sets[index].timestamp[tag_index] = timestamp;
            sets[index].valid[empty] = 1;
            evictions++;
        } else {
            // put in a empty block
            sets[index].tag[empty] = tag;
            sets[index].timestamp[empty] = timestamp;
            sets[index].valid[empty] = 1;
        }
    }
    timestamp++;
}
int getTag(void* address) {
    return (int)((long)address >> (b + s));
}
int getSet(void* address) {
    return (int)(((long)address >> b) & ~(~0 << s));
}
int main(int argc, char* argv[]) {
    parseArgs(argc, argv);
    init();
    FILE *file = fopen(t, "r");
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        count++;
        if (line[0] != ' ') continue;
        parseTrace(line);
    }
    fclose(file);
    printSummary(hits, misses, evictions);
}

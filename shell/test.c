#include "stdio.h"
int a= 1;
struct job_t {
    int b;
    char c;
};
struct job_t jobs[10];
int main() {
    while(1) {
        sleep(3);
        printf("\n...\n");
    }
}

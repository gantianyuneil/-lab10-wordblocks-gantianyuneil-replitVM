#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wordblocks.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    void *output;
    int outputlen;
    size_t len = sizeof(short);

    if (argc == 1) {
        fprintf(stderr, "usage: %s <words>\n", argv[0]);
        return -1;
    }

    if ((fp = fopen("words.out", "w")) == NULL) {
        perror("Could not open words.out");
        return -1;
    }

    /* Allocate exactly enough output */
    for (int i = 1; i < argc; i++) {
        len += sizeof(short) + strlen(argv[i]);
    }

    output = malloc(len);

    outputlen = wordblocks(argv + 1, output);
    fwrite(output, outputlen, 1, fp);

    fclose(fp);

    return 0;
}

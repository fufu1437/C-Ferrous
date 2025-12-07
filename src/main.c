#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "file.h"

int main(int argc, char** argv) {
    argc--; argv++;
    char *out = '\0'; char *file; char *o_p, *p;
    FILE *f; ARG arg;
    long long fileSize;
    // if((arg = malloc(sizeof(ARG)))==NULL) { printf("could not malloc arg\n"); return -1; }
    if(argc==0) { printf("enter args\n"); return -1; }
    for(int i=0;i<argc;i++) {
        get_args(argv++, &arg);
        switch (arg.t){
            case ARGS_OUTFILE:   out  = arg.v;argv++; i++; break;
            case ARGS_READ_FILE: file = arg.v; break;
        }
    }
    if((f = fopen( file, "r")) == NULL) { printf("cloud not open(%s)\n", file); return -1; }
    fileSize = getFileSize(file);
    // if(fileSize < 100) fileSize+=;
    if(fileSize == 0) { printf("(%s)size of %lld\n",file, fileSize); return -1; }
    if((o_p = malloc((fileSize <100) ? fileSize : ( (10 - (fileSize%10)) / 10) ) )==NULL) { printf("could not malloc p\n"); return -1; }
    p = o_p;

    fclose(f);
    free(o_p);
    return 0;
}

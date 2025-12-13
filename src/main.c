#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "file.h"
#include "lexer.h"

int main(int argc, char** argv) {
    argc--; argv++;
    char *out = '\0'; char *file; char *o_p, *p;
    FILE *f; ARG arg;

    size_t buffer = 300;

    long long fileSize;
    if(argc==0) { printf("enter args\n"); return -1; }
    for(int i=0;i<argc;i++) {
        get_args(argv++, &arg);
        switch (arg.type){
            case ARGS_OUTFILE:   out  = arg.value;argv++; i++; break;
            case ARGS_READ_FILE: file = arg.value; break;
        }
    }
    if((f = fopen( file, "r")) == NULL) { printf("cloud not open(%s)\n", file); return -1; }
    fileSize = getFileSize(file);
    if(fileSize == 0) { printf("(%s)size of %lld\n",file, fileSize); return -1; }
    // if((o_p = malloc((fileSize <100) ? fileSize : ( (10 - (fileSize%10)) / 10) ) )==NULL) { printf("could not malloc p\n"); return -1; }
    TOKEN tk;
    TOKEN* ptk = &tk;
    // tk.column = 0;

    // tk.cv = malloc(401);
    // if(tk.cv == NULL) { printf("could not malloc tk.cv.\n"); return -1; }
    // tk.cv[0] = '\0';
    // tk.cv[400] = '\0';

    // tk.ov = malloc(401);
    // if(tk.ov == NULL) { printf("could not malloc tk.ov.\n"); return -1; }
    // tk.ov[0] = '\0';
    // tk.ov[400] = '\0';

    // tk.nv = malloc(401);
    // if(tk.nv == NULL) { printf("could not malloc tk.nv.\n"); return -1; }
    // tk.nv[0] = '\0';
    // tk.nv[400] = '\0';

    // tk.v_int = 0;
    // tk.type = 0;
    // tk.line = 0;



    // 初始化tk的所有内容
    if(!(tk.ov = (TOKEN_V*)malloc(sizeof(TOKEN_V)))) { printf("could not malloc(%d) tk.ov\n", sizeof(TOKEN_V)); return -1; }
    if(!(tk.cv = (TOKEN_V*)malloc(sizeof(TOKEN_V)))) { printf("could not malloc(%d) tk.cv\n", sizeof(TOKEN_V)); free(tk.ov); return -1; }
    if(!(tk.nv = (TOKEN_V*)malloc(sizeof(TOKEN_V)))) { printf("could not malloc(%d) tk.nv\n", sizeof(TOKEN_V)); free(tk.ov); free(tk.cv); return -1; }
    if(!(tk.ov->value = (char*)malloc(buffer))) { printf("could not malloc(%d) tk.ov->value\n", buffer); free(tk.ov); free(tk.cv); free(tk.nv); return -1; }
    if(!(tk.cv->value = (char*)malloc(buffer))) { printf("could not malloc(%d) tk.cv->value\n", buffer); free(tk.ov->value); free(tk.ov); free(tk.cv); free(tk.nv); return -1; }
    if(!(tk.nv->value = (char*)malloc(buffer))) { printf("could not malloc(%d) tk.nv->value\n", buffer); free(tk.ov->value); free(tk.cv->value); free(tk.ov); free(tk.cv); free(tk.nv); return -1; }
    tk.ov->columnl = 0; tk.ov->len = 0; tk.ov->line = 0; tk.ov->type = TOKEN_NULL; memset(tk.ov->value,0,buffer);
    tk.cv->columnl = 0; tk.cv->len = 0; tk.cv->line = 0; tk.cv->type = TOKEN_NULL; memset(tk.cv->value,0,buffer);
    tk.nv->columnl = 0; tk.nv->len = 0; tk.nv->line = 0; tk.nv->type = TOKEN_NULL; memset(tk.nv->value,0,buffer);



    // do{
    //     fr_next_token(f, ptk);
    //     fr_token_type_discern(ptk);
    //     printf("%s\n", tk.cv);
    //     printf("%d\n\n", tk.type);
    // }while(tk.type != TOKEN_EOF);
    free(o_p);
    fclose(f);
    free(tk.ov);
    free(tk.cv);
    free(tk.nv);
    free(tk.cv);
    free(tk.ov->value);
    free(tk.cv->value);
    free(tk.nv->value);
    return 0;
}

#include "graf.h"

int main(int argc,char* argv[]){

    FILE* fin = fopen(argv[1],"r");
    if(!fin){
        return 1;
    }

    FILE* fout_graf  = fopen(argv[2],"w");
    if(!fout_graf){
        return 1;
    }

    FILE* fout_score  = fopen(argv[3],"w");
    if(!fout_score){
        return 1;
    }
    
    Graph *g = create(fin,fout_score);
    printGraph(fout_graf,g);

    fclose(fin);
    fclose(fout_graf);

    // afisare_score(fout_score,final,g);

    for (int i = 0; i < g->varfuri; i++) {
        free(g->m[i]);
    }
    free(g->m);
    free(g);

   
    fclose(fout_score);

   return 0;
}
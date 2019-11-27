#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearBuffer(){
  fpurge(stdin); //Limpeza de buffer em Sistemas Linux
  /*setbuf(stdin, NULL); // Se estiver utilizando Windows, comente a linha de código a cima e utilize essa */
}

int main(){

  FILE *storage_call;

  storage_call = fopen("search_files.txt", "r+");

  if(storage_call==NULL){
    printf("Erro ao abrir o arquivo\n");
  }
  char descricao[20] = "ID:";
  int count, count_line, n;
  char line[1000], teste[2], *lp;

clearBuffer();
while (fgets(line,1000, storage_call)!= NULL) {
    //
    count_line++;
     /*Lê o arquivo até que não tenha mais nada para ler, se utilizar apenas o fgets,
     lê até a primeira quebra de linha*/
     printf("%s\n", line);
     if (strstr(line, descricao)){
       count++;
       printf("Referencia: linha %d\n\n",  count_line);
       // Read until newline is hit or buffer size exceeded.
       for (lp = line; *lp != '\n' && (lp - line) < 1000; lp++) {

         // If encounter colon and sccanf reads at least 1 integer..
         if (*lp == ':' && sscanf(lp + 1, "%c", teste) == 1) {
           n = atoi(teste);
           fprintf(stdout, "%d\n", n);
          break;
      }
    }

     }



     clearBuffer();
 }

  fclose(storage_call);


//  fprintf(storage_call, "ID_Client:  \n");
//  fprintf(storage_call, "ID_Client:  \n");
//fclose(storage_call);



  return 0;
}

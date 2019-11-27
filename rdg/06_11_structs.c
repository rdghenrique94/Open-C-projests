#include <stdio.h>
#include <stdlib.h>

/*struct prof{

  char matricula[50];
  char nome  [50];
};

int main(void){


    struct prof infor[5];
    int cont;

      for (cont = 0; cont <5; cont++){
        printf("Digite Sua Matricula:\n");
          fgets(infor[cont].matricula, 50, stdin);
        printf("Digite Seu Nome:\n");
          fgets(infor[cont].nome, 50, stdin);
     }

      for (cont = 0; cont < 5; cont++){
        printf("Matricula %s\n",infor[cont].matricula);
        printf("Nome %s\n",infor[cont].nome);
     }
}

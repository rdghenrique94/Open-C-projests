#include <stdio_ext.h> // Se estiver utilizando sistemas Linux
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>





int main(){

  setlocale(LC_ALL,"Portuguese");

char menu_option;


do{
  printf("  ________________________________________________\n"
          " /                                                \\\n"
           "|    _________________________________________     |\n"
           "|   |                                         |    |\n"
           "|   |          ALANA'S CORPORATION            |    |\n"
           "|   |                                         |    |\n"
           "|   |  1-Criar Chamado                        |    |\n"
           "|   |  2-Histórico de chamados                |    |\n"
           "|   |  3-Enviar Mensagem                      |    |\n"
           "|   |  4-Sair                                 |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |_________________________________________|    |\n"
           "|                                                  |\n"
          "\\__________________________________________________/\n"
        "        \\___________________________________/\n"
            "    ___________________________________________\n\n");
    printf("Insira sua opção: ");

    menu_option = getchar(); //Pega a opção do usuário
    __fpurge(stdin); //Limpeza de buffer em Sistemas Linux
    /*setbuf(stdin, NULL); // Se estiver utilizando Windows, comente a linha de código a cima e utilize essa */

    switch(menu_option){

        case '1':   //Menu_option = Criar chamados

              do{
                printf("\n\n");
                printf("  ________________________________________________\n"
                        " /                                                \\\n"
                         "|    _________________________________________     |\n"
                         "|   |                                         |    |\n"
                         "|   |         ALANA'S CORPORATION             |    |\n"
                         "|   |                                         |    |\n"
                         "|   |            -CHAMADOS-                   |    |\n"
                         "|   |  1-Serviço de rede                      |    |\n"
                         "|   |  2-Internet, problemas com a conexão    |    |\n"
                         "|   |  3-Voltar                               |    |\n"
                         "|   |                                         |    |\n"
                         "|   |                                         |    |\n"
                         "|   |                                         |    |\n"
                         "|   |                                         |    |\n"
                         "|   |                                         |    |\n"
                         "|   |_________________________________________|    |\n"
                         "|                                                  |\n"
                        "\\__________________________________________________/\n"
                      "        \\___________________________________/\n"
                          "    ___________________________________________\n\n");
                  printf("Insira sua opção: ");
                  __fpurge(stdin);
                  menu_option = getchar();
                  //setbuf(stdin, NULL);
                  __fpurge(stdin);
                  //setbuf(stdin, NULL);

                  switch (menu_option) {

                    case '1':  //Chamados relacionados a serviço de internet
                    printf("Opção 1 de chamados acionado\n");
                    printf("\n\n");
                    printf("  ________________________________________________\n"
                            " /                                                \\\n"
                             "|    _________________________________________     |\n"
                             "|   |                                         |    |\n"
                             "|   |         ALANA'S CORPORATION             |    |\n"
                             "|   |                                         |    |\n"
                             "|   |            -CHAMADOS-                   |    |\n"
                             "|   |  Tipo do chamado: Serviço de internet   |    |\n"
                             "|   |  Título:                                |    |\n"
                             "|   |  Descrição:                             |    |\n"
                             "|   |  Data e autoria:                        |    |\n"
                             "|   |                                         |    |\n"
                             "|   |                                         |    |\n"
                             "|   |                                         |    |\n"
                             "|   |                                         |    |\n"
                             "|   |_________________________________________|    |\n"
                             "|                                                  |\n"
                            "\\__________________________________________________/\n"
                          "        \\___________________________________/\n"
                              "    ___________________________________________\n\n");
                    printf("Digite o Título do chamado: ");
                    __fpurge(stdin);
                    menu_option = getchar();
                    //setbuf(stdin, NULL);
                    __fpurge(stdin);
                    //setbuf(stdin, NULL);

                    break;

                    case '2':
                    printf("Opção 2 de chamados acionado\n");
                    break;

                    case '3':
                    break;

                    default:
                    printf("Invalid Option\n");
                    break;
                  }
              }
              while (menu_option != '3');

              //EM ANDAMENTO
        break;

        case '2':
            printf("Case 2 acionado\n");
        break;

        case'3':
            printf("case 3 acionado\n");
        break;

        case'4':
        break;

        default:
          printf("\n\ninvalid input\n");
        break;
      }

    }while(menu_option !='4'); // Com a utilização do Do While, da para incorporar o tratamento de erros


  return 0;
}

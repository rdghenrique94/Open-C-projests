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
           "|   |  ALANA'S CORPORATION                    |    |\n"
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
    //scanf("%c", &menu_option);
    menu_option = getchar();
    setbuf(stdin, NULL);

    switch(menu_option){

        case '1':
            printf("1 deu certo\n");

            break;
        case '2':
            printf("@@@@@@@@@\n");

            break;
        case'3':
            printf("case c");
            break;
        case'4':
          break;

       default:
          printf("\n\ninvalid input\n");
          break;
        }


      }while(menu_option !='4');



  return 0;
}

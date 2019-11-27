//#include <stdio_ext.h> // Se estiver utilizando sistemas Linux habilite essa biblioteca, caso não esteja comente essa linha de código
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


#define MAX_200 200
#define MAX_20 20
#define MAX_40 40
#define MAX_LINE 1000
#define BUFFER_SIZE 1000
#define MAXCHAR 100




typedef struct calls{

    /* Informações de cada chamado */
    char title_calls[MAX_40];
    char descr[MAX_200];
    char status[MAX_20];
    char author[MAX_20];
}Calls;


/*    O sistema possui dois tipos de login, um de cliente e outro de gerente
 *    Cada usuário possui um módulo com funcionalidades específicas conforme o
 *    nível do usuário.
 */
typedef struct managers{
    char login[10];
    char password[10];
    char name[10];
}Managers;


typedef struct customers{
    char login[10];
    char password[10];
}Customers;



// Variáveis globais

int id_call;
int id_search_temporary;
int search = 0;
int new_status;
int menu_option;
int search_status;
char temporary[3];
char message[400];
char menu_option_str[MAX_20];
char line[MAX_LINE]; //Será usado posteriormente para a exibição do historico de chamados



char serv_rede[MAX_20] = "Serviço de rede\0"; // chamado relacionados a serviço de rede
char serv_internet[MAX_40] = "Serviço de Internet\0"; // chamado relacionados a serviço de de internet





Calls calls;
Customers customers;
Managers managers;




/* Funções */

void clearBuffer(){
  ///__fpurge(stdin); //Sistemas Linux
  setbuf(stdin, NULL); // Se estiver utilizando Windows, comente a linha de código a cima e utilize essa */
}


void get_option(){
  clearBuffer();
  fgets(menu_option_str, MAX_40, stdin);
  menu_option = atoi(menu_option_str);
  clearBuffer();
}




/* Função de conversão de int para String */
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}




int numbers_of_calls(){

  FILE *file_calls;
  char txt[MAXCHAR];
  int number_of_calls;

  file_calls = fopen("calls.txt", "r");

  if (file_calls){

    while (fscanf(file_calls, " %99s", txt) != EOF)
    {

      if(strcmp("qtd_de_chamados:", txt) == 0 ){
           fscanf(file_calls, " %1023s", txt);
           number_of_calls = atoi(txt);
           printf("Quantidade de chamados: %d\n", number_of_calls);
      }
    }
    fclose(file_calls);
    return number_of_calls;
  }
  else{
    return 0;
  }
}



void replace_numbers_of_calls(){

    FILE * file_calls;
    FILE * file_temporary;
    char path[100];

    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE] = "qtd_de_chamados: 0\n";

    char temporary_str[10];
    int count, n, line = 8;


    id_call = numbers_of_calls() + 1;

    tostring(temporary_str, id_call);

    if(!(temporary_str[1])){
      temporary_str[1] = '\n';
      newline[19] = 0;
    }
    else{
      newline[19] = '\n';
    }

    newline[17] = temporary_str[0];
    newline[18] = temporary_str[1];



    file_calls  = fopen("calls.txt", "r");
    file_temporary = fopen("replace_temporary.txt", "w");



    if (file_calls == NULL || file_temporary == NULL)
    {
        printf("\nFile couldn't be opened\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return;
    }



    /*
     *  Lê a linha do arquivo fonte e escreve para o destino
     * do arquivo e modifica a linha.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, file_calls)) != NULL)
    {
        count++;

        if (count == line)
            fputs(newline, file_temporary);
        else
            fputs(buffer, file_temporary);
    }


    fclose(file_calls);
    fclose(file_temporary);


    remove("calls.txt");



    rename("replace_temporary.txt", "calls.txt");


}




int searchCall(int search_id){

  FILE *file_calls;
  char txt[MAXCHAR];
  int id, counter = 1;  // o contador começa em 1 pois o arquivo começa a contagem de linhas a partir do 1
  int line_of_id = 0;

  file_calls = fopen("calls.txt", "r");

  if (file_calls){

    while (fscanf(file_calls, " %99s", txt) != EOF)
    {

      if(strcmp("ID:", txt) == 0 ){

           counter +=9;

           fscanf(file_calls, " %1023s", txt);
           id = atoi(txt);

           if(search_id == id){
             line_of_id = counter;
             search = 1;
           }
      }
    }

    fclose(file_calls);

    return line_of_id;
  }

  else{
    return 0;
  }
}





void replaceStatus(int new_status){

    FILE * file_calls;
    FILE * file_temporary;



    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE] = "Status do chamado: 0\n";


    char temporary_str[2];
    int count, line;


    line = searchCall(id_search_temporary) + 2;
    tostring(temporary_str, new_status);

    newline[19] = temporary_str[0]; //modificando o status do chamado
    newline[20] = '\n';

    if(line == 2){
      return;
    }



    file_calls  = fopen("calls.txt", "r");
    file_temporary = fopen("replace_temporary.txt", "w");



    if (file_calls == NULL || file_temporary == NULL)
    {
        printf("\nFile couldn't be opened\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return;
    }



    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, file_calls)) != NULL)
    {
        count++;

        if (count == line)
            fputs(newline, file_temporary);
        else
            fputs(buffer, file_temporary);
    }


    fclose(file_calls);
    fclose(file_temporary);


    remove("calls.txt");

    rename("replace_temporary.txt", "calls.txt");
    printf("Status modificado com Sucesso\n\n");
}







int display_searched_status(int cod_status){

  FILE *file_calls;

  char txt[MAXCHAR];
  int status;
  int id_count = 0;
  int count_status = 0;

  //display range
  int counter;
  int first_line = 1, last_line = 0, count_line = 0;
  int rangef[50], rangl[50];



  file_calls = fopen("calls.txt", "r");

  if (file_calls){

    while (fscanf(file_calls, " %99s", txt) != EOF)
    {

      if(strcmp("Status", txt) == 0 ){

            first_line += 9; // A linha do ID de cada chamado segue um padrão a partir da linha 10
            last_line = first_line + 6;

           fscanf(file_calls, " %1023s", txt);
           fscanf(file_calls, " %1023s", txt);
           fscanf(file_calls, " %1023s", txt);
           status = atoi(txt);



           if(status == cod_status){

             rangef[count_status] = first_line;
             rangl[count_status] = last_line;
             count_status ++;
           }
      }
    }



    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                                                                                 |\n");
    printf("|                                          ALANA'S CORPORATION Ⓡ                                                  |\n");
    printf("|                                                                                                                 |\n");
    printf("|                                          HISTÓRICO DE CHAMADOS                                                  |\n");
    printf("-------------------------------------------------------------------------------------------------------------------\n\n\n");




    for(counter =0; counter < count_status; counter++){


        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        file_calls = fopen("calls.txt", "r");


        while (fgets(line, MAX_LINE, file_calls)) {

          count_line++;

          if( count_line >= rangef[counter] && count_line <= rangl[counter]){
            printf("%s\n",line );
          }
        }

        count_line = 0;

    }

    fclose(file_calls);
    return status;
  }
  else{
    return 0;
  }
}



//Carregamento do sistema
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}



//System colors
void displayColor(){
  printf("\033[1;33m");
}

void resetColor(){
  printf("\033[0m");
}





// System of calls

int main(){

  setlocale(LC_ALL,"Portuguese");



  //Organizando o uso de data e hora da biblioteca time.h

  int hours, minutes, seconds, day, month, year;


  time_t now_time;
  time(&now_time); // retorna as horas em segundos
  struct tm *info_time = localtime(&now_time); // converte de segundos para o sistema local, retornando um ponteiro de tipo tm

  hours = info_time->tm_hour;
  minutes = info_time->tm_min;
  seconds = info_time->tm_sec;

  day = info_time->tm_mday;
  month = info_time->tm_mon + 1; // retorna a quantidade de meses a partir 0
  year = info_time->tm_year + 1900; // retorn a quantidade de anos depois de 1900


  strcpy(calls.status, "0"); // Todos os chamados inicializarão Em aberto "0"

  strcpy(calls.author, "Jose da Silva\n");

  strcpy(managers.name, "Igor\n");

  strcpy(managers.login, "admin\n");
  strcpy(managers.password, "admin\n");
  strcpy(customers.login, "cliente\n");
  strcpy(customers.password, "1234\n");




  FILE *file_calls;
  FILE *message_feedback;



  char login[10];
  char password[10];

  int option_access = 0;


/*
 *   Para armazenar as mensagens de feedback e os chamados
 *   abertos pelo cliente foram criados os arquivos .txt abaixo
 */

  file_calls = fopen("calls.txt", "a");
  message_feedback = fopen("message_feedback.txt", "a");



  if (file_calls == NULL || message_feedback == NULL)
  {
      printf("\nFile couldn't be opened\n");
      printf("Please check whether file exists and you have read/write privilege.\n");
      return 0;
  }




  printf("  ________________________________________________\n"
          " /                                                \\\n"
           "|    _________________________________________     |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |           ALANA'S CORPORATION Ⓡ         |    |\n"
           "|   |                                         |    |\n"
           "|   |               Loading...                |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |                                         |    |\n"
           "|   |_________________________________________|    |\n"
           "|                                                  |\n"
          "\\__________________________________________________/\n"
        "        \\___________________________________/\n"
            "    ___________________________________________\n\n");


  for (int i = 0; i < 4 ; i++){
        delay(1000);
  }
  printf("\n\n");



  //System access

  while ( option_access == 0) {

    printf("  ________________________________________________\n"
            " /                                                \\\n"
             "|    _________________________________________     |\n"
             "|   |                                         |    |\n"
             "|   |          ALANA'S CORPORATION            |    |\n"
             "|   |                                         |    |\n"
             "|   | Login:                                  |    |\n"
             "|   | Senha:                                  |    |\n"
             "|   |                                         |    |\n"
             "|   |                                         |    |\n"
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
    printf("Login: ");
    clearBuffer();
    fgets(login, 10, stdin);
    printf("Password: ");
    clearBuffer();
    fgets(password, 10, stdin);




    if((strcmp(login, customers.login) == 0) && (strcmp(password, customers.password) == 0)){
      option_access = 1; //Opção de acesso ao modulo do cliente
      printf("Deu certo\n");}
    else if((strcmp(login, managers.login) == 0) && (strcmp(password, managers.password) == 0)){
      option_access = 2; //Opção de acesso ao modulo do gerente
    }else
      option_access = 0; /* Opção de acesso de login e senha incorreto -
                          permanece no loop até digitar o login e senha correto   */


    switch (option_access) {

      //USER MODULE
      case 1:
        printf("\033[0;32m\nCliente logado com sucesso\n\n\033[0m");


        // Menu de opções do sistema
         do{
           printf("  ________________________________________________\n"
                   " /                                                \\\n"
                    "|    _________________________________________     |\n"
                    "|   |                                         |    |\n"
                    "|   |          ALANA'S CORPORATION            |    |\n"
                    "|   |                                         |    |\n"
                    "|   |  1-Abrir Chamado                        |    |\n"
                    "|   |  2-Histórico de chamados                |    |\n"
                    "|   |  3-Enviar Mensagem                      |    |\n"
                    "|   |  4-Mensagens Recebidas                  |    |\n"
                    "|   |  5-Sair                                 |    |\n"
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
             get_option();



             switch(menu_option){

                 //Opção 1 - Abrir chamado
                 case 1:

                       do{
                         printf("\n\n");
                         printf("\033[0;32m\nOpção 1 - Abrir chamado acionado\n\n\033[0m");
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
                           get_option();



                           switch (menu_option) {


                             //Chamados relacionados a serviço de rede
                             case 1:

                               printf("\n\n");
                               printf("  ________________________________________________\n"
                                       " /                                                \\\n"
                                        "|    _________________________________________     |\n"
                                        "|   |                                         |    |\n"
                                        "|   |         ALANA'S CORPORATION             |    |\n"
                                        "|   |                                         |    |\n"
                                        "|   |            -CHAMADOS-                   |    |\n"
                                        "|   |  Tipo do chamado: Serviço de rede       |    |\n"
                                        "|   |  Título:                                |    |\n"
                                        "|   |  Descrição:                             |    |\n"
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
                               printf("Digite o Título do chamado: ");
                               clearBuffer();


                               fgets(calls.title_calls, MAX_40, stdin);
                               clearBuffer();

                               printf("Digite a descrição do chamado: ");
                               fgets(calls.descr, MAX_200, stdin);
                               clearBuffer();



                               // Formata o armazenamento dos chamados
                               replace_numbers_of_calls();
                               file_calls = fopen("calls.txt", "a");
                               fprintf(file_calls, "ID: %i\n", id_call);
                               fprintf(file_calls, "Autor: %s",calls.author);
                               fprintf(file_calls, "Status do chamado: %s\n", calls.status);
                               fprintf(file_calls, "Tipo do chamado: %s\n", serv_rede);
                               fprintf(file_calls, "Título: %s", calls.title_calls);
                               fprintf(file_calls, "Descrição: %s", calls.descr );
                               fprintf(file_calls, "Data e hora: %02d/%02d/%02d - %02d:%02d:%02d\n\n", day, month, year, hours, minutes, seconds);
                               fprintf(file_calls, "-----------------------------------------------------------------------------------------------------------------------\n" );
                               fclose(file_calls);



                             break;

                             //Chamados relacionados a serviço de internet
                             case 2:

                               printf("\n\n");
                               printf("  ________________________________________________\n"
                                       " /                                                \\\n"
                                        "|    _________________________________________     |\n"
                                        "|   |                                         |    |\n"
                                        "|   |         ALANA'S CORPORATION             |    |\n"
                                        "|   |                                         |    |\n"
                                        "|   |            -CHAMADOS-                   |    |\n"
                                        "|   |  Tipo do chamado: Serviço de Internet   |    |\n"
                                        "|   |  Título:                                |    |\n"
                                        "|   |  Descrição:                             |    |\n"
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
                               printf("Digite o Título do chamado: ");
                               clearBuffer();


                               fgets(calls.title_calls, MAX_40, stdin);
                               clearBuffer();


                               printf("Digite a descrição do chamado: ");
                               fgets(calls.descr, MAX_200, stdin);
                               clearBuffer();


                               // Formata o armazenamento dos chamados
                               replace_numbers_of_calls();
                               file_calls = fopen("calls.txt", "a");
                               fprintf(file_calls, "ID: %i\n", id_call);
                               fprintf(file_calls, "Autor: %s",calls.author);
                               fprintf(file_calls, "Status do chamado: %s\n", calls.status);
                               fprintf(file_calls, "Tipo do chamado: %s\n", serv_internet);
                               fprintf(file_calls, "Título: %s", calls.title_calls);
                               fprintf(file_calls, "Descrição: %s", calls.descr );
                               fprintf(file_calls, "Data e hora: %02d/%02d/%02d - %02d:%02d:%02d\n\n", day, month, year, hours, minutes, seconds);
                               fprintf(file_calls, "-----------------------------------------------------------------------------------------------------------------------\n" );
                               fclose(file_calls);


                             break;

                             //Retorna para o menu anterior
                             case 3:
                             break;


                             //Exception Handling
                             default:
                              printf("\033[0;31m Entrada Inválida, digite novamente\n \033[0m");
                             break;
                           }
                       }
                       while (menu_option != 3);

                 break;


                 //Opção 2 - Histórico de chamados
                 case 2:
                   printf("\n\n");
                   printf("\033[0;32m\nOpção 2 - Histórico de chamados acionado\n\n\033[0m");

                   fclose(file_calls);
                   file_calls = fopen("calls.txt", "r");
                   printf("\n\n");

                   while (fgets(line, MAX_LINE, file_calls)) {
                     displayColor();
                     printf("%s\n",line );
                   }
                   fclose(file_calls);
                   file_calls = fopen("calls.txt", "a");
                   resetColor();

                   printf("\033[0;31m\n\nVocê não possui mais chamados no seu histórico\n\n\033[0m");
                 break;


                 //Opção 3 - Enviar Mensagem
                 case 3:
                     printf("\033[0;32mopção 3 - Enviar Mensagem acionado\n\033[0m");
                     printf("\n\n");
                     printf("  ________________________________________________\n"
                             " /                                                \\\n"
                              "|    _________________________________________     |\n"
                              "|   |                                         |    |\n"
                              "|   |         ALANA'S CORPORATION             |    |\n"
                              "|   |                                         |    |\n"
                              "|   |          -MENSAGEM-FEEDBACK-            |    |\n"
                              "|   |                                         |    |\n"
                              "|   |                                         |    |\n"
                              "|   |                                         |    |\n"
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
                     printf("Digite sua mensagem: ");
                     clearBuffer();
                     fgets(message, 400, stdin);
                     clearBuffer();

                     fprintf(message_feedback, "Autor: %s\n",calls.author);
                     fprintf(message_feedback, "Mensagem: %s\n", message);
                     fprintf(message_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );

                 break;


                 //Opção 4 - Mensagens de feedback do gerente
                 case 4:
                  printf("\n\n");
                  printf("\033[0;32m\nOpção 4 - Mensagens recebidas acionado\n\n\033[0m");

                  message_feedback = fopen("managers_message.txt", "r");
                  displayColor();
                  printf("\n\n");

                  while (fgets(line, MAX_LINE, message_feedback)) {
                    printf("%s\n",line );
                  }
                  resetColor();

                  printf("\033[0;31m\n\nVocê não possui mais mensagens na caixa de entrada\n\n\033[0m");
                  fclose(message_feedback);
                 break;


                 //Opção 5- Sair do sistema
                 case 5:
                  option_access = 1;
                 break;


                 //Exception Handling
                 default:
                    printf("\033[0;31m Entrada Inválida, digite novamente\n \033[0m");
                 break;
               }

         }while(menu_option != 5);

        break; // break user module




      // MANAGERS MODULE
      case 2:
        printf("\033[0;32m\nAdministrador logado com sucesso\n\033[0m");
        do{
          printf("  ________________________________________________\n"
                  " /                                                \\\n"
                   "|    _________________________________________     |\n"
                   "|   |                                         |    |\n"
                   "|   |          ALANA'S CORPORATION            |    |\n"
                   "|   |                                         |    |\n"
                   "|   |  1-Visualizar Chamados                  |    |\n"
                   "|   |  2-Mudar Status dos chamados            |    |\n"
                   "|   |  3-Gerar relatorio                      |    |\n"
                   "|   |  4-Enviar mensagem                      |    |\n"
                   "|   |  5-Mensagens recebidas                  |    |\n"
                   "|   |  6-Sair                                 |    |\n"
                   "|   |                                         |    |\n"
                   "|   |                                         |    |\n"
                   "|   |                                         |    |\n"
                   "|   |_________________________________________|    |\n"
                   "|                                                  |\n"
                  "\\__________________________________________________/\n"
                "        \\___________________________________/\n"
                    "    ___________________________________________\n\n");
            printf("Insira sua opção: ");
            get_option();
            switch (menu_option) {


              //Opção 1 - Visualizar Chamados
              case 1:
                do {

                printf("\n\n");
                printf("\033[0;32m\nOpção 1 - Visualizar chamados acionado\n\n\033[0m");
                printf("  ________________________________________________\n"
                        " /                                                \\\n"
                         "|    _________________________________________     |\n"
                         "|   |                                         |    |\n"
                         "|   |          ALANA'S CORPORATION            |    |\n"
                         "|   |                                         |    |\n"
                         "|   |  1-Visualizar Chamados Abertos          |    |\n"
                         "|   |  2-Visualizar Chamados Fechados         |    |\n"
                         "|   |  3-Voltar                               |    |\n"
                         "|   |                                         |    |\n"
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
                  get_option();

                  switch (menu_option) {

                    //Chamados abertos
                    case 1:
                      search_status = 0;
                      displayColor();
                      display_searched_status(search_status);
                      resetColor();
                      printf("\033[0;31m\n\nVocê não possui mais chamados em aberto no seu histórico\n\n\033[0m");
                      break;

                    //Chamados abertos
                    case 2:
                      search_status = 3;
                      displayColor();
                      display_searched_status(search_status);
                      resetColor();
                      printf("\033[0;31m\n\nVocê não possui mais chamados fechados no seu histórico\n\n\033[0m");
                    break;

                    //voltar
                    case 3:
                    break;

                    //Exception Handling
                    default:
                      printf("\033[0;31m Entrada Inválida, digite novamente\n \033[0m");
                    break;

                  }
                }while(menu_option != 3);
              break;


              //Opção 2 - Mudar Status do chamado
              case 2:

                printf("\n\n");
                printf("\033[0;32m\nOpção 2 - Mudar Status acionado\n\n\033[0m");
                printf("  ________________________________________________\n"
                        " /                                                \\\n"
                         "|    _________________________________________     |\n"
                         "|   |                                         |    |\n"
                         "|   |          ALANA'S CORPORATION            |    |\n"
                         "|   |                                         |    |\n"
                         "|   |       Mudar de Status dos chamados      |    |\n"
                         "|   |                                         |    |\n"
                         "|   |  ID do chamado:                         |    |\n"
                         "|   |  Novo status:                           |    |\n"
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
                  printf("Insira o ID do chamado que deseja modifcar: ");
                  clearBuffer();
                  fgets(temporary, 3, stdin);
                  id_search_temporary = atoi(temporary);

                  printf("Insira o codigo do novo status: ");
                  clearBuffer();
                  fgets(temporary, 3, stdin);
                  new_status = atoi(temporary);
                  searchCall(id_search_temporary);
                  replaceStatus(new_status);



                  (search == 0) ? printf("\n\n \033[0;31m	ID não encontrado ou inválido \033[0m \n\n"): printf("\n");



                  /* Se o gerente modificar o status para 2 (Em antendimento - visita técnica), ele entra no if e pede para
                  agendar a visita técnica */
                  if((new_status == 2) && (search != 0)) {
                    printf("\n\n");
                    printf("  ________________________________________________\n"
                            " /                                                \\\n"
                             "|    _________________________________________     |\n"
                             "|   |                                         |    |\n"
                             "|   |          ALANA'S CORPORATION            |    |\n"
                             "|   |                                         |    |\n"
                             "|   |            Agendar Visita               |    |\n"
                             "|   |                                         |    |\n");
                      printf("|   |  \t   1 -Data: %02d/%02d/%02d\t - Manhã      |    |\n", day+1, month, year);
                      printf("|   |  \t   2 -Data: %02d/%02d/%02d\t - Tarde      |    |\n", day+1, month, year);
                      printf("|   |  \t   3 -Data: %02d/%02d/%02d\t - Manhã      |    |\n", day+2, month, year);
                      printf("|   |  \t   4 -Data: %02d/%02d/%02d\t - Tarde      |    |\n", day+2, month, year);
                      printf("|   |                                         |    |\n"
                             "|   |                                         |    |\n"
                             "|   |                                         |    |\n"
                             "|   |_________________________________________|    |\n"
                             "|                                                  |\n"
                            "\\__________________________________________________/\n"
                          "        \\___________________________________/\n"
                              "    ___________________________________________\n\n");
                              printf("Insira sua opção: ");
                              get_option();

                              switch (menu_option) {

                                //Opção 1
                                case 1:
                                  message_feedback = fopen("managers_message.txt", "a");
                                  fprintf(message_feedback, "Autor: %s\n", managers.name);
                                  fprintf(message_feedback, "Mensagem: O chamado com ID: %d foi agendado para visita técnica no dia: %02d/%02d/%02d - Manhã\n", id_search_temporary, day+1, month, year);
                                  fprintf(message_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );
                                  fclose(message_feedback);
                                break;

                                //Opção 2
                                case 2:
                                  message_feedback = fopen("managers_message.txt", "a");
                                  fprintf(message_feedback, "Autor: %s\n", managers.name);
                                  fprintf(message_feedback, "Mensagem: O chamado com ID: %d foi agendado para visita técnica no dia: %02d/%02d/%02d - Tarde\n", id_search_temporary, day+1, month, year);
                                  fprintf(message_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );
                                  fclose(message_feedback);
                                break;

                                //Opção 3
                                case 3:
                                  message_feedback = fopen("managers_message.txt", "a");
                                  fprintf(message_feedback, "Autor: %s\n", managers.name);
                                  fprintf(message_feedback, "Mensagem: O chamado com ID: %d foi agendado para visita técnica no dia: %02d/%02d/%02d - Manhã\n", id_search_temporary, day+2, month, year);
                                  fprintf(message_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );
                                  fclose(message_feedback);
                                break;

                                //Opção 4
                                case 4:
                                  message_feedback = fopen("managers_message.txt", "a");
                                  fprintf(message_feedback, "Autor: %s\n", managers.name);
                                  fprintf(message_feedback, "Mensagem: O chamado com ID: %d foi agendado para visita técnica no dia: %02d/%02d/%02d - Tarde\n", id_search_temporary, day+2, month, year);
                                  fprintf(message_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );
                                  fclose(message_feedback);
                                break;

                                default:
                                  printf("\033[0;31m	Digite uma opção válida\n \033[0m ");
                                break;

                              }
                  }

              break;


              //Opção 3 - Histórico de chamados - relatório
              case 3:
                printf("\033[0;32m\n\nopção 3 -Gerar Relatório acionado\n\033[0m");
                file_calls = fopen("calls.txt", "r");
                displayColor();
                while (fgets(line, MAX_LINE, file_calls)) {
                  printf("%s\n",line );
                }
                resetColor();
                fclose(file_calls);
              break;


              //Opção 4 - Mensagem de feedback para o cliente
              case 4:
                printf("\033[0;32m\n\nopção 4 - Enviar Mensagem acionado\n\033[0m");
                printf("\n\n");
                printf("  ________________________________________________\n"
                        " /                                                \\\n"
                         "|    _________________________________________     |\n"
                         "|   |                                         |    |\n"
                         "|   |         ALANA'S CORPORATION             |    |\n"
                         "|   |                                         |    |\n"
                         "|   |          -MENSAGEM-FEEDBACK-            |    |\n"
                         "|   |                                         |    |\n"
                         "|   |                                         |    |\n"
                         "|   |                                         |    |\n"
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
                printf("Digite sua mensagem: ");
                clearBuffer();
                fgets(message, 400, stdin);
                clearBuffer();

                message_feedback = fopen("managers_message.txt", "a");
                fprintf(message_feedback, "Autor: %s\n", managers.name);
                fprintf(message_feedback, "Mensagem: %s\n", message);
                fprintf(message_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );

              break;

              //Opção 5 - Mensagens recebidas
              case 5:
                printf("\n\n");
                printf("\033[0;32m\nOpção 5 - Mensagens recebidas acionado\n\n\033[0m");
                message_feedback = fopen("message_feedback.txt", "r");
                displayColor();

                while (fgets(line, MAX_LINE, message_feedback)) {
                  printf("%s\n",line );
                }

                printf("\033[0;31m\n\nVocê não possui mais mensagens na caixa de entrada\n\n\033[0m");
                resetColor();
                fclose(message_feedback);
              break;


              //Opção 6 - Sair dos sistema
              case 6:
              break;


              //Exception Handling
              default:
                printf("\033[0;31m\n\nEntrada Inválida, digite novamente\n\n\033[0m");
              break;

            }
          }while(menu_option != 6);
      break;


      //Exception Handling
      default:
        printf("\033[0;31m\n\nLogin ou senha incorreto\n\n \033[0m");
      break;
    }

  }  //End while System access


  return 0;
}

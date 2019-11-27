#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


int main()
{
setlocale(LC_ALL,"Portuguese");
setbuf(stdin,NULL);
FILE *file;
FILE *file1;

  file = fopen("C:\\Users\\NATHALIA\\Desktop\\string.txt", "w");
  file1 = fopen("C:\\Users\\NATHALIA\\Desktop\\numero.txt", "w");

        fprintf(file,"teste");
        fprintf(file1, "10 20 30");
        fclose(file);
        fclose(file1);


  file = fopen("C:\\Users\\NATHALIA\\Desktop\\string.txt", "r");
  file1 = fopen("C:\\Users\\NATHALIA\\Desktop\\numero.txt", "r");
    if(file == NULL){
        printf("Arquivo não pode ser aberto\n");
              system ("pause");
        return 0;
      }
      char frase[100];
      int x, y, z;

      while(fgets(frase,100,file) != NULL){     //dessa forma é lido toda a string
          printf("%s\n",frase);             //juntamente com quebra de linha
}
            fscanf(file,"%s\n",&frase);     //dessa forma só é lido a primeira linha
              printf("%s\n", frase);        //até a quebra de linha da string
            fscanf(file1,"%i %i %i",  &x, &y, &z);
              printf("%i %i %i\n", x, y ,z);

        fclose(file);
return 0;

}

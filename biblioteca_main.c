#include <stdio.h>
//#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct livro {
 char titulo[60];
 char autor[40];
 char editora[30];
 int ano;
 int exclusao_logica;
}Tlivro;

void biblioteca();
int menu();
int menu_procura();
int cadastrar_livro();
int listar_livro();
void procurar_livro();
int procurar_livro_titulo();
int procurar_livro_autor();
int procurar_livro_ano();

int main(){

    biblioteca();

    return 0;
}

void biblioteca(){
    int op;

    do{
        op = menu();
        //system("cls");

        switch(op){
            case 1:
                    if (cadastrar_livro()){
                        printf("\n\n\t[INFO] LIVRO CADASTRADO COM SUCESSO\n\n");
                    }else{
                        printf("\n\n\t[INFO] ERRO AO CADASTRAR LIVRO\n\n");
                    }
                break;

            case 2:

                break;

            case 3:
                    if (listar_livro()){
                        printf("\n\n\t[INFO] LIVROS LISTADO COM SUCESSO\n\n");
                    }else{
                        printf("\n\n\t[INFO] ERRO AO LISTAR LIVROS\n\n");
                    }
                break;

            case 4:
                procurar_livro();
                break;

            case 5:
                printf("\n\n\t[INFO] SAINDO \n");
                break;

            default :
                printf("\n\n\t[INFO] OPCAO INEXISTENTE\n");
        }

    }while(op != 5);
}

int menu(){
    int opcao;

    printf ("\t%c", 201);
    for(int i = 0; i < 50; i++) printf ("%c", 205);
    printf ("%c\n\t%c \t\t     BIBLIOTECA\t\t\t   %c\n\t%c", 187,186,186,204);
    for(int i = 0; i < 50; i++) printf ("%c", 205);
    printf("%c\n\t%c",185, 186);for(int i = 0; i < 50; i++) printf (" ");
    printf("%c\n\t%c\t 1 - CADASTRAR LIVRO\t\t\t   %c\n", 186, 186, 186);
    printf("\t%c\t 2 - EXCLUIR LIVRO (EXCLUSAO LOGICA )      %c\n", 186, 186);
    printf("\t%c\t 3 - LISTAR TODOS LIVROS\t\t   %c\n", 186, 186);
    printf("\t%c\t 4 - PROCURAR LIVRO     \t\t   %c\n", 186, 186);
    printf("\t%c\t 5 - SAIR\t\t\t\t   %c\n\t%c", 186, 186, 200);
    for(int i = 0; i < 50; i++) printf ("%c", 205);
    printf("%c\n",188);
    printf("\tDIGITE A OPCAO [  ]\b\b\b");
    //fflush(stdin);
    __fpurge(stdin);
    scanf("%i", &opcao);
    //fflush(stdin);
    __fpurge(stdin);



    do{
        if(opcao < 1 || opcao > 5){
            printf("\n\n\t[INFO] OPCAO INVALIDA, DIGITE NOVAMENTE\n");
            printf("\tDIGITE A OPCAO [  ]\b\b\b");
            //fflush(stdin);
            __fpurge(stdin);
            scanf("%i", &opcao);
            //fflush(stdin);
            __fpurge(stdin);
        }
    }while(opcao < 1 || opcao > 5);

    return opcao;
}

int menu_procura(){
    int opcao;

    printf ("\t%c", 201);
    for(int i = 0; i < 50; i++) printf ("%c", 205);
    printf ("%c\n\t%c \t\t     BIBLIOTECA\t\t\t   %c\n\t%c", 187,186,186,204);
    for(int i = 0; i < 50; i++) printf ("%c", 205);
    printf("%c\n\t%c",185, 186);for(int i = 0; i < 50; i++) printf (" ");
    printf("%c\n\t%c\tPESQUISAR LIVRO POR: \t\t\t   %c\n", 186, 186, 186);
    printf("\t%c\t 1 - TITULO DO LIVRO\t\t\t   %c\n", 186, 186);
    printf("\t%c\t 2 - NOME AUTOR     \t\t\t   %c\n", 186, 186);
    printf("\t%c\t 3 - ANO DE LANCAMENTO  \t\t   %c\n", 186, 186);
    printf("\t%c\t 4 - VOLTAR             \t\t   %c\n\t%c", 186, 186, 200);
    for(int i = 0; i < 50; i++) printf ("%c", 205);
    printf("%c\n",188);
    printf("\tDIGITE A OPCAO [  ]\b\b\b");
    //fflush(stdin);
    __fpurge(stdin);
    scanf("%i", &opcao);
    //fflush(stdin);
    __fpurge(stdin);

    do{
        if(opcao < 1 || opcao > 4){
            printf("\n\n\t[INFO] OPCAO INVALIDA, DIGITE NOVAMENTE\n");
            printf("\tDIGITE A OPCAO [  ]\b\b\b");
            //fflush(stdin);
            __fpurge(stdin);
            scanf("%i", &opcao);
            __fpurge(stdin);
            //fflush(stdin);
        }
    }while(opcao < 1 || opcao > 4);

    return opcao;
}


int cadastrar_livro(){
    FILE *pont_arq;
    Tlivro livro;

    if(!(pont_arq = fopen("biblioteca.txt", "a+"))){
        printf("n\n\t[INFO]Erro na abertura do arquivo!\n");
        return 0;
    }

    printf("\tINFORME O TITULO DO LIVRO: ");
    fgets(livro.titulo, 60, stdin);
    //livro.titulo[(strlen(livro.titulo))] = '\0';

    printf("\tINFORME O AUTOR DO LIVRO: ");
    fgets(livro.autor, 40, stdin);
    //livro.autor[strlen(livro.autor)] = '\0';

    printf("\tINFORME O EDITOR DO LIVRO: ");
    fgets(livro.editora, 30, stdin);
    //livro.editora[strlen(livro.editora)] = '\0';

    printf("\tINFORME O ANO DO LIVRO: ");
    scanf("%d", &livro.ano);

    livro.exclusao_logica = 0;
    //fgets(livro.ano, 6, stdin);
    //livro.ano[4] = '\0';

    fprintf(pont_arq, "%s%s%s%d%d", livro.titulo, livro.autor, livro.editora, livro.ano, livro.exclusao_logica);


    fclose(pont_arq);

    return 1;
}

int listar_livro(){
    FILE *pont_arq;
    Tlivro livro;

    if(!(pont_arq = fopen("biblioteca.txt", "r"))){
        printf("\n\n\t[INFO]Erro na abertura do arquivo!\n");
        return 0;
    }

    while(!feof(pont_arq)){
        fgets(livro.titulo, 60, pont_arq);
        fgets(livro.autor, 40, pont_arq);
        fgets(livro.editora, 30, pont_arq);
        fscanf(pont_arq, "%d", &livro.ano);
        fscanf(pont_arq, "%d", &livro.exclusao_logica);
        //fscanf(pont_arq, "%s%s%s%s",livro.titulo, livro.autor, livro.editora, livro.ano);

        if(livro.exclusao_logica == 0)
            printf("\n\tTitulo: %s\tAutor: %s\tEditor: %s\tAno: %d\n", livro.titulo, livro.autor, livro.editora, livro.ano);
    }

    fclose(pont_arq);
    return 1;
}


void procurar_livro(){
    int op;

    do{
        op = menu_procura();
        //system("cls");

        switch(op){
            case 1:
                    if (procurar_livro_titulo()){
                        printf("\n\n\t[INFO] LIVRO ENCONTRADO COM SUCESSO\n\n");
                    }else{
                        printf("\n\n\t[INFO] ERRO AO ENCONTRAR LIVRO\n\n");
                    }
                    op = 4;
                break;

            case 2:
                    if (procurar_livro_autor()){
                        printf("\n\n\t[INFO] LIVRO ENCONTRADO COM SUCESSO\n\n");
                    }else{
                        printf("\n\n\t[INFO] ERRO AO ENCONTRAR LIVRO\n\n");
                    }
                op = 4;
                break;

            case 3:
                    if (procurar_livro_ano()){
                        printf("\n\n\t[INFO] LIVRO ENCONTRADO COM SUCESSO\n\n");
                    }else{
                        printf("\n\n\t[INFO] ERRO AO ENCONTRAR LIVRO\n\n");
                    }
                op = 4;
                break;

            case 4:
                op = 4;
                break;

            default :
                printf("\n\n\t[INFO] OPCAO INEXISTENTE\n");
        }

    }while(op != 4);

}

int procurar_livro_titulo(){
    FILE *pont_arq;
    Tlivro livro;
    char nome_livro[60];
    int aux = 0;

    if(!(pont_arq = fopen("biblioteca.txt", "r"))){
        printf("\n\n\t[INFO]Erro na abertura do arquivo!\n");
        return 0;
    }

    printf("\n\tDigite o nome do livro que deseja procurar: ");
    fgets(nome_livro, 60, stdin);
    strlwr (nome_livro);

    while(!feof(pont_arq)){
        fgets(livro.titulo, 60, pont_arq);
        fgets(livro.autor, 40, pont_arq);
        fgets(livro.editora, 30, pont_arq);
        fscanf(pont_arq, "%d", &livro.ano);
        fscanf(pont_arq, "%d", &livro.exclusao_logica);
        strlwr (livro.titulo);

        if(livro.exclusao_logica == 0 ){
            if(strncmp(livro.titulo, nome_livro, (strlen(nome_livro)-1)) == 0){
                printf("\n\tTitulo: %s\tAutor: %s\tEditor: %s\tAno: %d\n", livro.titulo, livro.autor, livro.editora, livro.ano);
                aux = 1;
            }
        }
    }

    fclose(pont_arq);
    if(aux == 0)return 0;
    return 1;
}

int procurar_livro_autor(){
    FILE *pont_arq;
    Tlivro livro;
    char nome_autor[40];
    int aux = 0;

    if(!(pont_arq = fopen("biblioteca.txt", "r"))){
        printf("\n\n\t[INFO]Erro na abertura do arquivo!\n");
        return 0;
    }

    printf("\n\tDigite o nome do autor que deseja procurar: ");
    fgets(nome_autor, 40, stdin);
    strlwr (nome_autor);

    while(!feof(pont_arq)){
        fgets(livro.titulo, 60, pont_arq);
        fgets(livro.autor, 40, pont_arq);
        fgets(livro.editora, 30, pont_arq);
        fscanf(pont_arq, "%d", &livro.ano);
        fscanf(pont_arq, "%d", &livro.exclusao_logica);
        strlwr (livro.autor);

        if(livro.exclusao_logica == 0){
            if(strncmp(livro.autor, nome_autor, (strlen(nome_autor)-1)) == 0){
                printf("\n\tTitulo: %s\tAutor: %s\tEditor: %s\tAno: %d\n", livro.titulo, livro.autor, livro.editora, livro.ano);
                aux = 1;
            }
        }
    }

    fclose(pont_arq);
    if(aux == 0)return 0;
    return 1;
}

int procurar_livro_ano(){
    FILE *pont_arq;
    Tlivro livro;
    int ano;
    int aux = 0;

    if(!(pont_arq = fopen("biblioteca.txt", "r"))){
        printf("\n\n\t[INFO]Erro na abertura do arquivo!\n");
        return 0;
    }

    printf("\n\tDigite o ano do livro que deseja procurar: ");
    scanf("%d", &ano);

    while(!feof(pont_arq)){
        fgets(livro.titulo, 60, pont_arq);
        fgets(livro.autor, 40, pont_arq);
        fgets(livro.editora, 30, pont_arq);
        fscanf(pont_arq, "%d", &livro.ano);
        fscanf(pont_arq, "%d", &livro.exclusao_logica);
        strlwr (livro.autor);

        if(livro.exclusao_logica == 0){
            if(ano == livro.ano){
                printf("\n\tTitulo: %s\tAutor: %s\tEditor: %s\tAno: %d\n", livro.titulo, livro.autor, livro.editora, livro.ano);
                aux = 1;
            }
        }
    }

    fclose(pont_arq);
    if(aux == 0)return 0;
    return 1;
}

int busca_registro(){
    int achou = -1, posicao = 0;
    FILE *pont_arq;
    Tlivro livro;
    char nome_livro[60];

    if(!(pont_arq = fopen("biblioteca.txt", "r"))){
        printf("\n\n\t[INFO]Erro na abertura do arquivo!\n");
        return 0;
    }

    printf("\t Digite o nome do livro que deseja excluir");
    fgets(nome_livro, 60, stdin);

    rewind(pont_arq);

    while((!feof(pont_arq))&&(achou==-1)){
        fgets(livro.titulo, 60, pont_arq);
        fgets(livro.autor, 40, pont_arq);
        fgets(livro.editora, 30, pont_arq);
        fscanf(pont_arq, "%d", &livro.ano);
        fscanf(pont_arq, "%d", &livro.exclusao_logica);

        if(!feof(pont_arq)){
            if(strncmp(livro.autor, nome_livro, (strlen(livro.autor))) == 0){
                achou = 1;
            }else{
                posicao++;
            }
        }else{
            posicao = -1;
        }
    }

    if(achou == -1){
        posicao = -1;
    }

    fclose(pont_arq);
    return posicao;
}


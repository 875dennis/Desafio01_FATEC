//Grupo C05 - Alunos: Dennis Almeida, Lucas do Nascimento, Tatiana Gonçalves

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


char nome_musica [3] [30];
char nome_autor [3] [20];

main()
{
    setlocale(LC_ALL,"");

    int opcao;

    for( ; ; )
    {
        printf("1 - Incluir dados\n");
        printf("2 - Lista de dados\n");
        printf("3 - Pesquisar música\n");
        printf("4 - Pesquisar autor pela primeira letra\n");
        printf("5 - Altera dados\n");
        printf("6 - Exclui dados\n");
        printf("7 - Sair\n");
        printf("\nEscolha uma das opcões do menu acima: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao)
        {
            case 1:
                entrada();
                break;
            case 2:
                lista();
                break;
            case 3:
                pesquisaMusica();
                break;
            case 4:
                pesquisaAutor();
                break;
            case 5:
                alterarDado();
                break;
            case 6:
                excluir();
                break;
            case 7:
                sair();
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
        printf("\n");
    }
}

int entrada()
{
    printf("\nCadastro de musica:\n");
    FILE *arq;

    arq = fopen("DF01N2.txt","wt");
    if(arq == NULL)
    {
        printf("Erro!\n");
        exit(1);
    }

    for(int i=0; i<3; i++)
    {
        printf("\nInsira uma música: ");
        scanf("%s", &nome_musica[i][0]);
        getchar();
    }

    for(int i=0; i<3; i++)
    {
        printf("\nInsira um autor: ");
        scanf("%s", &nome_autor[i][0]);
        getchar();
    }

    fwrite(nome_musica,sizeof(nome_musica),1,arq);
    fwrite(nome_autor,sizeof(nome_autor),1,arq);
    fclose(arq);
}

int lista()
{
    printf("\Músicas e autores cadastrados:\n");
    FILE *arq;

    arq = fopen("DF01N2.txt","r");
    if(arq == NULL)
    {
        printf("Erro!\n");
        exit(1);
    }

    fread(nome_musica,sizeof(nome_musica),1,arq);
    fread(&nome_autor,sizeof(nome_autor),1,arq);
    fclose(arq);

    for(int i=0; i<3; i++)
    {
        if(nome_musica[i][0] != '0')
        {
            printf("\nMúsica: %s\n", nome_musica[i]);
            printf("Autor: %s\n", nome_autor[i]);
        }


    }
    printf("\n");

}

int pesquisaMusica()
{

    FILE *arq;
    int x, y, cont=0;
    char musica[30];

    printf("\nDigite uma música a ser procurada: ");
    scanf("%s", &musica[0]);
    getchar();

    arq = fopen("DF01N2.txt","r");
    if(arq == NULL)
    {
        printf("Erro!\n");
        exit(1);
    }

    fread(nome_musica,sizeof(nome_musica),1,arq);

    for(x=0; x<3; x++)
    {
        for(y=0; musica[y] != '\0'; y++)
        {
            if(musica[y] != nome_musica[x][y])
                break;
        }

        if(musica[y] == '\0' && nome_musica[x][y] == '\0')
        {
            printf("\nRegistro Encontrado!");
            printf("\nMúsica: %s\n", nome_musica[x]);
            return x;
        }
        else
        {
            cont++;
        }

    }
    fclose(arq);

    if(cont==3)
    {
        printf("Registro nao encontrado!\n");
        fclose(arq);
        return -1;
    }
}


int pesquisaAutor()
{

    char letra;
    int x, y, cont=0;

    FILE *arq;

    arq = fopen("DF01N2.txt","r");
    if(arq == NULL)
    {
        printf("Erro!\n");
        exit(1);
    }

    printf("\nDigite uma letra para realizar a pesquisa do autor: ");
    scanf("%c",&letra);
    getchar();

    fread(nome_musica,sizeof(nome_musica),1,arq);
    fread(nome_autor,sizeof(nome_autor),1,arq);

    for(x=0; x<3; x++)
    {
        {
            if(letra == nome_autor[x][0])
            {
            printf("\nRegistro Encontrado!");
            printf("\nMúsica: %s\n", nome_musica[x]);
            printf("\Autor: %s\n", nome_autor[x]);
            cont=1;
            return x;
            }
        }
    }
    fclose(arq);

    if(cont!=1)
    {
        printf("Registro não encontrado!\n");
    }

}


int alterarDado()
{
    FILE *arq;

    int registro;
    int x, y, cont=0;
    char musica[30];

    printf("\nDigite uma música a ser alterada: ");
    scanf("%s", &musica[0]);
    getchar();

    arq = fopen("DF01N2.txt","w");
    if(arq == NULL)
    {
        printf("Erro!\n");
        exit(1);
    }

    fread(nome_musica,sizeof(nome_musica),1,arq);

    for(x=0; x<3; x++)
    {
        for(y=0; musica[y] != '\0'; y++)

        {
            if(musica[y] != nome_musica[x][y])
                break;
        }

        if(musica[y] == '\0' && nome_musica[x][y] == '\0')
        {
            printf("\nRegistro Encontrado!");
            printf("\nInsira os dados para alterar:\n");
            printf("\nInsira uma nova música: ");
            scanf("%s", &nome_musica[x]);
            printf("\nInsira um novo autor: ");
            scanf("%s", &nome_autor[x]);

        }
        else
        {
            cont++;
        }

    }

    fwrite(nome_musica,sizeof(nome_musica),1,arq);
    fwrite(nome_autor,sizeof(nome_autor),1,arq);
    fclose(arq);
}

void excluir()
{
    FILE *arq;

    int registro, encontrado=-1;
    int x, y;
    char musica[30];
    char excluir;

    printf("\nDigite uma música a ser excluida: ");
    scanf("%s", &musica[0]);
    getchar();

    if(arq == NULL)
    {
        printf("Erro!\n");
        exit(1);
    }

    for(x=0; x<3; x++)
    {
        for(y=0; musica[y] != '\0'; y++)
        {
            if(musica[y] != nome_musica[x][y])
            {
             encontrado=0;
                break;
            }

        }
        if(encontrado == 0)
        {
            encontrado=-1;
            continue;
        }
        else
        {
            printf("\nRegistro Encontrado!");
            printf("\nDeseja excluir este registro? S ou s = [SIM] Outro caracter [NAO]\n");
            scanf("%c", &excluir);
        }
        if(excluir == 's' || excluir == 'S')
                {
                   nome_musica[x][0]='0';
                }

    }
    arq = fopen("DF01N2.txt","w");
    fwrite(nome_musica,sizeof(nome_musica),1,arq);
    fwrite(nome_autor,sizeof(nome_autor),1,arq);
    fclose(arq);
}

int sair()
{
    exit(0);
}


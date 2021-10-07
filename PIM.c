#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

//Declaração das Estruturas a serem utilizadas
typedef struct enderecoStruct
{
char numero[6];
char rua[40];
char cidade[20];
char estado[20];
char pais[20];
} Endereco;

typedef struct CadastroPessoaStruct
{
char nome[40];
char segredo[12];
char telefone[11];
char modalidade[20];
Endereco end;
} Pessoa;

//Declaração das variáveis
int input = 0;
int qtdUsers;
int tamUsers;
char users_dir[] = "Users.bin";
Pessoa *users;
FILE *arquivo;

//Declaração dos Procedimentos e Funções a serem utilizados
void menuPrincipal();
void menuUsers();
void menuAlterarUser();
void removerQuebraLinha();
void inserirUser();
void alterarEndereco();
void alterarNome();
void alterarTelefone();
int removerUser();
Pessoa receberUser();
Endereco receberEndereco();

//Início do main
int main(int argc, char** argv)
{
    menuPrincipal();
    return 0;
}

void erro(char *nome_arquivo)
{
    printf("Nao foi possivel abrir o arquivo %s\n", nome_arquivo);
}

void sucesso()
{
    system("cls");
    printf ("Operacao realizada com sucesso!");
}

void menuPrincipal()
{
    do
    {
        printf("\n");
        system("color A");
        printf("\n\t   #######   ##       #### ##     ## ########    #######    #######  ##    ##  #######\n");
        printf("\t  ##     ##  ##        ##  ###   ### ##      #  ##     ##  ##     ##  #    #  ##     ##\n");
        printf("\t ##       ## ##        ##  #### #### ##      # ##       #  ##          #  #   ##\n");
        printf("\t ##       ## ##        ##  ## ### ## ########  ##           #######     ##     #######\n");
        printf("\t ##       ## ##        ##  ##     ## ##        ##       #         ##    ##            ##\n");
        printf("\t  ##     ##  ##        ##  ##     ## ##         ##     ##  ##     ##    ##    ##     ##\n");
        printf("\t   #######   ######## #### ##     ## ##          #######    #######    ####    #######\n\n");
        printf("\n");
        printf ("\t\t\t\tSeja Bem-vindo!\n");
        printf ("\t\t\t===============================\n");
        printf ("\t\t\t|\t                      |\n");
        printf("\t\t\t|\t 1 - Atleta           |\n");
        printf("\t\t\t|\t 2 - Medico           |\n");
        printf("\t\t\t|\t 3 - Funcionario      |\n");
        printf("\t\t\t|\t 4 - Voluntario       |\n");
        printf("\t\t\t|\t 0 - Sair             |\n");
        printf ("\t\t\t|\t                      |\n");
        printf ("\t\t\t===============================\n");
        printf ("\n\n");
        printf("\t\t\tPor favor, selecione uma opcao: ");
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        switch(input)
        {
        case 1:
            menuUsers();
            break;
        case 2:
            menuUsers();
            break;
        case 3:
            menuUsers();
            break;
        case 4:
            menuUsers();
            break;
        case 0:
            exit(EXIT_SUCCESS);
        default:
            printf ("\n\t\t\tOpcao invalida!\n\n");
            fflush(stdin);
        }
    }
    while(input != 0);
    system("cls");
}

void menuUsers()
{
    do
    {
        printf("\n");
        printf ("\t\t\t\tArea de cadastro\n");
        printf ("\t\t\t===============================\n");
        printf ("\t\t\t|\t                      |\n");
        printf("\t\t\t|    1 - Cadastrar            |\n");
        printf("\t\t\t|    2 - Alterar Cadastro     |\n");
        printf("\t\t\t|    3 - Excluir Cadastro     |\n");
        printf("\t\t\t|    4 - Menu Principal       |\n");
        printf("\t\t\t|    0 - Sair                 |\n");
        printf ("\t\t\t|                             |\n");
        printf ("\t\t\t===============================\n");
        printf ("\n\n");
        printf("\t\t\tPor favor, selecione uma opcao: ");
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        switch(input)
        {
        case 1:
            fflush(stdin);
            inserirUser(receberUser());
            break;
        case 2:
            menuAlterarUser();
            break;
        case 3:
            removerUser(qtdUsers, users_dir);
            break;
        case 4:
            menuPrincipal();
            break;
        case 0:
            exit(EXIT_SUCCESS);
        default:
            printf ("\n\t\t\tOpcao invalida!\n\n");
            fflush(stdin);
        }
    }
    while(input != 0);
    system("cls");
}

void menuAlterarUser()
{
    do
    {
        printf("\n");
        printf ("\t\t\t\tGerenciar Dados\n");
        printf ("\t\t\t===============================\n");
        printf ("\t\t\t|\t                      |\n");
        printf("\t\t\t|    1 - Alterar Nome         |\n");
        printf("\t\t\t|    2 - Alterar Telefone     |\n");
        printf("\t\t\t|    3 - Alterar Endereco     |\n");
        printf("\t\t\t|    4 - Menu Principal       |\n");
        printf("\t\t\t|    0 - Sair                 |\n");
        printf ("\t\t\t|                             |\n");
        printf ("\t\t\t===============================\n");
        printf ("\n\n");
        printf("\t\t\tPor favor, selecione uma opcao: ");
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        switch(input)
        {
        case 1:
            alterarNome();
            break;
        case 2:
            alterarTelefone();
            break;
        case 3:
            alterarEndereco();
            break;
        case 4:
            menuPrincipal();
            break;
        case 0:
            exit(EXIT_SUCCESS);
        default:
            printf ("\n\t\t\tOpcao invalida!\n\n");
            fflush(stdin);
        }
    }
    while(input != 0);
    system("cls");
}

void removerQuebraLinha(char *string)
{
    if(string != NULL && strlen(string) > 0)
    {
        short tamanho = strlen(string);
        if(string[tamanho-1] == '\n')
        {
            string[tamanho-1] = '\0';
        }
    }
}

void receberString(char *string_destino, int quantidade_caracteres)
{
    fgets(string_destino, quantidade_caracteres, stdin);
    removerQuebraLinha(string_destino);
}

Pessoa receberUser()
{
    Pessoa p;

    printf("Nome: ");
    receberString(p.nome, 39);
    printf ("Telefone: ");
    receberString(p.telefone, 12);
    fflush(stdin);
    printf ("Informe sua modalidade: ");
    receberString(p.modalidade, 20);
    fflush(stdin);
    printf ("Crie uma Senha: ");
    receberString(p.segredo, 13);
    fflush(stdin);
    
    p.end = receberEndereco();

    sucesso();
    return p;
}

Endereco receberEndereco()
{
    Endereco e;

    printf ("Rua: ");
    receberString(e.rua, 39);
    fflush(stdin);
    printf ("Numero: ");
    receberString(e.numero, 5);
    fflush(stdin);
    printf ("Cidade: ");
    receberString(e.cidade, 20);
    printf ("Estado: ");
    receberString(e.estado, 20);
    printf ("Digite o nome do pais pelo qual ira competir: ");
    receberString(e.pais, 20);

    sucesso();
    return e;
}

void inserirUser(Pessoa p)
{
    if(qtdUsers == tamUsers)
    {
        tamUsers *= 1.5;
        users = realloc(users, tamUsers*sizeof(Pessoa));
    }
    users[qtdUsers] = p;
    qtdUsers++;
}    

void alterarNome()
{
    int i;
    char senha[11], nome[40];
    printf ("Digite a senha do usuario a ter o nome alterado: ");
    fgets(senha, 11, stdin);
    printf ("Digite o novo nome: ");
    fgets(nome, 39, stdin);
    for (i=0; i < qtdUsers; i++)
    {
        if(strcmp(users[i].segredo, senha) == 0)
        {
            strcpy(users[i].nome, nome);
            break;
        }
    }
}

void alterarTelefone()
{
    int i;
    char senha[11], fone[11];
    printf ("Digite a senha do usuario a ter o telefone alterado: ");
    fgets(senha, 11, stdin);
    printf ("Digite o novo numero: ");
    fgets(fone, 11, stdin);
    for (i=0; i < qtdUsers; i++)
    {
        if(strcmp(users[i].segredo, senha) == 0)
        {
            strcpy(users[i].telefone, fone);
            break;
        }
    }
}

void alterarEndereco()
{
    int i;
    char senha[12];
    printf ("Digite a senha do usuario a ter o endereco alterado: ");
    fgets(senha, 11, stdin);
    Endereco e;
    e = receberEndereco();
    for (i=0; i < qtdUsers; i++)
    {
        if(strcmp(users[i].segredo, senha) == 0)
        {
            users[i].end = e;
            break;
        }
    }
}


int removerUser(int qtd, char *dir)
{
int i, senha, sucess = 0;
printf("Digite a senha do usuario que deseja remover: ");
scanf ("%d", &senha);
for (i=0; i < qtd; i++)
{
    if((users[i].segredo - senha) == 0)
    {
        while(i < qtd-1)
        {
            users[i] = users[i+1];
            i++;
        }
        qtd--;
        sucess = 1;
        break;
    }
    else
    {
        erro(dir);
    }
}
return sucess;
}
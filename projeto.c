#include<stdio.h>
#include <iostream>
#include <exception>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define MAX 50
#define FILE_PA "Passageiros.txt"
#define FILE_PE "Passagens.txt"
#define FILE_CO "Compras.txt"

static int _numPassageiros = 0;              // numero total no sistema
static int _numPassagens = 0;
static int _numCompras = 0;

// Typedef's------------------------------//
typedef struct {
    int _idPassageiro;          //chave dupla id e cpf
    char _nome[MAX],
         _cpf[15];
} Passageiro;

typedef struct {
    int _idPassagem;            //chave unica 
    char _origem[MAX],
         _destino[MAX],
         _data[11],             // Formato: DD/MM/AAAA
         _horario[6];           // Formato: HH:MM
    float _preco,
          _assentosDisponiveis;
} Passagem;

typedef struct {
    int _idCompra,              //chave unica      
        _assento;
    Passageiro _passageiro;  
    Passagem _passagem;                 
} Compra;
//----------------------------------------//

// crud passageiros
void criar_Passageiro (Passageiro passageiro[]);
void salvar_Passageiros(Passageiro passageiro[], int num);
int carregar_Passageiros (Passageiro passageiro[]);
void listar_Passageiros (const Passageiro passageiro[]);
void buscar_Passageiro (const Passageiro passageiro[]);
void atualizar_Passageiro (Passageiro passageiro[]);
int apagar_Passageiro (Passageiro passageiro[]);

// crud passagens
int carregar_Passagem (Passagem passagem[]);
void criar_Passagem (Passagem passagem[]);
void listar_Passagens (const Passagem passagem[]);
void buscar_Passagem (const Passagem passagem[]);
void atualizar_Passagem (Passagem passagem[]);
int apagar_Passagem (Passagem passagem[]);

// crud compras
int carregar_Compra (Compra compra[]);
void criar_Compra(Compra compra[]);
void listar_Compras (const Compra compra[]);
void buscar_Compra (const Compra compra[]);
void atualizar_Compra (Compra compra[]);
int apagar_Compra (Compra compra[]);

// funcoes auxiliares
void menu(Passageiro passageiro[]);
void limparTela();
void pausarTela();
void limparBuffer();
void setLocal();

/*-------------------------*\ BLOCO MAIN /*--------------------------------*/
int main(){
    setLocal();
    Passageiro passageiros[MAX];
    _numPassageiros = carregar_Passageiros(passageiros);

    menu(passageiros);

    return 0;
}

/*-------------------------*\ FUNCOES AUXILIARES /*--------------------------------*/
void limparBuffer() {setbuf (stdin, NULL);}
void limparTela() {system ("cls");}
void pausarTela() {system("pause");}
void setLocal() {setlocale(LC_ALL, "pt_BR.UTF-8");}

void menu(Passageiro passageiro[]){
    int choice;
    do{
        limparTela();
            
        printf ("\n|---------------------->| SISTEMA COMPRA DE PASSAGENS |<----------------------|\n");
        printf ("|Bem-vindo(a) aos nossos serviços, favor inserir o atendimento que deseja:\n");
        putchar ('\n');
        
        printf ("|-----------> |MENU PASSAGEIRO| <-----------|\n");
        printf ("|01|-> Para cadastrar um passageiro.        |\n");
        printf ("|02|-> Para listar todos os passageiros.    |\n");
        printf ("|03|-> Para buscar um passageiro.           |\n");
        printf ("|04|-> Para atualizar um passageiro.        |\n");
        printf ("|05|-> Para apagar um passageiro.           |\n");
        printf ("|-------------------------------------------|\n");
        
        printf ("\n|----------------> |SAIR| <-----------------|\n");
        printf ("|06|-> Para salvar as informacoes e sair.   |\n");
        printf ("|-------------------------------------------|\n");
        printf ("|Sua escolha: ");
        scanf ("%d", &choice);
        limparBuffer();

        switch(choice){
            case 1:
                criar_Passageiro(passageiro);
                pausarTela();
                break;
            case 2:
                listar_Passageiros(passageiro);
                pausarTela();
                break;
            case 3:
                buscar_Passageiro(passageiro);
                pausarTela();
                break;
            case 4:
                atualizar_Passageiro(passageiro);
                pausarTela();
                break;
            case 5:
                apagar_Passageiro(passageiro);
                pausarTela();
                break;
            case 6:
                limparTela();
                printf("|Obrigado por utilizar nossos servicos. Volte sempre! ");
                pausarTela();
                break;
            default:
                printf("|Opção inválida! Por favor, escolha uma opção entre 1 e 6.\n");
                pausarTela();
                break;
        }
    } while(choice != 6);  // Continua até o usuário escolher sair (opção 6)
}


/*-------------------------*\ FUNCOES PASSAGEIROS /*--------------------------------*/
void criar_Passageiro(Passageiro passageiro[]) {
    limparBuffer();
    limparTela();

    printf("|----------> |CADASTRO PASSAGEIRO| <-----------|\n");

    if (_numPassageiros < MAX) {
        passageiro[_numPassageiros]._idPassageiro = _numPassageiros;  

        printf("|Nome: ");
        fgets(passageiro[_numPassageiros]._nome, sizeof(passageiro[_numPassageiros]._nome), stdin);
        passageiro[_numPassageiros]._nome[strcspn(passageiro[_numPassageiros]._nome, "\n")] = 0;
        limparBuffer();

        printf("|CPF: ");
        fgets(passageiro[_numPassageiros]._cpf, sizeof(passageiro[_numPassageiros]._cpf), stdin);
        passageiro[_numPassageiros]._cpf[strcspn(passageiro[_numPassageiros]._cpf, "\n")] = 0;
        limparBuffer();
        
        // Verificar CPF duplicado
        bool cpfDuplicado = false;
        for(int i = 0; i < _numPassageiros; i++) {
            if(strcmp(passageiro[_numPassageiros]._cpf, passageiro[i]._cpf) == 0) {
                printf("|O passageiro nao pode ser cadastrado pois o CPF %s ja existe no sistema.\n", 
                       passageiro[_numPassageiros]._cpf);
                cpfDuplicado = true;
                break;
            }
        }
        
        if (!cpfDuplicado) {
            _numPassageiros++;
            salvar_Passageiros(passageiro, _numPassageiros);
            printf("\n|Passageiro cadastrado com sucesso!\n");
            printf("|Numero total de passageiros: %d \n \n", _numPassageiros);
        }
    } else {
        printf("|Nao ha espaco suficiente em Passageiros.txt para armazenar o passageiro.\n");
    }
}


void salvar_Passageiros(Passageiro passageiro[], int num) {
    FILE *fp = fopen(FILE_PA, "w"); // abre em modo escrita (substitui o arquivo)
    
    if (!fp) {
        printf("|Erro ao abrir arquivo para salvar passageiros.\n");
        return;
    }
    
    for (int i = 0; i < num; i++) {
        fprintf(fp, "%d %s %s\n", 
                passageiro[i]._idPassageiro, 
                passageiro[i]._nome, 
                passageiro[i]._cpf);
    }
    
    fclose(fp);
}

int carregar_Passageiros(Passageiro passageiro[]) {
    int i = 0;
    FILE *fp = fopen(FILE_PA, "r"); 

    if (!fp) {
        fp = fopen(FILE_PA, "w");
        if (!fp) {
            throw std::runtime_error("|Erro ao criar arquivo de passageiros: " + std::string(FILE_PA));
        }
        fclose(fp);
        _numPassageiros = 0;
        return 0;
    }
    
    try {
        while (fscanf(fp, "%d %49s %14s", 
                      &passageiro[i]._idPassageiro, 
                      passageiro[i]._nome, 
                      passageiro[i]._cpf) == 3) {
            i++;
            if (i >= MAX) { 
                break;
            }
        }
        fclose(fp);
        _numPassageiros = i;
        return _numPassageiros;

    } catch (const std::exception &e) {
        std::cerr << "|Exceção capturada: " << e.what() << std::endl;
        if (fp) {
            fclose(fp);
        }
        return -1;  
    }
}

void listar_Passageiros (const Passageiro passageiro[]){
	limparTela();

	printf ("|----------> |LISTA PASSAGEIROS| <-----------|\n");
    if (_numPassageiros == 0) {
        printf("\n|Nenhum passageiro cadastrado no sistema.\n");
        return;
    }
    printf("|Passageiros cadastrados: %d \n", _numPassageiros);
    putchar('\n');
	for (int i=0; i<_numPassageiros; i++){
		printf ("|-----------> |Passageiro: %d| <-----------|\n", i);
        printf ("|Id: %d\n", passageiro[i]._idPassageiro);
		printf ("|Nome: %s\n", passageiro[i]._nome);
		printf ("|CPF: %s\n", passageiro[i]._cpf);
		printf ("|-----------------------------------------|\n");
		putchar('\n');
    }
}

void buscar_Passageiro(const Passageiro passageiro[]) {
    char busca[50]; // Tamanho adequado para um CPF
    bool encontrado = false; // Flag para verificar se encontrou algum passageiro
    
    limparBuffer();
    limparTela();
    
    printf("|----------> |BUSCA DE PASSAGEIRO| <-----------|\n");
    printf("|Insira o CPF do passageiro: ");
    fgets(busca, sizeof(busca), stdin);
    
    busca[strcspn(busca, "\n")] = 0;
    
    putchar('\n');
    for (int i = 0; i < _numPassageiros; i++) {
        if (strcmp(passageiro[i]._cpf, busca) == 0) {
            printf("\n|O passageiro %d condiz com a busca. \n", i);
            printf("|-----------> |PASSAGEIRO %d| <-----------|\n", i);
            printf("|ID|-> %d\n", passageiro[i]._idPassageiro);
            printf("|NOME|-> %s\n", passageiro[i]._nome);
            printf("|CPF|-> %s\n", passageiro[i]._cpf);
            printf("|--------------------------------------|\n");
            encontrado = true;
            break; 
        }
    }
    if (!encontrado) {
        printf("|Nenhum passageiro encontrado com o CPF: %s\n", busca);
    }
}

void atualizar_Passageiro(Passageiro passageiro[]) {
    int choice;
    int indice = -1;
    char novoNome[MAX];
    char novoCpf[15];
    
    listar_Passageiros(passageiro);
    printf("|----------> |ATUALIZAR PASSAGEIRO| <-----------|\n");
    
    // Verifica se há passageiros cadastrados
    if (_numPassageiros == 0) {
        printf("\n|Nenhum passageiro cadastrado no sistema.\n");
        return;
    }
    
    // Busca o passageiro pelo CPF
    char busca[50];
    limparBuffer();
    
    printf("|Insira o CPF do passageiro: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = 0;
    
    // Encontra o índice do passageiro
    for (int i = 0; i < _numPassageiros; i++) {
        if (strcmp(passageiro[i]._cpf, busca) == 0) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        printf("\n|Passageiro não encontrado com o CPF: %s\n", busca);
        return;
    }
    
    // Exibe os dados atuais do passageiro
    pausarTela();
    limparTela();
    printf("\n|Passageiro encontrado: \n");
    printf("|-----------> |PASSAGEIRO %d| <-----------|\n", indice);
    printf("|Id: %d\n", passageiro[indice]._idPassageiro);
    printf("|Nome: %s\n", passageiro[indice]._nome);
    printf("|CPF: %s\n", passageiro[indice]._cpf);
    printf("|-----------------------------------------|\n");
    
    do {
        printf("\n|---------------------------------------|\n");
        printf("|1|-> NOME\n");
        printf("|2|-> CPF\n");
        printf("|---------------------------------------|\n");
        printf("\n|Insira o número da informação que deseja alterar: ");
        scanf("%d", &choice);
        limparBuffer();
    } while (choice < 1 || choice > 2);
    
    switch (choice) {
        case 1:
            printf("|Insira o novo nome: ");
            fgets(novoNome, sizeof(novoNome), stdin);
            novoNome[strcspn(novoNome, "\n")] = 0;
            strcpy(passageiro[indice]._nome, novoNome);
            break;
        case 2:
            printf("|Insira o novo CPF: ");
            fgets(novoCpf, sizeof(novoCpf), stdin);
            novoCpf[strcspn(novoCpf, "\n")] = 0;
            strcpy(passageiro[indice]._cpf, novoCpf);
            break;
    }
    

    salvar_Passageiros(passageiro, _numPassageiros);
    printf("\n|Informações atualizadas!\n");

    printf("|-----------> |PASSAGEIRO %d| <-----------|\n", indice);
    printf("|Id: %d\n", passageiro[indice]._idPassageiro);
    printf("|Nome: %s\n", passageiro[indice]._nome);
    printf("|CPF: %s\n", passageiro[indice]._cpf);
    printf("|-----------------------------------------|\n");
    
}

int apagar_Passageiro(Passageiro passageiro[]) {
    listar_Passageiros(passageiro);
    if(_numPassageiros == 0){
        printf("|Impossivel acessar funcao.\n");
        return 0;
    }
    int apagar;
    bool encontrado = false;

    printf("|-----------> |APAGAR PASSAGEIRO| <------------|\n");
    printf("|Insira o ID do passageiro que deseja apagar do sistema: ");
    scanf("%d", &apagar);
    limparBuffer();  // Limpar o buffer após o scanf

    for (int i = 0; i < _numPassageiros; i++) {
        if (passageiro[i]._idPassageiro == apagar) {
            encontrado = true;
            
            // Deslocar todos os elementos seguintes uma posição para trás
            for (int u = i; u < _numPassageiros - 1; u++) {
                strcpy(passageiro[u]._nome, passageiro[u+1]._nome);
                strcpy(passageiro[u]._cpf, passageiro[u+1]._cpf);
                // Não copiamos o ID, vamos recalcular abaixo
            }
            
            // Decrementar o número de passageiros
            _numPassageiros--;
            
            // Atualizar todos os IDs para serem sequenciais
            for (int j = 0; j < _numPassageiros; j++) {
                passageiro[j]._idPassageiro = j;
            }
            
            salvar_Passageiros(passageiro, _numPassageiros);
            printf("|Passageiro de ID %d removido com sucesso!\n", apagar);
            break;  // Sai do loop após encontrar e remover
        }
    }
    
    if (!encontrado) {
        printf("|Passageiro de ID %d não encontrado!\n", apagar);
    }
    
    return _numPassageiros;
}

#include<stdio.h>
#include<iostream>
#include<exception>
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
    float _preco;
    int _assentosDisponiveis;
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
void salvar_Passageiros(Passageiro passageiro[]);
int carregar_Passageiros (Passageiro passageiro[]);
void listar_Passageiros(const Passageiro passageiro[]);
void buscar_Passageiro(const Passageiro passageiro[]);
void atualizar_Passageiro(Passageiro passageiro[]);
int apagar_Passageiro (Passageiro passageiro[]);

// crud passagens
void criar_Passagem (Passagem passagem[]);
void salvar_Passagens(Passagem passagem[]);
int carregar_Passagem (Passagem passagem[]);
void listar_Passagens (const Passagem passagem[]);
void buscar_Passagem (const Passagem passagem[]);
void atualizar_Passagem (Passagem passagem[]);
int apagar_Passagem (Passagem passagem[]);

// crud compras
void criar_Compra(Compra compra[]);
void salvar_Compra(Compra compra[]);
int carregar_Compra (Compra compra[]);
void listar_Compras(const Compra compra[]);
void buscar_Compra(const Compra compra[]);
void atualizar_Compra(Compra compra[]);
int apagar_Compra(Compra compra[]);

// funcoes auxiliares
void menu(Passageiro passageiro[], Passagem passagem[]);
void limparTela();
void pausarTela();
void limparBuffer();
void setLocal();

/*-------------------------*\ BLOCO MAIN /*--------------------------------*/
int main(){
    setLocal();
    Passageiro passageiros[MAX];
    Passagem passagens[MAX];
    _numPassagens = carregar_Passagem(passagens);
    _numPassageiros = carregar_Passageiros(passageiros);

    menu(passageiros, passagens);


    return 0;
}

/*-------------------------*\ FUNCOES AUXILIARES /*--------------------------------*/
void limparBuffer() {setbuf (stdin, NULL);}
void limparTela() {system ("cls");}
void pausarTela() {system("pause");}
void setLocal() {setlocale(LC_ALL, "pt_BR.UTF-8");}

void menu(Passageiro passageiro[], Passagem passagem[]){
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
        printf ("|------------> |MENU PASSAGEM| <------------|\n");
        printf ("|06|-> Para cadastrar uma passagem.         |\n");
        printf ("|07|-> Para listar todos as passagens.      |\n");
        printf ("|08|-> Para buscar uma passagem.            |\n");
        printf ("|09|-> Para atualizar uma passagem.         |\n");
        printf ("|10|-> Para apagar uma passagem.            |\n");
        printf ("|-------------------------------------------|\n");
        
        printf ("\n|----------------> |SAIR| <-----------------|\n");
        printf ("|11|-> Para salvar as informacoes e sair.   |\n");
        printf ("|-------------------------------------------|\n");
        printf ("|Sua escolha: ");
        scanf ("%d", &choice);
        limparBuffer();

        switch(choice){
            //------------------------ PASSAGEIRO ------------------------//
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
            //------------------------- PASSAGEM -------------------------//
            case 6:
                criar_Passagem(passagem);
                pausarTela();
                break;
            case 7:
                listar_Passagens(passagem);
                pausarTela();
                break;
            case 8:
                buscar_Passagem(passagem);
                pausarTela();
                break;
            case 9:
                atualizar_Passagem(passagem);
                pausarTela();
                break;
            case 10:
                apagar_Passagem(passagem);
                pausarTela();
                break;
            //-------------------------- COMPRA --------------------------//

            //--------------------------- SAIR ---------------------------//
            case 11:
                limparTela();
                printf("|Obrigado por utilizar nossos servicos. Volte sempre! ");
                pausarTela();
                break;
            default:
                printf("|Opção inválida! Por favor, escolha uma opção entre 1 e 6.\n");
                pausarTela();
                break;
        }
    } while(choice != 11);  // Continua até o usuário escolher sair (opção 6)
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
            salvar_Passageiros(passageiro);
            printf("\n|Passageiro cadastrado com sucesso!\n");
            printf("|Numero total de passageiros: %d \n \n", _numPassageiros);
        }
    } else {
        printf("|Nao ha espaco suficiente em Passageiros.txt para armazenar o passageiro.\n");
    }
}


void salvar_Passageiros(Passageiro passageiro[]) {
    FILE *fp = fopen(FILE_PA, "w"); // abre em modo escrita (substitui o arquivo)
    
    if (!fp) {
        printf("|Erro ao abrir arquivo para salvar passageiros.\n");
        return;
    }
    
    for (int i = 0; i < _numPassageiros; i++) {
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
    

    salvar_Passageiros(passageiro);
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
            
            for (int u = i; u < _numPassageiros - 1; u++) {
                strcpy(passageiro[u]._nome, passageiro[u+1]._nome);
                strcpy(passageiro[u]._cpf, passageiro[u+1]._cpf);
            }
        
            _numPassageiros--;
            
            // Atualizar todos os IDs para serem sequenciais
            for (int j = 0; j < _numPassageiros; j++) {
                passageiro[j]._idPassageiro = j;
            }
            
            salvar_Passageiros(passageiro);
            printf("|Passageiro de ID %d removido com sucesso!\n", apagar);
            break;  // Sai do loop após encontrar e remover
        }
    }
    if (!encontrado) {
        printf("|Passageiro de ID %d não encontrado!\n", apagar);
    }
    
    return _numPassageiros;
}

/*--------------------------*\ FUNCOES PASSAGEM /*---------------------------------*/
void criar_Passagem(Passagem passagem[]) {
    limparBuffer();
    limparTela();
        
    printf("|----------> |CADASTRO PASSAGEM| <-----------|\n");
        
    if (_numPassagens < MAX) {
        passagem[_numPassagens]._idPassagem = _numPassagens;  
        
        printf("|Origem: ");
        fgets(passagem[_numPassagens]._origem, sizeof(passagem[_numPassagens]._origem), stdin);
        passagem[_numPassagens]._origem[strcspn(passagem[_numPassagens]._origem, "\n")] = 0;
        limparBuffer();
        
        printf("|Destino: ");
        fgets(passagem[_numPassagens]._destino, sizeof(passagem[_numPassagens]._destino), stdin);
        passagem[_numPassagens]._destino[strcspn(passagem[_numPassagens]._destino, "\n")] = 0;
        limparBuffer();
        
        // Leitura da data com validação
        int dia, mes, ano;
        int dataValida = 0;
                
        while (!dataValida) {
            printf("|Data (DD/MM/AA): ");
            char inputData[20];
            fgets(inputData, sizeof(inputData), stdin);
                    
            if (sscanf(inputData, "%d/%d/%d", &dia, &mes, &ano) == 3) {
                // Validação básica da data
                if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 0 && ano <= 99) {
                    sprintf(passagem[_numPassagens]._data, "%02d/%02d/%02d", dia, mes, ano);
                    dataValida = 1;
                } else {
                    printf("Data inválida. Por favor, insira uma data válida.\n");
                }
            } else {
                printf("Formato inválido. Use DD/MM/AA.\n");
            }
            limparBuffer();
        }
        int hora, minuto;
        int horarioValido = 0;
                
        while (!horarioValido) {
            printf("|Horário (HH:MM): ");
            char inputHorario[20];
            fgets(inputHorario, sizeof(inputHorario), stdin);
                    
            if (sscanf(inputHorario, "%d:%d", &hora, &minuto) == 2) {
                // Validação do horário
                if (hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59) {
                    sprintf(passagem[_numPassagens]._horario, "%02d:%02d", hora, minuto);
                    horarioValido = 1;
                } else {
                    printf("Horário inválido. Por favor, insira um horário válido.\n");
                }
            } else {
                printf("Formato inválido. Use HH:MM.\n");
            }
            limparBuffer();
        }
                
        // Leitura do preço
        printf("|Preço (R$): ");
        scanf("%f", &passagem[_numPassagens]._preco);
        limparBuffer();
                
        // Leitura de assentos disponíveis
        printf("|Assentos disponíveis: ");
        scanf("%d", &passagem[_numPassagens]._assentosDisponiveis);
        limparBuffer();
                
        _numPassagens++;
        salvar_Passagens(passagem);
                
        printf("|Passagem cadastrada com sucesso!\n");
        printf("|Número total de passagens: %d\n\n", _numPassagens);

    } else {
        printf("|Não há espaço suficiente para armazenar a passagem.\n");
    }
}

void salvar_Passagens(Passagem passagem[]){
    FILE *fp = fopen(FILE_PE, "w"); // abre em modo escrita (substitui o arquivo)
    
    if (!fp) {
        printf("|Erro ao abrir arquivo para salvar passagens.\n");
        return;
    }
    
    for(int i=0; i< _numPassagens; i++){
        fprintf(fp, "%d %s %s %s %s %.2f %d",
                &passagem[i]._idPassagem,
                passagem[i]._origem,
                passagem[i]._destino,
                passagem[i]._data,
                passagem[i]._horario,
                passagem[i]._preco,
                passagem[i]._assentosDisponiveis
        );
    }
    fclose(fp);
}

int carregar_Passagem (Passagem passagem[]){
    int i = 0;
    FILE *fp = fopen(FILE_PE, "r"); 

    if (!fp) {
        fp = fopen(FILE_PE, "w");
        if (!fp) {
            throw std::runtime_error("|Erro ao criar arquivo de passagem: " + std::string(FILE_PE));
        }
        fclose(fp);
        _numPassagens = 0;
        return 0;
    }
    
    try {
        while (fscanf(fp, "%d %s %s %s %s %f %d",
            &passagem[i]._idPassagem,
            passagem[i]._origem,
            passagem[i]._destino,
            passagem[i]._data,
            passagem[i]._horario,
            &passagem[i]._preco,
            &passagem[i]._assentosDisponiveis) == 7) {
                i++;
                if (i >= MAX) { 
                    break;
                }
        }
        fclose(fp);
        _numPassagens = i;
        return _numPassagens;

    } catch (const std::exception &e) {
        std::cerr << "|Exceção capturada: " << e.what() << std::endl;
        if (fp) {
            fclose(fp);
        }
        return -1;  
    }
}

void listar_Passagens (const Passagem passagem[]){
    limparTela();

	printf ("|----------> |LISTA PASSAGENS| <-----------|\n");
    if (_numPassagens == 0) {
        printf("\n|Nenhuma passagem cadastrada no sistema.\n");
        return;
    }
    printf("|Passagens cadastradas: %d \n", _numPassagens);
    putchar('\n');
	for (int i=0; i<_numPassagens; i++){
		printf ("|-----------> |Passagem: %d| <-----------|\n", i);
        printf ("|Id: %d\n", passagem[i]._idPassagem);
		printf ("|Origem: %s\n", passagem[i]._origem);
		printf ("|Destino: %s\n", passagem[i]._destino);
        printf ("|Data: %s\n", passagem[i]._data);
        printf ("|Horario: %s\n", passagem[i]._horario);
        printf ("|Preco: %d\n", passagem[i]._preco);
        printf ("|Assentos disponiveis: %d\n", passagem[i]._assentosDisponiveis);
		printf ("|-----------------------------------------|\n");
		putchar('\n');
    }
}

void buscar_Passagem (const Passagem passagem[]){
    int busca;
    bool encontrado = false;
    
    limparBuffer();
    limparTela();
    
    printf("|----------> |BUSCA DE PASSAGEM| <-----------|\n");
    printf("|Insira o ID da passagem: ");
    scanf("%d", &busca);
    
    putchar('\n');
    for (int i = 0; i < _numPassagens; i++) {
        if (passagem[i]._idPassagem == busca) {
            printf ("|-----------> |Passagem: %d| <-----------|\n", i);
            printf ("|Id: %d\n", passagem[i]._idPassagem);
            printf ("|Origem: %s\n", passagem[i]._origem);
            printf ("|Destino: %s\n", passagem[i]._destino);
            printf ("|Data: %s\n", passagem[i]._data);
            printf ("|Horario: %s\n", passagem[i]._horario);
            printf ("|Preco: %d\n", passagem[i]._preco);
            printf ("|Assentos disponiveis: %d\n", passagem[i]._assentosDisponiveis);
            printf ("|-----------------------------------------|\n");
            encontrado = true;
            break; 
        }
    }
    if (!encontrado) {
        printf("|Nenhuma passagem encontrada com o ID: %d\n", busca);
    }
}

void atualizar_Passagem(Passagem passagem[]) {
    int choice;
    int indice = -1;
    char novaOrigem[MAX];
    char novoDestino[MAX];
    char novaData[11];
    char novoHorario[6];
    float novoPreco;
    int novosAssentos;
    
    listar_Passagens(passagem);
    printf("|----------> |ATUALIZAR PASSAGEM| <-----------|\n");
    
    if (_numPassagens == 0) {
        printf("\n|Nenhuma passagem cadastrada no sistema.\n");
        return;
    }
    
    int idBusca;
    limparBuffer();
    
    printf("|Insira o ID da passagem: ");
    scanf("%d", &idBusca);
    limparBuffer();
    
    // Encontra o índice da passagem
    for (int i = 0; i < _numPassagens; i++) {
        if (passagem[i]._idPassagem == idBusca) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        printf("\n|Passagem não encontrada com o ID: %d\n", idBusca);
        return;
    }
    
    // Exibe os dados atuais da passagem
    pausarTela();
    limparTela();
    printf("\n|Passagem encontrada: \n");
    printf("|-----------> |PASSAGEM %d| <-----------|\n", indice);
    printf("|ID: %d\n", passagem[indice]._idPassagem);
    printf("|Origem: %s\n", passagem[indice]._origem);
    printf("|Destino: %s\n", passagem[indice]._destino);
    printf("|Data: %s\n", passagem[indice]._data);
    printf("|Horário: %s\n", passagem[indice]._horario);
    printf("|Preço: R$ %.2f\n", passagem[indice]._preco);
    printf("|Assentos disponíveis: %d\n", passagem[indice]._assentosDisponiveis);
    printf("|-----------------------------------------|\n");
    
    do {
        printf("\n|---------------------------------------|\n");
        printf("|1|-> ORIGEM\n");
        printf("|2|-> DESTINO\n");
        printf("|3|-> DATA\n");
        printf("|4|-> HORÁRIO\n");
        printf("|5|-> PREÇO\n");
        printf("|6|-> ASSENTOS DISPONÍVEIS\n");
        printf("|---------------------------------------|\n");
        printf("\n|Insira o número da informação que deseja alterar: ");
        scanf("%d", &choice);
        limparBuffer();
    } while (choice < 1 || choice > 6);
    
    switch (choice) {
        case 1:
            printf("|Insira a nova origem: ");
            fgets(novaOrigem, sizeof(novaOrigem), stdin);
            novaOrigem[strcspn(novaOrigem, "\n")] = 0;
            strcpy(passagem[indice]._origem, novaOrigem);
            break;
        case 2:
            printf("|Insira o novo destino: ");
            fgets(novoDestino, sizeof(novoDestino), stdin);
            novoDestino[strcspn(novoDestino, "\n")] = 0;
            strcpy(passagem[indice]._destino, novoDestino);
            break;
        case 3:
            // Validação de data
            {
                int dia, mes, ano;
                int dataValida = 0;
                
                while (!dataValida) {
                    printf("|Nova data (DD/MM/AA): ");
                    char inputData[20];
                    fgets(inputData, sizeof(inputData), stdin);
                    
                    if (sscanf(inputData, "%d/%d/%d", &dia, &mes, &ano) == 3) {
                        if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 0 && ano <= 99) {
                            sprintf(novaData, "%02d/%02d/%02d", dia, mes, ano);
                            dataValida = 1;
                            strcpy(passagem[indice]._data, novaData);
                        } else {
                            printf("Data inválida. Por favor, insira uma data válida.\n");
                        }
                    } else {
                        printf("Formato inválido. Use DD/MM/AA.\n");
                    }
                }
            }
            break;
        case 4:
            // Validação de horário
            {
                int hora, minuto;
                int horarioValido = 0;
                
                while (!horarioValido) {
                    printf("|Novo horário (HH:MM): ");
                    char inputHorario[20];
                    fgets(inputHorario, sizeof(inputHorario), stdin);
                    
                    if (sscanf(inputHorario, "%d:%d", &hora, &minuto) == 2) {
                        if (hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59) {
                            sprintf(novoHorario, "%02d:%02d", hora, minuto);
                            horarioValido = 1;
                            strcpy(passagem[indice]._horario, novoHorario);
                        } else {
                            printf("Horário inválido. Por favor, insira um horário válido.\n");
                        }
                    } else {
                        printf("Formato inválido. Use HH:MM.\n");
                    }
                }
            }
            break;
        case 5:
            printf("|Insira o novo preço (R$): ");
            scanf("%f", &novoPreco);
            limparBuffer();
            passagem[indice]._preco = novoPreco;
            break;
        case 6:
            printf("|Insira o novo número de assentos disponíveis: ");
            scanf("%d", &novosAssentos);
            limparBuffer();
            passagem[indice]._assentosDisponiveis = novosAssentos;
            break;
    }
    
    salvar_Passagens(passagem);
    printf("\n|Informações atualizadas!\n");

    printf("|-----------> |PASSAGEM %d| <-----------|\n", indice);
    printf("|ID: %d\n", passagem[indice]._idPassagem);
    printf("|Origem: %s\n", passagem[indice]._origem);
    printf("|Destino: %s\n", passagem[indice]._destino);
    printf("|Data: %s\n", passagem[indice]._data);
    printf("|Horário: %s\n", passagem[indice]._horario);
    printf("|Preço: R$ %.2f\n", passagem[indice]._preco);
    printf("|Assentos disponíveis: %d\n", passagem[indice]._assentosDisponiveis);
    printf("|-----------------------------------------|\n");
}

int apagar_Passagem (Passagem passagem[]){
    listar_Passagens(passagem);

    if(_numPassagens == 0){
        printf("|Impossivel acessar funcao.\n");
        return 0;
    }

    int apagar;
    bool encontrado = false;

    printf("|-----------> |APAGAR PASSAGEM| <------------|\n");
    printf("|Insira o ID da passagem que deseja apagar do sistema: ");
    scanf("%d", &apagar);
    limparBuffer();  // Limpar o buffer após o scanf

    for (int i = 0; i < _numPassagens; i++) {
        if (passagem[i]._idPassagem == apagar) {
            encontrado = true;
            
            for (int u = i; u < _numPassagens - 1; u++) {
                strcpy(passagem[u]._origem, passagem[u+1]._origem);
                strcpy(passagem[u]._destino, passagem[u+1]._destino);
                strcpy(passagem[u]._horario, passagem[u+1]._horario);
                strcpy(passagem[u]._data, passagem[u+1]._data);
                passagem[u]._preco = passagem[u+1]._preco;
                passagem[u]._assentosDisponiveis = passagem[u+1]._assentosDisponiveis;
            }
        
            _numPassagens--;
            for (int j = 0; j < _numPassagens; j++) {
                passagem[j]._idPassagem = j;
            }
            
            salvar_Passagens(passagem);
            printf("|Passagem de ID %d removido com sucesso!\n", apagar);
            break;  
        }
    }
    if (!encontrado) {
        printf("|Passageiro de ID %d não encontrado!\n", apagar);
    }
    
    return _numPassageiros;
}

/*--------------------------*\ FUNCOES COMPRA /*---------------------------------*/

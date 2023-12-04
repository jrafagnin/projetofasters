#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <conio.h>
#include <limits>
#include <iomanip>

using namespace std;
/*                  STRUCTS USADAS PARA ARMAZENAR OS DADOS                    */
struct Usuario {
    string nome;
    string dataNascimento;
    string email;
    string senha;
};
struct Personagem {
    string nome;
    string classe;
    string pele;
    string raca;
    string cabelo;
    string arma;
    int vida;
    int mana;
    int forca;
    int agilidade;
};
struct Montaria {
    string raca;
    string nome;
    int vida;
    int agilidade;
    int cooldown;
};

/*                  PROTOTIPOS DAS FUNCOES                    */
void cadastrar(Usuario& usuario1);
bool login(const Usuario& usuario1);
char menu();
void personagem(Personagem& personagem1);
bool escolherArma(Personagem& personagem1);
bool atribuirPontosHabilidade(Personagem& personagem1);
int calcularIdade(const string& dataNascimento);
string obterSenhaEscondida();
void exibirLinhasPontos(const string& caracteristica, int pontos);
bool montaria(Montaria& montaria1);
void imprimirInformacoes( const Personagem& personagem1, const Montaria& montaria1);

/*                  FUNCAO PRINCIPAL                    */
int main() {
    bool continuar = true;
    Usuario usuario1;
    Personagem personagem1;
    Montaria montaria1;

    while (continuar) {
        char opcao = menu();

        switch (opcao) {
            case '1':
                if (login(usuario1)) {
                    continuar = false;
                }
                break;
            case '2':
                cadastrar(usuario1);
                break;
            case '3':
                cout << "Programa encerrado." << endl;
                continuar = false;
                break;
            default:
                cout << "Opcao invalida. Por favor, insira uma opcao valida." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }
    personagem(personagem1);
    escolherArma(personagem1);
    atribuirPontosHabilidade(personagem1);
    montaria(montaria1);
    imprimirInformacoes(personagem1,montaria1);
    system("pause");
    return 0;
}



/*                  FUNCOES DE TELAS                    */
// FUNCAO DE TELA DE CADASTRO
void cadastrar(Usuario& usuario1) {
    system("cls");
    char finalizar;
    cout << "------------------------------------------" << endl;
    cout << "|                CADASTRO                |" << endl;
    cout << "------------------------------------------" << endl << endl << endl;
    cin.ignore();
    cout << "NOME COMPLETO: ";
    getline(cin, usuario1.nome);
    cout << "EMAIL: ";
    getline(cin, usuario1.email);
    cout << "SENHA: ";
    string senha1 = obterSenhaEscondida();
    cout << endl;

    while (true) {
        cout << "CONFIRME A SENHA: ";
        string senha2 = obterSenhaEscondida();
        cout << endl;

        if (senha1 == senha2) {
            usuario1.senha = senha1;
            break;
        } else {
            cout << "As senhas nao coincidem. Tente novamente." << endl << endl;
        }
    }

    cout << "Senha confirmada" << endl << endl;
    cout << "DATA DE NASCIMENTO (dd mm aaaa): ";
    getline(cin, usuario1.dataNascimento);

    cout << "\n";
    int idade = calcularIdade(usuario1.dataNascimento);

    if (idade < 18) {
        cout << "Desculpe, voce deve ter pelo menos 18 anos para se cadastrar." << endl;
        cout << "Pressione enter para retornar ao menu";
        getchar();
    } else if (idade >= 18) {
        cout << "Cadastro realizado com sucesso!" << endl;
        cout << "Pressione enter para retornar ao menu" << endl << endl;
        getchar();
    }
}
// FUNCAO DE TELA DE LOGIN
bool login(const Usuario& usuario1) {
    int erro = 1;
    int tentativas = 3;
    system("cls");

    cout << "------------------------------------------" << endl;
    cout << "|                  LOGIN                 |" << endl;
    cout << "------------------------------------------" << endl << endl << endl;

    string emailDigitado;
    string senhaDigitada;

    cin.ignore();
    cout << "EMAIL: ";
    getline(cin, emailDigitado);

    while (emailDigitado != usuario1.email) {
        cout << "O email digitado nao esta cadastrado!" << endl;
        cout << "INSIRA O EMAIL NOVAMENTE:";
        getline(cin, emailDigitado);
    }

    cout << "SENHA: ";
    senhaDigitada = obterSenhaEscondida();
    cout << endl;

    while (erro < 3) {
        if (senhaDigitada == usuario1.senha) {
            cout << "Login realizado com sucesso!" << endl;
            cout << "ENTRANDO NO JOGO" << endl;
            return true;
        } else if (senhaDigitada != usuario1.senha) {
            tentativas--;
            erro++;
            cout << "Restam " << tentativas << " tentativas!" << endl;
            cout << "SENHA INVALIDA, INSIRA NOVAMENTE: ";
            senhaDigitada = obterSenhaEscondida();
            cout << endl;
        }
    }

    cout << "Voce excedeu o numero maximo de tentativas. pressione enter para encerrar o programa." << endl;
    getchar();
    exit(0);
}
// FUNCAO DE TELA DE MENU INICIAL
char menu() {
    char opcao;

    system("cls");
    cout << "------------------------------------------" << endl;
    cout << "|             MENU PRINCIPAL             |" << endl;
    cout << "------------------------------------------" << endl << endl << endl;
    cout << "1 - LOGIN " << endl;
    cout << "2 - CADASTRO " << endl;
    cout << "3 - SAIR" << endl << endl;

    while (true) {
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail() || cin.peek() != '\n' || (opcao != '1' && opcao != '2' && opcao != '3')) {
            cout << "Opcao invalida. Por favor, insira 1, 2 ou 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    return opcao;
}
// FUNCAO DE TELA DE CRIACAO DE PERSONAGEM
void personagem(Personagem& personagem1) {
    int opcao = 0;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << "|        CRIACAO DE PERSONAGEM           |" << endl;
    cout << "------------------------------------------" << endl << endl << endl;
    cout << "NOME DO PERSONAGEM: ";
    getline(cin, personagem1.nome);
    system("cls");
    cout << endl << "Racas disponiveis:" << endl << "1 - Humano" << endl << "2 - Elfo" << endl << "3 - Orc" << endl;

    do {
        cout << "Escolha a raca do seu personagem:";
        cin >> opcao;

        switch (opcao) {
            case 1:
                personagem1.raca = "Humano";
                break;
            case 2:
                personagem1.raca = "Elfo";
                break;
            case 3:
                personagem1.raca = "Orc";
                break;
            default:
                cout << "Opcao invalida! Escolha uma raca valida." << endl;
                break;
        }
    } while (opcao < 1 || opcao > 3);
    system("cls");
    cout << endl << "Cores de pele disponiveis:" << endl << "1 - Retinto" << endl << "2 - Negro" << endl << "3 - Pardo" << endl << "4 - Branco" << endl << "5 - Albino" << endl;

    do {
        cout << "Escolha a cor de pele do seu personagem:";
        cin >> opcao;

        switch (opcao) {
            case 1:
                personagem1.pele = "Retinto";
                break;
            case 2:
                personagem1.pele = "Negro";
                break;
            case 3:
                personagem1.pele = "Pardo";
                break;
            case 4:
                personagem1.pele = "Branco";
                break;
            case 5:
                personagem1.pele = "Albino";
                break;
            default:
                cout << "Opcao invalida! Escolha uma cor de pele valida." << endl;
                break;
        }
    } while (opcao < 1 || opcao > 5);
    system("cls");
    cout << endl << "Tipos de cabelo disponiveis:" << endl << "1 - Liso" << endl << "2 - Encaracolado" << endl << "3 - Crespo" << endl;

    do {
        cout << "Escolha o tipo de cabelo do seu personagem:";
        cin >> opcao;

        switch (opcao) {
            case 1:
                personagem1.cabelo = "Liso";
                break;
            case 2:
                personagem1.cabelo = "Encaracolado";
                break;
            case 3:
                personagem1.cabelo = "Crespo";
                break;
            default:
                cout << "Opcao invalida! Escolha um tipo de cabelo valido." << endl;
                break;
        }
    } while (opcao < 1 || opcao > 3);
    system("cls");
    cout << endl << "Classes disponiveis:" << endl << "1 - Paladino" << endl << "2 - Atirador" << endl << "3 - Guerreiro" << endl << "4 - Barbaro" << endl << "5 - Arqueiro" << endl;

    do {
        cout << "Escolha a classe do seu personagem:";
        cin >> opcao;

        switch (opcao) {
            case 1:
                personagem1.classe = "Paladino";
                break;
            case 2:
                personagem1.classe = "Atirador";
                break;
            case 3:
                personagem1.classe = "Guerreiro";
                break;
            case 4:
                personagem1.classe = "Barbaro";
                break;
            case 5:
                personagem1.classe = "Arqueiro";
                break;
            default:
                cout << "Opcao invalida! Escolha uma classe valida." << endl;
                break;
        }
    } while (opcao < 1 || opcao > 5);
}
// FUNCAO DE TELA DE ATRIBUTOS
bool atribuirPontosHabilidade(Personagem& personagem1) {
    int pontosRestantes = 20;

    if (personagem1.classe == "Paladino") {
        personagem1.vida = 8;
        personagem1.mana = 5;
        personagem1.forca = 4;
        personagem1.agilidade = 3;
    } else if (personagem1.classe == "Atirador") {
        personagem1.vida = 6;
        personagem1.mana = 7;
        personagem1.forca = 3;
        personagem1.agilidade = 4;
    } else if (personagem1.classe == "Guerreiro") {
        personagem1.vida = 9;
        personagem1.mana = 3;
        personagem1.forca = 5;
        personagem1.agilidade = 3;
    } else if (personagem1.classe == "Barbaro") {
        personagem1.vida = 10;
        personagem1.mana = 2;
        personagem1.forca = 6;
        personagem1.agilidade = 2;
    } else if (personagem1.classe == "Arqueiro") {
        personagem1.vida = 7;
        personagem1.mana = 6;
        personagem1.forca = 3;
        personagem1.agilidade = 4;
    } else {
        personagem1.vida = 5;
        personagem1.mana = 5;
        personagem1.forca = 5;
        personagem1.agilidade = 5;
    }

    while (pontosRestantes > 0) {
        system("cls");
        cout << "\nAtributos: "  << endl << endl;
        cout << "1 - Vida (" << personagem1.vida << " pontos)" << endl;
        exibirLinhasPontos("Vida", personagem1.vida);
        cout << endl;
        cout << "2 - Mana (" << personagem1.mana << " pontos)" << endl;
        exibirLinhasPontos("Mana", personagem1.mana);
        cout << endl;
        cout << "3 - Forca (" << personagem1.forca << " pontos)" << endl;
        exibirLinhasPontos("Forca", personagem1.forca);
        cout << endl;
        cout << "4 - Agilidade (" << personagem1.agilidade << " pontos)" << endl;
        exibirLinhasPontos("Agilidade", personagem1.agilidade);
        cout << endl;

        cout << "\nPontos restantes: " << pontosRestantes << endl;
        cout << "Escolha o atributo para adicionar pontos (1-4): ";

        int escolha;
        cin >> escolha;

        if (escolha < 1 || escolha > 4) {
            cout << "Opcao invalida. Escolha entre 1 e 4." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Quantos pontos deseja adicionar? ";
        int pontosAdicionados;
        cin >> pontosAdicionados;

        if (pontosAdicionados < 0 || pontosAdicionados > pontosRestantes) {
            cout << "Numero de pontos invalido. Tente novamente." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (escolha) {
            case 1:
                personagem1.vida += pontosAdicionados;
                break;
            case 2:
                personagem1.mana += pontosAdicionados;
                break;
            case 3:
                personagem1.forca += pontosAdicionados;
                break;
            case 4:
                personagem1.agilidade += pontosAdicionados;
                break;
            default:
                break;
        }

        pontosRestantes -= pontosAdicionados;
    }

    cout << "\nAtribuicao de pontos concluida!" << endl;
    return true;
}
     // FUNCAO DA TELA DE CRIACAO DE MONTARIA
bool montaria(Montaria& montaria1) {
    int opcao = 0;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << "|          CRIACAO DA MONTARIA           |" << endl;
    cout << "------------------------------------------" << endl << endl << endl;

    cout << "NOME DA MONTARIA: ";
    cin.ignore();
    getline(cin, montaria1.nome);
    system("cls");
    cout << endl << "Racas disponiveis:" << endl << "1 - Cavalo" << endl << "2 - Panda" << endl << "3 - Javali" << endl
         << "4 - Jacare" << endl << "5 - Alce" << endl;

    do {
        cout << "Escolha a raca da sua montaria:";
        cin >> opcao;

        switch (opcao) {
            case 1:
                montaria1.raca = "Cavalo";
                break;
            case 2:
                montaria1.raca = "Panda";
                break;
            case 3:
                montaria1.raca = "Javali";
                break;
            case 4:
                montaria1.raca = "Jacare";
                break;
            case 5:
                montaria1.raca = "Alce";
                break;
            default:
                cout << "Opcao invalida! Escolha uma raca valida." << endl;
                break;
        }
    } while (opcao < 1 || opcao > 5);

    int pontosRestantes = 15;

    if (montaria1.raca == "Cavalo") {
        montaria1.vida = 5;
        montaria1.agilidade = 5;
        montaria1.cooldown = 5;

    } else if (montaria1.raca == "Panda") {
        montaria1.vida = 8;
        montaria1.agilidade = 3;
        montaria1.cooldown = 4;

    } else if (montaria1.raca == "Javali") {
        montaria1.vida = 4;
        montaria1.agilidade = 8;
        montaria1.cooldown = 3;

    } else if (montaria1.raca == "Jacare") {
        montaria1.vida = 3;
        montaria1.agilidade = 10;
        montaria1.cooldown = 2;

    } else if (montaria1.raca == "Alce") {
        montaria1.vida = 10;
        montaria1.agilidade = 3;
        montaria1.cooldown = 2;

    } else {
        montaria1.vida = 5;
        montaria1.agilidade = 5;
        montaria1.cooldown = 5;
    }

    while (pontosRestantes > 0) {
        cout << "\nAtributos da montaria: " << endl << endl;
        cout << "1 - Vida (" << montaria1.vida << " pontos)" << endl;
        exibirLinhasPontos("Vida", montaria1.vida);
        cout << endl;
        cout << "2 - Agilidade (" << montaria1.agilidade << " pontos)" << endl;
        exibirLinhasPontos("Agilidade", montaria1.agilidade);
        cout << endl;
        cout << "3 - Cooldown (" << montaria1.cooldown << " pontos)" << endl;
        exibirLinhasPontos("Cooldown", montaria1.cooldown);
        cout << endl;

        cout << "\nPontos restantes: " << pontosRestantes << endl;
        cout << "Escolha o atributo para adicionar pontos (1-3): ";

        int escolha;
        cin >> escolha;

        if (escolha < 1 || escolha > 3) {
            cout << "Opcao invalida. Escolha entre 1 e 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Quantos pontos deseja adicionar? ";
        int pontosAdicionados;
        cin >> pontosAdicionados;

        if (pontosAdicionados < 0 || pontosAdicionados > pontosRestantes) {
            cout << "Numero de pontos invalido. Tente novamente." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (escolha) {
            case 1:
                montaria1.vida += pontosAdicionados;
                break;
            case 2:
                montaria1.agilidade += pontosAdicionados;
                break;
            case 3:
                montaria1.cooldown += pontosAdicionados;
                break;
            default:
                break;
        }

        pontosRestantes -= pontosAdicionados;
    }

    cout << "\nAtribuicao de pontos concluida!" << endl;
    return true;
}

     // FUNCAO DA TELA PARA IMPRIMIR INFORMACOES DO PERSONAGEM
void imprimirInformacoes( const Personagem& personagem1, const Montaria& montaria1) {
    system("cls");
    int velocidadeDeAtaque = (personagem1.agilidade)*2;
    int vidaTotal1 = (personagem1.vida)*10;
    int danoDeAtaque = (personagem1.forca)*5;
    int manaTotal = (personagem1.mana)*10;
    int velocidadeDeMovimento1 = (personagem1.agilidade)*20;
    int peso = (personagem1.forca)*100;


    int velocidadeDeMovimento2 = (montaria1.agilidade)*50;
    int vidaTotal2 = (montaria1.vida)*100;
    int cooldown = (montaria1.cooldown)*5;

    cout << "------------------------------------------" << endl;
    cout << "|        INFORMACOES DO PERSONAGEM       |" << endl;
    cout << "------------------------------------------" << endl << endl << endl;


    cout << "----------  PERSONAGEM  ----------" << endl;
    cout << "Nome: " << personagem1.nome << endl;
    cout << "Raca: " << personagem1.raca << endl;
    cout << "Pele: " << personagem1.pele << endl;
    cout << "Cabelo: " << personagem1.cabelo << endl<<endl;
    cout << "Classe: " << personagem1.classe << endl;
    cout << "Arma: " << personagem1.arma << endl<<endl;

    cout << "----------  ATRIBUTOS DO PERSONAGEM  ----------" << endl;
    cout << "Vida: " << vidaTotal1 << endl;
    cout << "Mana: " << manaTotal << endl;
    cout << "Dano de ataque: " << danoDeAtaque << endl;
    cout << "Velocidade de ataque: " << velocidadeDeAtaque << endl;
    cout << "Velocidade de movimento: " << velocidadeDeMovimento1 << endl;
    cout << "Peso maximo: " << peso << endl << endl;

    cout << "----------  MONTARIA  ----------" << endl;
    cout << "Nome: " << montaria1.nome << endl;
    cout << "Raca: " << montaria1.raca << endl;

    cout << "----------  ATRIBUTOS DA MONTARIA ----------" << endl;
    cout << "Vida: " << vidaTotal2 << endl;
    cout << "Velocidade de movimento: " << velocidadeDeMovimento2 << endl;
    cout << "Cooldown: " << cooldown << endl << endl;

}





/*                  FUNCOES DE UTILIDADE                    */
bool escolherArma(Personagem& personagem1) {
    int opcao = 0;

    cout << endl << "Armas disponiveis:" << endl;

    if (personagem1.classe == "Paladino") {
        cout << "1 - Espada" << endl << "2 - Escudo" << endl;
    } else if (personagem1.classe == "Atirador") {
        cout << "1 - Estilingue" << endl << "2 - Faca arremessavel" << endl;
    } else if (personagem1.classe == "Guerreiro") {
        cout << "1 - Machado de uma mao" << endl << "2 - Espada longa" << endl;
    } else if (personagem1.classe == "Barbaro") {
        cout << "1 - Clava" << endl << "2 - Machado Duplo" << endl;
    } else if (personagem1.classe == "Arqueiro") {
        cout << "1 - Arco Longo" << endl << "2 - Adagas duplas" << endl;
    } else {
        cout << "Classe desconhecida! Escolha uma arma generica." << endl;
        cout << "1 - Espada" << endl << "2 - Arco" << endl;
    }

    while (true) {
        cout << "Escolha a arma do seu personagem:";
        cin >> opcao;

        if (cin.fail() || (opcao != 1 && opcao != 2)) {
            cout << "Opcao invalida. Escolha 1 ou 2." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    if (personagem1.classe == "Paladino") {
        personagem1.arma = (opcao == 1) ? "Espada" : "Escudo";
    } else if (personagem1.classe == "Atirador") {
        personagem1.arma = (opcao == 1) ? "Estilingue" : "Faca arremessavel";
    } else if (personagem1.classe == "Guerreiro") {
        personagem1.arma = (opcao == 1) ? "Machado de uma mao" : "Espada longa";
    } else if (personagem1.classe == "Barbaro") {
        personagem1.arma = (opcao == 1) ? "Clava" : "Machado Duplo";
    } else if (personagem1.classe == "Arqueiro") {
        personagem1.arma = (opcao == 1) ? "Arco Longo" : "Adagas duplas";
    } else {
        personagem1.arma = (opcao == 1) ? "Espada" : "Arco";
    }

    return true;
}
     // FUNCAO PARA ESCONDER CARACTERES DA SENHA NA TELA DE LOGIN
string obterSenhaEscondida() {
    string senhaEscondida;
    char c;

    while (true) {
        c = _getch();  // CAPTURA O CARACTERE

        
        if (c == 13) { // ENCERRA A FUNCAO CASO ENTER SEJA PRESSIONADO
            break;
        }
        else if (c == 8) {  //APAGA UM CARACTERE DA TELA CASO BACKSPACE SEJA PRESSIONADO
            if (!senhaEscondida.empty()) {
                senhaEscondida.pop_back();
                cout << "\b \b";
            }
        }
        else { //IMPRIME * NO LUGAR DO CARACTERE PRESSIONADO
            senhaEscondida.push_back(c);
            cout << '*';
        }
    }

    return senhaEscondida;
}
     // FUNCAO PARA CALCULAR A IDADE E CONFERINDO SE É MAIOR QUE 18
int calcularIdade(const string& dataNascimento) {
    time_t t = time(0);
    tm* agora = localtime(&t);  // Use localtime em vez de localtime_s

    int anoAtual = agora->tm_year + 1900;
    int mesAtual = agora->tm_mon + 1;
    int diaAtual = agora->tm_mday;

    int anoNascimento, mesNascimento, diaNascimento;
    stringstream(dataNascimento) >> diaNascimento >> mesNascimento >> anoNascimento;

    int idade = anoAtual - anoNascimento;

    if (mesNascimento > mesAtual || (mesNascimento == mesAtual && diaNascimento > diaAtual)) {
        idade--;
    }

    return idade;
}
     // FUNCAO PARA EXIBIR OS PONTOS DE HABILIDADE COMO UMA LINHA
void exibirLinhasPontos(const string& caracteristica, int pontos) {
    cout << setw(10) << caracteristica << ": ";
    for (int i = 0; i < pontos; ++i) {
        cout << "O";
    }
    cout << endl;
}

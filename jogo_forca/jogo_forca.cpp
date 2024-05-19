#include <iostream> //inclui biblioteca string, dependendo do compilador usado
#include <string>
#include <fstream>
#include <ctime>    // seed
#include <cstdlib> //randon
#include <map>
#include <vector>

// compilar: g++ <arquivo.extensao> -o <arquivo.extensao_saida> -std=c++11 <- adiciona funcionalidades como foreach
// podemos tambem criar um arquivo Makefile com CXXFLAGS= -std=c++11 e usar make <nomearquivo>
using namespace std;

// posso declarar uma variavel ou constante global aqui
map<char, bool> chutes_palavra;

bool letra_existe(char letra, string palavra) {
    // foreach
    for (char l : palavra) {
        if (letra == l)
        return true;
    }
    return false;
}

void imprime_cabecalho() {
    cout << "*********************" <<'\n';
    cout << "*** Jogo da Forca ***"<<'\n';
    cout << "*********************"<<'\n';
    cout << '\n';
}

void imprime_jogo(string palavra) {
    for (char letra : palavra) {
        if (chutes_palavra[letra]) {
            cout << letra << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << '\n';
}

bool ganhou(string palavra_secreta) {
   for(char letra : palavra_secreta){
        if (!chutes_palavra[letra]){
            return false;
        }
   }
   return true; 
}
bool enforcado(int numero_erros) {
    return numero_erros > 5;
}

vector<string> le_arquivo(){
    // input file stream
    ifstream arquivo;
    vector<string> palavras_arquivo; 

    if(!arquivo.is_open()){
        arquivo.open("./palavras.txt");
    } else {
        cout << "Arquivo ja está aberto" << endl;
    }

    if(!arquivo.is_open()){
        cout << "Não foi possivel acessar o banco de palavras" << endl ;           
        exit(0); // para a execuçao do programa
    }

    //lendo a primeira linha do arquivo
    int qtd_palavras;
    arquivo >> qtd_palavras;

    // lendo as palavras
    for(int i = 0; i < qtd_palavras; i++) {
        string palavra_lida;
        arquivo >> palavra_lida;
        palavras_arquivo.push_back(palavra_lida);
    } 
    arquivo.close();   
    return palavras_arquivo;
}
string sorteia_palavra(){
    vector<string> palavras_arquivo = le_arquivo();
    srand(time(NULL));
    int indice_sort = rand() % palavras_arquivo.size();
    return palavras_arquivo[indice_sort];
}

void adiciona_palavra(){
    cout << "Qual palavra deseja adicionar?(letras minusculas)" << endl;
    string nova_palavra;
    cin >> nova_palavra;

    vector<string> lista_palavras = le_arquivo();
    lista_palavras.push_back(nova_palavra);

    reescreve_arquivo(lista_palavras);
}

void reescreve_arquivo(vector<string> lista_palavras){
    ofstream arquivo;

    if(!arquivo.is_open()){
        arquivo.open("./palavras.txt");
    } else {
        cout << "Arquivo ja está aberto" << endl;
    }

    if(!arquivo.is_open()){
        cout << "Não foi possivel abrir o arquivo para atualizar a lista" << endl ;           
        exit(0); // para a execuçao do programa
    }

    arquivo << lista_palavras.size() << endl;
    for(string palavra : lista_palavras){
        arquivo << palavra << endl;
    }
    arquivo.close();

}

int main() {
    string palavra_secreta = sorteia_palavra();
    string errados = "Chutes errados: ";
    int numero_erros = 0;
    imprime_cabecalho();

    while (!enforcado(numero_erros) && !ganhou(palavra_secreta)) {
        cout << errados << " " << endl;
        imprime_jogo(palavra_secreta);
        
        cout << "Seu chute: ";
        char chute;
        cin >> chute;
        chutes_palavra[chute] = true;
        if (letra_existe(chute, palavra_secreta)) {
            cout << "A palavra contém a letra!" << endl;
        }
        else {
            cout << "A palavra nao contém a letra." << endl;
            errados.push_back(chute);
            errados.push_back(' ');
            numero_erros++;
        }
        cout << '\n';
    }

    
    if(enforcado(numero_erros)){
        cout << "Fim de jogo, você perdeu, tente novamente!" << '\n'; 
    }
    else {
        cout << "Fim de jogo, você venceu! " << '\n';
        cout << "Deseja adicionar uma plavra nova palavra ao banco? [s/n]: " << ends;
        char resposta;
        cin >> resposta;
        if (resposta == 's'){
           adiciona_palavra(); 
        }
    }
    cout << "A palavra secreta era: " << palavra_secreta << '\n';
}

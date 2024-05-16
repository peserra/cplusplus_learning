#include <iostream> //inclui biblioteca string, dependendo do compilador usado
#include <string>
#include <map>

// compilar: g++ <arquivo.extensao> -o <arquivo.extensao_saida> -std=c++11 <- adiciona funcionalidades como foreach
// podemos tambem criar um arquivo Makefile com CXXFLAGS= -std=c++11 e usar make <nomearquivo>
using namespace std;

// posso declarar uma variavel ou constante global aqui
map<char, bool> chutes_palavra;
int numero_erros = 0;

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
bool enforcado() {
    return numero_erros > 5;
}

int main() {

    const string PALAVRA_SECRETA = "melancia";
    cout << PALAVRA_SECRETA << endl;
    // inicializado
    string errados = "Chutes errados: ";

    while (!enforcado() && !ganhou(PALAVRA_SECRETA)) {
        imprime_cabecalho();
        cout << errados << " " << endl;
        
        imprime_jogo(PALAVRA_SECRETA);
        
        cout << "Seu chute: ";
        char chute;
        cin >> chute;
        chutes_palavra[chute] = true;
        if (letra_existe(chute, PALAVRA_SECRETA)) {
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

    
    if(enforcado()){
        cout << "Fim de jogo, você perdeu, tente novamente!" << '\n'; 
    }
    else {
        cout << "Fim de jogo, você venceu! " << '\n';
    }
    cout << "A palavra secreta era: " << PALAVRA_SECRETA << '\n';
}

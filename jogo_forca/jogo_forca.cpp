#include <iostream> //inclui biblioteca string, dependendo do compilador usado
#include <string>
#include <map>
// compilar: g++ <arquivo.extensao> -o <arquivo.extensao_saida> -std=c++11 <- adiciona funcionalidades como foreach
// podemos tambem criar um arquivo Makefile com CXXFLAGS= -std=c++11 e usar make <nomearquivo>
using namespace std;

// posso declarar uma variavel ou constante global aqui
map<char, bool> chutes_palavra;

bool letra_existe(char letra, string palavra){
    //foreach 
    for(char l : palavra){
        if(letra == l)
            return true;
    }
    return false;
}

void imprime_jogo(string palavra){
    for(char letra : palavra){
        if(chutes_palavra[letra]){
            cout << letra << " ";
        }
        else {
            cout << "_ ";
        }
    }
}

int main(){
    const string PALAVRA_SECRETA = "melancia";
    cout << PALAVRA_SECRETA << endl;
    // inicializado
    bool enforcado = false;
    bool ganhou = false;
    string errados = "";
      
    while(!enforcado && !ganhou){
        imprime_jogo(PALAVRA_SECRETA);
        char chute;
        cin >> chute;
        chutes_palavra[chute] = true;
        if(letra_existe(chute, PALAVRA_SECRETA)){
            cout << "A palavra contém a letra!" << endl;
        }
        else {
            cout << "A palavra nao contém a letra." << endl;
            errados.push_back(chute);
            errados.push_back(' ');
            cout << errados << " " << endl;
        }
        
    }
}
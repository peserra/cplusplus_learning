#include<cstdlib>
#include<iostream>
#include<time.h>

using namespace std;


void print_cabecalho(){
    cout << "***********************************************************\n" << endl;
    cout << "*           Boas vindas ao jogo da adivinhação!*          *\n" << endl;
    cout << "***********************************************************\n" << endl;
}

int menu(){
    print_cabecalho();
    int dificuldade;
    bool dificuldade_ok = false;
    int valor_num_max;

    while(!dificuldade_ok){
        cout << "Selecione a dificuldade desejada [1-facil, 2-medio, 3-dificil]: " << endl;
        cin >> dificuldade;

        if(dificuldade < 0 || dificuldade >= 4){
            cout << "Insira um numero válido para dificuldade! [1-facil, 2-medio, 3-dificil]"<< endl;
        }
        else if(!dificuldade){
            cout << "Dificuldade deve ser indicada com apenas UM numero! [1-facil, 2-medio, 3-dificil]" << endl; 
        }
        else {
            dificuldade_ok = true;
        }
    }

    if(dificuldade_ok){
        switch (dificuldade)
        {
        case 1:
            valor_num_max = 100;
            break;
        case 2:
            valor_num_max = 200;
            break;        
        default:
            valor_num_max = 300;
            break;
        }
        return valor_num_max;
    }
    return 0;
}

int gera_numero_secreto(int max){
    srand(time(0));
    return rand() % max;
}

int main(){
    int total_de_palavras = menu();
    bool fim_de_jogo = false;
    int chute = 0;
    int numero_secreto = -1;

    double pontuacao = (double)total_de_palavras;
    double deducao = 0.0;
    
    if(total_de_palavras != 0){
        switch (total_de_palavras)
        {
        case 200:
            deducao = total_de_palavras / 20 * 1.25;
            break;
        case 300:
            deducao = total_de_palavras / 30 * 2;
            break;
        default:
            deducao = total_de_palavras / 10;
            break;
        }
        numero_secreto = gera_numero_secreto(total_de_palavras);
    } else {
        cout << "Erro: Dificuldade selecionada incorreta." << endl;
    }
    
    while(!fim_de_jogo){
        cout<< "Tente adivinhar o numero secreto: " <<endl;
        cin >> chute;
        double penalidade = abs((chute - numero_secreto)/2.0);
        
        if(pontuacao == 0.0) {
            cout << "Que pena, sua pontuacao zerou. Mais sorte na proxima vez!" << endl;
            break;
        }

        if(chute == numero_secreto){ 
            cout.precision(2);
            cout << fixed; // deixa a virgula fixa no lugar
            cout<< "Parabens! Voce acertou, o numero secreto era " << chute << "!" << endl;
            cout << "Sua pontuação foi: " << pontuacao << endl;
            fim_de_jogo = true;
        } else if (chute < numero_secreto){
            cout << "Seu chute foi menor do que o numero secreto. Tente novamente" << endl;
            pontuacao -= deducao + penalidade;
            if (pontuacao < 0)
                pontuacao = 0.0;
            cout << "Pontuacao atual: "<< pontuacao << endl;
        } else{
            cout << "Seu chute foi maior que o numero secreto. Tente novamente" << endl;
            pontuacao -= deducao + penalidade;
            if (pontuacao < 0)
                pontuacao = 0.0;
            cout << "Pontuacao atual: "<< pontuacao << endl;
        }
    }
    cout << "******************** FIM DE JOGO **************************" << endl;
}
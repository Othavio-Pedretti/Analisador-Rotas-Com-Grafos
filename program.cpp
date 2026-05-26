#include <iostream>
#include <fstream>


using namespace std;

int main(int argc, char *argv[]){
    string s;
    ifstream arquivo_entrada;
    string entrada;
    for (int i = 1; i < argc; ++i) {
        entrada += argv[i];
    }

    arquivo_entrada.open(entrada);

   if(!arquivo_entrada){
        cout << "Não foi possível abrir o arquivo ou o nome do arquivo não foi fornecido" << endl;
        exit(1);
   }

   /*sanitização*/

   while (arquivo_entrada >> s)
   {
        cout << s << endl;
   }
   
    arquivo_entrada.close();
    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
//#include "graph.cpp"

using namespace std;

int main(int argc, char *argv[]){
    string prb_id;
    string probe_src;
    string dst_addr;
    float rtt;
    string hop_from;
    string hop_to;
    string hop;
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

   string linha;
   string lixo;
   while (getline(arquivo_entrada, linha))
   {
        stringstream ss(linha);
        if(getline(ss, prb_id, ',') && getline(ss, probe_src, ',')){
            cout << prb_id << "\n"
                << probe_src << "\n";
        }
   }
   
    arquivo_entrada.close();
    return 0;
}
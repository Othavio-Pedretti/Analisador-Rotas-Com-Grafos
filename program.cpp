#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "graph.cpp"

using namespace std;

int main(int argc, char *argv[]){
    string prb_id, probe_src, dst_addr, rtt, hop_from, hop_to, hop;
    ifstream arquivo_entrada;
    string entrada;
    graph::digraph g;
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
        if(getline(ss, prb_id, ',') 
           && getline(ss, probe_src, ',') 
           && getline(ss, dst_addr, ',') 
           && getline(ss, hop, ',') 
           && getline(ss, hop_from, ',') 
           && getline(ss, hop_to, ',') 
           && getline(ss, rtt)){
            if(hop_from != "" && hop_to != ""){}
                g.insert_nodo(hop, prb_id, probe_src,hop_from,hop_to, dst_addr, rtt);

        }
   }
   
    cout << g.size() << " nodos" << endl;
    arquivo_entrada.close();
    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.cpp"
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[]){
    string prb_id, probe_src, dst_addr, rtt, hop_from, hop_to, hop;
    ifstream arquivo_entrada;
    string entrada;
    graph::digraph g;
    unordered_map<string, graph::digraph> map;
    int arestas = 0;
    int vertices = 0;
    for (int i = 1; i < argc; ++i) {
        entrada += argv[i];
    }

    arquivo_entrada.open(entrada);

   if(!arquivo_entrada){
        cout << "Não foi possível abrir o arquivo ou o nome do arquivo não foi fornecido" << endl;
        exit(1);
   }

   string linha;
   bool existeArestaIgual = false;
   while (getline(arquivo_entrada, linha))
   {

        stringstream ss(linha);
        if(getline(ss, prb_id, ',') 
           && getline(ss, probe_src, ',') 
           && getline(ss, dst_addr, ',') 
           && getline(ss, hop, ',') 
           && getline(ss, hop_from, ',') 
           && getline(ss, hop_to, ',') 
           && getline(ss, rtt, ',')){
            
             
            if(hop_to != "*"){
                if(hop_from != " " || hop_to != " "){
                    map[prb_id].nodes[hop] = {probe_src, dst_addr, rtt, hop_from};
                    vertices++;
                    for(auto& [prb_id, digrafo] : map){
                        for(auto& [hop, node] : digrafo.nodes){
                            for(auto& link : node.links){
                                if(link == hop_to){
                                    existeArestaIgual = true;
                                    break;
                                }
                            }
                            if(existeArestaIgual == false){
                                if(hop_from == digrafo.nodes[hop].hop_from){
                                    node.links.push_back(hop_to);
                                    arestas++;
                                }
                            }
                        }
                    }
                }
            }
        }
   }
   

   for (auto& [prb_id, digrafo] : map) {
    std::cout << "prb_id: " << prb_id << "\n";
        for (const auto& [hop, node] : digrafo.nodes) {
            std::cout << "    hop: " << hop << "\n";
            std::cout << "    hop_from: " << node.hop_from << "\n";
            std::cout << "    probe_src: " << node.probe_src << "\n";
            std::cout << "    dst_addr: "  << node.dst_addr  << "\n";
            std::cout << "    rtt: "       << node.rtt       << "\n";
            std::cout << "    links:";
            for (auto& destino : node.links) {
                std::cout << " " << destino;
            }
            std::cout << "\n";
        }
    }
    cout << "Carregamento inicial concluído! Foram inseridos " << vertices << " vertices e " << arestas << " arestas" << endl;
    arquivo_entrada.close();
    cout << "======MENU======" << endl <<
    "Digite a opção desejada:" << endl << 
    "1: Exibir Grafo" << endl <<
    "2: Encontrar o Menor Caminho" << endl <<
    "3: Calcular o Diâmetro do Grafo" << endl <<
    "4: Identificar Roteadores Críticos" << endl <<
    "5: Sair" << endl <<
    "================" << endl <<
    "Escolha uma das opções acima: ";
    int usuario;
    cin >> usuario;

    if(usuario == 1){
        cout << "Digite qual como quer vizualizar o grafo: " << endl <<
        "1: Tela" << endl <<
        "2: Imagem (PNG)" << endl <<
        "3: Documento (PDF)" << endl;
        int escolha;
        cin >> escolha;
        ofstream dot("graphED2.dot"); // cria o arquivo        
        if(escolha == 1){
            dot << "digraph {\n";
                for (auto& [prb_id, digrafo] : map) {
                    for (auto& [hop, node] : digrafo.nodes) {
                        if (node.links.empty())
                            continue;
                        dot << "\"" << node.hop_from << "\" -> {";
                        for (auto& link : node.links) {
                            dot << "\"" << link << "\" ";
                        }
                        dot << "};\n";
                    }
                }

                dot << "}\n";
                /// Gera o grafo usando o Graphviz com saida em uma tela
        }
        else if(escolha == 2){
            dot << "digraph {\n";
            for(auto& [prb_id, digrafo] : map){
                for(auto& [hop, node] : digrafo.nodes){
                    for(auto& link : node.links){
                        dot << "t\"" << node.hop_from << "\"  << -> << \"" << link << "\";\n";
                    }
                }
            }
            dot << "}\n";
            system("dot -Tpng graphED2.dot -o grafo.png");
        }
        else if(escolha == 3){
            dot << "digraph {\n";
            for(auto& [prb_id, digrafo] : map){
                for(auto& [hop, node] : digrafo.nodes){
                    for(auto& link : node.links){
                        dot << "t\"" << node.hop_from << "\"  << -> << \"" << link << "\";\n";
                    }
                }
            }
            dot << "}\n";
            system("dot -Tpdf graphED2.dot -o grafo.pdf");
        }
        
        
    }
    else if(usuario == 5){
        cout << "Saindo do programa..." << endl;
        return 0;
    }else{
        cout << "Opção inválida. Saindo do programa..." << endl;
        return 0;
    }
    
    
    return 0;
}
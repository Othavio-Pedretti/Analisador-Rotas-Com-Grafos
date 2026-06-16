/// biblioteca para grafos
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>

namespace graph{

  class digraph; // declaração antecipada da classe digraph
  extern std::unordered_map<std::string, digraph> map; 

    class digraph{
        private:
          // nodos do grafo - VERTÍCES
          struct node{
            //std::string prb_id;
            //std::string hop;
            std::string probe_src;
            std::string dst_addr;
            std::string rtt;
            std::string hop_from;
            std::vector<std::string> links; //lista de ponteiros p/ os nodos vizinhos - ARESTAS
          };

          //tabela hash, que mapeia o rótulo do nó para o objeto node
                             //<chave>, <valor>    
          std::unordered_map<std::string,node> nodes;
          std::unordered_set<node*> visited;
        
        public:
         //Insere um novo nó no grafo com o rótulo s
          void insert_nodo(const std::string& prb_id,
                            const std::string& hop, 
                            const std::string& probe_src, 
                            const std::string& dst_addr,
                            const std::string& hop_from,
                            const std::string& rtt){
            map[prb_id].nodes[hop] = {probe_src, dst_addr, rtt, hop_from};
          }

          void exibe_grafo(){
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
          }

          //retorna a quantidade de nós (vertices) do grafo
          size_t size(){
            return nodes.size();
          }
            
          
          //busca um nó pelo seu rótulo e retorna o endereço do nodo 
          node* find(const std::string& s){
            for(auto& [prb_id, digrafo] : map){
                for(auto& [hop, node] : digrafo.nodes){
                    if(node.hop_from == s){
                        return &node;
                    }
                }
            }

            return nullptr;
          }

          
          //INsere um aresta dirigida de 'from' para 'to'
          bool insert_link(const std::string& hop_from, const std::string& hop_to){
            for(auto& [prb_id, digrafo] : map){
                for(auto& [hop, node] : digrafo.nodes){
                    if(node.hop_from == hop_from){
                        node.links.push_back(hop_to);
                        return true;
                    }
                }
             }
             return false;
          }
          
          //existe uma aresta de?
          bool existe_aresta(const std::string& vertice, const std::string& novoLink){
            auto p = find(vertice);
            for (auto& link : p->links){
                if(link == novoLink){
                    return true;
                }
            }
             return false;
          }
          /*
          //numero de arestas que saem de um vertice
          size_t outdegree(const std::string& s){
            for(auto node : nodes){
              if(node.first == s){
                return node.second.links.size();
              }
            }
            return 0;
          }

          //numero de arestas que chegam a um vertice
          size_t indegree(const std::string& s){
            auto p = find(s);
            if(p == nullptr){
              return 0;
            }
            size_t qnt = 0;
            for(auto vertice : nodes){
                for(auto link : vertice.second.links)
                  if(link == s){
                    qnt++;
                  }
            }
            return qnt;
          }
          
          //numero de arestas conectadas a um vertice
          size_t degree(const std::string& s){
            auto p = find(s);
            if(p == nullptr){
              return 0;
            }
            return indegree(s) + outdegree(s);
          }
          
          */
         


          void export2dot(const std::string& filename){
            std::ofstream dot(filename); // cria o arquivo
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
            };
          
          
          void draWhithScreen(){
            export2dot("graphED2.dot");
            //std::system("dot -Tpng graphED2.dot -o grafo.png");
            std::system("dot -Tx11 graphED2.dot"); //funciona para linux, para windows tem que ser "dot -Tx11 graphED2.dot"
          }

          //funciona apenas para windows nesse momento pq o comando exibe imagem no windows
          //ESTUDAR COMO EXIBIR IMAGEM NO LINUX
          void drawPNG(){
            export2dot("graphED2.dot");
            std::system("dot -Tpng graphED2.dot -o grafo.png");
            //std::system("dot -Tx11 graphED2.dot"); //funciona para linux, para windows tem que ser "dot -Tx11 graphED2.dot"
          }

          void drawPDF(){
            export2dot("graphED2.dot");
            std::system("dot -Tpdf graphED2.dot -o grafo.pdf");
          }

        /*
          
          void remove_link(const std::string &from, const std::string &to){
            auto pfrom = find(from);
            if(!pfrom) return;
            auto pto = find(to);
            if(!pto) return;   
            
            auto it = std::find(pfrom->links.begin(), pfrom->links.end(), pto);
            if(it == pfrom->links.end()) return;
            pfrom->links.erase(it);
          }

          void remove_nodo(const std::string &key){
            //encontrar se aquele nodo é vizinho de algum outro nodo e remover
            auto p = find(key);
            if(!p) return;
            for(auto &[k,nd] : nodes){
              auto it = std::find(nd.links.begin(), nd.links.end(), p);
              if(it != nd.links.end()) nd.links.erase(it);
            }
            nodes.erase(key);
          }

          void recursive_DFS(node* p, int level = 0){
            if(visited.count(p) > 0)//ja foi visitado
            return;
            std::cout << std::string(level, '\t') << p->value << std::endl;
            visited.insert(p);
            for(auto ln : p->links){
              recursive_DFS(ln, level+1);
            }
          } 

          void DFS_from(const std::string &s){
            auto p = find(s);
            if(!p) return;
            visited.clear();
            recursive_DFS(p);
          }
        */
    }; /// fim da classe digraph
} //fim do namespace
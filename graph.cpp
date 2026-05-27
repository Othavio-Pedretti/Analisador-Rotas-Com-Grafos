/// biblioteca para grafos
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>

namespace graph{

    class digraph{
        private:
          // nodos do grafo - VERTÍCES
          struct node{
            std::string prb_id;
            std::string probe_src;
            std::string dst_addr;
            std::string rtt;
            std::vector<node*> links; //lista de ponteiros p/ os nodos vizinhos - ARESTAS
          };

          //tabela hash, que mapeia o rótulo do nó para o objeto node
                             //<chave>, <valor>    
          std::unordered_map<std::string,node> nodes;
          std::unordered_set<node*> visited;
        
        public:
         //Insere um novo nó no grafo com o rótulo s
          void insert_nodo(const std::string& hop, 
                            const std::string& prb_id, 
                            const std::string& probe_src, 
                            const std::string& dst_addr, 
                            const std::string& rtt){
            node aux;
            aux.prb_id = prb_id;
            aux.probe_src = probe_src;
            aux.dst_addr = dst_addr;
            aux.rtt = rtt; 
            nodes[hop] = aux;
          }

          

          //retorna a quantidade de nós (vertices) do grafo
          size_t size(){
            return nodes.size();
          }
            
          /*
          //busca um nó pelo seu rótulo e retorna o endereço do nodo 
          node* find(const std::string& s){
            auto it = nodes.find(s);//este find é do unordere_map
            return it==nodes.end() ?  nullptr : &it->second;
          }

          //INsere um aresta dirigida de 'from' para 'to'
          bool insert_link(const std::string& hop_from, const std::string& hop_to){
            auto pfrom = find(hop_from);
            if(pfrom == nullptr) return false; // nó de origem ñ existe
            auto pto = find(hop_to);
            if(pto == nullptr) return false; // nó de destino ñ existe

            pfrom->links.push_back(pto); //Adiciona a aresta na lista de adjacencia
            return true;
          }

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
                  if(link->value == s){
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

          void export2dot(const std::string& filename){
            std::ofstream dot(filename); // cria o arquivo
            dot << "digraph {\n";
            
            for(auto nd : nodes){ //  percorre todos os nodos
              dot << "\t" << nd.first; //escreve o rotulo do nodo (chave) 
              if(nd.second.links.size() > 0){
                dot << " -> {";
                for(auto vizinho : nd.second.links){
                  dot << vizinho->value << " ";
                }
                dot << "}"; //fecha chave da lista dos vizinhos
              }
              dot << ";\n"; 
            }
            dot << "}\n";//fecha chaves do digraph
            
          }
          
          void draw(){
            export2dot("graphED2.dot");
            std::system("dot -Tx11 graphED2.dot");

          }

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
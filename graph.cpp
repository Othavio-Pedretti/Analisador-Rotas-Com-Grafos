//biblioteca para grafos
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <cstdlib>

namespace graph{

    class digraph{
        private:
            // nodos do grafo - VERTICES
            struct node{
                std::string value; //valor
                std::vector<node*> links; //vizinhos: lista de ponteiros para os nodos vizinhos -ARESTAS --NESTE CASO IRA APENAS O HOP_TO
            }; 

        //tabela hash, que mapeia o rotulo do no para o objeto node
                            //<chave>, <valor>
        std::unordered_map<std::string, node> nodes;

        public:
            //insere um novo nodo no grafo com o rotulo s
            void insert_node(const std::string& s){
                node aux;
                aux.value = s;
                nodes[s] = aux;
            }
        
            //retorna a quantidade de nodos do grafo
         size_t size(){
            return nodes.size();
         }

        //busca um node pelo seu rotulo e retorna o endereço do nodo
        node* find(const std::string& s){
            auto it = nodes.find(s);
            return it == nodes.end() ? nullptr : &it->second;
        }

        //insere um aresta de 'from' para 'to'
        bool insert_link(const std::string& from, const std::string& to){
            auto pfrom = find(from);
            if(pfrom == nullptr) return false; //nodo de origem nao existe
            auto pto = find(to);
            if(pto == nullptr) return false; //nodo de destino nao existe

            pfrom->links.push_back(pto);//adiciona a aresta na lista
            return true;
        }
    };

}  //fim do namespace






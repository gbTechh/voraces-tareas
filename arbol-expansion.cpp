#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

class Grafo {
public:
    vector<tuple<int, vector<tuple<int, int>>>> nodos;
    vector<int> caminos;

    Grafo(int valor = 0) {
        nodos.resize(valor);
        for (int i = 0; i < valor; ++i) {
            std::get<0>(nodos[i]) = i; 
            std::get<1>(nodos[i]) = std::vector<std::tuple<int, int>>{};
        }
    }

    void insertNode(int v1, int v2, int peso) {
        // Asegurar que ambos nodos existan
        int max_node = max(v1, v2);
        if (max_node >= nodos.size()) {
            nodos.resize(max_node + 1);
            // Inicializar los nodos nuevos
            for (int i = 0; i < nodos.size(); ++i) {
                if (std::get<1>(nodos[i]).empty() && std::get<0>(nodos[i]) == 0 && i != 0) {
                    std::get<0>(nodos[i]) = i;
                    std::get<1>(nodos[i]) = std::vector<std::tuple<int, int>>{};
                }
            }
        }
        
        // Agregar arista de v1 a v2 si no existe
        if (!findNode(v1, v2)) {
            std::get<1>(nodos[v1]).push_back(std::make_tuple(v2, peso));
        }

        // Agregar arista de v2 a v1 si no existe (grafo no dirigido)
        if (!findNode(v2, v1)) {
            std::get<1>(nodos[v2]).push_back(std::make_tuple(v1, peso));
        }
    }

    bool findNode(int nodo_origen, int v) {
        if (nodo_origen >= nodos.size()) {
            return false; // Nodo origen no existe
        }
        // Recorre el vector de tuplas en get<1>(nodos[nodo_origen])
        for (const auto& tupla : std::get<1>(nodos[nodo_origen])) {
            if (std::get<0>(tupla) == v) {
                return true;
            }
        }
        return false;
    }

    void printGraph() {
        for (size_t i = 0; i < nodos.size(); ++i) {
            std::cout << i << ": [";
            const auto& aristas = std::get<1>(nodos[i]);
            for (size_t j = 0; j < aristas.size(); ++j) {
                int vecino = std::get<0>(aristas[j]);
                int peso = std::get<1>(aristas[j]);
                std::cout << "(" << vecino << ", " << peso << ")";
                if (j < aristas.size() - 1) std::cout << ", ";
            }
            std::cout << "]" << std::endl;
        }
    }

    tuple<int, int> minValueNodo(int nodoInicial, vector<int>& nodosVector) {
      cout<<"Nodo inicial min value: "<<nodoInicial<<endl;
      auto& vecTuplas = get<1>(nodos[nodoInicial]);
      if (vecTuplas.empty()) {
          return make_tuple(-1, INT_MAX);  // Vector vacío → retorna error
      }

      // Ordenamos las tuplas por peso (de menor a mayor) para facilitar la búsqueda
      sort(vecTuplas.begin(), vecTuplas.end(), 
          [](const auto& a, const auto& b) { return get<1>(a) < get<1>(b); });

      // 1. Buscar el primer nodo (con menor peso) que NO esté en nodosVector
      for (const auto& tupla : vecTuplas) {
          int nodoDestino = get<0>(tupla);
          if (!existeEnVector(nodosVector, nodoDestino)) {
              return tupla;  // Devuelve la primera tupla válida encontrada
          }
      }

      // 2. Si todos los nodos están en nodosVector, devolver el último elemento de nodosVector
      if (!nodosVector.empty()) {
          int ultimoNodo = nodosVector[nodosVector.size() - 2];    
          cout<<"*****ultimo nodo"<<ultimoNodo<<endl;
          // Buscar la tupla correspondiente al último nodo en nodosVector
          for (const auto& tupla : vecTuplas) {
            cout<<"TUPLAAA"<<get<0>(tupla)<<endl;
              if (get<1>(tupla) == ultimoNodo) {
                cout<<"E N CON TR A DO"<<endl;
                  return tupla;
              }
          }
      }

      // Si nodosVector está vacío o no se encontró el último nodo, devolver error
      return make_tuple(-1, INT_MAX);
    }

    bool existeEnVector(const std::vector<int>& vec, int elemento) {
      return std::find(vec.begin(), vec.end(), elemento) != vec.end();
    }



    int prim(int nodoInicial, int nodosRecorridos, int & caminoPeso, vector<int> & nodosVector){
      cout<<"nodo inicial: "<<nodoInicial<<", "<<nodosRecorridos<<", "<<caminoPeso<<"\n";
      if (nodosRecorridos == 2) {
        return caminoPeso;
      }
      auto tuplaMin = minValueNodo(nodoInicial, nodosVector);
      int nodo = get<0>(tuplaMin);
      int min = get<1>(tuplaMin);
      caminoPeso += min;
      cout<<"NODO :"<<nodo<<endl;
      nodosVector.push_back(nodo);
      if(!existeEnVector(nodosVector, nodo)){
        nodosRecorridos--;
      }
      
      prim(nodo, nodosRecorridos , caminoPeso, nodosVector);

      return caminoPeso;
    }

    int primAlgoritmo(int nodoInicial){
      size_t size = nodos.size();
      int p = 0;
      vector<int> nodosVector(size);
      return prim(nodoInicial, size, p, nodosVector);
    }
};

int main() {
    Grafo grafo(8); // Inicializa con 8 nodos
    
    grafo.insertNode(0, 1, 10); // Arista 0-10 con peso 1
    grafo.insertNode(0, 3, 15); // Arista 0-15 con peso 3
    grafo.insertNode(0, 2, 7);  // Arista 0-7 con peso 2
    grafo.insertNode(1, 4, 3);  // Arista 1-8 con peso 5
    grafo.insertNode(1, 5, 8);  // Arista 1-3 con peso 4
    grafo.insertNode(2, 7, 9); // Arista 4-14 con peso 5
    grafo.insertNode(2, 6, 12);  // Arista 5-5 con peso 2 (self-loop)
    grafo.insertNode(2, 5, 5);  // Arista 5-6 con peso 6
    grafo.insertNode(5, 6, 6); // Arista 6-12 con peso 2
    grafo.insertNode(4, 5, 14);  // Arista 2-9 con peso 7
    
    grafo.printGraph();

    int prim = grafo.primAlgoritmo(0);

    cout<<"prim: "<<prim<<"\n";
    return 0;
}

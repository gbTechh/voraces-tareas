#include <iostream>
#include <vector>

using namespace std;

int main() { 
	int T; cin >> T;

	vector<vector<int>> matriz(T, vector<int>(2));
	
	
	for (int t = 0; t < T; t++) { 
		int g;
		int d;
		cin >> g >> d;
		matriz[t][0] = g;
		matriz[t][1] = d;	
		
		if (g == 0) {
			return 0;
		}
		
	}
	
	int cero;
	cin>>cero;
	if (cero != 0){
		return 0;
	}
	
	int maximo = matriz[0][1]; // Inicializar con el primer valor de la segunda columna
	
	for (size_t i = 1; i < matriz.size(); i++) {
		if (matriz[i][1] > maximo) {
			maximo = matriz[i][1];
		}
	}
	vector<int> arr;
	int b = 0;	
	
	for (int i = maximo; i > 0; i--) {
		int mejor_g = 0;
		int mejor_indice = -1;		
	
		for (size_t j = 0; j < matriz.size(); j++) {
			if(matriz[j][1] == i && matriz[j][0] > mejor_g) {
				mejor_g = matriz[j][0];
				mejor_indice = j;
			}
		}
		
		
		if (mejor_g > 0 && mejor_indice != -1) {
			b += mejor_g;
			arr.push_back(mejor_indice + 1); // +1 porque los índices empiezan en 0
		}
	}
	
	/*cout << "Recorrido con índices:" << endl;
	for (size_t i = 0; i < matriz.size(); i++) {
		for (size_t j = 0; j < matriz[i].size(); j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}*/
	cout<<b<<"\n";
	for (size_t i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	
	
	
	

	
	return 0; 
}


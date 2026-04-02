#include <iostream>
#include <fstream>
#include <vector>
#include <random>
using namespace std;

random_device rd;
mt19937 gen(rd());

vector<int> lista_random(int n) {
    uniform_int_distribution<> dist(0, 1000000);
    vector<int> v(n);
    for(int &x : v) x = dist(gen);
    return v;
}

vector<int> lista_sortata(int n) {
    vector<int> v(n);
    for(int i = 0; i < n; i++) v[i] = i+1;
    return v;
}

vector<int> lista_invers(int n) {
    vector<int> v(n);
    for(int i = 0; i < n; i++) v[i] = n-i;
    return v;
}

vector<int> lista_aproape(int n, double procent=0.05) {
    vector<int> v = lista_sortata(n);
    int swaps = n*procent;
    uniform_int_distribution<> dist(0,n-1);
    for(int i=0;i<swaps;i++){
        int a = dist(gen);
        int b = dist(gen);
        swap(v[a],v[b]);
    }
    return v;
}

void scrie_in_fisier(const string &nume, const vector<int>& v){
    ofstream fout(nume);
    fout << v.size() << "\n";
    for(int x:v) fout << x << " ";
    fout << "\n";
    fout.close();
}

int main() {
    vector<int> dimensiuni = {1000000};
    for(int n: dimensiuni){
        scrie_in_fisier("random_" + to_string(n) + ".txt", lista_random(n));
        scrie_in_fisier("sortat_" + to_string(n) + ".txt", lista_sortata(n));
        scrie_in_fisier("invers_" + to_string(n) + ".txt", lista_invers(n));
        scrie_in_fisier("aproape_" + to_string(n) + ".txt", lista_aproape(n));
        cout << "Generat liste pentru n=" << n << "\n";
    }
    return 0;
}
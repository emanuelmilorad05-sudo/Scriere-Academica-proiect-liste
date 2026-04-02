#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

void afisare_lista(int n, const vector<int>& vec, ofstream& fout) {
    for (int i = 0; i < n; i++)
        fout << vec[i] << " ";
    fout << "\n";
}

void bubble_sort(int n, vector<int>& vec) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (vec[j] > vec[j + 1])
                swap(vec[j], vec[j + 1]);
}

void selection_sort(int n, vector<int>& vec) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (vec[j] < vec[min])
                min = j;
        swap(vec[i], vec[min]);
    }
}

void insertion_sort(int n, vector<int>& vec) {
    for (int i = 1; i < n; i++) {
        int aux = vec[i];
        int j = i - 1;
        while (j >= 0 && aux < vec[j]) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = aux;
    }
}

void merge(vector<int>& vec, int st, int mid, int dr) {
    vector<int> temp;
    int i = st, j = mid + 1;
    while (i <= mid && j <= dr)
        temp.push_back(vec[i] <= vec[j] ? vec[i++] : vec[j++]);
    while (i <= mid) temp.push_back(vec[i++]);
    while (j <= dr)  temp.push_back(vec[j++]);
    for (int k = 0; k < (int)temp.size(); k++)
        vec[st + k] = temp[k];
}

void merge_sort_rec(vector<int>& vec, int st, int dr) {
    if (st < dr) {
        int mid = (st + dr) / 2;
        merge_sort_rec(vec, st, mid);
        merge_sort_rec(vec, mid + 1, dr);
        merge(vec, st, mid, dr);
    }
}

void merge_sort(int n, vector<int>& vec) {
    merge_sort_rec(vec, 0, n - 1);
}

void ruleaza_sort(const string& nume,
                  void (*sortFn)(int, vector<int>&),
                  int n,
                  const vector<int>& original,
                  ofstream& fout)
{
    vector<int> vec = original;
    auto start = high_resolution_clock::now();
    sortFn(n, vec);
    auto stop  = high_resolution_clock::now();

    double sec = duration<double>(stop - start).count();

    fout << "=== " << nume << " ===\n";
    fout << "Timp: " << fixed << setprecision(6) << sec << " secunde\n";
    fout << "Rezultat: ";
    afisare_lista(n, vec, fout);
    fout << "\n";
    cout << fixed << setprecision(6);
    cout << "[" << nume << "] Timp: " << sec << " secunde\n";
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin) { cerr << "Eroare: nu pot deschide input.txt\n"; return 1; }
    if (!fout) { cerr << "Eroare: nu pot deschide output.txt\n"; return 1; }

    int n;
    fin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
        fin >> vec[i];

    cout << "Citit " << n << " elemente din input.txt\n\n";

    ruleaza_sort("Bubble Sort",    bubble_sort,    n, vec, fout);
    ruleaza_sort("Selection Sort", selection_sort, n, vec, fout);
    ruleaza_sort("Insertion Sort", insertion_sort, n, vec, fout);
    ruleaza_sort("Merge Sort",     merge_sort,     n, vec, fout);

    cout << "\nRezultatele au fost scrise in output.txt\n";
    return 0;
}
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#define MAX 100
using namespace std;

// Fungsi untuk menampilkan matriks dengan rapi
void tampilkanMatriks(int bobot[MAX][MAX], string namaSimpul[MAX], int jumlahSimpul) {
    cout << "\nMatriks Bobot (Jarak Antar Halte dalam KM):\n";
    cout << setw(15) << " ";
    for (int i = 0; i < jumlahSimpul; i++) {
        cout << setw(15) << namaSimpul[i];
    }
    cout << "\n";

    for (int i = 0; i < jumlahSimpul; i++) {
        cout << setw(15) << namaSimpul[i];
        for (int j = 0; j < jumlahSimpul; j++) {
            if (bobot[i][j] == 0)
                cout << setw(15) << "-";
            else
                cout << setw(15) << bobot[i][j];
        }
        cout << "\n";
    }
}

// Algoritma Dijkstra untuk mencari rute terpendek
void dijkstra(int asal, int tujuan, int bobot[MAX][MAX], int jumlahSimpul, string namaSimpul[MAX]) {
    vector<int> dist(jumlahSimpul, INT_MAX);
    vector<int> prev(jumlahSimpul, -1);
    vector<bool> visited(jumlahSimpul, false);
    dist[asal] = 0;

    for (int i = 0; i < jumlahSimpul - 1; i++) {
        int u = -1;

        for (int j = 0; j < jumlahSimpul; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INT_MAX)
            break;

        visited[u] = true;

        for (int v = 0; v < jumlahSimpul; v++) {
            if (bobot[u][v] && !visited[v] && dist[u] + bobot[u][v] < dist[v]) {
                dist[v] = dist[u] + bobot[u][v];
                prev[v] = u;
            }
        }
    }

    // Rekonstruksi rute
    vector<int> path;
    for (int v = tujuan; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    // Tampilkan hasil
    cout << "\nRute yang dilewati:\n";
    for (int i = 0; i < path.size(); i++) {
        cout << namaSimpul[path[i]];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\nJarak total: " << dist[tujuan] << " km\n";
}

int main() {
    int jumlahSimpul = 11;
    string namaSimpul[MAX] = {
        "Bandara", "Prambanan", "Kalasan", "Maguwoharjo", 
        "Janti", "Malioboro", "Tugu", "Gondomanan", 
        "UGM", "Condong Catur", "Terminal Jombor"
    };

    int bobot[MAX][MAX] = {0};

    // Input bobot (jarak antar halte)
    bobot[0][1] = 10; bobot[1][0] = 8;
    bobot[1][2] = 5;  bobot[2][1] = 5;
    bobot[2][3] = 7;  bobot[3][2] = 7;
    bobot[3][4] = 5;  bobot[4][3] = 5;
    bobot[4][5] = 10; bobot[5][4] = 10;
    bobot[5][6] = 3;  bobot[6][5] = 3;
    bobot[6][7] = 6;  bobot[7][6] = 6;
    bobot[7][1] = 20; bobot[1][7] = 20;
    bobot[8][6] = 5;  bobot[6][8] = 5;
    bobot[9][10] = 7; bobot[10][9] = 7;
    bobot[10][6] = 10; bobot[6][10] = 10;
    bobot[6][9] = 15; bobot[9][6] = 15;

    // Tampilkan matriks bobot
    tampilkanMatriks(bobot, namaSimpul, jumlahSimpul);

    // Input halte asal dan tujuan
    int asal, tujuan;
    cout << "\nMasukkan nomor halte asal (0 - 10): ";
    cin >> asal;
    cout << "Masukkan nomor halte tujuan (0 - 10): ";
    cin >> tujuan;

    // Validasi input
    if (asal < 0 || asal >= jumlahSimpul || tujuan < 0 || tujuan >= jumlahSimpul) {
        cout << "Nomor halte tidak valid.\n";
        return 0;
    }

    // Cari rute terpendek
    dijkstra(asal, tujuan, bobot, jumlahSimpul, namaSimpul);

    return 0;
}
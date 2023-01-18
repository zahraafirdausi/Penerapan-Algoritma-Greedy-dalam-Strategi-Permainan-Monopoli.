#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NEG 27
#define COL 6
#define MAX_CHAR 20

// membalik urutan dalam array
void reverse(double arr[][COL]){
    double bantu[1][COL];
    int i, j;
    for(i=0; i<NEG/2; i++){
        for(j=0; j<COL; j++){                   // a,b,c,d
            bantu[0][j] = arr[i][j];            // bantu=a
            arr[i][j] = arr[NEG-1-i][j];        // a=d
            arr[NEG-1-i][j] = bantu[0][j];      // d=bantu
        }
    }
}

// menggabungkan 2 subarray
void merge(double arr[][COL], int l, int m, int r, int kolom) {
    int i, j, k, x;
    int n1 = m - l + 1;
    int n2 = r - m;
    double L[n1][COL], R[n2][COL]; // buat temp array
    
    
    // Copy data ke array L[] dan R[]
    for (i = 0; i < n1; i++){
        for (j = 0; j < COL; j++){
            L[i][j] = arr[l + i][j];
        }
    }
    for (i = 0; i < n2; i++){
        for (j = 0; j < COL; j++){
            R[i][j] = arr[m + 1 + i][j];
        }
    }
    
    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i][kolom] <= R[j][kolom]) {
            for (x = 0; x < COL; x++){
                arr[k][x] = L[i][x];
            }
            i++;
        } else {
            for (x = 0; x < COL; x++){
                arr[k][x] = R[j][x];
            }
            j++;
        }
        k++;
    }
    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        for (x = 0; x < COL; x++){
            arr[k][x] = L[i][x];
        }
        i++;
        k++;
    }
    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        for (x = 0; x < COL; x++){
            arr[k][x] = R[j][x];
        }
        j++;
        k++;
    }
}

/* membagi array jadi 2 bagian, masing-masing dimergeSort, lalu hasil keduanya digabung */
void mergeSort(double arr[][COL], int l, int r, int kolom) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, kolom);
        mergeSort(arr, m + 1, r, kolom);
        merge(arr, l, m, r, kolom);
    }
}

int main() {
    double arr[NEG][COL]={0};
    int i, x, urutBy, a, b, c;

    // input array isinya {(cost, rent, frek, profit, density, id_negara)}
    for( i = 0; i < NEG; i++){
        scanf("%d %d %d", &a, &b, &c);
        arr[i][0] = a;
        arr[i][1] = b;
        arr[i][2] = c;
    }
    // hitung profit & density
    for( i = 0; i < NEG; i++){
        arr[i][3] = arr[i][1] * arr[i][2]; // profit = rent*frek    -> dibalik
        arr[i][4] = arr[i][3] / arr[i][0]; // density = profit/cost -> dibalik
        arr[i][5] = i;                             // id_negara
    }

    // mengurutkan
    scanf("%d", &urutBy);
    if (urutBy==0){    // by density
        mergeSort(arr, 0, NEG-1, 4);
        reverse(arr);
    } else if (urutBy == 1){ // by profit
        mergeSort(arr, 0, NEG-1, 3);
        reverse(arr);
    } else if (urutBy == 2){ // by cost
        mergeSort(arr, 0, NEG-1, 0);
    } else {
        printf("Input tidak valid\n");
    }

    // memasukkan data nama negara
    char negara[NEG][MAX_CHAR]={
        "Libya",
        "Sudan",
        "Station Japan",
        "Turkey",
        "Greece",
        "Bulgaria",
        "Poland",
        "Russia",
        "Ukraine",
        "Vatican",
        "Station Spain",
        "Lithuania",
        "Latvia",
        "Estonia",
        "Norway",
        "Sweden",
        "Finland",
        "Station USA",
        "Germany",
        "France",
        "United Kingdom",
        "Canada",
        "Mexico",
        "USA",
        "Station UK",
        "Qatar",
        "China"
    };
    // Greedy
    int modal, totalCost, untung;
    scanf("%d", &modal);
    totalCost = 0;
    untung = 0;
    
    printf("Daftar negara yang dibeli:\n");
    i = 0;
    for (i = 0; i < NEG; i++){
        if (totalCost+arr[i][0] <= modal){
            x = (int) arr[i][5];
            printf("-%d %s\n", x+1 ,negara[x]);
            untung += (int)arr[i][3];
            totalCost += arr[i][0];
        }
    }

    // statistik
    printf("Modal       : %d\n", modal);
    printf("Total biaya : %d\n", totalCost);
    printf("Sisa uang   : %d\n", modal-totalCost);
    printf("Keuntungan diharapkan: %d\n", untung);
    return 0;
}
/*
input: 
50  5   1
60  10  6
200 25  9
100 10  1
100 10  7
120 16  5
150 16  5
150 16  10
180 20  6
200 22  2
200 25  7
200 20  4
200 20  7
220 30  6
220 30  6
220 30  5
240 40  8
200 25  4
280 40  7
280 40  7
300 50  2
300 50  5
300 50  8
320 60  5
200 25  7
360 60  2
400 80  7
0 2000
*/

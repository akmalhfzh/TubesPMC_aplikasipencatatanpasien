#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    int tahun;
    int bulan;
    double revenue;
} PendapatanBulanan;

void parse_date(const char *date, int *tahun, int *bulan) {
    sscanf(date, "%d-%d", tahun, bulan);
}

void process_csv(const char *namafile) {
    FILE *file = fopen(namafile, "r");
    if (file == NULL) {
        perror("File tidak dapat dibuka");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    PendapatanBulanan pendapatan_bulanan[100];
    int monthly_count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        char date[20];
        double cost;
        int tahun, bulan;
        
        // baca tanggal
        token = strtok(NULL, ",");
        strcpy(date, token);
        
        // baca harga
        for (int i = 0; i < 5; i++) {
            token = strtok(NULL, ",");
        }
        cost = atof(token);

        parse_date(date, &tahun, &bulan);

        // Total Pendapatan
        int found = 0;
        for (int i = 0; i < monthly_count; i++) {
            if (pendapatan_bulanan[i].tahun == tahun && pendapatan_bulanan[i].bulan == bulan) {
                pendapatan_bulanan[i].revenue += cost;
                found = 1;
                break;
            }
        }
        if (!found) {
            pendapatan_bulanan[monthly_count].tahun = tahun;
            pendapatan_bulanan[monthly_count].bulan = bulan;
            pendapatan_bulanan[monthly_count].revenue = cost;
            monthly_count++;
        }
    }

    fclose(file);

    double pendapatan_tahunan[100] = {0};
    int annual_count = 0;

    printf("Monthly Revenue:\n");
    for (int i = 0; i < monthly_count; i++) {
        printf("Tahun: %d, Bulan: %d, Revenue: %.2f\n", pendapatan_bulanan[i].tahun, pendapatan_bulanan[i].bulan, pendapatan_bulanan[i].revenue);
        pendapatan_tahunan[pendapatan_bulanan[i].tahun - 2022] += pendapatan_bulanan[i].revenue;
    }

    printf("\nPendapatan Tahunan:\n");
    for (int i = 0; i < 100; i++) {
        if (pendapatan_tahunan[i] > 0) {
            printf("Tahun: %d, Revenue: %.2f\n", 2022 + i, pendapatan_tahunan[i]);
            annual_count++;
        }
    }

    double pendapatan_total = 0;
    for (int i = 0; i < 100; i++) {
        pendapatan_total += pendapatan_tahunan[i];
    }
    double pendapatan_ratarata = pendapatan_total / annual_count;
    printf("\nAverage Annual Revenue: %.2f\n", pendapatan_ratarata);
}

int main() {
    process_csv("riwayat_tindakan.csv");
    return 0;
}


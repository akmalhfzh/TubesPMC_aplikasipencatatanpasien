#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_YEARS 10
#define MAX_MONTHS 12

typedef struct {
    int year;
    int month;
    double revenue;
} Revenue;

typedef struct {
    int year;
    double revenue;
} AnnualRevenue;

// Fungsi untuk memparse tanggal dalam format DD-MM-YYYY
void parse_date(const char *date, int *day, int *month, int *year) {
    sscanf(date, "%d-%d-%d", day, month, year);
}

void process_csv(const char *filename, Revenue monthly_revenues[], int *monthly_count, AnnualRevenue annual_revenues[], int *annual_count, double *total_revenue) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); // Skip header line

    *monthly_count = 0;
    *annual_count = 0;
    *total_revenue = 0.0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        char date[20];
        double cost;
        int day, month, year;

        // Skip irrelevant column (kolom pertama)
        token = strtok(NULL, ",");

        // Baca tanggal dari kolom kedua
        token = strtok(NULL, ",");
        strcpy(date, token);

        // Skip irrelevant columns (kolom ketiga hingga keenam)
        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ",");
        }

        // baca biaya (kolom ketujuh)
        cost = atof(strtok(NULL, ","));

        // Parse tanggal untuk mendapatkan hari, bulan, tahun
        parse_date(date, &day, &month, &year);

        // Aggregate monthly revenue
        int found = 0;
        for (int i = 0; i < *monthly_count; i++) {
            if (monthly_revenues[i].year == year && monthly_revenues[i].month == month) {
                monthly_revenues[i].revenue += cost;
                found = 1;
                break;
            }
        }
        if (!found) {
            monthly_revenues[*monthly_count].year = year;
            monthly_revenues[*monthly_count].month = month;
            monthly_revenues[*monthly_count].revenue = cost;
            (*monthly_count)++;
        }

        // Aggregate annual revenue
        found = 0;
        for (int i = 0; i < *annual_count; i++) {
            if (annual_revenues[i].year == year) {
                annual_revenues[i].revenue += cost;
                found = 1;
                break;
            }
        }
        if (!found) {
            annual_revenues[*annual_count].year = year;
            annual_revenues[*annual_count].revenue = cost;
            (*annual_count)++;
        }

        *total_revenue += cost;
    }

    fclose(file);
}

int main() {
    Revenue monthly_revenues[MAX_YEARS * MAX_MONTHS] = {0};
    AnnualRevenue annual_revenues[MAX_YEARS] = {0};
    int monthly_count, annual_count;
    double total_revenue;

    process_csv("RiwayatPasien.csv", monthly_revenues, &monthly_count, annual_revenues, &annual_count, &total_revenue);

    printf("Pendapatan Bulanan:\n");
    for (int i = 0; i < monthly_count; i++) {
        printf("Tahun: %d, Bulan: %d, Pendapatan: %.2f\n", monthly_revenues[i].year, monthly_revenues[i].month, monthly_revenues[i].revenue);
    }

    printf("\nPendapatan Tahunan:\n");
    for (int i = 0; i < annual_count; i++) {
        printf("Tahun: %d, Pendapatan: %.2f\n", annual_revenues[i].year, annual_revenues[i].revenue);
    }

    printf("\nTotal Pendapatan Klinik: %.2f\n", total_revenue);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_YEARS 10
#define MAX_MONTHS 12

typedef struct RiwayatPasien {
    int indeksriwayat;
    char tanggal_kunjungan[20];
    char id_pasien[50];
    char diagnosis[100];
    char tindakan[100];
    char kontrol[20];
    double biaya;
    struct RiwayatPasien *next;
} RiwayatPasien;

// Fungsi untuk memparse tanggal dalam format DD-MM-YYYY
void parse_date(const char *date, int *day, int *month, int *year) {
    sscanf(date, "%d-%d-%d", day, month, year);
}

// Fungsi untuk memeriksa apakah ada data pendapatan bulanan yang sudah ada
int find_monthly_index(RiwayatPasien *monthly_revenues, int count, int year, int month) {
    for (int i = 0; i < count; i++) {
        int day, m, y;
        parse_date(monthly_revenues[i].tanggal_kunjungan, &day, &m, &y);
        if (y == year && m == month) {
            return i;
        }
    }
    return -1;
}

// Fungsi untuk memeriksa apakah ada data pendapatan tahunan yang sudah ada
int find_annual_index(RiwayatPasien *annual_revenues, int count, int year) {
    for (int i = 0; i < count; i++) {
        int day, month, y;
        parse_date(annual_revenues[i].tanggal_kunjungan, &day, &month, &y);
        if (y == year) {
            return i;
        }
    }
    return -1;
}

void process_csv(const char *filename, RiwayatPasien monthly_revenues[], int *monthly_count, RiwayatPasien annual_revenues[], int *annual_count, double *total_revenue) {
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
        RiwayatPasien riwayat;
        // Inisialisasi riwayat untuk menghindari data sisa
        memset(&riwayat, 0, sizeof(RiwayatPasien));
        
        sscanf(line, "%d,%19[^,],%49[^,],%99[^,],%99[^,],%19[^,],%lf",
               &riwayat.indeksriwayat, riwayat.tanggal_kunjungan, riwayat.id_pasien,
               riwayat.diagnosis, riwayat.tindakan, riwayat.kontrol, &riwayat.biaya);

        int day, month, year;
        parse_date(riwayat.tanggal_kunjungan, &day, &month, &year);

        // Menghitung total pendapatan tiap bulan
        int monthly_index = find_monthly_index(monthly_revenues, *monthly_count, year, month);
        if (monthly_index != -1) {
            monthly_revenues[monthly_index].biaya += riwayat.biaya;
        } else {
            if (*monthly_count < MAX_YEARS * MAX_MONTHS) {  // Pastikan tidak melebihi batas array
                monthly_revenues[*monthly_count] = riwayat;
                (*monthly_count)++;
            } else {
                printf("Warning: Monthly revenue array is full, skipping data for month %d/%d\n", month, year);
            }
        }

        // Menghitung total pendapatan tiap tahun
        int annual_index = find_annual_index(annual_revenues, *annual_count, year);
        if (annual_index != -1) {
            annual_revenues[annual_index].biaya += riwayat.biaya;
        } else {
            if (*annual_count < MAX_YEARS) {  // Pastikan tidak melebihi batas array
                annual_revenues[*annual_count] = riwayat;
                (*annual_count)++;
            } else {
                printf("Warning: Annual revenue array is full, skipping data for year %d\n", year);
            }
        }

        *total_revenue += riwayat.biaya;
    }

    fclose(file);
}

int main() {
    RiwayatPasien monthly_revenues[MAX_YEARS * MAX_MONTHS] = {0};
    RiwayatPasien annual_revenues[MAX_YEARS] = {0};
    int monthly_count, annual_count;
    double total_revenue;

    process_csv("RiwayatPasien.csv", monthly_revenues, &monthly_count, annual_revenues, &annual_count, &total_revenue);

    printf("Pendapatan Bulanan:\n");
    for (int i = 0; i < monthly_count; i++) {
        int day, month, year;
        parse_date(monthly_revenues[i].tanggal_kunjungan, &day, &month, &year);
        printf("Tahun: %d, Bulan: %d, Pendapatan: %.2f\n", year, month, monthly_revenues[i].biaya);
    }

    printf("\nPendapatan Tahunan:\n");
    for (int i = 0; i < annual_count; i++) {
        int day, month, year;
        parse_date(annual_revenues[i].tanggal_kunjungan, &day, &month, &year);
        printf("Tahun: %d, Pendapatan: %.2f\n", year, annual_revenues[i].biaya);
    }

    printf("\nTotal Pendapatan Klinik: %.2f\n", total_revenue);

    return 0;
}

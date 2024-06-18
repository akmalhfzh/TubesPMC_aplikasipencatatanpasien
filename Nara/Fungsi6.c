#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data yang digunakan
typedef struct Pasien {
    int indekspasien;
    char nama_pasien[100];
    char alamat[150];
    char kota[50];
    char tempat_lahir[50];
    char tanggal_lahir[30];
    int umur;
    char nomor_bpjs[20];
    char id_pasien[50];
    struct Pasien *next;
} Pasien;

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

typedef struct BiayaTindakan {
    int indekstindakan;
    char aktivitas[20];
    double biayatindakan;
    struct BiayaTindakan *next;
} BiayaTindakan;

typedef struct DiseaseCount {
    char disease[100];
    int count;
    struct DiseaseCount *next;
} DiseaseCount;

typedef struct MonthYearCount {
    char month_year[20];
    int patient_count;
    DiseaseCount *disease_head;
    struct MonthYearCount *next;
} MonthYearCount;

typedef struct YearCount {
    char year[5];
    MonthYearCount *month_head;
    struct YearCount *next;
} YearCount;

// Fungsi untuk menghapus whitespace berlebih di akhir string
void trim_trailing_whitespace(char *str) {
    char *end;
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\n' || *end == '\r')) {
        end--;
    }
    end[1] = '\0';
}

// Fungsi untuk membaca CSV pasien dan menyimpan ke dalam linked list Pasien
int baca_csv_pasien(const char *nama_file, Pasien **head) {
    FILE *file = fopen(nama_file, "r");
    if (file == NULL) {
        printf("File tidak ditemukan.\n");
        return 0;
    }

    char baris[500];
    fgets(baris, sizeof(baris), file);  // Membaca header
    while (fgets(baris, sizeof(baris), file)) {
        Pasien *pasien = (Pasien*)malloc(sizeof(Pasien));
        sscanf(baris, "%d,%99[^,],%149[^,],%49[^,],%49[^,],%29[^,],%d,%19[^,],%49[^,]",
               &pasien->indekspasien, pasien->nama_pasien, pasien->alamat, pasien->kota,
               pasien->tempat_lahir, pasien->tanggal_lahir, &pasien->umur,
               pasien->nomor_bpjs, pasien->id_pasien);
        pasien->next = NULL;
        
        // Trim trailing whitespace
        trim_trailing_whitespace(pasien->id_pasien);

        if (*head == NULL) {
            *head = pasien;
        } else {
            Pasien *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = pasien;
        }
    }
    fclose(file);
    return 1;
}

// Fungsi untuk membaca CSV riwayat dan menyimpan ke dalam linked list RiwayatPasien
int baca_csv_riwayat(const char *nama_file, RiwayatPasien **head) {
    FILE *file = fopen(nama_file, "r");
    if (file == NULL) {
        printf("File tidak ditemukan.\n");
        return 0;
    }

    char baris[500];
    fgets(baris, sizeof(baris), file);  // Membaca header
    while (fgets(baris, sizeof(baris), file)) {
        RiwayatPasien *riwayat = (RiwayatPasien*)malloc(sizeof(RiwayatPasien));
        sscanf(baris, "%d,%19[^,],%49[^,],%99[^,],%99[^,],%19[^,],%lf",
               &riwayat->indeksriwayat, riwayat->tanggal_kunjungan, riwayat->id_pasien,
               riwayat->diagnosis, riwayat->tindakan, riwayat->kontrol, &riwayat->biaya);
        riwayat->next = NULL;
        
        // Trim trailing whitespace
        trim_trailing_whitespace(riwayat->id_pasien);

        if (*head == NULL) {
            *head = riwayat;
        } else {
            RiwayatPasien *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = riwayat;
        }
    }
    fclose(file);
    return 1;
}

// Fungsi untuk menampilkan semua riwayat kunjungan pasien
void tampilkan_riwayat_pasien(RiwayatPasien *head) {
    RiwayatPasien *riwayat = head;
    char ID[20];
    int found;
    printf("Input patient ID: ");
    fgets(ID, 20, stdin);
    ID[strcspn(ID, "\n")] = 0;


    while (riwayat != NULL) {
        if (strcmp(riwayat->id_pasien, ID) == 0) {
            found = 1;
            printf("Tanggal Kunjungan: %s\n", riwayat->tanggal_kunjungan);
            printf("ID Pasien: %s\n", riwayat->id_pasien);
            printf("Diagnosis: %s\n", riwayat->diagnosis);
            printf("Tindakan: %s\n", riwayat->tindakan);
            printf("Kontrol: %s\n", riwayat->kontrol);
            printf("Biaya: %.2f\n", riwayat->biaya);
            printf("-------------------------\n");
            }
        riwayat = riwayat->next;
    }
    if (found == 0){
        printf("\nTheres no patient with the inputted ID!\n\n");
    }
}

int main() {
    Pasien *head_pasien = NULL;
    RiwayatPasien *head_riwayat = NULL;

    // Membaca data dari file CSV
    if (!baca_csv_pasien("DataPasien.csv", &head_pasien)) {
        printf("Gagal membaca file DataPasien.csv.\n");
        return 1;
    }
    if (!baca_csv_riwayat("RiwayatPasien.csv", &head_riwayat)) {
        printf("Gagal membaca file RiwayatPasien.csv.\n");
        return 1;
    }

    // Memanggil fungsi untuk menampilkan semua riwayat pasien
    printf("Informasi riwayat pasien:\n");
    printf("-------------------------\n");
    tampilkan_riwayat_pasien(head_riwayat);

    return 0;
}

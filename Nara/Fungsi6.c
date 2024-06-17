#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Fungsi untuk menghapus whitespace berlebih di akhir string
void trim_trailing_whitespace(char *str) {
    char *end;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    end[1] = '\0';
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

// Fungsi untuk membaca CSV data dan menyimpannya ke dalam linked list Pasien
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
               pasien->tempat_lahir, pasien->tanggal_lahir, &pasien->umur, pasien->nomor_bpjs, pasien->id_pasien);
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

// Fungsi untuk menampilkan informasi kepada petugas medis terkait pasien yang perlu kembali kontrol
void tampilkan_pasien_kontrol(RiwayatPasien *head_riwayat, Pasien *head_pasien) {
    RiwayatPasien *riwayat = head_riwayat;
    while (riwayat != NULL) {
        if (strcmp(riwayat->kontrol, "Y") == 0) {
            Pasien *pasien = head_pasien;
            while (pasien != NULL) {
                if (strcmp(pasien->id_pasien, riwayat->id_pasien) == 0) {
                    printf("Nama Pasien: %s\n", pasien->nama_pasien);
                    printf("Alamat: %s\n", pasien->alamat);
                    printf("Kota: %s\n", pasien->kota);
                    printf("Tempat Lahir: %s\n", pasien->tempat_lahir);
                    printf("Tanggal Lahir: %s\n", pasien->tanggal_lahir);
                    printf("Umur: %d\n", pasien->umur);
                    printf("Nomor BPJS: %s\n", pasien->nomor_bpjs);
                    printf("ID Pasien: %s\n", pasien->id_pasien);
                    printf("Indeks Riwayat: %d\n", riwayat->indeksriwayat);
                    printf("Tanggal Kunjungan: %s\n", riwayat->tanggal_kunjungan);
                    printf("Diagnosis: %s\n", riwayat->diagnosis);
                    printf("Tindakan: %s\n", riwayat->tindakan);
                    printf("Biaya: %.2f\n", riwayat->biaya);
                    printf("-------------------------\n");
                    break;
                }
                pasien = pasien->next;
            }
        }
        riwayat = riwayat->next;
    }
}

int main() {
    Pasien *head_pasien = NULL;
    RiwayatPasien *head_riwayat = NULL;

    if (!baca_csv_pasien("DataPasien.csv", &head_pasien)) {
        return 1;
    }
    if (!baca_csv_riwayat("RiwayatPasien.csv", &head_riwayat)) {
        return 1;
    }

    // Memanggil fungsi untuk menampilkan informasi pasien yang perlu kontrol
    printf("Informasi pasien yang perlu kembali kontrol:\n");
    printf("-------------------------\n");
    tampilkan_pasien_kontrol(head_riwayat, head_pasien);

    return 0;
}

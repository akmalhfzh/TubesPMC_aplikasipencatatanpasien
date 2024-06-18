#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data pasien
typedef struct Pasien {
    int umur;
    int indekspasien;
    char nama_pasien[100];
    char alamat[150];
    char kota[50];
    char tempat_lahir[50];
    char tanggal_lahir[30];
    char nomor_bpjs[20];
    char id_pasien[50];
    struct Pasien *next;
} Pasien;

// Struktur data riwayat pasien
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

Pasien* head_pasien = NULL;
RiwayatPasien* head_riwayat = NULL;

// Fungsi untuk menambah data riwayat pasien
void tambah_riwayat(int indeksriwayat, const char *tanggal_kunjungan, const char *id_pasien, const char *diagnosis, const char *tindakan, const char *kontrol, double biaya) {
    RiwayatPasien *new_riwayat = (RiwayatPasien*)malloc(sizeof(RiwayatPasien));
    new_riwayat->indeksriwayat = indeksriwayat;
    strcpy(new_riwayat->tanggal_kunjungan, tanggal_kunjungan);
    strcpy(new_riwayat->id_pasien, id_pasien);
    strcpy(new_riwayat->diagnosis, diagnosis);
    strcpy(new_riwayat->tindakan, tindakan);
    strcpy(new_riwayat->kontrol, kontrol);
    new_riwayat->biaya = biaya;
    new_riwayat->next = head_riwayat;
    head_riwayat = new_riwayat;
}

// Fungsi untuk menghapus data riwayat pasien berdasarkan id_pasien dan tanggal_kunjungan
void hapus_riwayat(const char *id_pasien, const char *tanggal_kunjungan) {
    RiwayatPasien *current = head_riwayat;
    RiwayatPasien *prev = NULL;

    while (current != NULL && (strcmp(current->id_pasien, id_pasien) != 0 || strcmp(current->tanggal_kunjungan, tanggal_kunjungan) != 0)) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Riwayat dengan ID %s dan tanggal %s tidak ditemukan.\n", id_pasien, tanggal_kunjungan);
        return;
    }

    if (prev == NULL) {
        head_riwayat = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Riwayat dengan ID %s dan tanggal %s telah dihapus.\n", id_pasien, tanggal_kunjungan);
}

// Fungsi untuk mencari data riwayat pasien berdasarkan id_pasien dan tanggal_kunjungan
RiwayatPasien* cari_riwayat(const char *id_pasien, const char *tanggal_kunjungan) {
    RiwayatPasien *current = head_riwayat;

    while (current != NULL) {
        if (strcmp(current->id_pasien, id_pasien) == 0 && strcmp(current->tanggal_kunjungan, tanggal_kunjungan) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Fungsi untuk mengubah data riwayat pasien berdasarkan id_pasien dan tanggal_kunjungan
void ubah_riwayat(const char *id_pasien, const char *tanggal_kunjungan, const char *diagnosis, const char *tindakan, const char *kontrol, double biaya) {
    RiwayatPasien *riwayat = cari_riwayat(id_pasien, tanggal_kunjungan);

    if (riwayat == NULL) {
        printf("Riwayat dengan ID %s dan tanggal %s tidak ditemukan.\n", id_pasien, tanggal_kunjungan);
        return;
    }

    strcpy(riwayat->diagnosis, diagnosis);
    strcpy(riwayat->tindakan, tindakan);
    strcpy(riwayat->kontrol, kontrol);
    riwayat->biaya = biaya;

    printf("Data riwayat dengan ID %s dan tanggal %s telah diubah.\n", id_pasien, tanggal_kunjungan);
}

void input_tambah_riwayat() {
    int indeksriwayat;
    char tanggal_kunjungan[20];
    char id_pasien[50];
    char diagnosis[100];
    char tindakan[100];
    char kontrol[20];
    double biaya;

    printf("Masukkan indeks riwayat: ");
    scanf("%d", &indeksriwayat);
    printf("Masukkan tanggal kunjungan (DD-MM-YYYY): ");
    scanf(" %[^\n]", tanggal_kunjungan);
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id_pasien);
    printf("Masukkan diagnosis: ");
    scanf(" %[^\n]", diagnosis);
    printf("Masukkan tindakan: ");
    scanf(" %[^\n]", tindakan);
    printf("Masukkan kontrol: ");
    scanf(" %[^\n]", kontrol);
    printf("Masukkan biaya: ");
    scanf("%lf", &biaya);

    tambah_riwayat(indeksriwayat, tanggal_kunjungan, id_pasien, diagnosis, tindakan, kontrol, biaya);
}

void input_hapus_riwayat() {
    char id_pasien[50];
    char tanggal_kunjungan[20];
    printf("Masukkan ID pasien yang akan dihapus riwayatnya: ");
    scanf(" %[^\n]", id_pasien);
    printf("Masukkan tanggal kunjungan yang akan dihapus riwayatnya (DD-MM-YYYY): ");
    scanf(" %[^\n]", tanggal_kunjungan);

    hapus_riwayat(id_pasien, tanggal_kunjungan);
}

void input_ubah_riwayat() {
    char tanggal_kunjungan[20];
    char id_pasien[50];
    char diagnosis[100];
    char tindakan[100];
    char kontrol[20];
    double biaya;

    printf("Masukkan ID pasien yang akan diubah riwayatnya: ");
    scanf(" %[^\n]", id_pasien);
    printf("Masukkan tanggal kunjungan yang akan diubah riwayatnya (DD-MM-YYYY): ");
    scanf(" %[^\n]", tanggal_kunjungan);

    printf("Masukkan diagnosis baru: ");
    scanf(" %[^\n]", diagnosis);
    printf("Masukkan tindakan baru: ");
    scanf(" %[^\n]", tindakan);
    printf("Masukkan kontrol baru: ");
    scanf(" %[^\n]", kontrol);
    printf("Masukkan biaya baru: ");
    scanf("%lf", &biaya);

    ubah_riwayat(id_pasien, tanggal_kunjungan, diagnosis, tindakan, kontrol, biaya);
}

void input_cari_riwayat() {
    char id_pasien[50];
    char tanggal_kunjungan[20];
    printf("Masukkan ID pasien yang akan dicari riwayatnya: ");
    scanf(" %[^\n]", id_pasien);
    printf("Masukkan tanggal kunjungan yang akan dicari riwayatnya (DD-MM-YYYY): ");
    scanf(" %[^\n]", tanggal_kunjungan);

    RiwayatPasien *riwayat = cari_riwayat(id_pasien, tanggal_kunjungan);
    if (riwayat != NULL) {
        printf("Data riwayat ditemukan:\n");
        printf("ID Pasien: %s\n", riwayat->id_pasien);
        printf("Tanggal Kunjungan: %s\n", riwayat->tanggal_kunjungan);
        printf("Diagnosis: %s\n", riwayat->diagnosis);
        printf("Tindakan: %s\n", riwayat->tindakan);
        printf("Kontrol: %s\n", riwayat->kontrol);
        printf("Biaya: %.2f\n", riwayat->biaya);
    } else {
        printf("Riwayat dengan ID %s dan tanggal %s tidak ditemukan.\n", id_pasien, tanggal_kunjungan);
    }
}

int main() {
    int pilihan;

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Riwayat\n");
        printf("2. Hapus Riwayat\n");
        printf("3. Ubah Riwayat\n");
        printf("4. Cari Riwayat\n");
        printf("5. Cetak Semua Riwayat\n");
        printf("6. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                input_tambah_riwayat();
                break;
            case 2:
                input_hapus_riwayat();
                break;
            case 3:
                input_ubah_riwayat();
                break;
            case 4:
                input_cari_riwayat();
                break;
            case 5:
                cetak_riwayat();
                break;
            case 6:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (pilihan != 6);

    return 0;
}

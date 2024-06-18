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

Pasien* head_pasien = NULL;

// Fungsi untuk menambah data pasien
void tambah_pasien(int umur, int indekspasien, const char *nama_pasien, const char *alamat, const char *kota, const char *tempat_lahir, const char *tanggal_lahir, const char *nomor_bpjs, const char *id_pasien) {
    Pasien *new_pasien = (Pasien*)malloc(sizeof(Pasien));
    new_pasien->umur = umur;
    new_pasien->indekspasien = indekspasien;
    strcpy(new_pasien->nama_pasien, nama_pasien);
    strcpy(new_pasien->alamat, alamat);
    strcpy(new_pasien->kota, kota);
    strcpy(new_pasien->tempat_lahir, tempat_lahir);
    strcpy(new_pasien->tanggal_lahir, tanggal_lahir);
    strcpy(new_pasien->nomor_bpjs, nomor_bpjs);
    strcpy(new_pasien->id_pasien, id_pasien);
    new_pasien->next = head_pasien;
    head_pasien = new_pasien;
}

// Fungsi untuk menghapus data pasien berdasarkan id_pasien
void hapus_pasien(const char *id_pasien) {
    Pasien *current = head_pasien;
    Pasien *prev = NULL;

    while (current != NULL && strcmp(current->id_pasien, id_pasien) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Pasien dengan ID %s tidak ditemukan.\n", id_pasien);
        return;
    }

    if (prev == NULL) {
        head_pasien = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Pasien dengan ID %s telah dihapus.\n", id_pasien);
}

// Fungsi untuk mencari data pasien berdasarkan id_pasien
Pasien* cari_pasien(const char *id_pasien) {
    Pasien *current = head_pasien;

    while (current != NULL) {
        if (strcmp(current->id_pasien, id_pasien) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Fungsi untuk mengubah data pasien berdasarkan id_pasien
void ubah_pasien(const char *id_pasien, int umur, const char *nama_pasien, const char *alamat, const char *kota, const char *tempat_lahir, const char *tanggal_lahir, const char *nomor_bpjs) {
    Pasien *pasien = cari_pasien(id_pasien);

    if (pasien == NULL) {
        printf("Pasien dengan ID %s tidak ditemukan.\n", id_pasien);
        return;
    }

    pasien->umur = umur;
    strcpy(pasien->nama_pasien, nama_pasien);
    strcpy(pasien->alamat, alamat);
    strcpy(pasien->kota, kota);
    strcpy(pasien->tempat_lahir, tempat_lahir);
    strcpy(pasien->tanggal_lahir, tanggal_lahir);
    strcpy(pasien->nomor_bpjs, nomor_bpjs);

    printf("Data pasien dengan ID %s telah diubah.\n", id_pasien);
}

// Fungsi untuk mencetak data semua pasien (untuk debugging)
void cetak_pasien() {
    Pasien *current = head_pasien;

    while (current != NULL) {
        printf("ID Pasien: %s\n", current->id_pasien);
        printf("Nama: %s\n", current->nama_pasien);
        printf("Alamat: %s\n", current->alamat);
        printf("Kota: %s\n", current->kota);
        printf("Tempat Lahir: %s\n", current->tempat_lahir);
        printf("Tanggal Lahir: %s\n", current->tanggal_lahir);
        printf("Umur: %d\n", current->umur);
        printf("Nomor BPJS: %s\n\n", current->nomor_bpjs);
        current = current->next;
    }
}

void input_tambah_pasien() {
    int umur, indekspasien;
    char nama_pasien[100];
    char alamat[150];
    char kota[50];
    char tempat_lahir[50];
    char tanggal_lahir[30];
    char nomor_bpjs[20];
    char id_pasien[50];

    printf("Masukkan umur: ");
    scanf("%d", &umur);
    printf("Masukkan indeks pasien: ");
    scanf("%d", &indekspasien);
    printf("Masukkan nama pasien: ");
    scanf(" %[^\n]", nama_pasien);
    printf("Masukkan alamat: ");
    scanf(" %[^\n]", alamat);
    printf("Masukkan kota: ");
    scanf(" %[^\n]", kota);
    printf("Masukkan tempat lahir: ");
    scanf(" %[^\n]", tempat_lahir);
    printf("Masukkan tanggal lahir (DD-MM-YYYY): ");
    scanf(" %[^\n]", tanggal_lahir);
    printf("Masukkan nomor BPJS: ");
    scanf(" %[^\n]", nomor_bpjs);
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id_pasien);

    tambah_pasien(umur, indekspasien, nama_pasien, alamat, kota, tempat_lahir, tanggal_lahir, nomor_bpjs, id_pasien);
}

void input_hapus_pasien() {
    char id_pasien[50];
    printf("Masukkan ID pasien yang akan dihapus: ");
    scanf(" %[^\n]", id_pasien);

    hapus_pasien(id_pasien);
}

void input_ubah_pasien() {
    int umur;
    char nama_pasien[100];
    char alamat[150];
    char kota[50];
    char tempat_lahir[50];
    char tanggal_lahir[30];
    char nomor_bpjs[20];
    char id_pasien[50];

    printf("Masukkan ID pasien yang akan diubah: ");
    scanf(" %[^\n]", id_pasien);
    
    printf("Masukkan umur baru: ");
    scanf("%d", &umur);
    printf("Masukkan nama pasien baru: ");
    scanf(" %[^\n]", nama_pasien);
    printf("Masukkan alamat baru: ");
    scanf(" %[^\n]", alamat);
    printf("Masukkan kota baru: ");
    scanf(" %[^\n]", kota);
    printf("Masukkan tempat lahir baru: ");
    scanf(" %[^\n]", tempat_lahir);
    printf("Masukkan tanggal lahir baru (DD-MM-YYYY): ");
    scanf(" %[^\n]", tanggal_lahir);
    printf("Masukkan nomor BPJS baru: ");
    scanf(" %[^\n]", nomor_bpjs);

    ubah_pasien(id_pasien, umur, nama_pasien, alamat, kota, tempat_lahir, tanggal_lahir, nomor_bpjs);
}

void input_cari_pasien() {
    char id_pasien[50];
    printf("Masukkan ID pasien yang akan dicari: ");
    scanf(" %[^\n]", id_pasien);

    Pasien *pasien = cari_pasien(id_pasien);
    if (pasien != NULL) {
        printf("Data pasien ditemukan:\n");
        printf("ID Pasien: %s\n", pasien->id_pasien);
        printf("Nama: %s\n", pasien->nama_pasien);
        printf("Alamat: %s\n", pasien->alamat);
        printf("Kota: %s\n", pasien->kota);
        printf("Tempat Lahir: %s\n", pasien->tempat_lahir);
        printf("Tanggal Lahir: %s\n", pasien->tanggal_lahir);
        printf("Umur: %d\n", pasien->umur);
        printf("Nomor BPJS: %s\n", pasien->nomor_bpjs);
    } else {
        printf("Pasien dengan ID %s tidak ditemukan.\n", id_pasien);
    }
}

int main() {
    int pilihan;

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Pasien\n");
        printf("2. Hapus Pasien\n");
        printf("3. Ubah Pasien\n");
        printf("4. Cari Pasien\n");
        printf("5. Tampilkan Semua Pasien\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                input_tambah_pasien();
                break;
            case 2:
                input_hapus_pasien();
                break;
            case 3:
                input_ubah_pasien();
                break;
            case 4:
                input_cari_pasien();
                break;
            case 5:
                cetak_pasien();
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

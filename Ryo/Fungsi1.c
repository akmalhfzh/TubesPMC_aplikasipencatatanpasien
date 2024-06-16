#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pasien {
    char id_pasien[20];
    char nama_lengkap[100];
    char alamat[200];
    char kota[50];
    char tempat_lahir[50];
    char tanggal_lahir[11];
    int umur;
    int no_bpjs;
    struct Pasien* next;
} Pasien;

Pasien* head_pasien = NULL;

void tambahPasien(char id_pasien[], char nama_lengkap[], char alamat[], char kota[], char tempat_lahir[], char tanggal_lahir[], int umur, int no_bpjs) {
    Pasien* new_pasien = (Pasien*)malloc(sizeof(Pasien));
    strcpy(new_pasien->id_pasien, id_pasien);
    strcpy(new_pasien->nama_lengkap, nama_lengkap);
    strcpy(new_pasien->alamat, alamat);
    strcpy(new_pasien->kota, kota);
    strcpy(new_pasien->tempat_lahir, tempat_lahir);
    strcpy(new_pasien->tanggal_lahir, tanggal_lahir);
    new_pasien->umur = umur;
    new_pasien->no_bpjs = no_bpjs;
    new_pasien->next = head_pasien;
    head_pasien = new_pasien;
}

void cariPasien(char nama_lengkap[]) {
    Pasien* current = head_pasien;
    while (current != NULL) {
        if (strstr(current->nama_lengkap, nama_lengkap) != NULL) {
            printf("ID: %s, Nama Lengkap: %s, Alamat: %s, Kota: %s, Tempat Lahir: %s, Tanggal Lahir: %s, Umur: %d, No BPJS: %d\n",
                   current->id_pasien, current->nama_lengkap, current->alamat, current->kota,
                   current->tempat_lahir, current->tanggal_lahir, current->umur, current->no_bpjs);
        }
        current = current->next;
    }
}

void ubahPasien(char id_pasien[], char nama_lengkap[], char alamat[], char kota[], char tempat_lahir[], char tanggal_lahir[], int umur, int no_bpjs) {
    Pasien* current = head_pasien;
    while (current != NULL) {
        if (strcmp(current->id_pasien, id_pasien) == 0) {
            strcpy(current->nama_lengkap, nama_lengkap);
            strcpy(current->alamat, alamat);
            strcpy(current->kota, kota);
            strcpy(current->tempat_lahir, tempat_lahir);
            strcpy(current->tanggal_lahir, tanggal_lahir);
            current->umur = umur;
            current->no_bpjs = no_bpjs;
            printf("Data pasien dengan ID %s berhasil diubah.\n", id_pasien);
            return;
        }
        current = current->next;
    }
    printf("Pasien dengan ID %s tidak ditemukan.\n", id_pasien);
}

void hapusPasien(char id_pasien[]) {
    Pasien* current = head_pasien;
    Pasien* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->id_pasien, id_pasien) == 0) {
            if (previous == NULL) {
                head_pasien = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Pasien dengan ID %s berhasil dihapus.\n", id_pasien);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Pasien dengan ID %s tidak ditemukan.\n", id_pasien);
}

int main() {
    return 0;
}

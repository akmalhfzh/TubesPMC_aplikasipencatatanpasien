#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Riwayat {
    char tanggal[11];
    char id_pasien[20];
    char diagnosis[200];
    char tindakan[200];
    char kontrol[11];
    int biaya;
    struct Riwayat* next;
} Riwayat;

Riwayat* head_riwayat = NULL;

void tambahRiwayat(char tanggal[], char id_pasien[], char diagnosis[], char tindakan[], char kontrol[], int biaya) {
    Riwayat* new_riwayat = (Riwayat*)malloc(sizeof(Riwayat));
    strcpy(new_riwayat->tanggal, tanggal);
    strcpy(new_riwayat->id_pasien, id_pasien);
    strcpy(new_riwayat->diagnosis, diagnosis);
    strcpy(new_riwayat->tindakan, tindakan);
    strcpy(new_riwayat->kontrol, kontrol);
    new_riwayat->biaya = biaya;
    new_riwayat->next = head_riwayat;
    head_riwayat = new_riwayat;
}

void cariRiwayat(char id_pasien[]) {
    Riwayat* current = head_riwayat;
    while (current != NULL) {
        if (strcmp(current->id_pasien, id_pasien) == 0) {
            printf("Tanggal: %s, ID Pasien: %s, Diagnosis: %s, Tindakan: %s, Kontrol: %s, Biaya: %d\n",
                   current->tanggal, current->id_pasien, current->diagnosis, current->tindakan, current->kontrol, current->biaya);
        }
        current = current->next;
    }
}

void ubahRiwayat(char tanggal[], char id_pasien[], char diagnosis[], char tindakan[], char kontrol[], int biaya) {
    Riwayat* current = head_riwayat;
    while (current != NULL) {
        if (strcmp(current->tanggal, tanggal) == 0 && strcmp(current->id_pasien, id_pasien) == 0) {
            strcpy(current->diagnosis, diagnosis);
            strcpy(current->tindakan, tindakan);
            strcpy(current->kontrol, kontrol);
            current->biaya = biaya;
            printf("Riwayat dengan Tanggal %s dan ID Pasien %s berhasil diubah.\n", tanggal, id_pasien);
            return;
        }
        current = current->next;
    }
    printf("Riwayat dengan Tanggal %s dan ID Pasien %s tidak ditemukan.\n", tanggal, id_pasien);
}

void hapusRiwayat(char tanggal[], char id_pasien[]) {
    Riwayat* current = head_riwayat;
    Riwayat* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->tanggal, tanggal) == 0 && strcmp(current->id_pasien, id_pasien) == 0) {
            if (previous == NULL) {
                head_riwayat = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Riwayat dengan Tanggal %s dan ID Pasien %s berhasil dihapus.\n", tanggal, id_pasien);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Riwayat dengan Tanggal %s dan ID Pasien %s tidak ditemukan.\n", tanggal, id_pasien);
}

int main() {
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Struktur data pasien
typedef struct dataPasien {
    char nama[255];
    char alamat[255];
    char kota[255];
    char tempatLahir[255];
    int tanggalLahir[3];    // [0] = tanggal, [1] = bulan, [2] = tahun
    int umur;
    char noBpjs[255];
    char idPasien[255];
    struct dataPasien* next;
} dataPasien;

// Struktur riwayat diagnosis
typedef struct riwayatDiagnosis {
    int tanggalPeriksa[3];    // [0] = tanggal, [1] = bulan, [2] = tahun
    char idPasien[255];
    char diagnosis[255];
    char tindakan[255];
    int tanggalKontrol[3];    // [0] = tanggal, [1] = bulan, [2] = tahun
    int biaya;
    struct riwayatDiagnosis* next;
} riwayatDiagnosis;

dataPasien *dataPasienHead = NULL;
riwayatDiagnosis *riwayatDiagnosisHead = NULL;

// Fungsi untuk mengkonversi bulan dari integer ke string
void intToStringMonth(int month, char monthOut[255]){
    const char* months[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    if(month >= 1 && month <= 12){
        strcpy(monthOut, months[month - 1]);
    }
}

// Fungsi untuk membaca file CSV pasien
void readFile1(char fileName[255]){
    FILE* stream = fopen(fileName, "r");
    if (stream == NULL){
        printf("File %s tidak ditemukan\n", fileName);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), stream)) {
        dataPasien* newPasien = (dataPasien*) malloc(sizeof(dataPasien));
        char *token = strtok(line, ";");
        strcpy(newPasien->nama, token);
        
        token = strtok(NULL, ";");
        strcpy(newPasien->alamat, token);
        
        token = strtok(NULL, ";");
        strcpy(newPasien->kota, token);
        
        token = strtok(NULL, ";");
        strcpy(newPasien->tempatLahir, token);
        
        token = strtok(NULL, ";");
        newPasien->tanggalLahir[0] = atoi(token);
        
        token = strtok(NULL, ";");
        newPasien->tanggalLahir[1] = atoi(token);
        
        token = strtok(NULL, ";");
        newPasien->tanggalLahir[2] = atoi(token);
        
        token = strtok(NULL, ";");
        newPasien->umur = atoi(token);
        
        token = strtok(NULL, ";");
        strcpy(newPasien->noBpjs, token);
        
        token = strtok(NULL, "\n");
        strcpy(newPasien->idPasien, token);
        
        newPasien->next = dataPasienHead;
        dataPasienHead = newPasien;
    }
    fclose(stream);
}

// Fungsi untuk membaca file CSV riwayat diagnosis
void readFile2(char fileName[255]){
    FILE* stream = fopen(fileName, "r");
    if (stream == NULL){
        printf("File %s tidak ditemukan\n", fileName);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), stream)) {
        riwayatDiagnosis* newDiagnosis = (riwayatDiagnosis*) malloc(sizeof(riwayatDiagnosis));
        char *token = strtok(line, ";");
        
        newDiagnosis->tanggalPeriksa[0] = atoi(token);
        
        token = strtok(NULL, ";");
        newDiagnosis->tanggalPeriksa[1] = atoi(token);
        
        token = strtok(NULL, ";");
        newDiagnosis->tanggalPeriksa[2] = atoi(token);
        
        token = strtok(NULL, ";");
        strcpy(newDiagnosis->idPasien, token);
        
        token = strtok(NULL, ";");
        strcpy(newDiagnosis->diagnosis, token);
        
        token = strtok(NULL, ";");
        strcpy(newDiagnosis->tindakan, token);
        
        token = strtok(NULL, ";");
        newDiagnosis->tanggalKontrol[0] = atoi(token);
        
        token = strtok(NULL, ";");
        newDiagnosis->tanggalKontrol[1] = atoi(token);
        
        token = strtok(NULL, ";");
        newDiagnosis->tanggalKontrol[2] = atoi(token);
        
        token = strtok(NULL, "\n");
        newDiagnosis->biaya = atoi(token);
        
        newDiagnosis->next = riwayatDiagnosisHead;
        riwayatDiagnosisHead = newDiagnosis;
    }
    fclose(stream);
}

// Fungsi untuk menulis data pasien ke file CSV
void writeFile1(char filename[255]){
    FILE* stream = fopen(filename, "w");
    if (stream == NULL){
        printf("Error opening file %s for writing\n", filename);
        return;
    }
    dataPasien* current = dataPasienHead;
    while (current != NULL){
        fprintf(stream, "%s;%s;%s;%s;%d;%d;%d;%d;%s;%s\n", current->nama, current->alamat, current->kota, current->tempatLahir, current->tanggalLahir[0], current->tanggalLahir[1], current->tanggalLahir[2], current->umur, current->noBpjs, current->idPasien);
        current = current->next;
    }
    fclose(stream);
}

// Fungsi untuk menulis riwayat diagnosis ke file CSV
void writeFile2(char filename[255]){
    FILE* stream = fopen(filename, "w");
    if (stream == NULL){
        printf("Error opening file %s for writing\n", filename);
        return;
    }
    riwayatDiagnosis* current = riwayatDiagnosisHead;
    while (current != NULL){
        fprintf(stream, "%d;%d;%d;%s;%s;%s;%d;%d;%d;%d\n", current->tanggalPeriksa[0], current->tanggalPeriksa[1], current->tanggalPeriksa[2], current->idPasien, current->diagnosis, current->tindakan, current->tanggalKontrol[0], current->tanggalKontrol[1], current->tanggalKontrol[2], current->biaya);
        current = current->next;
    }
    fclose(stream);
}

// Fungsi untuk menulis data ke file
void writeFile(){
    writeFile1("tes1.csv");
    writeFile2("tes2.csv");
}

// Fungsi untuk menambah data pasien
void tambahDataPasien() {
    dataPasien* newPasien = (dataPasien*) malloc(sizeof(dataPasien));
    
    printf("Masukkan nama: ");
    scanf("%s", newPasien->nama);
    printf("Masukkan alamat: ");
    scanf("%s", newPasien->alamat);
    printf("Masukkan kota: ");
    scanf("%s", newPasien->kota);
    printf("Masukkan tempat lahir: ");
    scanf("%s", newPasien->tempatLahir);
    printf("Masukkan tanggal lahir (DD MM YYYY): ");
    scanf("%d %d %d", &newPasien->tanggalLahir[0], &newPasien->tanggalLahir[1], &newPasien->tanggalLahir[2]);
    printf("Masukkan umur: ");
    scanf("%d", &newPasien->umur);
    printf("Masukkan no BPJS: ");
    scanf("%s", newPasien->noBpjs);
    printf("Masukkan ID Pasien: ");
    scanf("%s", newPasien->idPasien);
    
    newPasien->next = dataPasienHead;
    dataPasienHead = newPasien;
    
    printf("Data pasien berhasil ditambahkan.\n");
}

// Fungsi untuk menambah riwayat diagnosis
void tambahRiwayatDiagnosis() {
    riwayatDiagnosis* newDiagnosis = (riwayatDiagnosis*) malloc(sizeof(riwayatDiagnosis));
    
    printf("Masukkan tanggal periksa (DD MM YYYY): ");
    scanf("%d %d %d", &newDiagnosis->tanggalPeriksa[0], &newDiagnosis->tanggalPeriksa[1], &newDiagnosis->tanggalPeriksa[2]);
    printf("Masukkan ID Pasien: ");
    scanf("%s", newDiagnosis->idPasien);
    printf("Masukkan diagnosis: ");
    scanf("%s", newDiagnosis->diagnosis);
    printf("Masukkan tindakan: ");
    scanf("%s", newDiagnosis->tindakan);
    printf("Masukkan tanggal kontrol (DD MM YYYY): ");
    scanf("%d %d %d", &newDiagnosis->tanggalKontrol[0], &newDiagnosis->tanggalKontrol[1], &newDiagnosis->tanggalKontrol[2]);
    printf("Masukkan biaya: ");
    scanf("%d", &newDiagnosis->biaya);
    
    newDiagnosis->next = riwayatDiagnosisHead;
    riwayatDiagnosisHead = newDiagnosis;
    
    printf("Riwayat diagnosis berhasil ditambahkan.\n");
}

// Fungsi untuk mencari data pasien berdasarkan ID
dataPasien* cariDataPasien(char idPasien[255]) {
    dataPasien* current = dataPasienHead;
    while (current != NULL) {
        if (strcmp(current->idPasien, idPasien) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Fungsi untuk mengubah data pasien
void ubahDataPasien() {
    char idPasien[255];
    printf("Masukkan ID Pasien yang akan diubah: ");
    scanf("%s", idPasien);
    
    dataPasien* pasien = cariDataPasien(idPasien);
    if (pasien == NULL) {
        printf("Pasien dengan ID %s tidak ditemukan.\n", idPasien);
        return;
    }
    
    printf("Masukkan nama baru: ");
    scanf("%s", pasien->nama);
    printf("Masukkan alamat baru: ");
    scanf("%s", pasien->alamat);
    printf("Masukkan kota baru: ");
    scanf("%s", pasien->kota);
    printf("Masukkan tempat lahir baru: ");
    scanf("%s", pasien->tempatLahir);
    printf("Masukkan tanggal lahir baru (DD MM YYYY): ");
    scanf("%d %d %d", &pasien->tanggalLahir[0], &pasien->tanggalLahir[1], &pasien->tanggalLahir[2]);
    printf("Masukkan umur baru: ");
    scanf("%d", &pasien->umur);
    printf("Masukkan no BPJS baru: ");
    scanf("%s", pasien->noBpjs);
    
    printf("Data pasien berhasil diubah.\n");
}

// Fungsi untuk menghapus data pasien
void hapusDataPasien() {
    char idPasien[255];
    printf("Masukkan ID Pasien yang akan dihapus: ");
    scanf("%s", idPasien);
    
    dataPasien* current = dataPasienHead;
    dataPasien* previous = NULL;
    
    while (current != NULL && strcmp(current->idPasien, idPasien) != 0) {
        previous = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Pasien dengan ID %s tidak ditemukan.\n", idPasien);
        return;
    }
    
    if (previous == NULL) {
        dataPasienHead = current->next;
    } else {
        previous->next = current->next;
    }
    
    free(current);
    printf("Data pasien berhasil dihapus.\n");
}

// Fungsi untuk menghapus riwayat diagnosis
void hapusRiwayatDiagnosis() {
    char idPasien[255];
    printf("Masukkan ID Pasien yang riwayat diagnosisnya akan dihapus: ");
    scanf("%s", idPasien);
    
    riwayatDiagnosis* current = riwayatDiagnosisHead;
    riwayatDiagnosis* previous = NULL;
    
    while (current != NULL && strcmp(current->idPasien, idPasien) != 0) {
        previous = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Riwayat diagnosis dengan ID Pasien %s tidak ditemukan.\n", idPasien);
        return;
    }
    
    if (previous == NULL) {
        riwayatDiagnosisHead = current->next;
    } else {
        previous->next = current->next;
    }
    
    free(current);
    printf("Riwayat diagnosis berhasil dihapus.\n");
}

// Fungsi untuk mendapatkan laporan pendapatan
void laporanPendapatan() {
    int totalPendapatan = 0;
    riwayatDiagnosis* current = riwayatDiagnosisHead;
    while (current != NULL) {
        totalPendapatan += current->biaya;
        current = current->next;
    }
    printf("Total pendapatan: %d\n", totalPendapatan);
}

// Fungsi untuk menghitung jumlah pasien
void jumlahPasien() {
    int jumlah = 0;
    dataPasien* current = dataPasienHead;
    while (current != NULL) {
        jumlah++;
        current = current->next;
    }
    printf("Jumlah pasien: %d\n", jumlah);
}

// Fungsi untuk menampilkan pasien yang perlu kembali kontrol
void pasienPerluKontrol() {
    riwayatDiagnosis* current = riwayatDiagnosisHead;
    while (current != NULL) {
        if (current->tanggalKontrol[0] != 0 || current->tanggalKontrol[1] != 0 || current->tanggalKontrol[2] != 0) {
            printf("ID Pasien: %s, Tanggal Kontrol: %d-%d-%d\n", current->idPasien, current->tanggalKontrol[0], current->tanggalKontrol[1], current->tanggalKontrol[2]);
        }
        current = current->next;
    }
}

// Fungsi utama
int main(){    
    // Membaca file CSV
    readFile1("DataPasien.csv");
    readFile2("RiwayatDiagnosis.csv");

    int pilihan;
    while(1) {
        printf("\nMenu:\n");
        printf("1. Tambah Data Pasien\n");
        printf("2. Tambah Riwayat Diagnosis\n");
        printf("3. Ubah Data Pasien\n");
        printf("4. Hapus Data Pasien\n");
        printf("5. Hapus Riwayat Diagnosis\n");
        printf("6. Laporan Pendapatan\n");
        printf("7. Jumlah Pasien\n");
        printf("8. Pasien Perlu Kontrol\n");
        printf("9. Simpan dan Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                tambahDataPasien();
                break;
            case 2:
                tambahRiwayatDiagnosis();
                break;
            case 3:
                ubahDataPasien();
                break;
            case 4:
                hapusDataPasien();
                break;
            case 5:
                hapusRiwayatDiagnosis();
                break;
            case 6:
                laporanPendapatan();
                break;
            case 7:
                jumlahPasien();
                break;
            case 8:
                pasienPerluKontrol();
                break;
            case 9:
                writeFile();
                printf("Data telah disimpan. Program selesai.\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}

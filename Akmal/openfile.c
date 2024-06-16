#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct dataPasien
{
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

typedef struct riwayatDiagnosis
{
    int tanggalPeriksa[3];    // [0] = tanggal, [1] = bulan, [2] = tahun
    char idPasien[255];
    char diagnosis[255];
    char tindakan[255];
    int tanggalKontrol[3];    // [0] = tanggal, [1] = bulan, [2] = tahun
    int biaya;
    struct riwayatDiagnosis* next;
} riwayatDiagnosis;

dataPasien *dataPasienHead;
riwayatDiagnosis *riwayatDiagnosisHead;

void intToStringMonth(int month, char monthOut[255]){
    if(month == 1){
        strcpy(monthOut, "Januari");
    }
    else if(month == 2){
        strcpy(monthOut, "Februari");
    }
    else if(month == 3){
        strcpy(monthOut, "Maret");
    }
    else if(month == 4){
        strcpy(monthOut, "April");
    }
    else if(month == 5){
        strcpy(monthOut, "Mei");
    }
    else if(month == 6){
        strcpy(monthOut, "Juni");
    }
    else if(month == 7){
        strcpy(monthOut, "Juli");
    }
    else if(month == 8){
        strcpy(monthOut, "Agustus");
    }
    else if(month == 9){
        strcpy(monthOut, "September");
    }
    else if(month == 10){
        strcpy(monthOut, "Oktober");
    }
    else if(month == 11){
        strcpy(monthOut, "November");
    }
    else if(month == 12){
        strcpy(monthOut, "Desember");
    }
}

void readFile1(char fileName[255]){
    FILE* stream = fopen(fileName, "r");
    if (stream == NULL){
        printf("File %s tidak ditemukan", fileName);
        return;
    }

    char line[255];
    char tempLine[255];
    char* token;
    int i = 0;

    fgets(line, 255, stream);   
    while(fgets(line, 255, stream)){
        strcpy(tempLine, line);
        token = strtok(tempLine, ";");  // skip data nomor
        
        // Parsing and adding to linked list dataPasien
        dataPasien* newPasien = (dataPasien*) malloc(sizeof(dataPasien));
        token = strtok(NULL, ";");  // nama
        strcpy(newPasien->nama, token);
        token = strtok(NULL, ";");  // alamat
        strcpy(newPasien->alamat, token);
        token = strtok(NULL, ";");  // kota
        strcpy(newPasien->kota, token);
        token = strtok(NULL, ";");  // tempatLahir
        strcpy(newPasien->tempatLahir, token);
        token = strtok(NULL, ";");  // tanggalLahir
        newPasien->tanggalLahir[0] = atoi(token);
        token = strtok(NULL, ";");  // tanggalLahir
        newPasien->tanggalLahir[1] = atoi(token);
        token = strtok(NULL, ";");  // tanggalLahir
        newPasien->tanggalLahir[2] = atoi(token);
        token = strtok(NULL, ";");  // umur
        newPasien->umur = atoi(token);
        token = strtok(NULL, ";");  // noBpjs
        strcpy(newPasien->noBpjs, token);
        token = strtok(NULL, ";");  // idPasien
        strcpy(newPasien->idPasien, token);
        
        newPasien->next = dataPasienHead;
        dataPasienHead = newPasien;
    }
    fclose(stream);
}

void readFile2(char fileName[255]){
    FILE* stream = fopen(fileName, "r");
    if (stream == NULL){
        printf("File %s tidak ditemukan", fileName);
        return;
    }

    char line[255];
    char tempLine[255];
    char* token;
    int i = 0;

    fgets(line, 255, stream);   
    while(fgets(line, 255, stream)){
        strcpy(tempLine, line);
        token = strtok(tempLine, ";");  // skip  data nomor

        // Parsing and adding to linked list riwayatDiagnosis
        riwayatDiagnosis* newDiagnosis = (riwayatDiagnosis*) malloc(sizeof(riwayatDiagnosis));
        token = strtok(NULL, ";");  // tanggal periksa
        newDiagnosis->tanggalPeriksa[0] = atoi(token);
        token = strtok(NULL, ";");  // tanggal periksa
        newDiagnosis->tanggalPeriksa[1] = atoi(token);
        token = strtok(NULL, ";");  // tanggal periksa
        newDiagnosis->tanggalPeriksa[2] = atoi(token);
        token = strtok(NULL, ";");  // id pasien
        strcpy(newDiagnosis->idPasien, token);
        token = strtok(NULL, ";");  // diagnosis
        strcpy(newDiagnosis->diagnosis, token);
        token = strtok(NULL, ";");  // tindakan
        strcpy(newDiagnosis->tindakan, token);
        token = strtok(NULL, ";");  // tanggal kontrol
        newDiagnosis->tanggalKontrol[0] = atoi(token);
        token = strtok(NULL, ";");  // tanggal kontrol
        newDiagnosis->tanggalKontrol[1] = atoi(token);
        token = strtok(NULL, ";");  // tanggal kontrol
        newDiagnosis->tanggalKontrol[2] = atoi(token);
        token = strtok(NULL, ";");  // biaya
        newDiagnosis->biaya = atoi(token);
        newDiagnosis->next = riwayatDiagnosisHead;
        riwayatDiagnosisHead = newDiagnosis;

    }
    fclose(stream);
}

void writeFile1(char filename[255]){
    FILE* stream = fopen(filename, "w");
    if (stream == NULL){
        printf("Error opening file %s for writing", filename);
        return;
    }
    dataPasien* current = dataPasienHead;
    while (current != NULL){
        fprintf(stream, "%s;%s;%s;%s;%d;%d;%d;%s;%s\n", current->nama, current->alamat, current->kota, current->tempatLahir, current->tanggalLahir[0], current->tanggalLahir[1], current->tanggalLahir[2], current->noBpjs, current->idPasien);
        current = current->next;
    }
    fclose(stream);
}

void writeFile2(char filename[255]){
    FILE* stream = fopen(filename, "w");
    if (stream == NULL){
        printf("Error opening file %s for writing", filename);
        return;
    }
    riwayatDiagnosis* current = riwayatDiagnosisHead;
    while (current != NULL){
        fprintf(stream, "%d;%s;%s;%d;%d\n", current->tanggalPeriksa[0], current->tanggalPeriksa[1], current->tanggalPeriksa[2], current->idPasien, current->diagnosis, current->tindakan, current->tanggalKontrol[0], current->tanggalKontrol[1], current->tanggalKontrol[2], current->biaya);
        current = current->next;
    }
    fclose(stream);
}

void writeFile(){
    writeFile1("tes1.csv");
    writeFile2("tes2.csv");
}

int main(){    
    // Allocating memory for dataPasienHead and riwayatDiagnosisHead
    dataPasienHead = (dataPasien*) malloc(sizeof(dataPasien));
    riwayatDiagnosisHead = (riwayatDiagnosis*) malloc(sizeof(riwayatDiagnosis));

    // Reading CSV files
    readFile1("DataPasien.csv");
    readFile2("RiwayatDiagnosis.csv");

    // Writing combined data to CSV files
    writeFile();

    return 0;
}

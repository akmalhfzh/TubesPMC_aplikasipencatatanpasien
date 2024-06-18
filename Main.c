#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_YEARS 10
#define MAX_MONTHS 12

// Struktur data yang digunakan
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
RiwayatPasien* head_riwayat = NULL;

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

// Fungsi untuk membaca csv data biaya tindakan
int baca_csv_biaya(const char *nama_file, BiayaTindakan **head) {
    FILE *file = fopen(nama_file, "r");
    if (file == NULL) {
        printf("File tidak ditemukan.\n");
        return 0;
    }

    char baris[200];
    fgets(baris, sizeof(baris), file);  // Membaca header
    while (fgets(baris, sizeof(baris), file)) {
        BiayaTindakan *biaya = (BiayaTindakan*)malloc(sizeof(BiayaTindakan));
        sscanf(baris, "%d,%19[^,],%lf", &biaya->indekstindakan, biaya->aktivitas, &biaya->biayatindakan);
        biaya->next = NULL;

        if (*head == NULL) {
            *head = biaya;
        } else {
            BiayaTindakan *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = biaya;
        }
    }
    fclose(file);
    return 1;
}

// Fungsi untuk mendapatkan nomor bulan
const char *get_month_number(const char *month_name) {
    if (strcmp(month_name, "Januari") == 0) return "01";
    if (strcmp(month_name, "Februari") == 0) return "02";
    if (strcmp(month_name, "Maret") == 0) return "03";
    if (strcmp(month_name, "April") == 0) return "04";
    if (strcmp(month_name, "Mei") == 0) return "05";
    if (strcmp(month_name, "Juni") == 0) return "06";
    if (strcmp(month_name, "Juli") == 0) return "07";
    if (strcmp(month_name, "Agustus") == 0) return "08";
    if (strcmp(month_name, "September") == 0) return "09";
    if (strcmp(month_name, "Oktober") == 0) return "10";
    if (strcmp(month_name, "November") == 0) return "11";
    if (strcmp(month_name, "Desember") == 0) return "12";
    return "00";
}

// Fungsi untuk mendapatkan nama bulan dari nomor bulan
const char *get_month_name(const char *month_number) {
    if (strcmp(month_number, "01") == 0) return "Januari";
    if (strcmp(month_number, "02") == 0) return "Februari";
    if (strcmp(month_number, "03") == 0) return "Maret";
    if (strcmp(month_number, "04") == 0) return "April";
    if (strcmp(month_number, "05") == 0) return "Mei";
    if (strcmp(month_number, "06") == 0) return "Juni";
    if (strcmp(month_number, "07") == 0) return "Juli";
    if (strcmp(month_number, "08") == 0) return "Agustus";
    if (strcmp(month_number, "09") == 0) return "September";
    if (strcmp(month_number, "10") == 0) return "Oktober";
    if (strcmp(month_number, "11") == 0) return "November";
    if (strcmp(month_number, "12") == 0) return "Desember";
    return "Tidak Diketahui";
}

// Fungsi untuk menambahkan pasien berdasarkan bulan dan tahun
void tambah_pasien_bulan_tahun(YearCount **head, const char *year, const char *month_year, const char *diagnosis) {
    YearCount *current_year = *head;

    while (current_year != NULL && strcmp(current_year->year, year) != 0) {
        current_year = current_year->next;
    }

    if (current_year == NULL) {
        current_year = (YearCount*)malloc(sizeof(YearCount));
        strcpy(current_year->year, year);
        current_year->month_head = NULL;
        current_year->next = *head;
        *head = current_year;
    }

    MonthYearCount *current_month = current_year->month_head;
    while (current_month != NULL && strcmp(current_month->month_year, month_year) != 0) {
        current_month = current_month->next;
    }

    if (current_month == NULL) {
        current_month = (MonthYearCount*)malloc(sizeof(MonthYearCount));
        strcpy(current_month->month_year, month_year);
        current_month->patient_count = 0;
        current_month->disease_head = NULL;
        current_month->next = current_year->month_head;
        current_year->month_head = current_month;
    }

    current_month->patient_count++;

    DiseaseCount *current_disease = current_month->disease_head;
    while (current_disease != NULL && strcmp(current_disease->disease, diagnosis) != 0) {
        current_disease = current_disease->next;
    }

    if (current_disease == NULL) {
        current_disease = (DiseaseCount*)malloc(sizeof(DiseaseCount));
        strcpy(current_disease->disease, diagnosis);
        current_disease->count = 0;
        current_disease->next = current_month->disease_head;
        current_month->disease_head = current_disease;
    }

    current_disease->count++;
}

// Fungsi untuk menampilkan informasi pasien berdasarkan ID pasien
void informasi_pasien(Pasien *head_pasien, const char *id_pasien) {
    Pasien *current = head_pasien;
    int found = 0;

    printf("Informasi Pasien dengan ID: %s\n", id_pasien);
    while (current != NULL) {
        if (strcmp(current->id_pasien, id_pasien) == 0) {
            found = 1;
                printf("%d. Nama: %s \nAlamat: %s \nKota: %s \nTempat Lahir: %s \nTanggal Lahir: %s \nUmur: %d \nNo BPJS: %s \nID Pasien: %s\n", current->indekspasien, current->nama_pasien, 
               current->alamat, current->kota, current->tempat_lahir, current->tanggal_lahir, current->umur, current->nomor_bpjs, current->id_pasien);
        }
        current = current->next;
    }

    if (!found) {
        printf("Tidak ada informasi pasien ditemukan untuk ID pasien: %s\n", id_pasien);
    }
}

// Fungsi untuk menampilkan riwayat medis seorang pasien berdasarkan ID pasien
void informasi_riwayat_pasien(RiwayatPasien *head_riwayat, const char *id_pasien) {
    RiwayatPasien *current = head_riwayat;
    int found = 0;

    printf("Riwayat Medis :\n");

    while (current != NULL) {
        if (strcmp(current->id_pasien, id_pasien) == 0) {
            found = 1;
            printf("Tanggal : %s, Diagnosis :%s, Tindakan :%s\n",
            current->tanggal_kunjungan, current->diagnosis, current->tindakan);
        }
        current = current->next;
    }
    if (!found) {
        printf("Tidak ada riwayat medis ditemukan untuk ID pasien: %s\n", id_pasien);
    }
}

// Fungsi untuk mengurutkan penyakit berdasarkan jumlah dalam urutan menurun
DiseaseCount *sort_disease_count(DiseaseCount *head) {
    DiseaseCount *sorted = NULL;
    DiseaseCount *current = head;
    while (current != NULL) {
        DiseaseCount *next = current->next;
        if (!sorted || sorted->count < current->count) {
            current->next = sorted;
            sorted = current;
        } else {
            DiseaseCount *temp = sorted;
            while (temp->next && temp->next->count >= current->count) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

MonthYearCount *sort_month_year_count(MonthYearCount *head) {
    MonthYearCount *sorted = NULL;
    MonthYearCount *current = head;

    while (current != NULL) {
        MonthYearCount *next = current->next;
        if (!sorted || strcmp(current->month_year, sorted->month_year) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            MonthYearCount *temp = sorted;
            while (temp->next && strcmp(temp->next->month_year, current->month_year) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

void jumlah_pasien_dan_penyakit_per_tahun(RiwayatPasien *head) {
    YearCount *head_count = NULL;
    RiwayatPasien *temp = head;

    while (temp != NULL) {
        char day[3], month[10], year[5], month_year[20];
        sscanf(temp->tanggal_kunjungan, "%2s %9s %4s", day, month, year);
        sprintf(month_year, "%s-%s", get_month_number(month), year);

        tambah_pasien_bulan_tahun(&head_count, year, month_year, temp->diagnosis);

        temp = temp->next;
    }

    // Sort the YearCount linked list by year in descending order
    YearCount *sorted_head_year = NULL;
    while (head_count != NULL) {
        YearCount *max_year = head_count;
        YearCount *prev_max_year = NULL;
        YearCount *prev = head_count;
        YearCount *current = head_count->next;

        while (current != NULL) {
            if (strcmp(current->year, max_year->year) > 0) {
                max_year = current;
                prev_max_year = prev;
            }
            prev = current;
            current = current->next;
        }

        if (prev_max_year != NULL) {
            prev_max_year->next = max_year->next;
        } else {
            head_count = max_year->next;
        }

        max_year->next = sorted_head_year;
        sorted_head_year = max_year;
    }

    // Display sorted YearCount list in table format
    YearCount *year_temp = sorted_head_year;
    while (year_temp != NULL) {
        printf("=======================================================\n");
        printf("|                      Tahun %s                     |\n", year_temp->year);
        printf("=======================================================\n");
        printf("| Bulan Tahun | Jumlah Pasien |   Penyakit   | Jumlah |\n");
        printf("=======================================================\n");

        // Sort the MonthYearCount linked list by month in ascending order
        year_temp->month_head = sort_month_year_count(year_temp->month_head);

        MonthYearCount *count_temp = year_temp->month_head;
        while (count_temp != NULL) {
            char month[3], year[5];
            sscanf(count_temp->month_year, "%2s-%4s", month, year);
            printf("| %-11s | %-13d |", get_month_name(month), count_temp->patient_count);

            // Sort and display DiseaseCount list for the current month
            count_temp->disease_head = sort_disease_count(count_temp->disease_head);
            DiseaseCount *disease_temp = count_temp->disease_head;
            int first_disease = 1;
            while (disease_temp != NULL) {
                if (!first_disease) {
                    printf("|             |               |");
                }
                printf(" %-12s | %-6d |\n", disease_temp->disease, disease_temp->count);
                first_disease = 0;
                disease_temp = disease_temp->next;
            }

            if (count_temp->disease_head == NULL) {
                printf("\n");
            }

            count_temp = count_temp->next;
            printf("-------------------------------------------------------\n"); // Pemisah tiap bulan
        }

        year_temp = year_temp->next;
    }
    printf("=======================================================\n");
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

// Fungsi untuk menampilkan semua riwayat kunjungan pasien
void tampilkan_riwayat_pasien(RiwayatPasien *head) {
    RiwayatPasien *riwayat = head;
    while (riwayat != NULL) {
        printf("Tanggal Kunjungan: %s\n", riwayat->tanggal_kunjungan);
        printf("ID Pasien: %s\n", riwayat->id_pasien);
        printf("Diagnosis: %s\n", riwayat->diagnosis);
        printf("Tindakan: %s\n", riwayat->tindakan);
        printf("Kontrol: %s\n", riwayat->kontrol);
        printf("Biaya: %.2f\n", riwayat->biaya);
        printf("-------------------------\n");
        riwayat = riwayat->next;
    }
}

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

void process_revenues(RiwayatPasien *head_riwayat, RiwayatPasien monthly_revenues[], int *monthly_count, RiwayatPasien annual_revenues[], int *annual_count, double *total_revenue) {
    *monthly_count = 0;
    *annual_count = 0;
    *total_revenue = 0.0;

    RiwayatPasien *current = head_riwayat;
    while (current != NULL) {
        int day, month, year;
        parse_date(current->tanggal_kunjungan, &day, &month, &year);

        // Menghitung total pendapatan tiap bulan
        int monthly_index = find_monthly_index(monthly_revenues, *monthly_count, year, month);
        if (monthly_index != -1) {
            monthly_revenues[monthly_index].biaya += current->biaya;
        } else {
            if (*monthly_count < MAX_YEARS * MAX_MONTHS) {  // Pastikan tidak melebihi batas array
                monthly_revenues[*monthly_count] = *current;
                (*monthly_count)++;
            } else {
                printf("Warning: Monthly revenue array is full, skipping data for month %d/%d\n", month, year);
            }
        }

        // Menghitung total pendapatan tiap tahun
        int annual_index = find_annual_index(annual_revenues, *annual_count, year);
        if (annual_index != -1) {
            annual_revenues[annual_index].biaya += current->biaya;
        } else {
            if (*annual_count < MAX_YEARS) {  // Pastikan tidak melebihi batas array
                annual_revenues[*annual_count] = *current;
                (*annual_count)++;
            } else {
                printf("Warning: Annual revenue array is full, skipping data for year %d\n", year);
            }
        }

        *total_revenue += current->biaya;
        current = current->next;
    }
}

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

// Fungsi main
int main() {
    Pasien *head_pasien = NULL;
    RiwayatPasien *head_riwayat = NULL;

    if (!baca_csv_pasien("DataPasien.csv", &head_pasien)) {
        return 1;
    }
    if (!baca_csv_riwayat("RiwayatPasien.csv", &head_riwayat)) {
        return 1;
    }

    int pilihan;
    int pilihancase1;
    int pilihancase2;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Data Pasien\n");
        printf("2. Riwayat Diagnosis\n");
        printf("3. Informasi Pasien dan Riwayat Medis\n");
        printf("4. Laporan Pendapatan\n");
        printf("5. Jumlah Pasien\n");
        printf("6. Pasien Perlu Kontrol\n");
        printf("7. Simpan dan Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
            printf("\nMenu:\n");
            printf("1. Tambah Data Pasien\n");
            printf("2. Ubah Data Pasien\n");
            printf("3. Cari Data Pasien\n");
            printf("4. Hapus Data Pasien\n");
            printf("pilihan: ");
            scanf("%d", &pilihancase1);
                if (pilihancase1 == 1){
                    // tambahDataPasien();
                    input_tambah_pasien();
                    break;
                } else if (pilihancase1 == 2){
                    // ubahDataPasien();
                    input_ubah_pasien();
                    break;
                } else if (pilihancase1 == 3){
                    // cariDataPasien();
                    input_cari_pasien();
                    break;
                } else if (pilihancase1 == 4){
                    // hapusDataPasien();
                    input_hapus_pasien();
                    break;
                }
            case 2:
            printf("\nMenu:\n");
            printf("1. Tambah Riwayat Diagnosis\n");
            printf("2. Ubah Riwayat Diagnosis\n");
            printf("3. Cari Riwayat Diagnosis\n");
            printf("4. Hapus Riwayat Diagnosis\n");
            printf("pilihan: ");
            scanf("%d", &pilihancase2);
                if (pilihancase2 == 1){
                    // tambahRiwayatDiagnosis();
                    input_tambah_riwayat();
                    break;
                } else if (pilihancase2 == 2){
                    // ubahRiwayatDiagnosis();
                    input_ubah_riwayat();
                    break;
                } else if (pilihancase2 == 3){
                    // cariRiwayatDiagnosis();
                    input_cari_riwayat();
                    break;
                } else if (pilihancase2 == 4){
                    // hapusRiwayatDiagnosis();
                    input_hapus_riwayat();
                    break;
                }
            case 3:
                {
                char id_pasien[50];
                printf("Masukkan ID Pasien: ");
                scanf(" %[^\n]", id_pasien);
                printf("\n");
                informasi_pasien(head_pasien, id_pasien);
                informasi_riwayat_pasien(head_riwayat, id_pasien);
                }
                break;
            case 4:
                // laporanpendapatan();
                RiwayatPasien monthly_revenues[MAX_YEARS * MAX_MONTHS] = {0};
                RiwayatPasien annual_revenues[MAX_YEARS] = {0};
                int monthly_count, annual_count;
                double total_revenue;

                process_revenues(head_riwayat, monthly_revenues, &monthly_count, annual_revenues, &annual_count, &total_revenue);

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
                break;
            case 5:
                jumlah_pasien_dan_penyakit_per_tahun(head_riwayat);
                break;
            case 6:
                // Memanggil fungsi untuk menampilkan semua riwayat pasien
                printf("Informasi riwayat pasien:\n");
                printf("-------------------------\n");
                tampilkan_riwayat_pasien(head_riwayat);
                break;
            case 7:
                // writeFile();
                printf("Data telah disimpan. Program selesai.\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    }
    return 0;
    }

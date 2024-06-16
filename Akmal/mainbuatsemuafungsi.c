#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures
typedef struct {
    int id;
    char name[100];
    int age;
    char gender[10];
} Patient;

typedef struct {
    int patient_id;
    char visit_date[20];
    char diagnosis[100];
    char treatment[100];
} MedicalRecord;

// Function prototypes
void readPatientsFromFile(const char *filename);
void readRecordsFromFile(const char *filename);
void writePatientsToFile(const char *filename);
void writeRecordsToFile(const char *filename);
void addPatient();
void modifyPatient();
void deletePatient();
void searchPatient();
void addMedicalRecord();
void modifyMedicalRecord();
void deleteMedicalRecord();
void searchMedicalRecord();
void generateMonthlyReport();
void generateAnnualReport();
void reportPatientStatistics();
void reportFollowUpPatients();

// Global arrays to store data
Patient patients[100];
MedicalRecord records[100];
int patientCount = 0;
int recordCount = 0;

// Main function
int main() {
    readPatientsFromFile("DataPasien.csv");
    readRecordsFromFile("RiwayatDiagnosis.csv");

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add Patient\n");
        printf("2. Modify Patient\n");
        printf("3. Delete Patient\n");
        printf("4. Search Patient\n");
        printf("5. Add Medical Record\n");
        printf("6. Modify Medical Record\n");
        printf("7. Delete Medical Record\n");
        printf("8. Search Medical Record\n");
        printf("9. Generate Monthly Report\n");
        printf("10. Generate Annual Report\n");
        printf("11. Report Patient Statistics\n");
        printf("12. Report Follow-Up Patients\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addPatient(); break;
            case 2: modifyPatient(); break;
            case 3: deletePatient(); break;
            case 4: searchPatient(); break;
            case 5: addMedicalRecord(); break;
            case 6: modifyMedicalRecord(); break;
            case 7: deleteMedicalRecord(); break;
            case 8: searchMedicalRecord(); break;
            case 9: generateMonthlyReport(); break;
            case 10: generateAnnualReport(); break;
            case 11: reportPatientStatistics(); break;
            case 12: reportFollowUpPatients(); break;
            case 13: 
                writePatientsToFile("DataPasien_modified.csv");
                writeRecordsToFile("RiwayatDiagnosis_modified.csv");
                exit(0); 
                break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 13);
    
    return 0;
}

// Function to read patients from a CSV file
void readPatientsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s for reading.\n", filename);
        return;
    }

    while (fscanf(file, "%d,%99[^,],%d,%9s", &patients[patientCount].id, patients[patientCount].name, 
            &patients[patientCount].age, patients[patientCount].gender) != EOF) {
        patientCount++;
    }

    fclose(file);
    printf("Read %d patients from file %s.\n", patientCount, filename);
}

// Function to read medical records from a CSV file
void readRecordsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s for reading.\n", filename);
        return;
    }

    while (fscanf(file, "%d,%19[^,],%99[^,],%99[^\n]", &records[recordCount].patient_id, records[recordCount].visit_date, 
            records[recordCount].diagnosis, records[recordCount].treatment) != EOF) {
        recordCount++;
    }

    fclose(file);
    printf("Read %d medical records from file %s.\n", recordCount, filename);
}

// Function to write patients to a CSV file
void writePatientsToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%d,%s,%d,%s\n", patients[i].id, patients[i].name, patients[i].age, patients[i].gender);
    }

    fclose(file);
    printf("Wrote %d patients to file %s.\n", patientCount, filename);
}

// Function to write medical records to a CSV file
void writeRecordsToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        fprintf(file, "%d,%s,%s,%s\n", records[i].patient_id, records[i].visit_date, records[i].diagnosis, records[i].treatment);
    }

    fclose(file);
    printf("Wrote %d medical records to file %s.\n", recordCount, filename);
}

// Function implementations for adding, modifying, deleting, and searching patients and records
void addPatient() {
    if (patientCount < 100) {
        printf("Enter patient ID: ");
        scanf("%d", &patients[patientCount].id);
        printf("Enter name: ");
        scanf("%s", patients[patientCount].name);
        printf("Enter age: ");
        scanf("%d", &patients[patientCount].age);
        printf("Enter gender: ");
        scanf("%s", patients[patientCount].gender);
        patientCount++;
        printf("Patient added successfully!\n");
    } else {
        printf("Patient list is full!\n");
    }
}

void modifyPatient() {
    int id, found = -1;
    printf("Enter patient ID to modify: ");
    scanf("%d", &id);
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("Enter new name: ");
        scanf("%s", patients[found].name);
        printf("Enter new age: ");
        scanf("%d", &patients[found].age);
        printf("Enter new gender: ");
        scanf("%s", patients[found].gender);
        printf("Patient modified successfully!\n");
    } else {
        printf("Patient not found!\n");
    }
}

void deletePatient() {
    int id, found = -1;
    printf("Enter patient ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < patientCount - 1; i++) {
            patients[i] = patients[i + 1];
        }
        patientCount--;
        printf("Patient deleted successfully!\n");
    } else {
        printf("Patient not found!\n");
    }
}

void searchPatient() {
    int id, found = -1;
    printf("Enter patient ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("Patient ID: %d\n", patients[found].id);
        printf("Name: %s\n", patients[found].name);
        printf("Age: %d\n", patients[found].age);
        printf("Gender: %s\n", patients[found].gender);
    } else {
        printf("Patient not found!\n");
    }
}

void addMedicalRecord() {
    if (recordCount < 100) {
        printf("Enter patient ID: ");
        scanf("%d", &records[recordCount].patient_id);
        printf("Enter visit date: ");
        scanf("%s", records[recordCount].visit_date);
        printf("Enter diagnosis: ");
        scanf("%s", records[recordCount].diagnosis);
        printf("Enter treatment: ");
        scanf("%s", records[recordCount].treatment);
        recordCount++;
        printf("Medical record added successfully!\n");
    } else {
        printf("Medical record list is full!\n");
    }
}

void modifyMedicalRecord() {
    int id, found = -1;
    printf("Enter patient ID to modify record: ");
    scanf("%d", &id);
    for (int i = 0; i < recordCount; i++) {
        if (records[i].patient_id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("Enter new visit date: ");
        scanf("%s", records[found].visit_date);
        printf("Enter new diagnosis: ");
        scanf("%s", records[found].diagnosis);
        printf("Enter new treatment: ");
        scanf("%s", records[found].treatment);
        printf("Medical record modified successfully!\n");
    } else {
        printf("Medical record not found!\n");
    }
}

void deleteMedicalRecord() {
    int id, found = -1;
    printf("Enter patient ID to delete record: ");
    scanf("%d", &id);
    for (int i = 0; i < recordCount; i++) {
        if (records[i].patient_id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < recordCount - 1; i++) {
            records[i] = records[i + 1];
        }
        recordCount--;
        printf("Medical record deleted successfully!\n");
    } else {
        printf("Medical record not found!\n");
    }
}

void searchMedicalRecord() {
    int id, found = -1;
    printf("Enter patient ID to search record: ");
    scanf("%d", &id);
    for (int i = 0; i < recordCount; i++) {
        if (records[i].patient_id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("Patient ID: %d\n", records[found].patient_id);
        printf("Visit Date: %s\n", records[found].visit_date);
        printf("Diagnosis: %s\n", records[found].diagnosis);
        printf("Treatment: %s\n", records[found].treatment);
    } else {
        printf("Medical record not found!\n");
    }
}

void generateMonthlyReport() {
    // Implementation for generating a monthly financial report
}

void generateAnnualReport() {
    // Implementation for generating an annual financial report
}

void reportPatientStatistics() {
    // Implementation for reporting patient statistics
}

void reportFollowUpPatients() {
    // Implementation for reporting follow-up patients
}

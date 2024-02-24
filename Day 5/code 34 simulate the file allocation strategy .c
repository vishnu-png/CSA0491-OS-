#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

// Structure representing a record in the file
struct Record {
    int id;
    char data[100];
};

// Structure representing the file
struct File {
    struct Record records[MAX_RECORDS];
    int num_records;
};

// Function to add a record to the file
void addRecord(struct File *file, int id, const char *data) {
    if (file->num_records < MAX_RECORDS) {
        struct Record newRecord;
        newRecord.id = id;
        snprintf(newRecord.data, sizeof(newRecord.data), "%s", data);
        file->records[file->num_records++] = newRecord;
        printf("Record added successfully.\n");
    } else {
        printf("File is full. Cannot add more records.\n");
    }
}

// Function to read all records in the file
void readRecords(const struct File *file) {
    printf("Records in the file:\n");
    for (int i = 0; i < file->num_records; ++i) {
        printf("Record %d: ID = %d, Data = %s\n", i+1, file->records[i].id, file->records[i].data);
    }
}

int main() {
    struct File file;
    file.num_records = 0;

    int choice, id;
    char data[100];

    do {
        printf("\n1. Add Record\n");
        printf("2. Read Records\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter record ID: ");
                scanf("%d", &id);
                printf("Enter record data: ");
                scanf("%s", data);
                addRecord(&file, id, data);
                break;
            case 2:
                readRecords(&file);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}

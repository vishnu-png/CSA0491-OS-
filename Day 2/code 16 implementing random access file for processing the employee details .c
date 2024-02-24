#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50
#define FILENAME "employee.dat"

struct Employee {
    int emp_id;
    char name[MAX_NAME_LENGTH];
    float salary;
};

void addEmployee(FILE *file) {
    struct Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.emp_id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fseek(file, (emp.emp_id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

void displayEmployee(FILE *file, int emp_id) {
    struct Employee emp;
    fseek(file, (emp_id - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);
    printf("Employee ID: %d\n", emp.emp_id);
    printf("Employee Name: %s\n", emp.name);
    printf("Employee Salary: %.2f\n", emp.salary);
}

int main() {
    FILE *file = fopen(FILENAME, "r+");
    if (!file) {
        file = fopen(FILENAME, "w+");
        if (!file) {
            perror("Error creating file");
            return 1;
        }
    }

    int choice;
    do {
        printf("\nEmployee Database\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                printf("Enter employee ID: ");
                int emp_id;
                scanf("%d", &emp_id);
                displayEmployee(file, emp_id);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    fclose(file);
    return 0;
}

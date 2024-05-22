#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.txt"
#define TEMP_FILENAME "temp.txt"

// Function to get employee details from user
void get_employee_details(char *id, char *name, int *age, char *department, float *salary) {
    printf("Enter Employee ID: ");
    scanf("%s", id);
    printf("Enter Employee Name: ");
    scanf("%s", name);
    printf("Enter Employee Age: ");
    scanf("%d", age);
    printf("Enter Employee Department: ");
    scanf("%s", department);
    printf("Enter Employee Salary: ");
    scanf("%f", salary);
}

// Function to store employee details in a file
void store_employee_details(char *id, char *name, int age, char *department, float salary) {
    FILE *file = fopen(FILENAME, "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Write the employee details
    fprintf(file, "%s,%s,%d,%s,%.2f\n", id, name, age, department, salary);

    fclose(file);
}

// Function to display all employees
void display_employees() {
    char line[256];
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        printf("No employee records found.\n");
        return;
    }

    printf("ID, Name, Age, Department, Salary\n");
    printf("------------------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// Function to delete an employee record
void delete_employee(char *id) {
    FILE *file = fopen(FILENAME, "r");
    FILE *temp_file = fopen(TEMP_FILENAME, "w");

    if (file == NULL || temp_file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, id) == NULL) {
            fputs(line, temp_file);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);

    if (found) {
        printf("Employee with ID %s deleted successfully.\n", id);
    } else {
        printf("Employee with ID %s not found.\n", id);
    }
}

// Function to update an employee record
void update_employee(char *id) {
    FILE *file = fopen(FILENAME, "r");
    FILE *temp_file = fopen(TEMP_FILENAME, "w");

    if (file == NULL || temp_file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, id) != NULL) {
            found = 1;
            char name[50], department[50];
            int age;
            float salary;
            printf("Enter new details for employee with ID %s\n", id);
            get_employee_details(id, name, &age, department, &salary);
            fprintf(temp_file, "%s,%s,%d,%s,%.2f\n", id, name, age, department, salary);
        } else {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);

    if (found) {
        printf("Employee with ID %s updated successfully.\n", id);
    } else {
        printf("Employee with ID %s not found.\n", id);
    }
}

// Function to display the menu
void display_menu() {
    printf("Employee Management System\n");
    printf("1. Add Employee\n");
    printf("2. Display Employees\n");
    printf("3. Delete Employee\n");
    printf("4. Update Employee\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char id[20];

    // Ensure file has a header
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        file = fopen(FILENAME, "w");
        if (file != NULL) {
            fprintf(file, "ID,Name,Age,Department,Salary\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    char name[50], department[50];
                    int age;
                    float salary;
                    get_employee_details(id, name, &age, department, &salary);
                    store_employee_details(id, name, age, department, salary);
                    break;
                }
            case 2:
                display_employees();
                break;
            case 3:
                printf("Enter Employee ID to delete: ");
                scanf("%s", id);
                delete_employee(id);
                break;
            case 4:
                printf("Enter Employee ID to update: ");
                scanf("%s", id);
                update_employee(id);
                break;
            case 5:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

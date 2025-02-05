#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100

struct Employee {
    int employee_id;
    char name[50];
    char department[50];
    char designation[50];
    float salary;
};

void add_employee(struct Employee *employees, int *num_employees);
void display_employees(struct Employee *employees, int num_employees);
void search_employee(struct Employee *employees, int num_employees);
void update_employee(struct Employee *employees, int num_employees);
void delete_employee(struct Employee *employees, int *num_employees);
void save_data(struct Employee *employees, int num_employees);
void load_data(struct Employee *employees, int *num_employees);

int main() {
    struct Employee employees[MAX_EMPLOYEES];
    int num_employees = 0;
    int choice;

    // Load data from file on program start
    load_data(employees, &num_employees);

    do {
        printf("\n\nFaculty and Staff Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Save Data\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_employee(employees, &num_employees);
                break;
            case 2:
                display_employees(employees, num_employees);
                break;
            case 3:
                search_employee(employees, num_employees);
                break;
            case 4:
                update_employee(employees, num_employees);
                break;
            case 5:
                delete_employee(employees, &num_employees);
                break;
            case 6:
                save_data(employees, num_employees);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}

void add_employee(struct Employee *employees, int *num_employees) {
    if (*num_employees >= MAX_EMPLOYEES) {
        printf("Maximum number of employees reached.\n");
        return;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &employees[*num_employees].employee_id);

    printf("Enter Employee Name: ");
    scanf(" %[^\n]", employees[*num_employees].name); // Read full name with spaces

    printf("Enter Department: ");
    scanf(" %[^\n]", employees[*num_employees].department);

    printf("Enter Designation: ");
    scanf(" %[^\n]", employees[*num_employees].designation);

    printf("Enter Salary: ");
    scanf("%f", &employees[*num_employees].salary);

    (*num_employees)++;
    printf("Employee added successfully!\n");
}

void display_employees(struct Employee *employees, int num_employees) {
    if (num_employees == 0) {
        printf("No employees found.\n");
        return;
    }

    printf("\nEmployee Details:\n");
    printf("-----------------------------------------------------------\n");
    printf("ID\tName\t\tDepartment\tDesignation\tSalary\n");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < num_employees; i++) {
        printf("%d\t%s\t\t%s\t\t%s\t%.2f\n", employees[i].employee_id, employees[i].name, employees[i].department, employees[i].designation, employees[i].salary);
    }
    printf("-----------------------------------------------------------\n");
}

void search_employee(struct Employee *employees, int num_employees) {
    int search_id;
    int found = 0;

    printf("Enter Employee ID to search: ");
    scanf("%d", &search_id);

    for (int i = 0; i < num_employees; i++) {
        if (employees[i].employee_id == search_id) {
            printf("\nEmployee Found:\n");
            printf("ID: %d\n", employees[i].employee_id);
            printf("Name: %s\n", employees[i].name);
            printf("Department: %s\n", employees[i].department);
            printf("Designation: %s\n", employees[i].designation);
            printf("Salary: %.2f\n", employees[i].salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    }
}

void update_employee(struct Employee *employees, int num_employees) {
    int update_id;
    int found = 0;

    printf("Enter Employee ID to update: ");
    scanf("%d", &update_id);

    for (int i = 0; i < num_employees; i++) {
        if (employees[i].employee_id == update_id) {
            printf("Enter New Employee Name: ");
            scanf(" %[^\n]", employees[i].name);

            printf("Enter New Department: ");
            scanf(" %[^\n]", employees[i].department);

            printf("Enter New Designation: ");
            scanf(" %[^\n]", employees[i].designation);

            printf("Enter New Salary: ");
            scanf("%f", &employees[i].salary);

            printf("Employee updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    }
}

void delete_employee(struct Employee *employees, int *num_employees) {
    int delete_id;
    int found = 0;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &delete_id);

    for (int i = 0; i < *num_employees; i++) {
        if (employees[i].employee_id == delete_id) {
            for (int j = i; j < *num_employees - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*num_employees)--;
            printf("Employee deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    }
}

void save_data(struct Employee *employees, int num_employees) {
    FILE *fp;
    fp = fopen("employee_data.txt", "wb"); // Open file in binary write mode
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&num_employees, sizeof(int), 1, fp); // Write number of employees
    fwrite(employees, sizeof(struct Employee), num_employees, fp); // Write employee data

    fclose(fp);
    printf("Data saved successfully!\n");
}

void load_data(struct Employee *employees, int *num_employees) {
    FILE *fp;
    fp = fopen("employee_data.txt", "rb"); // Open file in binary read mode
    if (fp == NULL) {
        printf("No existing data found. Starting with an empty database.\n");
        return;
    }

    fread(num_employees, sizeof(int), 1, fp); // Read number of employees
    fread(employees, sizeof(struct Employee), *num_employees, fp); // Read employee data

    fclose(fp);
    printf("Data loaded successfully!\n");
}
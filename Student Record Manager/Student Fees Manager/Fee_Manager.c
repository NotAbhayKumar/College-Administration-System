#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_FEES 5

struct Student {
    int student_id;
    char name[50];
    float fees_paid;
    float total_fees;
    struct Fee {
        char fee_name[50];
        float amount;
        int is_paid; // 1 for paid, 0 for unpaid
    } fees[MAX_FEES];
};

void add_student(struct Student *students, int *num_students);
void add_fee(struct Student *students, int student_index);
void pay_fee(struct Student *students, int student_index);
void view_student_fees(struct Student *students, int student_index);
void view_all_students(struct Student *students, int num_students);
void select_student(struct Student *students, int num_students, int *student_index);
void save_data(struct Student *students, int num_students);
void load_data(struct Student *students, int *num_students);

int main() {
    struct Student students[MAX_STUDENTS];
    int num_students = 0;
    int student_index = -1;
    int choice;

    load_data(students, &num_students);

    do {
        printf("\n\nStudent Fees Management System\n");
        printf("1. Add Student\n");
        printf("2. Select Student\n");
        printf("3. Add Fee\n");
        printf("4. Pay Fee\n");
        printf("5. View Student Fees\n");
        printf("6. View All Students\n");
        printf("7. Save Data\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student(students, &num_students);
                break;
            case 2:
                select_student(students, num_students, &student_index);
                break;
            case 3:
                if (student_index != -1) {
                    add_fee(students, student_index);
                } else {
                    printf("Please select a student first.\n");
                }
                break;
            case 4:
                if (student_index != -1) {
                    pay_fee(students, student_index);
                } else {
                    printf("Please select a student first.\n");
                }
                break;
            case 5:
                if (student_index != -1) {
                    view_student_fees(students, student_index);
                } else {
                    printf("Please select a student first.\n");
                }
                break;
            case 6:
                view_all_students(students, num_students);
                break;
            case 7:
                save_data(students, num_students);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 8);

    return 0;
}

void add_student(struct Student *students, int *num_students) {
    if (*num_students >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &students[*num_students].student_id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", students[*num_students].name); 

    students[*num_students].fees_paid = 0.0;
    students[*num_students].total_fees = 0.0;

    // Initialize fees to zero initially
    for (int i = 0; i < MAX_FEES; i++) {
        strcpy(students[*num_students].fees[i].fee_name, "");
        students[*num_students].fees[i].amount = 0.0;
        students[*num_students].fees[i].is_paid = 0;
    }

    (*num_students)++;
    printf("Student added successfully!\n");
}

void add_fee(struct Student *students, int student_index) {
    int fee_index = -1; 
    for (int i = 0; i < MAX_FEES; i++) {
        if (strlen(students[student_index].fees[i].fee_name) == 0) {
            fee_index = i;
            break;
        }
    }

    if (fee_index == -1) {
        printf("Maximum number of fees for this student reached.\n");
        return;
    }

    printf("Enter Fee Name: ");
    scanf(" %[^\n]", students[student_index].fees[fee_index].fee_name);

    printf("Enter Fee Amount: ");
    scanf("%f", &students[student_index].fees[fee_index].amount);

    students[student_index].total_fees += students[student_index].fees[fee_index].amount;

    printf("Fee added successfully!\n");
}

void pay_fee(struct Student *students, int student_index) {
    int fee_index;

    printf("Enter Fee Index to mark as paid (starting from 1): ");
    scanf("%d", &fee_index);

    if (fee_index < 1 || fee_index > MAX_FEES || 
        strlen(students[student_index].fees[fee_index - 1].fee_name) == 0) {
        printf("Invalid fee index.\n");
        return;
    }

    if (students[student_index].fees[fee_index - 1].is_paid == 1) {
        printf("Fee is already paid.\n");
        return;
    }

    students[student_index].fees[fee_index - 1].is_paid = 1;
    students[student_index].fees_paid += students[student_index].fees[fee_index - 1].amount;

    printf("Fee payment recorded successfully!\n");
}

void view_student_fees(struct Student *students, int student_index) {
    printf("\nFee Details for Student ID: %d\n", students[student_index].student_id);
    printf("-------------------------------------------------\n");
    printf("Fee Name\t\tAmount\t\tPaid\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < MAX_FEES; i++) {
        if (strlen(students[student_index].fees[i].fee_name) > 0) {
            printf("%-20s\t%.2f\t%s\n", 
                   students[student_index].fees[i].fee_name, 
                   students[student_index].fees[i].amount, 
                   students[student_index].fees[i].is_paid ? "Yes" : "No");
        }
    }
    printf("-------------------------------------------------\n");
    printf("Total Fees: %.2f\n", students[student_index].total_fees);
    printf("Fees Paid: %.2f\n", students[student_index].fees_paid);
    printf("Outstanding Fees: %.2f\n", students[student_index].total_fees - students[student_index].fees_paid);
}

void view_all_students(struct Student *students, int num_students) {
    if (num_students == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\nStudent List:\n");
    printf("-------------------------------------------------------------------------\n");
    printf("ID\tName\t\t\tTotal Fees\t\tFees Paid\n");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < num_students; i++) {
        printf("%d\t%-20s\t%.2f\t\t%.2f\n", 
               students[i].student_id, 
               students[i].name, 
               students[i].total_fees, 
               students[i].fees_paid);
    }
    printf("-------------------------------------------------------------------------\n");
}

void select_student(struct Student *students, int num_students, int *student_index) {
    int search_id;
    int found = 0;

    printf("Enter Student ID to select: ");
    scanf("%d", &search_id);

    for (int i = 0; i < num_students; i++) {
        if (students[i].student_id == search_id) {
            *student_index = i;
            printf("Student selected successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
        *student_index = -1; // Reset student_index if not found
    }
}

void save_data(struct Student *students, int num_students) {
    FILE *fp;
    fp = fopen("student_fees_data.txt", "wb"); 
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&num_students, sizeof(int), 1, fp); 
    fwrite(students, sizeof(struct Student), num_students, fp); 

    fclose(fp);
    printf("Data saved successfully!\n");
}

void load_data(struct Student *students, int *num_students) {
    FILE *fp;
    fp = fopen("student_fees_data.txt", "rb"); 

    if (fp == NULL) {
        printf("No existing data found. Starting with an empty database.\n");
        *num_students = 0; 
        return;
    }

    fread(num_students, sizeof(int), 1, fp); 
    fread(students, sizeof(struct Student), *num_students, fp); 

    fclose(fp);
    printf("Data loaded successfully!\n");
}
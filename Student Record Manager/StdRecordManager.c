#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int student_id;
    char name[50];
    char department[50];
    int marks[5]; // Assuming 5 subjects
    float average_marks;
};

void add_student(struct Student *students, int *num_students);
void display_students(struct Student *students, int num_students);
void search_student(struct Student *students, int num_students);
void update_student(struct Student *students, int num_students);
void delete_student(struct Student *students, int *num_students);
void save_data(struct Student *students, int num_students);
void load_data(struct Student *students, int *num_students);

int main() {
    struct Student students[MAX_STUDENTS];
    int num_students = 0;
    int choice;

    // Load data from file on program start
    load_data(students, &num_students);

    do {
        printf("\n\nCollege Administration System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Save Data\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student(students, &num_students);
                break;
            case 2:
                display_students(students, num_students);
                break;
            case 3:
                search_student(students, num_students);
                break;
            case 4:
                update_student(students, num_students);
                break;
            case 5:
                delete_student(students, &num_students);
                break;
            case 6:
                save_data(students, num_students);
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

void add_student(struct Student *students, int *num_students) {
    if (*num_students >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &students[*num_students].student_id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", students[*num_students].name); // Read full name with spaces

    printf("Enter Department: ");
    scanf(" %[^\n]", students[*num_students].department);

    printf("Enter Marks in 5 Subjects:\n");
    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%d", &students[*num_students].marks[i]);
    }

    // Calculate average marks
    float total_marks = 0;
    for (int i = 0; i < 5; i++) {
        total_marks += students[*num_students].marks[i];
    }
    students[*num_students].average_marks = total_marks / 5;

    (*num_students)++;
    printf("Student added successfully!\n");
}

void display_students(struct Student *students, int num_students) {
    if (num_students == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\nStudent Details:\n");
    printf("-------------------------------------------------\n");
    printf("ID\tName\t\tDepartment\tAverage Marks\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < num_students; i++) {
        printf("%d\t%s\t\t%s\t\t%.2f\n", students[i].student_id, students[i].name, students[i].department, students[i].average_marks);
    }
    printf("-------------------------------------------------\n");
}

void search_student(struct Student *students, int num_students) {
    int search_id;
    int found = 0;

    printf("Enter Student ID to search: ");
    scanf("%d", &search_id);

    for (int i = 0; i < num_students; i++) {
        if (students[i].student_id == search_id) {
            printf("\nStudent Found:\n");
            printf("ID: %d\n", students[i].student_id);
            printf("Name: %s\n", students[i].name);
            printf("Department: %s\n", students[i].department);
            printf("Average Marks: %.2f\n", students[i].average_marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void update_student(struct Student *students, int num_students) {
    int update_id;
    int found = 0;

    printf("Enter Student ID to update: ");
    scanf("%d", &update_id);

    for (int i = 0; i < num_students; i++) {
        if (students[i].student_id == update_id) {
            printf("Enter New Student Name: ");
            scanf(" %[^\n]", students[i].name);

            printf("Enter New Department: ");
            scanf(" %[^\n]", students[i].department);

            printf("Enter New Marks in 5 Subjects:\n");
            for (int j = 0; j < 5; j++) {
                printf("Subject %d: ", j + 1);
                scanf("%d", &students[i].marks[j]);
            }

            // Recalculate average marks
            float total_marks = 0;
            for (int j = 0; j < 5; j++) {
                total_marks += students[i].marks[j];
            }
            students[i].average_marks = total_marks / 5;

            printf("Student updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void delete_student(struct Student *students, int *num_students) {
    int delete_id;
    int found = 0;

    printf("Enter Student ID to delete: ");
    scanf("%d", &delete_id);

    for (int i = 0; i < *num_students; i++) {
        if (students[i].student_id == delete_id) {
            for (int j = i; j < *num_students - 1; j++) {
                students[j] = students[j + 1];
            }
            (*num_students)--;
            printf("Student deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void save_data(struct Student *students, int num_students) {
    FILE *fp;
    fp = fopen("student_data.txt", "wb"); // Open file in binary write mode
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&num_students, sizeof(int), 1, fp); // Write number of students
    fwrite(students, sizeof(struct Student), num_students, fp); // Write student data

    fclose(fp);
    printf("Data saved successfully!\n");
}

void load_data(struct Student *students, int *num_students) {
    FILE *fp;
    fp = fopen("student_data.txt", "rb"); // Open file in binary read mode
    if (fp == NULL) {
        printf("No existing data found. Starting with an empty database.\n");
        return;
    }

    fread(num_students, sizeof(int), 1, fp); // Read number of students
    fread(students, sizeof(struct Student), *num_students, fp); // Read student data

    fclose(fp);
    printf("Data loaded successfully!\n");
}
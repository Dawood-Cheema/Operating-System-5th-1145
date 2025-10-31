/* Write a C program that:
1.  Defines a structure containing:   Student ID (integer)
  Student Name (string - max 50 chars)   Marks (float)
  Grade (char - to be calculated by thread)
2.  Create an array of 3 student records with sample data
3.  Create 3 threads, each thread receives one student structure and:   Determines grade based on marks:

  = 85: Grade A
  = 70: Grade B
  = 60: Grade C
  = 50: Grade D
  < 50: Grade F
  Prints the student information with the calculated grade
4.  Main thread waits for all threads to complete */

// Dawood Saif
// 23-NTU-CS-1145


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// here we have declaring struct data type for multipe datas like int, char, float, etc
typedef struct {
    int student_id;
    char student_name[50];
    float marks;
    char grade;
} Students;  // name of struct



void* calculate_grade(void* arg) {
    Students *student = (Students*) arg; // making object of class

                                    // Here we are using Conditions to give grades
                                    // means who will get A, B,C and D depending on their Marks
    if (student->marks >= 85) {
        student->grade = 'A';
    } else if (student->marks >= 70) {
        student->grade = 'B';
    } else if (student->marks >= 60) {
        student->grade = 'C';
    } else if (student->marks >= 50) {
        student->grade = 'D';
    } else {
        student->grade = 'F';
    }
        // here we are print
    printf("Student ID: %d\n", student->student_id);
    printf("Student Name: %s\n", student->student_name);
    printf("Marks: %.2f\n", student->marks);
    printf("Grade: %c\n", student->grade);

    return NULL;

}

int main(void){ 
    //data passing to the threads through lop
    Students students[3]= {
        {1, "Dawood Saif", 90, ' '},
        {2, "Abdul Rehman", 80, ' '},
        {3, "Laiba Saif", 60, ' '},  
       
    };

    pthread_t threads[3];

    for(int i=0; i<3; i++ ){
        pthread_create(&threads[i], NULL, calculate_grade, (void*)&students[i]);
        // Here the Thread has creadted and 4 arguments are passing 
    }

    for (int i=0; i<3; i++) {
        pthread_join(threads[i], NULL);
    }
    // Here we thread because it stops after excuting but we do this to stop and save output

    return 0;
}


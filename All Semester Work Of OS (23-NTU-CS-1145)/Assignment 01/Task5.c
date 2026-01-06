// Task 5 – Struct‑Based Thread Communication
// Dawood Saif
// Reg. No. 23-NTU-CS-1145  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int dean_count = 0;
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

void *student_thread(void *arg) {
    Student *s = (Student*)arg;
    printf("Student ID: %d, Name: %s, GPA: %.2f\n", s->student_id, s->name, s->gpa);
    if (s->gpa >= 3.5f) {
        printf("%s made the Dean's List.\n", s->name);
        dean_count++;
    } else {
        printf("%s did not make the Dean's List.\n", s->name);
    }
    return NULL;
}

int main() {
    pthread_t tid[3];
    Student *s1 = malloc(sizeof(Student));
    Student *s2 = malloc(sizeof(Student));
    Student *s3 = malloc(sizeof(Student));

    // Example students - change as required
    s1->student_id = 1; strcpy(s1->name, "Dawood"); s1->gpa = 3.55f;
    s2->student_id = 2; strcpy(s2->name, "Saif");  s2->gpa = 3.99f;
    s3->student_id = 3; strcpy(s3->name, "Cheema"); s3->gpa = 3.04f;

    pthread_create(&tid[0], NULL, student_thread, s1);
    pthread_create(&tid[1], NULL, student_thread, s2);
    pthread_create(&tid[2], NULL, student_thread, s3);


    // Wait and count in main thread after join
    for (int i = 0; i < 3; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("Dean Count: %d \nMain thread: Completed.\n",dean_count);

    // Free memory
    free(s1); 
    free(s2); 
    free(s3);
    return 0;
}
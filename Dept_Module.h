/**
 * @file dept_module.h
 * @brief Header file for department module functionalities.
 */

#ifndef DEPT_MODULE_H
#define DEPT_MODULE_H

#include<stdio.h>

extern int faculty_capacity;   /**< Capacity of the faculty list */
extern int faculty_size;       /**< Current size of the faculty list */
extern int student_capacity;   /**< Capacity of the student list */
extern int student_size;       /**< Current size of the student list */
extern int course_capacity;    /**< Capacity of the course list */
extern int course_size;        /**< Current size of the course list */
extern int offered_courses_capacity; /**< Capacity of the offered courses list */
extern int offered_courses_size;     /**< Current size of the offered courses list */

/**
 * @brief Initializes the basic capacities and sizes for faculties, students, courses, and offered courses.
 * 
 * @param fac_cap Faculty capacity
 * @param fac_size Faculty size
 * @param std_cap Student capacity
 * @param std_size Student size
 * @param cou_cap Course capacity
 * @param cou_size Course size
 * @param ofc_cap Offered courses capacity
 * @param ofc_size Offered courses size
 */
void basic_capacity(int fac_cap, int fac_size, 
                    int std_cap, int std_size, 
                    int cou_cap, int cou_size, 
                    int ofc_cap, int ofc_size);

/**
 * @brief Gets a string input without an array.
 * 
 * @param c Address of the char pointer
 * @return The head of the string
 */
char* getString(char* c);

/**
 * @struct course_info
 * @brief Structure to store course information.
 */
typedef struct course_info {
    char* code;     /**< Course code */
    char* title;    /**< Course title */
    int credit;     /**< Course credit */
} cou;

/**
 * @brief Initializes the course list.
 * 
 * @param course_list Pointer to the course list
 */
void cou_init_list(cou*** course_list);

/**
 * @brief Hash function for course codes.
 * 
 * @param code Course code
 * 
 * @return Hash value
 */
int cou_hash_function(char* code);

/**
 * @brief Inserts a course into the course list.
 * 
 * @param course_list Pointer to the course list
 * @param course Course to be inserted
 */
void cou_insert(cou** course_list, cou* course);

/**
 * @brief Deletes a course from the course list using its key.
 * 
 * @param course_list Pointer to the course list
 * @param key Key of the course to be deleted
 */
void cou_delete(cou** course_list, int key);

/**
 * @brief Edits a course in the course list.
 * 
 * @param course_list Pointer to the course list
 * @param key Key of the course to be edited
 * @param title New title of the course
 * @param credit New credit of the course
 */
void cou_edit(cou** course_list, int key, char* title, int credit);

/**
 * @brief Creates a new course node.
 * 
 * @param code Course code
 * @param title Course title
 * @param credit Course credit
 * 
 * @return Pointer to the created course node
 */
cou* cou_createnode(char* code, char* title, int credit);

/**
 * @brief Gets a course from the course list using its code.
 * 
 * @param course_list Pointer to the course list
 * @param code Course code
 * 
 * @return Pointer to the course
 */
cou* cou_get(cou** course_list, char* code);

typedef struct student_info std;

/**
 * @struct student_list
 * @brief Structure to store a list of students.
 */
typedef struct student_list {
    std* student;                   /**< Pointer to the student */
    struct student_list* next;      /**< Pointer to the next student in the list */
} std_list;

/**
 * @brief Inserts a student into the student list.
 * 
 * @param std_list_head Pointer to the head of the student list
 * @param student Student to be inserted
 */
void std_list_insert(std_list** std_list_head, std_list* student);

/**
 * @brief Deletes a student from the student list.
 * 
 * @param std_list_head Pointer to the head of the student list
 * @param student Student to be deleted
 */
void std_list_delete(std_list** std_list_head, std* student);

/**
 * @brief Frees the student list.
 * 
 * @param std_list_head Pointer to the head of the student list
 */
void std_free_list(std_list** std_list_head);

/**
 * @brief Creates a new student list node.
 * 
 * @param student Pointer to the student
 * 
 * @return Pointer to the created student list node
 */
std_list* std_list_createnode(std* student);

/**
 * @struct offered_courses
 * @brief Structure to store information about offered courses.
 */
typedef struct offered_courses {
    cou* course;                    /**< Pointer to the course */
    int section;                    /**< Section number */
    char* faculty_initial;          /**< Initials of the faculty */
    int num_of_std;                 /**< Number of students */
    int max_std;                    /**< Maximum number of students */
    std_list* std_list;             /**< List of students */
} ofc;

/**
 * @brief Initializes the offered courses list.
 * 
 * @param offered_courses_list Pointer to the offered courses list
 */
void ofc_init_list(ofc*** offered_courses_list);

/**
 * @brief Hash function for offered courses.
 * 
 * @param code Course code
 * @param section Section number
 * 
 * @return Hash value
 */
int ofc_hash_function(char* code, int section);

/**
 * @brief Inserts a course into the offered courses list.
 * 
 * @param offered_courses_list Pointer to the offered courses list
 * @param course Course to be inserted
 */
void ofc_insert(ofc** offered_courses_list, ofc* course);

/**
 * @brief Deletes a course from the offered courses list using its key.
 * 
 * @param offered_courses_list Pointer to the offered courses list
 * @param key Key of the course to be deleted
 */
void ofc_delete(ofc** offered_courses_list, int key);

/**
 * @brief Edits a course in the offered courses list.
 * 
 * @param offered_courses_list Pointer to the offered courses list
 * @param key Key of the course to be edited
 * @param faculty_initial New initials of the faculty
 * @param max_std New maximum number of students
 */
void ofc_edit(ofc** offered_courses_list, int key, char* faculty_initial, int max_std);

/**
 * @brief Creates a new offered course node.
 * 
 * @param course Pointer to the course
 * @param section Section number
 * @param fac_initial Initials of the faculty
 * @param max_std Maximum number of students
 * 
 * @return Pointer to the created offered course node
 */
ofc* ofc_createnode(cou* course, int section, char* fac_initial, int max_std);

/**
 * @brief Gets a course from the offered courses list using its code and section.
 * 
 * @param offered_courses_list Pointer to the offered courses list
 * @param code Course code
 * @param section Section number
 * 
 * @return Pointer to the course
 */
ofc* ofc_get(ofc** offered_courses_list, char* code, int section);

/**
 * @struct assigned_course
 * @brief Structure to store information about assigned courses.
 */
typedef struct assigned_course {
    ofc* course;                    /**< Pointer to the course */
    struct assigned_course* next;   /**< Pointer to the next assigned course in the list */
} ac_list;

/**
 * @brief Inserts a course into the assigned courses list.
 * 
 * @param ac_list_head Pointer to the head of the assigned courses list
 * @param course Course to be inserted
 */
void ac_list_insert(ac_list** ac_list_head, ac_list* course);

/**
 * @brief Deletes a course from the assigned courses list.
 * 
 * @param ac_list_head Pointer to the head of the assigned courses list
 * @param course Course to be deleted
 */
void ac_list_delete(ac_list** ac_list_head, ofc* course);

/**
 * @brief Frees the assigned courses list.
 * 
 * @param ac_list_head Pointer to the head of the assigned courses list
 */
void ac_free_list(ac_list** ac_list_head);

/**
 * @brief Creates a new assigned course node.
 * 
 * @param course Pointer to the course
 * 
 * @return Pointer to the created assigned course node
 */
ac_list* ac_list_createnode(ofc* course);

/**
 * @struct student_info
 * @brief Structure to store information about a student.
 */
typedef struct student_info {
    char* ID;                       /**< Student ID */
    char* name;                     /**< Student name */
    int semester;                   /**< Semester number */
    ac_list* selected_courses;      /**< List of selected courses */
} std;

/**
 * @brief Initializes the student list.
 * 
 * @param student_list Pointer to the student list
 */
void std_init_list(std*** student_list);

/**
 * @brief Hash function for student IDs.
 * 
 * @param ID Student ID
 * 
 * @return Hash value
 */
int std_hash_function(char* ID);

/**
 * @brief Inserts a student into the student list.
 * 
 * @param student_list Pointer to the student list
 * @param student Student to be inserted
 */
void std_insert(std** student_list, std* student);

/**
 * @brief Deletes a student from the student list using its key.
 * 
 * @param student_list Pointer to the student list
 * @param key Key of the student to be deleted
 */
void std_delete(std** student_list, int key);

/**
 * @brief Edits a student in the student list.
 * 
 * @param student_list Pointer to the student list
 * @param key Key of the student to be edited
 * @param name New name of the student
 * @param semester New semester number of the student
 */
void std_edit(std** student_list, int key, char* name, int semester);

/**
 * @brief Creates a new student node.
 * 
 * @param ID Unique student number
 * @param name Student's name
 * @param semester Semester number
 * 
 * @return Address of the created student node
 */
std* std_createnode(char* ID, char* name, int semester);

/**
 * @brief Gets a student from the student list using their ID.
 * 
 * @param student_list Pointer to the student list
 * @param ID Student ID
 * 
 * @return Pointer to the student
 */
std* std_get(std** student_list, char* ID);

/**
 * @struct faculty_info
 * @brief Structure to store information about a faculty member.
 */
typedef struct faculty_info {
    char* initial;                  /**< Faculty initial */
    char* name;                     /**< Faculty name */
    int num_assigned_sections;      /**< Number of assigned sections */
    ac_list* assigned_sections;     /**< List of assigned sections */
} fac;

/**
 * @brief Initializes the faculty list.
 * 
 * @param faculty_list Pointer to the faculty list
 */
void fac_init_list(fac*** faculty_list);

/**
 * @brief Hash function for faculty initials.
 * 
 * @param initial Faculty initial
 * 
 * @return Hash value
 */
int fac_hash_function(char* initial);

/**
 * @brief Inserts a faculty member into the faculty list.
 * 
 * @param faculty_list Pointer to the faculty list
 * @param faculty Faculty member to be inserted
 */
void fac_insert(fac** faculty_list, fac* faculty);

/**
 * @brief Deletes a faculty member from the faculty list using their key.
 * 
 * @param faculty_list Pointer to the faculty list
 * @param key Key of the faculty member to be deleted
 */
void fac_delete(fac** faculty_list, int key);

/**
 * @brief Edits a faculty member in the faculty list.
 * 
 * @param faculty_list Pointer to the faculty list
 * @param key Key of the faculty member to be edited
 * @param name New name of the faculty member
 */
void fac_edit(fac** faculty_list, int key, char* name);

/**
 * @brief Creates a new faculty node.
 * 
 * @param initial Faculty initial
 * @param name Faculty name
 * 
 * @return Pointer to the created faculty node
 */
fac* fac_createnode(char* initial, char* name);

/**
 * @brief Gets a faculty member from the faculty list using their initial.
 * 
 * @param faculty_list Pointer to the faculty list
 * @param initial Faculty initial
 * 
 * @return Pointer to the faculty member
 */
fac* fac_get(fac** faculty_list, char* initial);

#endif 
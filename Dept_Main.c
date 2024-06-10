#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#include"Dept_Module.h"

void view_menu();
void add_menu();
void remove_menu();
void edit_menu();
void offer_courses_menu();
void enroll_menu();

void fac_display_title();
void std_display_title();
void cou_display_title();
void ofc_display_title();

void fac_info_print(fac* faculty);
void fac_info_list_print(fac** faculty_list);
void std_info_print(std* student);
void std_info_list_print(std** student_list);
void cou_info_print(cou* course);
void cou_info_list_print(cou** course_list);
void ofc_info_print(ofc* course,int wstd);
void ofc_info_list_print(ofc** offered_courses_list);

cou** course_list;
ofc** offered_courses_list;
std** student_list;
fac** faculty_list;

int main() {
    basic_capacity(100,0,100,0,100,0,100,0);
    cou_init_list(&course_list);
    ofc_init_list(&offered_courses_list);
    std_init_list(&student_list);
    fac_init_list(&faculty_list);
    std_insert(student_list,std_createnode("2023-1-60-093","Robiul Islam",1));
    std_insert(student_list,std_createnode("2023-1-60-097","Hassan Shawon",2));
    std_insert(student_list,std_createnode("2023-1-60-089","Ahnaf Anan",3));
    std_insert(student_list,std_createnode("2023-1-60-095","MD. Irfan",1));
    std_insert(student_list,std_createnode("2023-1-60-021","Shihab Mahmud",2));
    fac_insert(faculty_list,fac_createnode("DHMAI","Hasan Mahmud"));
    fac_insert(faculty_list,fac_createnode("RDA","Rashedul Amin"));
    fac_insert(faculty_list,fac_createnode("AKMN","AKM Nazimuddin"));
    fac_insert(faculty_list,fac_createnode("IMRAN","MD. Imran"));
    fac_insert(faculty_list,fac_createnode("FMAR","FM. Arif"));
    cou_insert(course_list,cou_createnode("CSE200","Engineering Drawing",1));
    cou_insert(course_list,cou_createnode("CSE207","Data Structure",4));
    cou_insert(course_list,cou_createnode("CSE209","Electrical Circuits",4));
    cou_insert(course_list,cou_createnode("MAT104","Coordinate Geometry",3));
    cou_insert(course_list,cou_createnode("STA102","Statistics",3));
    int choice;
    do {
        printf("\n");
        printf(" +===== Main Menu =====+\n");
        printf("||  1. View            ||\n");
        printf("||  2. Add             ||\n");
        printf("||  3. Remove          ||\n");
        printf("||  4. Edit            ||\n");
        printf("||  5. Offer Courses   ||\n");
        printf("||  6. Enroll          ||\n");
        printf("||  0. Exit            ||\n");
        printf(" +=====================+\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                view_menu();
                break;
            case 2:
                add_menu();
                break;
            case 3:
                remove_menu();
                break;
            case 4:
                edit_menu();
                break;
            case 5:
                offer_courses_menu();
                break;
            case 6:
                enroll_menu();
                break;
            case 0:
                printf("Exiting...\n");
                getch();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        system("cls");
    } while (choice != 0);
    return 0;
}

void view_menu() {
    int choice;
    int key;
    char* code = NULL;
    do {
        printf("\n====== View Menu ======\n");
        printf("  1. View Faculty Profile\n");
        printf("  2. View Student Profile\n");
        printf("  3. View Course Information\n");
        printf("  4. View Offered Course Information\n");
        printf("  5. View Faculty List\n");
        printf("  6. View Student List\n");
        printf("  7. View Course List\n");
        printf("  8. View Offered Course List\n");
        printf("  0. Return to Main Menu\n");
        printf("=======================\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
        fflush(stdin);
        switch (choice) {
            case 1:
                printf("Enter Faculty Initial: ");
                char* initial;
                initial = getString(initial);
                key = fac_hash_function(initial);
                if(*(faculty_list + key) != NULL){
                    fac_display_title();
                    fac_info_print(*(faculty_list + key));
                }else
                    printf("No Faculty found with that initial.\n");
                break;
            case 2:
                printf("Enter Student ID: ");
                char* ID;
                ID = getString(ID);
                key = std_hash_function(ID);
                if(*(student_list + key) != NULL){
                    std_display_title();
                    std_info_print(*(student_list + key));
                }else
                    printf("No Student found with that ID.\n");
                break;
            case 3:
                printf("Enter Course Code: ");
                code = getString(code);
                key = cou_hash_function(code);
                if(*(course_list + key) != NULL){
                    cou_display_title();
                    cou_info_print(*(course_list + key));
                }else
                    printf("No Course found with that code.\n");
                break;
            case 4:
                printf("Enter Course Code: ");
                int section;
                code = getString(code);
                printf("Enter Section: ");
                scanf("%d",&section);
                key = ofc_hash_function(code,section);
                if(*(offered_courses_list + key) != NULL){
                    ofc_display_title();
                    ofc_info_print(*(offered_courses_list + key),1);
                }else
                    printf("No Offered Course found with that code and section.\n");
                break;
            case 5:
                fac_info_list_print(faculty_list);
                break;
            case 6:
                std_info_list_print(student_list);
                break;
            case 7:
                cou_info_list_print(course_list);
                break;
            case 8:
                ofc_info_list_print(offered_courses_list);
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        getch();
        system("cls");
        fflush(stdin);
    } while (choice != 0);
}

void add_menu() {
    int choice=0;
    char* ID=NULL;
    char* name=NULL;
    int semester;
    char* initial=NULL;
    char* code=NULL;
    char* title=NULL;
    int credit;
    int key;
    do {
        printf("\n====== Add Menu ======\n");
        printf("  1. Add Student\n");
        printf("  2. Add Faculty\n");
        printf("  3. Add Course\n");
        printf("  0. Return to Main Menu\n");
        printf("======================\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
        fflush(stdin);

        switch (choice) {
            case 1:
                adstd:
                printf("Enter Student ID: ");
                ID = getString(ID);
                key = std_hash_function(ID);
                if(*(student_list+key) != NULL){
                    printf("Conflicting ID Number.\n");
                    goto adstd;
                }
                printf("Enter Student Name: ");
                name = getString(name);
                printf("Enter Semester Number: ");
                scanf("%d",&semester);
                std_insert(student_list,std_createnode(ID,name,semester));
                printf("Student added successfully.\n");
                break;
            case 2:
                adfac:
                printf("Enter Faculty Initial: ");
                initial = getString(initial);
                key = fac_hash_function(initial);
                if(*(faculty_list+key) != NULL){
                    printf("Conflicting Faculty Initial.\n");
                    goto adfac;
                }
                printf("Enter Faculty Name: ");
                name = getString(name);
                fac_insert(faculty_list,fac_createnode(initial,name));
                printf("Faculty added successfully.\n");
                break;
            case 3:
                adcou:
                printf("Enter Course Code: ");
                code = getString(code);
                key = cou_hash_function(code);
                if(*(course_list+key) != NULL){
                    printf("Conflicting Course Code.\n");
                    goto adcou;
                }
                printf("Enter Course Title: ");
                title = getString(title);
                printf("Enter Course Credit: ");
                scanf("%d",&credit);
                cou_insert(course_list,cou_createnode(code,title,credit));
                printf("Course added successfully.\n");
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        getch();
        system("cls");
        fflush(stdin);
    } while (choice != 0);
}

void remove_menu() {
    int choice;
    char* ID;
    char* initial;
    char* code;
    int key;
    do {
        printf("\n====== Remove Menu ======\n");
        printf("  1. Remove Student\n");
        printf("  2. Remove Faculty\n");
        printf("  3. Remove Course\n");
        printf("  0. Return to Main Menu\n");
        printf("=======================\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
        fflush(stdin);
        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                ID = getString(ID);
                key = std_hash_function(ID);
                if(*(student_list + key) != NULL){
                    std_delete(student_list,key);
                }else
                    printf("No Student found with that ID.\n");
                printf("Student removed successfully.\n");
                break;
            case 2:
                printf("Enter Faculty Initial: ");
                initial = getString(initial);
                key = fac_hash_function(initial);
                if(*(faculty_list + key) != NULL){
                    fac_delete(faculty_list,key);
                }else
                    printf("No Faculty found with that initial.\n");
                printf("Faculty removed successfully.\n");
                break;
            case 3:
                printf("Enter Course Code: ");
                code = getString(code);
                key = cou_hash_function(code);
                if(*(course_list + key) != NULL){
                    cou_delete(course_list,key);
                }else
                    printf("No Course found with that code.\n");
                printf("Course removed successfully.\n");
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        getch();
        system("cls");
        fflush(stdin);
    } while (choice != 0);
}

void edit_menu() {
    int choice;
    char* ID=NULL;
    char* name=NULL;
    int semester;
    char* initial=NULL;
    char* code=NULL;
    char* title=NULL;
    int credit;
    int key;
    do {
        printf("\n====== Edit Menu ======\n");
        printf("  1. Edit Student\n");
        printf("  2. Edit Faculty\n");
        printf("  3. Edit Course\n");
        printf("  4. Edit Offered Course\n");
        printf("  0. Return to Main Menu\n");
        printf("=====================\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
        fflush(stdin);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                ID = getString(ID);
                key = std_hash_function(ID);
                if(*(student_list + key) != NULL){
                    printf("Enter New Student Name: ");
                    name = getString(name);
                    printf("Enter New Semester Number: ");
                    scanf("%d",&semester);
                    std_edit(student_list,key,name,semester);
                }else
                    printf("No Student found with that ID.\n");
                printf("Student details updated successfully.\n");
                break;
            case 2:
                printf("Enter Faculty Initial: ");
                initial = getString(initial);
                key = fac_hash_function(initial);
                if(*(faculty_list + key) != NULL){
                    printf("Enter New Faculty Name: ");
                    name = getString(name);
                    fac_edit(faculty_list,key,name);
                }else
                    printf("No Faculty found with that initial.\n");
                printf("Faculty details updated successfully.\n");
                break;
            case 3:
                printf("Enter Course Code: ");
                code = getString(code);
                key = cou_hash_function(code);
                if(*(course_list + key) != NULL){
                    printf("Enter New Course Title: ");
                    title = getString(title);
                    printf("Enter New Course Credit: ");
                    scanf("%d",&credit);
                    cou_edit(course_list,key,title,credit);
                }else
                    printf("No Course found with that code.\n");
                printf("Course details updated successfully.\n");
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        getch();
        system("cls");
        fflush(stdin);
    } while (choice != 0);
}

void offer_courses_menu() {
    int choice;
    char* code;
    int section;
    char* initial;
    int max_std;
    int key;
    do{
        printf("\n====== Offer Courses Menu ======\n");
        printf("  1. Offer a New Course\n");
        printf("  2. Edit an Offered Course\n");
        printf("  3. Remove an Offered Course\n");
        printf("  0. Return to Main Menu\n");
        printf("================================\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
        fflush(stdin);

        switch (choice) {
            case 1:
                if(course_size > 0){
                    course_selection:
                    cou_info_list_print(course_list);
                    printf("\nEnter Course Code: ");
                    code = getString(code);
                    key = cou_hash_function(code);
                    if(*(course_list + key) == NULL){
                        printf("Invalid Code\n");
                        goto course_selection;
                    }
                    initial=NULL;
                    section_selection:
                    printf("Enter Section: ");
                    scanf("%d", &section);
                    key = ofc_hash_function(code,section);
                    if(*(offered_courses_list + key) != NULL){
                        printf("Conflicting Section Number\n");
                        goto section_selection;
                    }
                    printf("Enter Max Student Number: ");
                    scanf("%d", &max_std);
                    key = cou_hash_function(code);
                    ofc_insert(offered_courses_list,
                               ofc_createnode(*(course_list + key),
                                              section,initial,max_std));
                    printf("Course offered successfully.\n");
                }else
                    printf("No Courses available to offer.\n");
                break;
            case 2:
                if(offered_courses_size > 0){
                    ofc_selection:
                    ofc_info_list_print(offered_courses_list);
                    printf("\nEnter Course Code: ");
                    code = getString(code);
                    printf("\nEnter Section: ");
                    scanf("%d",&section);
                    key = ofc_hash_function(code,section);
                    if(*(offered_courses_list + key) == NULL){
                        printf("Invalid course Code or section.\n");
                        goto ofc_selection;
                    }
                    ofc_fac_selection:
                    fac_info_list_print(faculty_list);
                    printf("\nEnter Faculty Initial: ");
                    initial = getString(initial);
                    key = cou_hash_function(initial);
                    if(*(faculty_list + key) == NULL){
                        printf("Invalid Initial.\n");
                        goto ofc_fac_selection;
                    }
                    printf("Enter Max Student Number: ");
                    scanf("%d", &max_std);
                    key = ofc_hash_function(code,section);
                    ofc_edit(offered_courses_list,key,initial,max_std);
                }else
                    printf("No Offered Course found with that code and section.\n");
                break;
            case 3:
                if(offered_courses_size > 0){
                    ofc_selection_remove:
                    ofc_info_list_print(offered_courses_list);
                    printf("\nEnter Course Code: ");
                    code = getString(code);
                    printf("\nEnter Section: ");
                    scanf("%d",&section);
                    key = ofc_hash_function(code,section);
                    if(*(offered_courses_list + key) == NULL){
                        printf("Invalid course Code or Section.\n");
                        goto ofc_selection_remove;
                    }
                    ofc_delete(offered_courses_list,key);
                }else
                    printf("No Offered Courses available.\n");
                break;
            case 4:
                ofc_info_list_print(offered_courses_list);
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        getch();
        system("cls");
        fflush(stdin);
    }while(choice != 0);    
}

void enroll_menu() {
    int choice;
    char* ID;
    char* code;
    int section;
    char* initial;
    int max_std;
    int key1,key2;
    do{
        printf("\n====== Course Enrollment Menu ======\n");
        printf("  1. Enroll Student\n");
        printf("  2. Enroll Faculty\n");
        printf("  3. Unenroll Student\n");
        printf("  4. Unenroll Faculty\n");
        printf("  0. Return to Main Menu\n");
        printf("====================================\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
        fflush(stdin);

        switch (choice) {
            case 1:
                if(student_size > 0 && offered_courses_size > 0){
                    std_select:
                    std_info_list_print(student_list);
                    printf("\nEnter Student ID: ");
                    ID = getString(ID);
                    key1 = std_hash_function(ID);
                    if(*(student_list + key1) == NULL){
                        printf("Invalid ID.\n");
                        goto std_select;
                    }
                    ofcs_selection:
                    ofc_info_list_print(offered_courses_list);
                    printf("\nEnter Course Code: ");
                    code = getString(code);
                    printf("\nEnter Section: ");
                    scanf("%d",&section);
                    key2 = ofc_hash_function(code,section);
                    if(*(offered_courses_list + key2) == NULL){
                        printf("Invalid course Code or section.\n");
                        goto ofcs_selection;
                    }
                    ac_list_insert(&((*(student_list+key1))->selected_courses),
                                      ac_list_createnode(*(offered_courses_list + key2)));
                    std_list_insert(&((*(offered_courses_list + key2))->std_list),
                                      std_list_createnode(*(student_list+key1)));
                    (*(offered_courses_list + key2))->num_of_std++;
                    printf("Student enrolled successfully.\n");
                }else
                    printf("There are no offered courses or Students\n");
                break;
            case 2:
                if(faculty_size > 0 && offered_courses_size > 0){
                    fac_select:
                    fac_info_list_print(faculty_list);
                    printf("\nEnter Faculty Initial: ");
                    initial = getString(initial);
                    key1 = std_hash_function(initial);
                    if(*(faculty_list + key1) == NULL){
                        printf("Invalid Initial.\n");
                        goto fac_select;
                    }
                    ofcf_selection:
                    ofc_info_list_print(offered_courses_list);
                    printf("\nEnter Course Code: ");
                    code = getString(code);
                    printf("\nEnter Section: ");
                    scanf("%d",&section);
                    key2 = ofc_hash_function(code,section);
                    if(*(offered_courses_list + key2) == NULL){
                        printf("Invalid course Code or section.\n");
                        goto ofcf_selection;
                    }
                    (*(offered_courses_list + key2))->faculty_initial=initial;
                    ac_list_insert(&((*(faculty_list+key1))->assigned_sections),
                                   ac_list_createnode(*(offered_courses_list + key2)));
                    printf("Faculty enrolled successfully.\n");               
                }else
                    printf("There are no offered courses or Faculties\n");
                break;
            case 3:
                if(offered_courses_size > 0){
                    ofcr_selection:
                    ofc_info_list_print(offered_courses_list);
                    printf("\nEnter Course Code: ");
                    code = getString(code);
                    printf("\nEnter Section: ");
                    scanf("%d",&section);
                    key2 = ofc_hash_function(code,section);
                    if(*(offered_courses_list + key2) == NULL){
                        printf("Invalid course Code or section.\n");
                        goto ofcr_selection;
                    }
                    if((*(offered_courses_list + key2))->num_of_std == 0){
                        printf("No Students available for unenroll in this section.\n");
                        break;
                    }
                    st_select:
                    ofc_display_title();
                    ofc_info_print(*(offered_courses_list + key2),1);
                    printf("\nEnter Student ID: ");
                    fflush(stdin);
                    ID = getString(ID);
                    std_list* temp=(*(offered_courses_list + key2))->std_list;
                    while(temp != NULL){
                        if(strcmp(temp->student->ID,ID) == 0)
                            break;
                        temp = temp->next;
                    }
                    if(temp == NULL){
                        printf("Invalid ID.\n");
                        goto st_select;
                    }
                    key1 = std_hash_function(ID);
                    ac_list_delete(&((*(student_list+key1))->selected_courses),*(offered_courses_list + key2));
                    std_list_delete(&((*(offered_courses_list + key2))->std_list),*(student_list+key1));
                    (*(offered_courses_list + key2))->num_of_std--;
                    printf("Student unenrolled successfully.\n");
                }else
                    printf("There are no offered courses\n");
                break;
            case 4:
                if(offered_courses_size > 0){
                    ofcfu_selection:
                    ofc_info_list_print(offered_courses_list);
                    printf("\nEnter Course Code: ");
                    code = getString(code);
                    printf("\nEnter Section: ");
                    scanf("%d",&section);
                    key2 = ofc_hash_function(code,section);
                    if(*(offered_courses_list + key2) == NULL){
                        printf("Invalid course Code or section.\n");
                        goto ofcfu_selection;
                    }
                    if((*(offered_courses_list + key2))->faculty_initial==NULL){
                        printf("No faculty available to unenroll in this course.\n");
                        break;
                    }
                    key1 = fac_hash_function((*(offered_courses_list + key2))->faculty_initial);
                    ac_list_delete(&((*(faculty_list+key1))->assigned_sections),*(offered_courses_list + key2));
                    (*(offered_courses_list + key2))->faculty_initial=NULL;
                    printf("Faculty unenrolled successfully.\n");
                }else
                    printf("There are no offered courses\n");

                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        getch();
        system("cls");
        fflush(stdin);
    }while(choice != 0); 
}

void fac_display_title(){
    printf("------------------------------------------------------------\n");
    printf("Initial Name            Assigned_Sections\n");
    printf("------------------------------------------------------------\n");
}
void fac_info_print(fac* faculty){
    printf("%-7s %-15s ",faculty->initial,faculty->name);
    ac_list* course = faculty->assigned_sections;
    while(course != NULL){
        printf("%-6s-%d |",course->course->course->code,course->course->section);
        course=course->next;
    }
    printf("\n");
}
void fac_info_list_print(fac** faculty_list){
    if(faculty_size > 0){
        fac_display_title();
        for(int i=0;i<faculty_capacity;i++){
            if(*(faculty_list+i) != NULL)
                fac_info_print(*(faculty_list+i));
        }
    }else
        printf("There are no faculties\n");
}
void std_display_title(){
    printf("------------------------------------------------------------\n");
    printf("ID_Number     Name            Semester Courses\n");
    printf("------------------------------------------------------------\n");
}
void std_info_print(std* student){
    printf("%-13s %-15s ",student->ID,student->name);
    if(student->semester == 1)
        printf("%-8s ","SPRING");
    else if(student->semester == 2)
        printf("%-8s ","SUMMER");
    else
        printf("%-8s ","FALL");
    ac_list* course = student->selected_courses;
    while(course != NULL){
        printf("%-6s-%d |",course->course->course->code,course->course->section);
        course=course->next;
    }
    printf("\n");
}
void std_info_list_print(std** student_list){
    if(student_size > 0){
        std_display_title();
        for(int i=0;i<student_capacity;i++){
            if(*(student_list+i) != NULL)
                std_info_print(*(student_list+i));
        }
    }else
        printf("There are no Students\n");
}
void cou_display_title(){
    printf("------------------------------------------------------------\n");
    printf("Course_Code Credit Title\n");
    printf("------------------------------------------------------------\n");
}
void cou_info_print(cou* course){
    printf("%-11s %-6d %-41s\n",course->code,course->credit,course->title);
}
void cou_info_list_print(cou** course_list){
    if(course_size > 0){
        cou_display_title();
        for(int i=0;i<course_capacity;i++){
            if(*(course_list+i) != NULL)
                cou_info_print(*(course_list+i));
        }
    }else
        printf("There are no Courses\n");
}
void ofc_display_title(){
    printf("------------------------------------------------------------\n");
    printf("Course_Code Section Fac_Initial Num_Student Max_Student\n");
    printf("------------------------------------------------------------\n");
}
void ofc_info_print(ofc* course,int wstd){
    printf("%-11s %-7d %-11s %-11d %-11d\n",course->course->code,
                                            course->section,
                                            course->faculty_initial,
                                            course->num_of_std,
                                            course->max_std);
    if(wstd!=0){
        std_list* temp = course->std_list;
        int i=1;
        while(temp != NULL){
            printf("\n\t%-3d. %s\n",i++,temp->student->ID);
            temp = temp->next;
        }
    }
}
void ofc_info_list_print(ofc** offered_courses_list){
    if(offered_courses_size > 0){
        ofc_display_title();
        for(int i=0;i<offered_courses_capacity;i++){
            if(*(offered_courses_list+i) != NULL)
                ofc_info_print(*(offered_courses_list+i),0);
        }
    }else
        printf("There are no Offered Courses\n");
}
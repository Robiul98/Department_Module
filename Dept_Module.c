#include "Dept_Module.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int faculty_capacity,
    faculty_size,
    student_capacity,
    student_size,
    course_capacity,
    course_size,
    offered_courses_capacity,
    offered_courses_size;

void basic_capacity(int fac_cap,int fac_size,
                    int std_cap,int std_size,
                    int cou_cap,int cou_size,
                    int ofc_cap,int ofc_size){
    faculty_capacity = fac_cap;
    faculty_size     = fac_size;
    student_capacity = std_cap;
    student_size     = std_size;
    course_capacity  = cou_cap;
    course_size      = cou_size;
    offered_courses_capacity=ofc_cap;
    offered_courses_size= ofc_size;
}

char* getString(char* c){
    c = (char*)malloc(sizeof(char));
    int temp;
    *c='\0';
    for(int i=0;(temp=getchar()) != '\n' && temp != EOF; i++){
        c = realloc(c,(i+2));
        *(c+i)=(char)temp;
        *(c+i+1)='\0';
    }
    return c;
}

void cou_init_list(cou*** course_list){
    *course_list = (cou**)malloc(course_capacity * sizeof(cou*));
    for(int i=0;i<course_capacity;i++)
        *(*course_list + i) = NULL;
}
int  cou_hash_function(char* code){
    strupr(code);
    int key=0;
    for(int i=0;*(code + i) != '\0';i++)
        key += *(code + i) * (i+1);
    key = key % course_capacity;
    return key;
}
void cou_insert(cou** course_list,cou* course){
    int key = cou_hash_function(course->code);
    *(course_list + key) = course;
    course_size++;
}
void cou_delete(cou** course_list,int key){
    free((*(course_list + key))->code);
    free((*(course_list + key))->title);
    free((*(course_list + key)));
    *(course_list + key) = NULL;
    course_size--;
}
void cou_edit(cou** course_list,int key,char* title,int credit){
    (*(course_list + key))->title=title;
    (*(course_list + key))->credit=credit;
}
cou* cou_createnode(char* code,char* title,int credit){
    cou* course;
    course = (cou*)malloc(sizeof(cou));
    course->code=code;
    course->title=title;
    course->credit=credit;
    return course;
}
cou* cou_get(cou** course_list,char* code){
    int key = cou_hash_function(code);
    return *(course_list + key);
}

void std_list_insert(std_list** std_list_head, std_list* student){
    if(std_list_head != NULL){
        student->next= *std_list_head;
        *std_list_head= student;
    }else
        *std_list_head= student;
}
void std_list_delete(std_list** std_list_head, std* student){
    std_list* temp = *std_list_head,*temp2;
    if((*std_list_head)->student == student){
        *std_list_head = (*std_list_head)->next;
        free(temp);
        return;
    }
    while(temp != NULL)
        if(temp->next->student == student){
            temp2 = temp->next;
            temp->next=temp->next->next;
            free(temp2);
            break;
        }else
            temp=temp->next;
}
void std_free_list(std_list** std_list_head){
    std_list* temp;
    temp= *std_list_head;
    while(temp != NULL){
        temp = *std_list_head;
        *std_list_head= temp->next;
        free(temp);
    }
}
std_list* std_list_createnode(std* student){
    std_list* std;
    std= (std_list*)malloc(sizeof(std_list*));
    std->student=student;
    std->next=NULL;
    return std;
}

void ofc_init_list(ofc*** offered_courses_list){
   *offered_courses_list = (ofc**)malloc(offered_courses_capacity * sizeof(ofc*));
    for(int i=0;i<offered_courses_capacity;i++)
        *(*offered_courses_list + i) = NULL;
}
int  ofc_hash_function(char* code,int section){
    strupr(code);
    int key=0;
    for(int i=0;*(code + i) != '\0';i++)
        key += *(code + i) * (i+1) + section;
    key = key % offered_courses_capacity;
    return key;
}
void ofc_insert(ofc** offered_courses_list,ofc* course){
    int key = ofc_hash_function(course->course->code,course->section);
    *(offered_courses_list + key) = course;
    offered_courses_size++;
}
void ofc_delete(ofc** offered_courses_list,int key){
    free((*(offered_courses_list + key))->faculty_initial);
    std_free_list(&((*(offered_courses_list + key))->std_list));
    free((*(offered_courses_list + key)));
    *(offered_courses_list + key) = NULL;
    offered_courses_size--;
}
void ofc_edit(ofc** offered_courses_list,int key,
              char* faculty_initial,int max_std){
    (*(offered_courses_list + key))->faculty_initial=faculty_initial;
    (*(offered_courses_list + key))->max_std=max_std;
}
ofc* ofc_createnode(cou* course,int section,char* fac_initial,int max_std){
    ofc* offer;
    offer = (ofc*)malloc(sizeof(ofc));
    offer->course=course;
    offer->section=section;
    offer->faculty_initial=fac_initial;
    offer->num_of_std=0;
    offer->max_std=max_std;
    offer->std_list=NULL;
    return offer;
}
ofc* ofc_get(ofc** offered_courses_list,char* code,int section){
    int key = ofc_hash_function(code,section);
    return *(offered_courses_list + key);
}

void ac_list_insert(ac_list** ac_list_head, ac_list* course){
    if(ac_list_head != NULL){
        course->next= *ac_list_head;
        *ac_list_head=course;
    }else
        *ac_list_head=course;
}
void ac_list_delete(ac_list** ac_list_head, ofc* course){
    ac_list* temp = *ac_list_head,*temp2;
    if((*ac_list_head)->course == course){
        *ac_list_head = (*ac_list_head)->next;
        free(temp);
        return;
    }
    while(temp != NULL)
        if(temp->next->course == course){
            temp2 = temp->next;
            temp->next=temp->next->next;
            free(temp2);
            break;
        }else
            temp=temp->next;
}
void ac_free_list(ac_list** ac_list_head){
    ac_list* temp;
    temp= *ac_list_head; 
    while(temp != NULL){
        temp = *ac_list_head;
        *ac_list_head= temp->next;
        free(temp);
    }
}
ac_list* ac_list_createnode(ofc* course){
    ac_list* cou;
    cou= (ac_list*)malloc(sizeof(ac_list));
    cou->course=course;
    cou->next=NULL;
    return cou;
}

void std_init_list(std*** student_list){
    *student_list = (std**)malloc(student_capacity * sizeof(std*));
    for(int i=0;i<student_capacity;i++)
        *(*student_list + i) = NULL;
}
int  std_hash_function(char* ID){
    int key=0;
    for(int i=0;*(ID + i) != '\0';i++)
        key += *(ID + i) * (i+1);
    key = key % student_capacity;
    return key;
}
void std_insert(std** student_list,std* student){
    int key = std_hash_function(student->ID);
    *(student_list + key) = student;
    student_size++;
}
void std_delete(std** student_list,int key){
    free((*(student_list + key))->ID);
    free((*(student_list + key))->name);
    ac_free_list(&((*(student_list + key))->selected_courses));
    free(*(student_list + key));
    *(student_list + key) = NULL;
    student_size--;
}
void std_edit(std** student_list,int key,char* name,int semester){
    (*(student_list + key))->name=name;
    (*(student_list + key))->semester=semester;
}

std* std_createnode(char* ID,char* name,int semester){
    std* student;
    student = (std*)malloc(sizeof(std));
    student->ID=ID;
    student->name=name;
    student->semester=semester;
    student->selected_courses=NULL;
    return student;
}
std* std_get(std** student_list,char* ID){
    int key = std_hash_function(ID);
    return *(student_list + key);
}

void fac_init_list(fac*** faculty_list){
    *faculty_list = (fac**)malloc(faculty_capacity * sizeof(fac*));
    for(int i=0;i<faculty_capacity;i++)
        *(*faculty_list + i) = NULL;
}
int  fac_hash_function(char* initial){
    strupr(initial);
    int key=0;
    for(int i=0;*(initial + i) != '\0';i++)
        key += *(initial + i) * (i+1);
    key = key % faculty_capacity;
    return key;  
}
void fac_insert(fac** faculty_list,fac* faculty){
    int key = fac_hash_function(faculty->initial);
    *(faculty_list + key) = faculty;
    faculty_size++;
}
void fac_delete(fac** faculty_list,int key){
    free((*(faculty_list + key))->initial);
    free((*(faculty_list + key))->name);
    ac_free_list(&((*(faculty_list + key))->assigned_sections));
    free((*(faculty_list + key)));
    *(faculty_list + key) = NULL;
    faculty_size--;
}
void fac_edit(fac** faculty_list,int key,char* name){
    (*(faculty_list + key))->name=name;
}
fac* fac_createnode(char* initial,char* name){
    fac* faculty;
    faculty = (fac*)malloc(sizeof(fac));
    faculty->initial=initial;
    faculty->name=name;
    faculty->num_assigned_sections=0;
    faculty->assigned_sections=NULL;
    return faculty;
}
fac* fac_get(fac** faculty_list,char* initial){
    int key = fac_hash_function(initial);
    return *(faculty_list + key);
}
//
//  main.c
//  linked_list_c
//
//  Created by LKLFS on 16/6/12.
//  Copyright © 2016年 LKLFS. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// 创建结构体
typedef struct student{
    char name[20];	//姓名
    char ID[20];	//学号
    int age;		//年龄
    int score;		//成绩
}stu_t;

typedef struct node {
    // 数据
    void * data;
    struct node * next;
}node_t;

// 创建节点
node_t * create_node(void);
//添加节点
void add_node(node_t * head, void * data);
//遍历节点
void travel_list(node_t * head, void (*func)(node_t *));

//创建结构体
stu_t * create_data_struct(void);
//遍历打印每名学生的信息
void print_students(node_t * head);
//查找学生，打印学生信息(name)
void find_students(node_t * head, stu_t * student);
//(ID)
void find_students2(node_t * head, stu_t * student);
//删除学生
void remove_students(node_t * head, stu_t * student);

int main(int argc, const char * argv[]) {
    // 构建链表
    // 创建头节点，头结点是第一个节点，不存储数据
    node_t * head = create_node();
    node_t * A = create_node();
    node_t * B = create_node();
    node_t * C = create_node();
    node_t * D = create_node();
    
    //创建结构体，存储数据
    stu_t * new_student_A = create_data_struct();
    new_student_A->age = (int)random() % 100;
    new_student_A->score = (int)random() % 100;
    A->data = new_student_A;
    
    //创建结构体，存储数据
    stu_t * new_student_B = create_data_struct();
    new_student_B->age = (int)random() % 100;
    new_student_B->score = (int)random() % 100;
    B->data = new_student_B;
    
    //创建结构体，存储数据
    stu_t * new_student_C = create_data_struct();
    new_student_C->age = (int)random() % 100;
    new_student_C->score = (int)random() % 100;
    C->data = new_student_C;
    
    //创建结构体，存储数据
    stu_t * new_student_D = create_data_struct();
    new_student_D->age = (int)random() % 100;
    new_student_D->score = (int)random() % 100;
    D->data = new_student_D;
    
    head->next = A;
    A->next = B;
    B->next = C;
    C->next = D;

    while (1) {
        printf("请选择操作:(1)添加一名学生, (2)打印所有学生信息, (3)通过姓名查找一名学生, (4)通过学号查找一名学生, (5)通过姓名删除学生, (6)链表逆序\n");
        int ctrl;
        scanf("%d", &ctrl);
        
        if (ctrl == 1) {
            
            printf("请输入学生姓名、学号、年龄和成绩!\n");
            //创建结构体，存储数据
            stu_t * new_student = create_data_struct();
            scanf("%s%s%d%d", new_student->name, new_student->ID, &new_student->age, &new_student->score);
            //将新建节点添加到链上
            add_node(head, new_student);
            
        } else if (ctrl == 2) {
            //打印学生信息
            //遍历链表的每个节点
            print_students(head);
            
        }else if (ctrl == 3) {
            
            printf("请输入学生的姓名:\n");
            
            //创建一个参照数据源
            stu_t * student = create_data_struct();
            scanf("%s", student->name);
            
            //通过参照数据源，查找学生
            find_students(head, student);
            free(student);
            
        }
        //***********************************************
        else if (ctrl == 4) {
            
            printf("请输入学生的学号:\n");
            
            //创建一个参照数据源
            stu_t * student = create_data_struct();
            scanf("%s", student->ID);
            
            //通过参照数据源，查找学生
            find_students2(head, student);
            free(student);
            
        }
        
        
        //***********************************************
        else if (ctrl == 5) {
            
            printf("请输入学生的姓名:\n");
            
            //创建一个参照数据源
            stu_t * student = create_data_struct();
            scanf("%s", student->name);
            
            //删除学生
            remove_students(head, student);
        }
        else if (ctrl == 6){
            // 逆序  (迭代循环法)
            node_t * prev = create_node();
            // 将A节点的next指针指向prev
            A->next = prev;
            prev->next = NULL;
            head->next = B;

            B->next = A;
            head->next = C;
            
            C->next = B;
            head->next = D;
            
            D->next = C;
            
            A->next = NULL;
        }
    }
}

#pragma mark - 链表相关
/*------关于链表的操作-------*/

//创建节点
node_t * create_node(void)
{
    node_t * p = (node_t *)malloc(sizeof(node_t));
    if (!p) {
        perror("p");
        exit(-1);
    }
    //因为堆空间不再栈里，所以空间并不会在函数返回后消失
    //堆空间默认清空，所以这句话可以不写。
    p->next = NULL;
    return p;
}

//添加节点
void add_node(node_t * head, void * new_data)
{
    //将new_node添加到已有链表的最后
    while (head->next) {
        head = head->next;
    }
    
    //创建新的节点，存储数据
    node_t * new_node = create_node();
    new_node->data = new_data;
    
    //将新节点添加到原链表尾端
    head->next = new_node;
    new_node->next = NULL;
    return;
}

//遍历节点
void travel_list(node_t * head,
                 void(*func)(node_t *))
{
    while((head = head->next)) {
        func(head);
    }
}





//根据参照，查找节点
node_t * find_nodes(node_t * head, void * data,
                    int (*cmp)(void *, void *))
{
    //返回值是一个链表
    node_t * findedHead = create_node();
    
    //遍历原链表，找到符合数据源要求的添加到新链表
    while ((head = head->next)) {
        if (cmp(head->data, data)) {
            add_node(findedHead, head->data);
        }
    }
    
    return findedHead;
}

//根据参照，删除一个节点
void remove_nodes(node_t * head, void * data,
                  int (*cmp)(void *, void *))
{
    while (head->next) {
        if (cmp(head->next->data, data)) {
            free(head->next->data);
            node_t * tmp = head->next->next;
            free(head->next);
            head->next = tmp;
        } else {
            head = head->next;
        }
    }
}


//释放整条链表
void free_list(node_t * head)
{
    while (head) {
        node_t * tmp = head->next;
        free(head);
        head = tmp;
    }
    return;
}




#pragma mark - 数据源相关
/*------关于数据源-------*/
//创建结构体
stu_t * create_data_struct(void)
{
    stu_t * p = (stu_t *)malloc(sizeof(stu_t));
    if (!p) {
        perror("malloc");
        exit(-1);
    }
    return p;
}


//打印节点
void print_node(node_t * node)
{
    stu_t * student = (stu_t *)node->data;
    printf("姓名:%s 学号:%s 年龄:%d 成绩:%d\n", student->name, student->ID, student->age, student->score);
}


//遍历打印每名学生的信息
void print_students(node_t * head)
{
    travel_list(head, print_node);
    return;
}

//比较学生
int cmp_students_name(void * stu1, void * stu2)
{
    return strcmp(((stu_t *)stu1)->name, ((stu_t *)stu2)->name) == 0;
}
//*****************************
//比较学生（ID）
int cmp_students_ID(void * stu1, void * stu2)
{
    return strcmp(((stu_t *)stu1)->ID, ((stu_t *)stu2)->ID) == 0;
}
//*****************************
//查找学生，打印学生信息
void find_students(node_t * head, stu_t * student)
{
    node_t * finded = find_nodes(head, student, cmp_students_name);
    
    print_students(finded);
    
    free_list(finded);
}
//*****************************
//查找学生，打印学生信息(ID)
void find_students2(node_t * head, stu_t * student)
{
    node_t * finded = find_nodes(head, student, cmp_students_ID);
    
    print_students(finded);
    
    free_list(finded);
}
//*****************************
//删除学生
void remove_students(node_t * head, stu_t * student)
{
    remove_nodes(head, student, cmp_students_name);
    
    print_students(head);
}


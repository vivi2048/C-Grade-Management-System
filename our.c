#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void clean();                                             // 清屏
void st_check_grade(int id);                              // 打印 id 对应的信息
void change_password(int id);                             // 修改 id 对应的密码
void file_input(int id);                                  // 文件录入
void one_input(int id);                                   // 单个录入
void input_grade(int id);                                 // 录入成绩
void change_grade(int id);                                // 修改成绩
void check_grade(int id);                                 // 打印成绩
void reset_password();                                    // 重置密码
int signin(int* id);                                      // 用户登录
int check(int id, int password);                          // 检查账号密码
void print_st_menu(int id);                               // 打印学生菜单
void print_te_menu(int id);                               // 打印老师菜单
void print_op_menu(int id);                               // 打印管理员菜单  opid:00

// 学生结构体
typedef struct student {
    char name[50];                  // 姓  名
    int id;                         // 账  号
    int password;                   // 密  码
    int sex;                        // 性  别  男:1 女:0
    int age;                        // 年  龄
    double math1;                   // 线性代数   teid:01
    double math2;                   // 微积分     teid:02
    double math3;                   // 离散数学   teid:03
    double pro;                     // 程序设计   teid:04
} Stu;

// 学生链表
typedef struct Node {
    Stu student;
    struct Node* next;
} Node;

// 老师链表
typedef struct Node2 {
    int id;
    int password;
    struct Node2* next;
} Node2;

// 全局变量 链表头
typedef struct Node* Link;
Link head = NULL;
typedef struct Node2* Link2;
Link2 head2 = NULL;
Link tmp;
int Z=0;
// 主函数 选择菜单
int main() {
    int id;
    int i = signin(&id);
    switch (i) {
    case 1:
        print_op_menu(id);
        break;
    case 2:
        print_te_menu(id);
        break;
    case 3:
        print_st_menu(id);
        break;
    }
    return 0;
}

// 清屏
void clean() {
    printf("\033[2J\033[H");
}

// 打印 id 对应的信息
void st_check_grade(int id) {
    clean();
    printf("id:%d\n", id);
    Link p = head;
    for (;p->next == NULL;p = p->next) {
        if (id == p->student.id) {
            printf("姓名:%s\n", p->student.name);
            printf("账号:%d\n", p->student.id);
            printf("性别:%d\n", p->student.sex);
            printf("年龄:%d\n", p->student.age);
            printf("线性代数成绩:%lf\n", p->student.math1);
            printf("微积分成绩:%lf\n", p->student.math2);
            printf("离散数学成绩:%lf\n", p->student.math3);
            printf("程序设计成绩:%lf\n", p->student.pro);
            getch();
            print_st_menu(id);
        }
    }
}

// 修改 id 对应的密码
void change_password(int id) {
    clean();
    printf("id:%d\n", id);
    int newpassword1, newpassword2;
    Link p = head;
    printf("请输入新的密码:");
    scanf("%d", &newpassword1);
    printf("请确认新的密码:");
    scanf("%d", &newpassword2);
    if (newpassword1 != newpassword2) {
        printf("两次密码不一致，请重新输入!");
        getch();
        change_password(id);
    } else {
        for (;p->next == NULL;p = p->next) {
            while (id == p->student.id) {
                p->student.password = newpassword1;
                printf("修改成功！\n");
                getch();
                print_st_menu(id);
            }
        }
    }
}

// 打印学生菜单
void print_st_menu(int id) {
    clean();

    printf("学生菜单\n");
    printf("|1.查询成绩\n");
    printf("|2.修改密码\n");
    printf("|3.返回\n");
    printf("请输入相应的序号选择:");

    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3) {
        switch (i) {
        case 1:
            st_check_grade(id);
            break;
        case 2:
            change_password(id);
            break;
        case 3:
            main();
        }
    } else {
        print_st_menu(id);
    }
}

// 文件录入
void file_input(int id) {

    FILE* fp = NULL;
    char filename[100];
    printf("请输入您要加载的文件地址：");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("文件打开出错\n");
        return;
    }
    head = (malloc)(sizeof(Node));
    head->next = NULL;
    while (!feof(fp)) {
        Stu data;
        fscanf(fp, "%s %d %d %d %d %lf %lf %lf %lf", data.name, &data.id, &data.password, &data.sex, &data.age, &data.math1, &data.math2, &data.math3, &data.pro);
        Link node;
        node = (malloc)(sizeof(Node));
        node->student = data;
        node->next = head->next;
        head->next = node;
    }
    fclose(fp);
    printf("数据加载成功\n");
    getch();
    print_te_menu(id);
}

// 单个录入
void one_input(int id) {
    clean();
    if (id == 00) {
        printf("进入管理员模式\n");
    }

    Stu Student;
    printf("请输入学生账号:");
    scanf("%d", &Student.id);
    printf("请输入学生姓名:");
    scanf("%s", Student.name);
    printf("请输入学生性别:");
    scanf("%d", &Student.sex);
    printf("请输入学生年龄:");
    scanf("%d", &Student.age);
    printf("请输入线性代数成绩:");
    scanf("%lf", &Student.math1);
    printf("请输入微积分成绩:");
    scanf("%lf", &Student.math2);
    printf("请输入离散数学成绩:");
    scanf("%lf", &Student.math3);
    printf("请输入程序设计成绩:");
    scanf("%lf", &Student.pro);
    Link node;
    node = (malloc)(sizeof(Node));
    node->student = Student;
    if(Z==0){
    head=tmp=NULL;
    head=(malloc)(sizeof(Node));
    tmp=head;
    tmp->next=NULL;
	Z++;
	}
	if(head==NULL){
        node->student=Student;
 		head=node;
 		tmp=node;
 		tmp->next=NULL;
    }
    else{
		node->student=Student;
 		tmp->next=node;
 		tmp=node;
 		tmp->next=NULL;
	}
    printf("录入成功！\n");
    getch();
    print_te_menu(id);
}

// 录入成绩 文件录入或单个录入
void input_grade(int id) {
    clean();

    printf("录入方式\n");
    printf("||1.文件录入\n");
    printf("||2.单个录入\n");
    printf("||3.返回\n");
    printf("请输入相应的序号选择:");

    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3) {
        switch (i) {
        case 1:
            file_input(id);
            break;
        case 2:
            one_input(id);
            break;
        case 3:
            print_te_menu(id);
            break;
        }
    } else {
        input_grade(id);
    }
}

// 修改成绩
void change_grade(int id) {

    if (id == 00) {
        int K;
        int H;
        printf("进入管理员模式\n");
        printf("请选择你要修改的学科：\n");
        printf("1.线性代数\n");
        printf("2.微积分\n");
        printf("3.离散数学\n");
        printf("4.程序设计\n");
        scanf("%d", &K);
        if (K == 1) {
            printf("请输入所修改的学生的学号\n");
            scanf("%d", &H);
            Link nod;
            nod = head;
            while (nod->student.id == H) {
                nod = nod->next;
            }
            printf("请输入该学生修改后的成绩\n");
            double F;
            scanf("%lf", &F);
            nod->student.math1 = F;
        }
        if (K == 2) {
            printf("请输入所修改的学生的学号\n");
            scanf("%d", &H);
            Link nod;
            nod = head;
            while (nod->student.id == H) {
                nod = nod->next;
            }
            printf("请输入该学生修改后的成绩\n");
            double F;
            scanf("%lf", &F);
            nod->student.math2 = F;
        }
        if (K == 3) {
            printf("请输入所修改的学生的学号\n");
            scanf("%d", &H);
            Link nod;
            nod = head;
            while (nod->student.id == H) {
                nod = nod->next;
            }
            printf("请输入该学生修改后的成绩\n");
            double F;
            scanf("%lf", &F);
            nod->student.math3 = F;
        }
        if (K == 4) {
            printf("请输入所修改的学生的学号\n");
            scanf("%d", &H);
            Link nod;
            nod = head;
            while (nod->student.id == H) {
                nod = nod->next;
            }
            printf("请输入该学生修改后的成绩\n");
            double F;
            scanf("%lf", &F);
            nod->student.pro = F;
        }
    }
    if (id == 01) {
        int H;
        double F;
        printf("进入老师模式\n");
        printf("现您可以修改线性代数成绩\n");
        printf("请输入所修改的学生的学号\n");
        scanf("%d", &H);
        Link nod;
        nod = head;
        while (nod->student.id == H) {
            nod = nod->next;
        }
        printf("请输入该学生修改后的成绩\n");
        scanf("%lf", &F);
        nod->student.math1 = F;
    }
    if (id == 02) {
        int H;
        double F;
        printf("进入老师模式\n");
        printf("现您可以修改微积分成绩\n");
        printf("请输入所修改的学生的学号\n");
        scanf("%d", &H);
        Link nod;
        nod = head;
        while (nod->student.id == H) {
            nod = nod->next;
        }
        printf("请输入该学生修改后的成绩\n");
        scanf("%lf", &F);
        nod->student.math2 = F;
    }
    if (id == 03) {
        int H;
        double F;
        printf("进入老师模式\n");
        printf("现您可以修改离散数学成绩\n");
        printf("请输入所修改的学生的学号\n");
        scanf("%d", &H);
        Link nod;
        nod = head;
        while (nod->student.id == H) {
            nod = nod->next;
        }
        printf("请输入该学生修改后的成绩\n");
        scanf("%lf", &F);
        nod->student.math3 = F;
    }
    if (id == 04) {
        int H;
        double F;
        printf("进入老师模式\n");
        printf("现您可以修改程序设计成绩\n");
        printf("请输入所修改的学生的学号\n");
        scanf("%d", &H);
        Link nod;
        nod = head;
        while (nod->student.id == H) {
            nod = nod->next;
        }
        printf("请输入该学生修改后的成绩\n");
        scanf("%lf", &F);
        nod->student.pro = F;
    }
}

// 打印成绩
void check_grade(int id) {
    Link Head;
    Head = head->next;
    if (id == 00) {
        printf("进入管理员模式\n");
        printf("学生姓名          学生学号          学生年龄          学生性别          线性代数成绩          微积分成绩          离散数学成绩          程序设计成绩\n");
        do {
            printf("   %s                %d                  %d                 ", Head->student.name, Head->student.id, Head->student.age);
            if (Head->student.sex == 0) {
                printf("女                ");
            } else if (Head->student.sex) {
                printf("男                 ");
            }
            printf("%.2lf                ", Head->student.math1);
            printf("%.2lf                ", Head->student.math2);
            printf("%.2lf                   ", Head->student.math3);
            printf("%.2lf\n", Head->student.pro);
            Head = Head->next;
        } while (Head != NULL);
    }
    if (id == 01 || id == 02 || id == 03 || id == 04) {
        printf("进入老师模式\n");
        printf("当前您可查看线性代数成绩\n");
        printf("学生姓名          学生学号          学生年龄          学生性别          ");
        if (id == 01) {
            printf("线性代数成绩\n");
        } else if (id == 02) {
            printf("微积分成绩\n");
        } else if (id == 03) {
            printf("离散数学成绩\n");
        } else if (id == 04) {
            printf("程序设计成绩\n");
        }
        do {
            printf("   %s                %d                  %d                 ", Head->student.name, Head->student.id, Head->student.age);
            if (Head->student.sex == 0) {
                printf("女                ");
            } else if (Head->student.sex) {
                printf("男                 ");
            }
            if (id == 01) {
                printf("%.2lf\n", Head->student.math1);
            } else if (id == 02) {
                printf("%.2lf\n", Head->student.math2);
            } else if (id == 03) {
                printf("%.2lf\n", Head->student.math3);
            } else if (id == 04) {
                printf("%.2lf\n", Head->student.pro);
            }
        } while (Head->next != NULL);
    }
}

// 打印老师菜单
void print_te_menu(int id) {
    clean();

    printf("老师菜单\n");
    printf("|1.录入成绩\n");
    printf("|2.修改成绩\n");
    printf("|3.查询成绩\n");
    printf("|4.修改密码\n");
    printf("|5.退出\n");
    printf("请输入相应的序号选择:");

    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5) {
        switch (i) {
        case 1:
            input_grade(id);
            break;
        case 2:
            change_grade(id);
            break;
        case 3:
            check_grade(id);
            break;
        case 4:
            change_password(id);
            break;
        case 5:
            return;
        }
    } else {
        print_te_menu(id);
    }
}

// 打印管理员菜单
void print_op_menu(int id) {
    clean();

    printf("管理员菜单\n");
    printf("|1.录入成绩\n");
    printf("|2.修改成绩\n");
    printf("|3.查询成绩\n");
    printf("|4.密码设置\n");
    printf("|5.退出\n");
    printf("请输入相应的序号选择:");

    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5) {
        switch (i) {
        case 1:
            input_grade(id);
            break;
        case 2:
            change_grade(id);
            break;
        case 3:
            check_grade(id);
            break;
        case 4:
            reset_password(id);
            break;
        case 5:
            return;
        }
    } else {
        print_op_menu(id);
    }
}

// 重置密码
void reset_password(int id) {
    Link p1 = head;
    Link2 p2 = head2;
    printf("---------------------");
    printf("1.重置老师或学生密码");
    printf("2.初始化所有密码");
    printf("3.返回上一级菜单");
    printf("---------------------");
    int flag;
    scanf("%d", &flag);
    if (flag == 1) {
        printf("请输入需要重置密码的id");
        int i;
        scanf("%d", &i);
        for (;1;) {
            if (p2->id == i) {
                printf("您将要重置教师%d的密码,输入Y以确认", i);
                char qr;
                qr = getchar();
                if (strcmp(&qr, "y") == 0 || strcmp(&qr, "Y") == 0) {
                    p2->password = p2->id;
                    printf("修改成功(初始密码与id相同)");
                } else {
                    printf("返回上一级菜单");
                    break;
                }
                return;
            } else {
                p2 = p2->next;
            }
            if (p2->next == NULL) {
                break;
            }
        }
        for (;1;) {
            if (p1->student.id == i) {
                printf("您将要重置学生%d的密码,输入Y以确认", i);
                char qr;
                qr = getchar();
                if (strcmp(&qr, "y") == 0 || strcmp(&qr, "Y") == 0) {
                    p1->student.password = p1->student.id;
                    printf("修改成功(初始密码与id相同)");
                } else {
                    printf("返回上一级菜单");
                    break;
                }
            } else {
                p1 = p1->next;
            }
            if (p1->next == NULL) {
                break;
            }
        }
        print_op_menu(id);
    } else if (flag == 2) {
        for (;1;) {
            if (p1->next == NULL) {
                break;
            } else {
                p1->student.password = p1->student.id;
                p1 = p1->next;
            }
            if (p2->next == NULL) {
                break;
            } else {
                p2->password = p2->id;
                p2 = p2->next;
            }
        }
        printf("完成");
        print_op_menu(id);
    } else if (flag == 3) {
        print_op_menu(id);
    } else {
        printf("错误的输入，返回上一级菜单");
        print_op_menu(id);
    }
    return;
}

// 检查账号密码 默认密码与账号相同
int check(int id, int password) {
    // 判断管理员
    if (id == 00 && password == 00) {
        return 1;
    }

    // 判断老师
    Link2 p2 = head2->next;
    while (NULL != p2) {
        if (p2->id == id && p2->password == password) {
            return 2;
        }
        p2 = p2->next;
    }

    // 判断学生
    Link p = head->next;
    while (NULL != p) {
        if (p->student.id == id && p->student.password == password) {
            return 3;
        }
        p = p->next;
    }
    // 错误
    return 0;
}

// 用户登录
int signin(int* id) {

    int iid;
    printf("请输入账号:");
    scanf("%d", &iid);

    int password;
    printf("请输入密码:");
    scanf("%d", &password);

    int flag = check(iid, password);

    if (flag) {
        (*id) = iid;
        return flag;
    } else {
        clean();
        printf("账号或密码错误\n");
        return signin(id);
    }
}

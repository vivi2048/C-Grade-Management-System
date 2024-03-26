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
void reset_password(int id);                              // 重置密码
int signin(int* id);                                      // 用户登录
int check(int id, int password);                          // 检查账号密码
void print_st_menu(int id);                               // 打印学生菜单
void print_te_menu(int id);                               // 打印老师菜单
void print_op_menu(int id);                               // 打印管理员菜单  opid:0
void score_input(int id);								  // 录入竞赛加分绩点  
void print_all(int id);									  // 导出当前序列所有学生成绩 
void bubbleSort_math1();                                  // 链表冒泡排序

// 学生结构体
typedef struct student {
    char name[50];                  // 姓  名
    int id;                         // 账  号
    int password;                   // 密  码
    int sex;                        // 性  别  男:1 女:0
    int age;                        // 年  龄
    double math1;                   // 线性代数   teid:1
    double math2;                   // 微积分     teid:2
    double math3;                   // 离散数学   teid:3
    double pro;                     // 程序设计   teid:4
    double score;					// 竞赛加分绩点
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

// 全局变量
typedef struct Node* Link;
Link head = NULL;
typedef struct Node2* Link2;
Link2 head2 = NULL;
Link tmp;
int Z = 0;

// 老师链表初始化
void te_start() {
    FILE* fp = NULL;
    char filename[] = "te.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("老师数据加载出错\n");
        return;
    }
    Link2 node = NULL;
    while (!feof(fp)) {
        int id, passward;
        fscanf(fp, "%d %d", &id, &passward);
        if (head2 == NULL) {
            head2 = malloc(sizeof(Node2));
            head2->id = id;
            head2->password = passward;
            head2->next = NULL;
            node = head2;
        } else {
            node->next = malloc(sizeof(Node2));
            node = node->next;
            node->id = id;
            node->password = passward;
            node->next = NULL;
        }
    }
    fclose(fp);
}

// 学生链表初始化
void st_start() {
    FILE* fp = NULL;
    char filename[] = "student.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("学生数据加载出错\n");
        return;
    }
    while (!feof(fp)) {
        Stu data;
        fscanf(fp, "%s %d %d %d %d %lf %lf %lf %lf %lf", data.name, &data.id, &data.password, &data.sex, &data.age, &data.math1, &data.math2, &data.math3, &data.pro, &data.score);
        Link node;
        node = (malloc)(sizeof(Node));
        node->student = data;
        if (Z == 0) {
            head = tmp = NULL;
            head = (malloc)(sizeof(Node));
            tmp = head;
            tmp->next = NULL;
            Z++;
        }
        if (head == NULL) {
            node->student = data;
            head = node;
            tmp = node;
            tmp->next = NULL;
        } else {
            node->student = data;
            tmp->next = node;
            tmp = node;
            tmp->next = NULL;
        }
    }
    fclose(fp);
}

// 主函数 选择菜单
int main() {
    te_start();
    st_start();
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
    while (p != NULL) {
        if (id == p->student.id) {
            printf("姓名:\t\t%s\n", p->student.name);
            printf("账号:\t\t%d\n", p->student.id);
            printf("性别:\t\t%d\n", p->student.sex);
            printf("年龄:\t\t%d\n", p->student.age);
            printf("线性代数成绩:\t%.2lf\n", p->student.math1);
            printf("微积分成绩:\t%.2lf\n", p->student.math2);
            printf("离散数学成绩:\t%.2lf\n", p->student.math3);
            printf("程序设计成绩:\t%.2lf\n", p->student.pro);
            printf("竞赛加分绩点:\t%.4lf\n", p->student.score);
            break;
        }
        p = p->next;
    }
    getch();
    print_st_menu(id);
}

// 重置
void re_st5te() {
    FILE* file;
    file = fopen("te.txt", "w");
    Link2 pp = head2;
    for(int i = 0;i < 4;i++) {
        fprintf(file, "%d %d\n", pp->id, pp->password);
        pp = pp->next;
    }
    fclose(file);
    FILE* file1;
    file1 = fopen("student.txt", "w");
    Link p = head->next;
    while (p->next != NULL) {
        fprintf(file1, "%s %d %d %d %d %.2lf %.2lf %.2lf %.2lf %.4f\n", p->student.name, p->student.id, p->student.password, p->student.sex, p->student.age, p->student.math1, p->student.math2, p->student.math3, p->student.pro, p->student.score);
        p = p->next;
    }
    fclose(file1);
}

// 修改 id 对应的密码
void change_password(int id) {
    clean();
    printf("id:%d\n", id);
    int newpassword1, newpassword2;
    printf("请输入新的密码:");
    scanf("%d", &newpassword1);
    printf("请确认新的密码:");
    scanf("%d", &newpassword2);
    if (newpassword1 != newpassword2) {
        printf("两次密码不一致，请重新输入!");
        getch();
        change_password(id);
    } else {
        if (id == 1 || id == 2 || id == 3 || id == 4) {
            Link2 p = head2;
            while (p != NULL) {
                while (id == p->id) {
                    p->password = newpassword1;
                    re_st5te();
                    break;
                }
                p = p->next;
            }
        } else {
            Link p = head->next;
            while (p->next != NULL) {
                while (id == p->student.id) {
                    p->student.password = newpassword1;
                    re_st5te(id);
                    break;
                }
                p = p->next;
            }
        }
    }
    printf("修改成功！\n");
    getch();
    if (id == 1 || id == 2 || id == 3 || id == 4) {
        print_te_menu(id);
    } else {
        print_st_menu(id);
    }
}

// 打印学生菜单
void print_st_menu(int id) {
    clean();
    printf("学生菜单\n");
    printf("|1.查询成绩\n");
    printf("|2.修改密码\n");
    printf("|3.退出\n");
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
            exit(0);
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
    while (!feof(fp)) {
        Stu data;
        fscanf(fp, "%s %d %d %d %lf %lf %lf %lf", data.name, &data.id, &data.sex, &data.age, &data.math1, &data.math2, &data.math3, &data.pro);
        Link node;
        node = (malloc)(sizeof(Node));
        node->student = data;
        if (Z == 0) {
            head = tmp = NULL;
            head = (malloc)(sizeof(Node));
            tmp = head;
            tmp->next = NULL;
            Z++;
        }
        if (head == NULL) {
            node->student = data;
            head = node;
            tmp = node;
            tmp->next = NULL;
        } else {
            node->student = data;
            tmp->next = node;
            tmp = node;
            tmp->next = NULL;
        }
    }
    fclose(fp);
    printf("数据加载成功\n");
    getch();
    print_te_menu(id);
}

// 单个录入
void one_input(int id) {
    clean();
    if (id == 0) {
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
    if (Z == 0) {
        head = tmp = NULL;
        head = (malloc)(sizeof(Node));
        tmp = head;
        tmp->next = NULL;
        Z++;
    }
    if (head == NULL) {
        node->student = Student;
        head = node;
        tmp = node;
        tmp->next = NULL;
    } else {
        node->student = Student;
        tmp->next = node;
        tmp = node;
        tmp->next = NULL;
    }
    printf("录入成功！\n");
    getch();
    print_te_menu(id);
}

//录入竞赛加分绩点
void score_input(int id) {
    if (id == 0) {
        printf("请输入该竞赛学生的学号\n");
        int H;
        scanf("%d", &H);
        Link Head;
        Head = head;
        while (Head->student.id != H) {
            Head = Head->next;
        }
        printf("请输入该学生竞赛绩点\n");
        double J;
        scanf("%lf", &J);
        Head->student.score = J;
    } else if (id == 01 || id == 02 || id == 03 || id == 04) {
        printf("您的权限不足");
    }
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

//修改成绩子系统 
void change_grade_son(int K) {
    printf("请输入所修改的学生的学号\n");
    int H;
    scanf("%d", &H);
    Link Head;
    Head = head;
    while (Head->student.id != H) {
        Head = Head->next;
    }
    printf("请输入该学生修改后的成绩\n");
    double F;
    scanf("%lf", &F);
    if (K == 1) {
        Head->student.math1 = F;
    } else if (K == 2) {
        Head->student.math2 = F;
    } else if (K == 3) {
        Head->student.math3 = F;
    } else if (K == 4) {
        Head->student.pro = F;
    }
}

// 修改成绩
void change_grade(int id) {
    int K;
    if (id == 00) {
        printf("进入管理员模式\n");
        printf("请选择你要修改的学科：\n");
        printf("1.线性代数\n");
        printf("2.微积分\n");
        printf("3.离散数学\n");
        printf("4.程序设计\n");
        scanf("%d", &K);
        change_grade_son(K);
    }
    if (id == 01) {
        K = 1;
        printf("现已进入线性代数老师编辑模式");
        change_grade_son(K);
    }
    if (id == 02) {
        K = 2;
        printf("现已进入微积分老师编辑模式");
        change_grade_son(K);
    }
    if (id == 03) {
        K = 3;
        printf("现已进入离散数学老师编辑模式");
        change_grade_son(K);
    }
    if (id == 04) {
        K = 4;
        printf("现已进入程序设计老师编辑模式");
        change_grade_son(K);
    }
    getch();
    print_te_menu(id);
}

// 打印成绩
void check_grade(int id) {
    Link Head;
    Head = head->next;
    if (id == 00) {
        printf("进入管理员模式\n");
        printf("学生姓名\t  学生学号\t  学生年龄\t  学生性别\t  线性代数成绩 \t\t  微积分成绩 \t\t  离散数学成绩 \t\t  程序设计成绩 \t\t  竞赛绩点\n");
        do {
            printf("   %s\t\t  %d\t\t  %d\t\t", Head->student.name, Head->student.id, Head->student.age);
            if (Head->student.sex == 0) {
                printf("  女\t\t");
            } else if (Head->student.sex) {
                printf("  男\t\t");
            }
            printf("  %-6.2lf\t\t", Head->student.math1);
            printf("  %-6.2lf\t\t", Head->student.math2);
            printf("  %-6.2lf\t\t", Head->student.math3);
            printf("  %-6.2lf\t\t", Head->student.pro);
            printf("  %-4.1lf\n", Head->student.score);
            Head = Head->next;
        } while (Head->next != NULL);
    }
    if (id == 01 || id == 02 || id == 03 || id == 04) {
        printf("进入老师模式\n");
        printf("学生姓名\t  学生学号\t  学生年龄\t  学生性别\t  ");
        if (id == 01) {
            printf("线性代数成绩 \t\t  竞赛绩点\n");
        } else if (id == 02) {
            printf("微积分成绩 \t\t  竞赛绩点\n");
        } else if (id == 03) {
            printf("离散数学成绩 \t\t  竞赛绩点\n");
        } else if (id == 04) {
            printf("程序设计成绩 \t\t  竞赛绩点\n");
        }
        do {
            printf("   %s\t\t  %d\t\t  %d\t\t", Head->student.name, Head->student.id, Head->student.age);
            if (!Head->student.sex) {
                printf("  女\t\t");
            } else {
                printf("  男\t\t");
            }
            if (id == 01) {
                printf("  %6.2lf\t\t", Head->student.math1);
                printf("  %6.1lf\n", Head->student.score);
            } else if (id == 02) {
                printf("  %6.2lf\t\t", Head->student.math2);
                printf("  %6.1lf\n", Head->student.score);
            } else if (id == 03) {
                printf("  %6.2lf\t\t", Head->student.math3);
                printf("  %6.1lf\n", Head->student.score);
            } else if (id == 04) {
                printf("  %6.2lf\t\t", Head->student.pro);
                printf("  %6.1lf\n", Head->student.score);
            }
            Head = Head->next;
        } while (Head->next != NULL);
    }
    getch();
    if (!id) {
        print_op_menu(id);
    } else {
        print_te_menu(id);
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
    printf("|5.打印成绩单\n");
    printf("|6.退出\n");
    printf("请输入相应的序号选择:");
    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6) {
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
            print_all(id);
            break;
        case 6:
            exit(0);
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
    printf("|5.导出成绩单\n");
    printf("|6.退出\n");
    printf("请输入相应的序号选择:");
    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6) {
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
            print_all(id);
            break;
        case 6:
            return;
        }
    } else {
        print_op_menu(id);
    }
}

// 重置密码
void reset_password(int id) {
    clean();
    Link p1 = head->next;
    Link2 p2 = head2;
    printf("密码设置\n");
    printf("||1.重置老师或学生密码\n");
    printf("||2.初始化所有密码\n");
    printf("||3.返回\n");
    printf("请输入相应的序号选择:");
    int flag;
    scanf("%d", &flag);
    if (flag == 1) {
        printf("输入需要重置密码的id:");
        int i;
        scanf("%d", &i);
        while (p2 != NULL) {
            if (p2->id == i) {
                p2->password = p2->id;
                printf("修改成功(重置密码与id相同)");
                getch();
                break;
            }
            p2 = p2->next;
        }
        while (p1 != NULL) {
            if (p1->student.id == i) {
                p2->password = p2->id;
                printf("修改成功(重置密码与id相同)");
                getch();
                break;
            }
            p1 = p1->next;
        }
        re_st5te();
        print_op_menu(id);
    } else if (flag == 2) {
        while (p1 != NULL) {
            p1->student.password = p1->student.id;
            p1 = p1->next;
        }
        while (p2 != NULL) {
            p2->password = p2->id;
            p2 = p2->next;
        }
        re_st5te(id);
        printf("初始化所有密码完成!");
        getch();
        print_op_menu(id);
    } else if (flag == 3) {
        print_op_menu(id);
    } else {
        reset_password(id);
    }
    return;
}

// 检查账号密码 默认密码与账号相同
int check(int id, int password) {
    if (id == 00 && password == 00) {
        return 1;
    }
    Link2 p2 = head2;
    while (NULL != p2) {
        if (p2->id == id && p2->password == password) {
            return 2;
        }
        p2 = p2->next;
    }
    Link p = head->next;
    while (NULL != p) {
        if (p->student.id == id && p->student.password == password) {
            return 3;
        }
        p = p->next;
    }
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

//导出当前所有成绩 
void print_all(int id) {
    bubbleSort_math1();
    FILE* file;
    char filename[100];
    printf("请输入您要另存的文件名称(若存在同名文件则会被覆盖!):");
    scanf("%s", filename);
    strcat(filename, ".txt");
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("失败");
        return;
    }
    Link p = head->next;
    if (!id) {
        fprintf(file, "姓名\t学号\t性别\t年龄\t线性代数\t微积分\t离散数学\t程序设计\t竞赛绩点\n");
        while (p->next != NULL) {
            fprintf(file, "%s\t%d\t%d\t%d\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.4f\n", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.math1, p->student.math2, p->student.math3, p->student.pro, p->student.score);
            p = p->next;
        }
    }
    fclose(file);
}

void bubbleSort_math1(int i){
    Link pre, cur, next, end, temp, p;
    end = NULL;
    while (head->next!= end) {
        for (pre = head, cur = pre->next, next = cur->next;next != end;pre = pre->next, cur = cur->next, next = next->next) {
            if (cur->student.math1 < next->student.math1) {
                cur->next = next->next;
                pre->next = next;
                next->next = cur;
                temp = next;
                next = cur;
                cur = temp;
            }
        }
        end = cur;
    }
    printf("该科目成绩单如下:\n");
    for (p = head->next ,i = 1;p!= NULL;p = p->next, i++){
        printf("%d %s %.2lf\n", i, p->student.name, p->student.math1);
    }
}
void evaluate(char ){
	
}


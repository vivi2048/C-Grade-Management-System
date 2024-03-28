#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define math1iii 3.5
#define math2iii 4.0
#define math3iii 3.0
#define proiii 3.5

#define st_start_format      "%s %d %d %d %d %lf %lf %lf %lf %lf %[^\n]"
#define st_re_format         "%s\t%d\t%d\t%d\t%d\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.4f\t%s"
#define file_input_format    "%s %d %d %d %lf %lf %lf %lf"
#define file_output_format   "\n%s\t\t%d\t\t%d\t\t%d\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.4f"

#define st_start_data        data.name, &data.id, &data.password, &data.sex, &data.age, &data.math1, &data.math2, &data.math3, &data.pro, &data.score, data.evaluation
#define st_re_data           p->student.name, p->student.id, p->student.password, p->student.sex, p->student.age, p->student.math1, p->student.math2, p->student.math3, p->student.pro, p->student.score, p->student.evaluation
#define file_input_data      data.name, &data.id, &data.sex, &data.age, &data.math1, &data.math2, &data.math3, &data.pro
#define file_output_data     p->student.name, p->student.id, p->student.sex, p->student.age, p->student.math1, p->student.math2, p->student.math3, p->student.pro, p->student.score

void clean();                                             // 清屏
void st_check_grade(int id);                              // 打印 id对应的信息
void change_password(int id);                             // 修改 id对应的密码
void op_file_input(int id);                               // op文件录入
void op_one_input(int id);                                // op单个录入
void te_file_input(int id);                               // te文件录入
void op_input_grade(int id);                              // 录入成绩
void change_grade(int id);                                // 修改成绩
void check_grade(int id);                                 // 打印成绩
void reset_password(int id);                              // 重置密码
void print_st_menu(int id);                               // 打印学生菜单
void print_te_menu(int id);                               // 打印老师菜单
void print_op_menu(int id);                               // 打印管理员菜单  opid:0
void score_input(int id);								  // 录入竞赛  
void print_all(int id);					     			  // 导出成绩 
void bubbleSort(int id);                                  // 链表排序
void asa(double s[], int* max, int* min);                 // 进步空间
void te_start();                                          // 老师链表初始化
void st_start();                                          // 学生链表初始化
void re_st5te();                                          // 保存
void change_grade_son(int K, int id);                     // 修改成绩子系统
void evaluate(int id);                                    // 录入评语
void delet_student(int id); 							  // 删除学生
void te_change_grade(int id);                             // 老师成绩录入
void banji(int id);                                       // 打印班级信息
int signin(int* id);                                      // 用户登录
int check(int id, int password);                          // 检查账号密码
double jidian(double i);                                  // 成绩对应绩点

// 学生结构体
typedef struct student {
    char name[50];                                        // 姓名
    int id;                                               // 账号
    int password;                                         // 密码
    int sex;                                              // 性别         男:1 女:0
    int age;                                              // 年龄
    double math1;                                         // 线性代数     teid:1 3.5
    double math2;                                         // 微积分       teid:2 4.0
    double math3;                                         // 离散数学     teid:3 3.0
    double pro;                                           // 程序设计     teid:4 3.5
    double score;				                          // 竞赛绩点
    char evaluation[500];                                 // 评语 
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

// 全局变量 学生
typedef struct Node* Link;
Link head = NULL, tmp;
int Z = 0;

// 全局变量 老师
typedef struct Node2* Link2;
Link2 head2 = NULL;

// 主函数 选择菜单
int main() {
    te_start();
    st_start();
    int id;
    int i = signin(&id);
    switch (i) {
    case 1:
        print_op_menu(id);break;
    case 2:
        print_te_menu(id);break;
    case 3:
        print_st_menu(id);break;
    }
    return 0;
}

// 打印管理员菜单
void print_op_menu(int id) {
    clean();
    printf("管理员菜单\n");
    printf("|1.录入成绩\n");
    printf("|2.修改成绩\n");
    printf("|3.查询成绩\n");
    printf("|4.密码设置\n");
    printf("|5.导出成绩\n");
    printf("|6.录入竞赛\n");
    printf("|7.删除学生\n");
    printf("|8.退出\n");
    printf("请输入相应的序号选择:");
    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8) {
        switch (i) {
        case 1:
            op_input_grade(id);break;
        case 2:
            change_grade(id);break;
        case 3:
            check_grade(id);break;
        case 4:
            reset_password(id);break;
        case 5:
            print_all(id);break;
        case 6:
            score_input(id);break;
        case 7:
            delet_student(id);break;
        case 8:
            exit(0);
        }
    } else print_op_menu(id);
}

// 打印老师菜单
void print_te_menu(int id) {
    clean();
    printf("老师菜单\n");
    printf("|1.成绩录入\n");
    printf("|2.查询成绩\n");
    printf("|3.修改密码\n");
    printf("|4.导出成绩\n");
    printf("|5.录入评语\n");
    printf("|6.退出\n");
    printf("请输入相应的序号选择:");
    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6) {
        switch (i) {
        case 1:
            te_change_grade(id);break;
        case 2:
            check_grade(id);break;
        case 3:
            change_password(id);break;
        case 4:
            print_all(id);break;
        case 5:
            evaluate(id);break;
        case 6:
            exit(0);
        }
    } else print_te_menu(id);
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
            st_check_grade(id);break;
        case 2:
            change_password(id);break;
        case 3:
            exit(0);
        }
    } else print_st_menu(id);
}

void te_change_grade(int id) {
    clean();
    printf("成绩录入菜单\n");
    printf("||1.文件覆盖\n");
    printf("||2.单个修改\n");
    printf("||3.返回\n");
    printf("请输入相应的序号选择:");
    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3) {
        switch (i) {
        case 1:
            te_file_input(id);break;
        case 2:
            change_grade(id);break;
        case 3:
            print_te_menu(id);
        }
    } else te_change_grade(id);
}

// 单科文件覆盖
void te_file_input(int id) {
    FILE* fp = NULL;
    char filename[100];
    printf("请输入文件地址:");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) printf("文件打开出错!");
    else {
        while (!feof(fp)) {
            int H;
            double F;
            fscanf(fp, "%d %lf", &H, &F);
            Link Head = head->next;
            while (Head != NULL) {
                if (H == Head->student.id) break;
                Head = Head->next;
            }
            if (Head == NULL) continue;
            if (id == 1) Head->student.math1 = F;
            else if (id == 2) Head->student.math2 = F;
            else if (id == 3) Head->student.math3 = F;
            else if (id == 4) Head->student.pro = F;
        }
        fclose(fp);
        printf("数据加载成功!");
    }
    re_st5te();
    getch();
    print_te_menu(id);
}

// 老师链表初始化
void te_start() {
    FILE* fp = NULL;
    char filename[] = "te.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("老师数据加载出错!\n");
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
        printf("学生数据加载出错!\n");
        return;
    }
    while (!feof(fp)) {
        Stu data;
        fscanf(fp, st_start_format, st_start_data);
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

// 清屏
void clean() {
    system("cls");
}

// 进步空间
void asa(double s[], int* max, int* min) {
    double t = 0, t2 = 100;
    int i;
    for (i = 0;i < 4;i++) {
        if (s[i] > t) {
            t = s[i];
            (*max) = i;
        }
        if (s[i] < t2) {
            t2 = s[i];
            (*min) = i;
        }
    }
}

// 成绩对应绩点
double jidian(double i) {
    if (i < 60)return 0;
    else if (i >= 60 && i < 64) return 1.0;
    else if (i >= 64 && i < 67) return 1.3;
    else if (i >= 67 && i < 70) return 1.7;
    else if (i >= 70 && i < 74) return 2.0;
    else if (i >= 74 && i < 77) return 2.3;
    else if (i >= 77 && i < 80) return 2.7;
    else if (i >= 80 && i < 84) return 3.0;
    else if (i >= 84 && i < 87) return 3.3;
    else if (i >= 87 && i < 90) return 3.7;
    else return 4.0;
}

// 打印班级信息 21231223
void banji(int id) {
    char xueyuan[5][100] = { "计算机","电子","汽车","人工智能","软件" };
    printf("%s学院20%d级%d班%d号\n\n", xueyuan[id / 1000000 - 21], id / 10000 % 100, id / 100 % 100, id % 100);
}

// 打印 id 对应的信息
void st_check_grade(int id) {
    clean();
    char sss[4][100] = { "线性代数","微积分","离散数学","程序设计" };
    Link p = head;
    while (p != NULL) {
        if (id == p->student.id) {
            banji(id);
            printf("姓名:\t\t%s\n", p->student.name);
            printf("账号:\t\t%d\n", p->student.id);
            printf("性别:\t\t");
            if (p->student.sex)printf("男\n");
            else printf("女\n");
            printf("年龄:\t\t%d\n", p->student.age);
            printf("微积分:\t\t%.2lf (%.2lf)\n", p->student.math2, jidian(p->student.math2));
            printf("线性代数:\t%.2lf (%.2lf)\n", p->student.math1, jidian(p->student.math1));
            printf("离散数学:\t%.2lf (%.2lf)\n", p->student.math3, jidian(p->student.math3));
            printf("程序设计:\t%.2lf (%.2lf)\n", p->student.pro, jidian(p->student.pro));
            printf("竞赛绩点:\t%.2lf\n", p->student.score);
            double iii = jidian(p->student.math2) * math2iii + jidian(p->student.math1) * math1iii + jidian(p->student.math3) * math3iii + jidian(p->student.pro) * proiii;
            printf("平均绩点:\t%.2lf\n\n", iii / (math1iii + math2iii + math3iii + proiii) + p->student.score);
            int max, min;
            double s[4];
            s[0] = p->student.math1;
            s[1] = p->student.math2;
            s[2] = p->student.math3;
            s[3] = p->student.pro;
            asa(s, &max, &min);
            printf("优势科目:\t%s\n", sss[max]);
            printf("劣势科目:\t%s\n", sss[min]);
            printf("学科差距:\t%.2lf\n", s[max] - s[min]);
            printf("教师评语:\t%s", p->student.evaluation);
            break;
        }
        p = p->next;
    }
    getch();
    print_st_menu(id);
}

// 保存 
void re_st5te() {
    FILE* file;                            // 老师
    file = fopen("te.txt", "w");
    Link2 pp = head2;
    int i;
    for (i = 0;i < 4;i++) {
        fprintf(file, "%d\t%d", pp->id, pp->password);
        if (i != 3) fprintf(file, "\n");
        pp = pp->next;
    }
    fclose(file);
    FILE* file1;                           // 学生
    file1 = fopen("student.txt", "w");
    Link p = head->next;
    while (p != NULL) {
        fprintf(file1, st_re_format, st_re_data);
        if (p->next != NULL) fprintf(file1, "\n");
        p = p->next;
    }
    fclose(file1);
}

// 修改 id 对应的密码
void change_password(int id) {
    clean();
    int newpassword1, newpassword2;
    printf("请输入新的密码:");
    scanf("%d", &newpassword1);
    printf("请确认新的密码:");
    scanf("%d", &newpassword2);
    if (newpassword1 != newpassword2) {
        printf("两次密码不一致,请重新输入!");
        getch();
        change_password(id);
        return;
    } else {
        if (id == 1 || id == 2 || id == 3 || id == 4) {
            Link2 p = head2;
            for (;p != NULL;p = p->next) {
                while (id == p->id) {
                    p->password = newpassword1;
                    break;
                }
            }
        } else {
            Link p = head->next;
            for (;p != NULL;p = p->next) {
                while (id == p->student.id) {
                    p->student.password = newpassword1;
                    break;
                }
            }
        }
        re_st5te();
        printf("修改成功!");
        getch();
        if (id == 1 || id == 2 || id == 3 || id == 4) {
            print_te_menu(id);
        } else {
            print_st_menu(id);
        }
    }
}

// 文件录入
void op_file_input(int id) {
    FILE* fp = NULL;
    char filename[100];
    printf("请输入文件地址:");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) printf("文件打开出错!");
    else {
        while (!feof(fp)) {
            Stu data;
            fscanf(fp, file_input_format, file_input_data);
            data.password = data.id;
            data.score = 0;
            data.evaluation[0] = '#';
            data.evaluation[1] = '\0';
            Link qq = head;
            Link node;
            int flag = 1;
            for (;qq != NULL;qq = qq->next) if (data.id == qq->student.id) flag = 0;
            if (flag) {
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
                    head = node;
                    tmp = node;
                    tmp->next = NULL;
                } else {
                    tmp->next = node;
                    tmp = node;
                    tmp->next = NULL;
                }
            }
        }
        fclose(fp);
        printf("数据加载成功!");
    }
    getch();
    re_st5te();
    if (id == 0) print_op_menu(id);
    else print_te_menu(id);
}

// 单个录入
void op_one_input(int id) {
    clean();
    Stu Student;
    printf("请输入学生账号:");
    scanf("%d", &Student.id);
    Student.password = Student.id;
    Student.score = 0;
    Student.evaluation[0] = '#';
    Student.evaluation[1] = '\0';
    if (Z != 0) {
        Link nd;
        nd = (malloc)(sizeof(Node));
        nd = head;
        int W = 0;
        do {
            if (Student.id == nd->student.id) W++;
            nd = nd->next;
        } while (Student.id == nd->student.id);
        if (W == 1) {
            printf("该学生已经录入!\n");
            getch();
            op_input_grade(id);
        }
    }
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
    printf("录入成功!");
    re_st5te();
    getch();
    print_op_menu(id);
}

//录入竞赛加分绩点
void score_input(int id) {
    clean();
    printf("请输入竞赛学生的学号:");
    int H;
    scanf("%d", &H);
    Link Head = head->next;
    while (Head != NULL) {
        if (H == Head->student.id) break;
        Head = Head->next;
    }
    if (Head == NULL) {
        printf("该学生不存在!");
        getch();
        print_op_menu(id);
    }
    printf("请输入该学生的竞赛绩点:");
    double J;
    scanf("%lf", &J);
    Head->student.score = J;
    printf("录入成功!");
    re_st5te();
    getch();
    print_op_menu(id);
}

// 管理员录入成绩 文件录入或单个录入
void op_input_grade(int id) {
    clean();
    printf("录入方式菜单\n");
    printf("||1.文件录入\n");
    printf("||2.单个录入\n");
    printf("||3.返回\n");
    printf("请输入相应的序号选择:");
    int i;
    scanf("%d", &i);
    if (i == 1 || i == 2 || i == 3) {
        switch (i) {
        case 1:
            op_file_input(id);break;
        case 2:
            op_one_input(id);break;
        case 3:
            print_op_menu(id);break;
        }
    } else op_input_grade(id);
}

// 修改成绩子系统 
void change_grade_son(int K, int id) {
    printf("请输入你要修改学生的学号:");
    int H;
    scanf("%d", &H);
    Link Head = head->next;
    while (Head != NULL) {
        if (H == Head->student.id) break;
        Head = Head->next;
    }
    if (Head == NULL) {
        printf("该学生不存在!");
        getch();
        change_grade(id);
    }
    printf("请输入修改后的成绩:");
    double F;
    scanf("%lf", &F);
    if (K == 1) Head->student.math1 = F;
    else if (K == 2) Head->student.math2 = F;
    else if (K == 3) Head->student.math3 = F;
    else if (K == 4) Head->student.pro = F;
    printf("修改成功!");
}

// 修改成绩
void change_grade(int id) {
    clean();
    if (id == 0) {
        printf("学科目录\n");
        printf("||1.线性代数\n");
        printf("||2.微积分\n");
        printf("||3.离散数学\n");
        printf("||4.程序设计\n");
        printf("||5.返回\n");
        printf("请选择你要修改的学科:");
        int K;
        scanf("%d", &K);
        if (K == 1) change_grade_son(K, id);
        else if (K == 2) change_grade_son(K, id);
        else if (K == 3) change_grade_son(K, id);
        else if (K == 4) change_grade_son(K, id);
        else if (K == 5) print_op_menu(id);
        else change_grade(id);
    } else if (id == 1) change_grade_son(id, id);
    else if (id == 2) change_grade_son(id, id);
    else if (id == 3) change_grade_son(id, id);
    else if (id == 4) change_grade_son(id, id);
    re_st5te();
    getch();
    if (id == 0) print_op_menu(id);
    else print_te_menu(id);
}

// 打印成绩
void check_grade(int id) {
    clean();
    Link Head;
    Head = head->next;
    if (id == 0) {
        printf("姓名\t学号\t年龄\t性别\t线性代数\t微积分\t\t离散数学\t程序设计\t竞赛绩点\n");
        do {
            printf("%s\t%d\t%d\t", Head->student.name, Head->student.id, Head->student.age);
            if (Head->student.sex == 0) printf("女\t");
            else printf("男\t");
            printf("%.2lf\t\t", Head->student.math1);
            printf("%.2lf\t\t", Head->student.math2);
            printf("%.2lf\t\t", Head->student.math3);
            printf("%.2lf\t\t", Head->student.pro);
            printf("%.2lf\n", Head->student.score);
            Head = Head->next;
        } while (Head != NULL);
    } else {
        printf("姓名\t学号\t年龄\t性别\t");
        if (id == 1) printf("线性代数\n");
        else if (id == 2) printf("微积分\n");
        else if (id == 3) printf("离散数学\n");
        else if (id == 4) printf("程序设计\n");
        do {
            printf("%s\t%d\t%d\t", Head->student.name, Head->student.id, Head->student.age);
            if (!Head->student.sex) printf("女\t");
            else printf("男\t");
            if (id == 01) printf("%.2lf\n", Head->student.math1);
            else if (id == 02) printf("%.2lf\n", Head->student.math2);
            else if (id == 03) printf("%.2lf\n", Head->student.math3);
            else if (id == 04) printf("%.2lf\n", Head->student.pro);
            Head = Head->next;
        } while (Head != NULL);
    }
    getch();
    if (id == 0) print_op_menu(id);
    else print_te_menu(id);
}

// 录入评语 
void evaluate(int id) {
    clean();
    printf("请输入学生id:");
    int sid;
    scanf("%d", &sid);
    int flag = 1;
    Link p;
    for (p = head->next;p != NULL;p = p->next) {
        if (sid == p->student.id) {
            flag = 0;
            getchar();
            printf("请输入学生评语:");
            char str[500];
            scanf("%[^\n]", str);
            strcat(p->student.evaluation, str);
            re_st5te();
            printf("录入成功!");
            getch();
            break;
        }
    }
    if (flag) {
        printf("id不存在!");
        getch();
        print_te_menu(id);
    }
    print_te_menu(id);
}

// 重置密码
void reset_password(int id) {
    clean();
    Link p1 = head->next;
    Link2 p2 = head2;
    printf("密码设置菜单\n");
    printf("||1.重置单个密码\n");
    printf("||2.重置所有密码\n");
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
                printf("修改成功,重置密码与id相同!");
                getch();
                break;
            }
            p2 = p2->next;
        }
        while (p1 != NULL) {
            if (p1->student.id == i) {
                p1->student.password = p1->student.id;
                printf("修改成功,重置密码与id相同!");
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
    } else if (flag == 3) print_op_menu(id);
    else reset_password(id);
    return;
}

// 检查账号密码 默认密码与账号相同
int check(int id, int password) {
    if (id == 00 && password == 00) return 1;
    Link2 p2 = head2;
    while (NULL != p2) {
        if (p2->id == id && p2->password == password) return 2;
        p2 = p2->next;
    }
    Link p = head->next;
    while (NULL != p) {
        if (p->student.id == id && p->student.password == password) return 3;
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
        printf("账号或密码错误,请重新输入!\n");
        return signin(id);
    }
}

// 导出成绩 
void print_all(int id) {
    clean();
    bubbleSort(id);
    FILE* file;
    char filename[100];
    printf("请输入导出文件名称(注意若存在同名文件则会被覆盖):");
    scanf("%s", filename);
    strcat(filename, ".txt");
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("失败");
        return;
    }
    Link p = head->next;
    if (id == 0)  fprintf(file, "姓名\t\t学号\t\t性别\t\t年龄\t\t线性代数\t\t微积分\t\t离散数学\t\t程序设计\t\t竞赛绩点");
    else if (id == 1)  fprintf(file, "姓名\t\t\t学号\t\t性别\t\t年龄\t\t线性代数");
    else if (id == 2)  fprintf(file, "姓名\t\t\t学号\t\t性别\t\t年龄\t\t微积分");
    else if (id == 3)  fprintf(file, "姓名\t\t\t学号\t\t性别\t\t年龄\t\t离散数学");
    else if (id == 4)  fprintf(file, "姓名\t\t\t学号\t\t性别\t\t年龄\t\t程序设计");
    while (p != NULL) {
        if (id == 0) fprintf(file, file_output_format, file_output_data);
        else if (id == 1) fprintf(file, "\n%s\t\t\t%d\t\t%d\t\t%d\t\t%.2lf", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.math1);
        else if (id == 2) fprintf(file, "\n%s\t\t\t%d\t\t%d\t\t%d\t\t%.2lf", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.math2);
        else if (id == 3) fprintf(file, "\n%s\t\t\t%d\t\t%d\t\t%d\t\t%.2lf", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.math3);
        else if (id == 4) fprintf(file, "\n%s\t\t\t%d\t\t%d\t\t%d\t\t%.2lf", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.pro);
        p = p->next;
    }
    fclose(file);
    printf("导出成功!");
    getch();
    if (id == 0) print_op_menu(id);
    else print_te_menu(id);
}

// 链表排序
void bubbleSort(int id) {
    double x1, x2;
    Link pre, cur, next, end, temp;
    end = NULL;
    while (head->next != end) {
        for (pre = head, cur = pre->next, next = cur->next;next != end;pre = pre->next, cur = cur->next, next = next->next) {
            if (!id) {
                x1 = cur->student.pro + cur->student.math3 + cur->student.math2 + cur->student.math1;
                x2 = next->student.pro + next->student.math3 + next->student.math2 + next->student.math1;
            } else if (id == 1) {
                x1 = cur->student.math1;x2 = next->student.math1;
            } else if (id == 2) {
                x1 = cur->student.math2;x2 = next->student.math2;
            } else if (id == 3) {
                x1 = cur->student.math3;x2 = next->student.math3;
            } else if (id == 4) {
                x1 = cur->student.pro;x2 = next->student.pro;
            }
            if (x1 < x2) {
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
}

// 删除学生信息
void delet_student(int id) {
    clean();
    printf("请输入您要删除的学生的学号:");
    Link NOD;
    NOD = (malloc)(sizeof(Node));
    NOD = head;
    int D;
    scanf("%d", &D);
    while (NOD->next != NULL && NOD->next->student.id != D) {
        NOD = NOD->next;
    }
    if (NOD->next == NULL) printf("该学生不存在!");
    else {
        NOD->next = NOD->next->next;
        printf("删除成功!");
    }
    re_st5te();
    getch();
    if (id == 0) print_op_menu(id);
    else print_te_menu(id);
}

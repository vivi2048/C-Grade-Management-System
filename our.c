#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void clean();                                             // ����
void st_check_grade(int id);                              // ��ӡ id ��Ӧ����Ϣ
void change_password(int id);                             // �޸� id ��Ӧ������
void file_input(int id);                                  // �ļ�¼��
void one_input(int id);                                   // ����¼��
void input_grade(int id);                                 // ¼��ɼ�
void change_grade(int id);                                // �޸ĳɼ�
void check_grade(int id);                                 // ��ӡ�ɼ�
void reset_password(int id);                              // ��������
int signin(int* id);                                      // �û���¼
int check(int id, int password);                          // ����˺�����
void print_st_menu(int id);                               // ��ӡѧ���˵�
void print_te_menu(int id);                               // ��ӡ��ʦ�˵�
void print_op_menu(int id);                               // ��ӡ����Ա�˵�  opid:0
void score_input(int id);								  // ¼�뾺���ӷּ���  
void print_all(int id);									  // ������ǰ��������ѧ���ɼ� 
void bubbleSort_math1();                                  // ����ð������

// ѧ���ṹ��
typedef struct student {
    char name[50];                  // ��  ��
    int id;                         // ��  ��
    int password;                   // ��  ��
    int sex;                        // ��  ��  ��:1 Ů:0
    int age;                        // ��  ��
    double math1;                   // ���Դ���   teid:1
    double math2;                   // ΢����     teid:2
    double math3;                   // ��ɢ��ѧ   teid:3
    double pro;                     // �������   teid:4
    double score;					// �����ӷּ���
} Stu;

// ѧ������
typedef struct Node {
    Stu student;
    struct Node* next;
} Node;

// ��ʦ����
typedef struct Node2 {
    int id;
    int password;
    struct Node2* next;
} Node2;

// ȫ�ֱ���
typedef struct Node* Link;
Link head = NULL;
typedef struct Node2* Link2;
Link2 head2 = NULL;
Link tmp;
int Z = 0;

// ��ʦ�����ʼ��
void te_start() {
    FILE* fp = NULL;
    char filename[] = "te.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("��ʦ���ݼ��س���\n");
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

// ѧ�������ʼ��
void st_start() {
    FILE* fp = NULL;
    char filename[] = "student.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("ѧ�����ݼ��س���\n");
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

// ������ ѡ��˵�
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

// ����
void clean() {
    printf("\033[2J\033[H");
}

// ��ӡ id ��Ӧ����Ϣ
void st_check_grade(int id) {
    clean();
    printf("id:%d\n", id);
    Link p = head;
    while (p != NULL) {
        if (id == p->student.id) {
            printf("����:\t\t%s\n", p->student.name);
            printf("�˺�:\t\t%d\n", p->student.id);
            printf("�Ա�:\t\t%d\n", p->student.sex);
            printf("����:\t\t%d\n", p->student.age);
            printf("���Դ����ɼ�:\t%.2lf\n", p->student.math1);
            printf("΢���ֳɼ�:\t%.2lf\n", p->student.math2);
            printf("��ɢ��ѧ�ɼ�:\t%.2lf\n", p->student.math3);
            printf("������Ƴɼ�:\t%.2lf\n", p->student.pro);
            printf("�����ӷּ���:\t%.4lf\n", p->student.score);
            break;
        }
        p = p->next;
    }
    getch();
    print_st_menu(id);
}

// ����
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

// �޸� id ��Ӧ������
void change_password(int id) {
    clean();
    printf("id:%d\n", id);
    int newpassword1, newpassword2;
    printf("�������µ�����:");
    scanf("%d", &newpassword1);
    printf("��ȷ���µ�����:");
    scanf("%d", &newpassword2);
    if (newpassword1 != newpassword2) {
        printf("�������벻һ�£�����������!");
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
    printf("�޸ĳɹ���\n");
    getch();
    if (id == 1 || id == 2 || id == 3 || id == 4) {
        print_te_menu(id);
    } else {
        print_st_menu(id);
    }
}

// ��ӡѧ���˵�
void print_st_menu(int id) {
    clean();
    printf("ѧ���˵�\n");
    printf("|1.��ѯ�ɼ�\n");
    printf("|2.�޸�����\n");
    printf("|3.�˳�\n");
    printf("��������Ӧ�����ѡ��:");
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

// �ļ�¼��
void file_input(int id) {
    FILE* fp = NULL;
    char filename[100];
    printf("��������Ҫ���ص��ļ���ַ��");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("�ļ��򿪳���\n");
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
    printf("���ݼ��سɹ�\n");
    getch();
    print_te_menu(id);
}

// ����¼��
void one_input(int id) {
    clean();
    if (id == 0) {
        printf("�������Աģʽ\n");
    }
    Stu Student;
    printf("������ѧ���˺�:");
    scanf("%d", &Student.id);
    printf("������ѧ������:");
    scanf("%s", Student.name);
    printf("������ѧ���Ա�:");
    scanf("%d", &Student.sex);
    printf("������ѧ������:");
    scanf("%d", &Student.age);
    printf("���������Դ����ɼ�:");
    scanf("%lf", &Student.math1);
    printf("������΢���ֳɼ�:");
    scanf("%lf", &Student.math2);
    printf("��������ɢ��ѧ�ɼ�:");
    scanf("%lf", &Student.math3);
    printf("�����������Ƴɼ�:");
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
    printf("¼��ɹ���\n");
    getch();
    print_te_menu(id);
}

//¼�뾺���ӷּ���
void score_input(int id) {
    if (id == 0) {
        printf("������þ���ѧ����ѧ��\n");
        int H;
        scanf("%d", &H);
        Link Head;
        Head = head;
        while (Head->student.id != H) {
            Head = Head->next;
        }
        printf("�������ѧ����������\n");
        double J;
        scanf("%lf", &J);
        Head->student.score = J;
    } else if (id == 01 || id == 02 || id == 03 || id == 04) {
        printf("����Ȩ�޲���");
    }
    getch();
    print_te_menu(id);
}

// ¼��ɼ� �ļ�¼��򵥸�¼��
void input_grade(int id) {
    clean();
    printf("¼�뷽ʽ\n");
    printf("||1.�ļ�¼��\n");
    printf("||2.����¼��\n");
    printf("||3.����\n");
    printf("��������Ӧ�����ѡ��:");
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

//�޸ĳɼ���ϵͳ 
void change_grade_son(int K) {
    printf("���������޸ĵ�ѧ����ѧ��\n");
    int H;
    scanf("%d", &H);
    Link Head;
    Head = head;
    while (Head->student.id != H) {
        Head = Head->next;
    }
    printf("�������ѧ���޸ĺ�ĳɼ�\n");
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

// �޸ĳɼ�
void change_grade(int id) {
    int K;
    if (id == 00) {
        printf("�������Աģʽ\n");
        printf("��ѡ����Ҫ�޸ĵ�ѧ�ƣ�\n");
        printf("1.���Դ���\n");
        printf("2.΢����\n");
        printf("3.��ɢ��ѧ\n");
        printf("4.�������\n");
        scanf("%d", &K);
        change_grade_son(K);
    }
    if (id == 01) {
        K = 1;
        printf("���ѽ������Դ�����ʦ�༭ģʽ");
        change_grade_son(K);
    }
    if (id == 02) {
        K = 2;
        printf("���ѽ���΢������ʦ�༭ģʽ");
        change_grade_son(K);
    }
    if (id == 03) {
        K = 3;
        printf("���ѽ�����ɢ��ѧ��ʦ�༭ģʽ");
        change_grade_son(K);
    }
    if (id == 04) {
        K = 4;
        printf("���ѽ�����������ʦ�༭ģʽ");
        change_grade_son(K);
    }
    getch();
    print_te_menu(id);
}

// ��ӡ�ɼ�
void check_grade(int id) {
    Link Head;
    Head = head->next;
    if (id == 00) {
        printf("�������Աģʽ\n");
        printf("ѧ������\t  ѧ��ѧ��\t  ѧ������\t  ѧ���Ա�\t  ���Դ����ɼ� \t\t  ΢���ֳɼ� \t\t  ��ɢ��ѧ�ɼ� \t\t  ������Ƴɼ� \t\t  ��������\n");
        do {
            printf("   %s\t\t  %d\t\t  %d\t\t", Head->student.name, Head->student.id, Head->student.age);
            if (Head->student.sex == 0) {
                printf("  Ů\t\t");
            } else if (Head->student.sex) {
                printf("  ��\t\t");
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
        printf("������ʦģʽ\n");
        printf("ѧ������\t  ѧ��ѧ��\t  ѧ������\t  ѧ���Ա�\t  ");
        if (id == 01) {
            printf("���Դ����ɼ� \t\t  ��������\n");
        } else if (id == 02) {
            printf("΢���ֳɼ� \t\t  ��������\n");
        } else if (id == 03) {
            printf("��ɢ��ѧ�ɼ� \t\t  ��������\n");
        } else if (id == 04) {
            printf("������Ƴɼ� \t\t  ��������\n");
        }
        do {
            printf("   %s\t\t  %d\t\t  %d\t\t", Head->student.name, Head->student.id, Head->student.age);
            if (!Head->student.sex) {
                printf("  Ů\t\t");
            } else {
                printf("  ��\t\t");
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

// ��ӡ��ʦ�˵�
void print_te_menu(int id) {
    clean();
    printf("��ʦ�˵�\n");
    printf("|1.¼��ɼ�\n");
    printf("|2.�޸ĳɼ�\n");
    printf("|3.��ѯ�ɼ�\n");
    printf("|4.�޸�����\n");
    printf("|5.��ӡ�ɼ���\n");
    printf("|6.�˳�\n");
    printf("��������Ӧ�����ѡ��:");
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

// ��ӡ����Ա�˵�
void print_op_menu(int id) {
    clean();
    printf("����Ա�˵�\n");
    printf("|1.¼��ɼ�\n");
    printf("|2.�޸ĳɼ�\n");
    printf("|3.��ѯ�ɼ�\n");
    printf("|4.��������\n");
    printf("|5.�����ɼ���\n");
    printf("|6.�˳�\n");
    printf("��������Ӧ�����ѡ��:");
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

// ��������
void reset_password(int id) {
    clean();
    Link p1 = head->next;
    Link2 p2 = head2;
    printf("��������\n");
    printf("||1.������ʦ��ѧ������\n");
    printf("||2.��ʼ����������\n");
    printf("||3.����\n");
    printf("��������Ӧ�����ѡ��:");
    int flag;
    scanf("%d", &flag);
    if (flag == 1) {
        printf("������Ҫ���������id:");
        int i;
        scanf("%d", &i);
        while (p2 != NULL) {
            if (p2->id == i) {
                p2->password = p2->id;
                printf("�޸ĳɹ�(����������id��ͬ)");
                getch();
                break;
            }
            p2 = p2->next;
        }
        while (p1 != NULL) {
            if (p1->student.id == i) {
                p2->password = p2->id;
                printf("�޸ĳɹ�(����������id��ͬ)");
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
        printf("��ʼ�������������!");
        getch();
        print_op_menu(id);
    } else if (flag == 3) {
        print_op_menu(id);
    } else {
        reset_password(id);
    }
    return;
}

// ����˺����� Ĭ���������˺���ͬ
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

// �û���¼
int signin(int* id) {
    int iid;
    printf("�������˺�:");
    scanf("%d", &iid);
    int password;
    printf("����������:");
    scanf("%d", &password);
    int flag = check(iid, password);
    if (flag) {
        (*id) = iid;
        return flag;
    } else {
        clean();
        printf("�˺Ż��������\n");
        return signin(id);
    }
}

//������ǰ���гɼ� 
void print_all(int id) {
    bubbleSort_math1();
    FILE* file;
    char filename[100];
    printf("��������Ҫ�����ļ�����(������ͬ���ļ���ᱻ����!):");
    scanf("%s", filename);
    strcat(filename, ".txt");
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("ʧ��");
        return;
    }
    Link p = head->next;
    if (!id) {
        fprintf(file, "����\tѧ��\t�Ա�\t����\t���Դ���\t΢����\t��ɢ��ѧ\t�������\t��������\n");
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
    printf("�ÿ�Ŀ�ɼ�������:\n");
    for (p = head->next ,i = 1;p!= NULL;p = p->next, i++){
        printf("%d %s %.2lf\n", i, p->student.name, p->student.math1);
    }
}
void evaluate(char ){
	
}


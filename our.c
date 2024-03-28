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

void clean();                                             // ����
void st_check_grade(int id);                              // ��ӡ id��Ӧ����Ϣ
void change_password(int id);                             // �޸� id��Ӧ������
void op_file_input(int id);                               // op�ļ�¼��
void op_one_input(int id);                                // op����¼��
void te_file_input(int id);                               // te�ļ�¼��
void op_input_grade(int id);                              // ¼��ɼ�
void change_grade(int id);                                // �޸ĳɼ�
void check_grade(int id);                                 // ��ӡ�ɼ�
void reset_password(int id);                              // ��������
void print_st_menu(int id);                               // ��ӡѧ���˵�
void print_te_menu(int id);                               // ��ӡ��ʦ�˵�
void print_op_menu(int id);                               // ��ӡ����Ա�˵�  opid:0
void score_input(int id);								  // ¼�뾺��  
void print_all(int id);					     			  // �����ɼ� 
void bubbleSort(int id);                                  // ��������
void asa(double s[], int* max, int* min);                 // �����ռ�
void te_start();                                          // ��ʦ�����ʼ��
void st_start();                                          // ѧ�������ʼ��
void re_st5te();                                          // ����
void change_grade_son(int K, int id);                     // �޸ĳɼ���ϵͳ
void evaluate(int id);                                    // ¼������
void delet_student(int id); 							  // ɾ��ѧ��
void te_change_grade(int id);                             // ��ʦ�ɼ�¼��
void banji(int id);                                       // ��ӡ�༶��Ϣ
int signin(int* id);                                      // �û���¼
int check(int id, int password);                          // ����˺�����
double jidian(double i);                                  // �ɼ���Ӧ����

// ѧ���ṹ��
typedef struct student {
    char name[50];                                        // ����
    int id;                                               // �˺�
    int password;                                         // ����
    int sex;                                              // �Ա�         ��:1 Ů:0
    int age;                                              // ����
    double math1;                                         // ���Դ���     teid:1 3.5
    double math2;                                         // ΢����       teid:2 4.0
    double math3;                                         // ��ɢ��ѧ     teid:3 3.0
    double pro;                                           // �������     teid:4 3.5
    double score;				                          // ��������
    char evaluation[500];                                 // ���� 
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

// ȫ�ֱ��� ѧ��
typedef struct Node* Link;
Link head = NULL, tmp;
int Z = 0;

// ȫ�ֱ��� ��ʦ
typedef struct Node2* Link2;
Link2 head2 = NULL;

// ������ ѡ��˵�
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

// ��ӡ����Ա�˵�
void print_op_menu(int id) {
    clean();
    printf("����Ա�˵�\n");
    printf("|1.¼��ɼ�\n");
    printf("|2.�޸ĳɼ�\n");
    printf("|3.��ѯ�ɼ�\n");
    printf("|4.��������\n");
    printf("|5.�����ɼ�\n");
    printf("|6.¼�뾺��\n");
    printf("|7.ɾ��ѧ��\n");
    printf("|8.�˳�\n");
    printf("��������Ӧ�����ѡ��:");
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

// ��ӡ��ʦ�˵�
void print_te_menu(int id) {
    clean();
    printf("��ʦ�˵�\n");
    printf("|1.�ɼ�¼��\n");
    printf("|2.��ѯ�ɼ�\n");
    printf("|3.�޸�����\n");
    printf("|4.�����ɼ�\n");
    printf("|5.¼������\n");
    printf("|6.�˳�\n");
    printf("��������Ӧ�����ѡ��:");
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
    printf("�ɼ�¼��˵�\n");
    printf("||1.�ļ�����\n");
    printf("||2.�����޸�\n");
    printf("||3.����\n");
    printf("��������Ӧ�����ѡ��:");
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

// �����ļ�����
void te_file_input(int id) {
    FILE* fp = NULL;
    char filename[100];
    printf("�������ļ���ַ:");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) printf("�ļ��򿪳���!");
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
        printf("���ݼ��سɹ�!");
    }
    re_st5te();
    getch();
    print_te_menu(id);
}

// ��ʦ�����ʼ��
void te_start() {
    FILE* fp = NULL;
    char filename[] = "te.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("��ʦ���ݼ��س���!\n");
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
        printf("ѧ�����ݼ��س���!\n");
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

// ����
void clean() {
    system("cls");
}

// �����ռ�
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

// �ɼ���Ӧ����
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

// ��ӡ�༶��Ϣ 21231223
void banji(int id) {
    char xueyuan[5][100] = { "�����","����","����","�˹�����","���" };
    printf("%sѧԺ20%d��%d��%d��\n\n", xueyuan[id / 1000000 - 21], id / 10000 % 100, id / 100 % 100, id % 100);
}

// ��ӡ id ��Ӧ����Ϣ
void st_check_grade(int id) {
    clean();
    char sss[4][100] = { "���Դ���","΢����","��ɢ��ѧ","�������" };
    Link p = head;
    while (p != NULL) {
        if (id == p->student.id) {
            banji(id);
            printf("����:\t\t%s\n", p->student.name);
            printf("�˺�:\t\t%d\n", p->student.id);
            printf("�Ա�:\t\t");
            if (p->student.sex)printf("��\n");
            else printf("Ů\n");
            printf("����:\t\t%d\n", p->student.age);
            printf("΢����:\t\t%.2lf (%.2lf)\n", p->student.math2, jidian(p->student.math2));
            printf("���Դ���:\t%.2lf (%.2lf)\n", p->student.math1, jidian(p->student.math1));
            printf("��ɢ��ѧ:\t%.2lf (%.2lf)\n", p->student.math3, jidian(p->student.math3));
            printf("�������:\t%.2lf (%.2lf)\n", p->student.pro, jidian(p->student.pro));
            printf("��������:\t%.2lf\n", p->student.score);
            double iii = jidian(p->student.math2) * math2iii + jidian(p->student.math1) * math1iii + jidian(p->student.math3) * math3iii + jidian(p->student.pro) * proiii;
            printf("ƽ������:\t%.2lf\n\n", iii / (math1iii + math2iii + math3iii + proiii) + p->student.score);
            int max, min;
            double s[4];
            s[0] = p->student.math1;
            s[1] = p->student.math2;
            s[2] = p->student.math3;
            s[3] = p->student.pro;
            asa(s, &max, &min);
            printf("���ƿ�Ŀ:\t%s\n", sss[max]);
            printf("���ƿ�Ŀ:\t%s\n", sss[min]);
            printf("ѧ�Ʋ��:\t%.2lf\n", s[max] - s[min]);
            printf("��ʦ����:\t%s", p->student.evaluation);
            break;
        }
        p = p->next;
    }
    getch();
    print_st_menu(id);
}

// ���� 
void re_st5te() {
    FILE* file;                            // ��ʦ
    file = fopen("te.txt", "w");
    Link2 pp = head2;
    int i;
    for (i = 0;i < 4;i++) {
        fprintf(file, "%d\t%d", pp->id, pp->password);
        if (i != 3) fprintf(file, "\n");
        pp = pp->next;
    }
    fclose(file);
    FILE* file1;                           // ѧ��
    file1 = fopen("student.txt", "w");
    Link p = head->next;
    while (p != NULL) {
        fprintf(file1, st_re_format, st_re_data);
        if (p->next != NULL) fprintf(file1, "\n");
        p = p->next;
    }
    fclose(file1);
}

// �޸� id ��Ӧ������
void change_password(int id) {
    clean();
    int newpassword1, newpassword2;
    printf("�������µ�����:");
    scanf("%d", &newpassword1);
    printf("��ȷ���µ�����:");
    scanf("%d", &newpassword2);
    if (newpassword1 != newpassword2) {
        printf("�������벻һ��,����������!");
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
        printf("�޸ĳɹ�!");
        getch();
        if (id == 1 || id == 2 || id == 3 || id == 4) {
            print_te_menu(id);
        } else {
            print_st_menu(id);
        }
    }
}

// �ļ�¼��
void op_file_input(int id) {
    FILE* fp = NULL;
    char filename[100];
    printf("�������ļ���ַ:");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) printf("�ļ��򿪳���!");
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
        printf("���ݼ��سɹ�!");
    }
    getch();
    re_st5te();
    if (id == 0) print_op_menu(id);
    else print_te_menu(id);
}

// ����¼��
void op_one_input(int id) {
    clean();
    Stu Student;
    printf("������ѧ���˺�:");
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
            printf("��ѧ���Ѿ�¼��!\n");
            getch();
            op_input_grade(id);
        }
    }
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
    printf("¼��ɹ�!");
    re_st5te();
    getch();
    print_op_menu(id);
}

//¼�뾺���ӷּ���
void score_input(int id) {
    clean();
    printf("�����뾺��ѧ����ѧ��:");
    int H;
    scanf("%d", &H);
    Link Head = head->next;
    while (Head != NULL) {
        if (H == Head->student.id) break;
        Head = Head->next;
    }
    if (Head == NULL) {
        printf("��ѧ��������!");
        getch();
        print_op_menu(id);
    }
    printf("�������ѧ���ľ�������:");
    double J;
    scanf("%lf", &J);
    Head->student.score = J;
    printf("¼��ɹ�!");
    re_st5te();
    getch();
    print_op_menu(id);
}

// ����Ա¼��ɼ� �ļ�¼��򵥸�¼��
void op_input_grade(int id) {
    clean();
    printf("¼�뷽ʽ�˵�\n");
    printf("||1.�ļ�¼��\n");
    printf("||2.����¼��\n");
    printf("||3.����\n");
    printf("��������Ӧ�����ѡ��:");
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

// �޸ĳɼ���ϵͳ 
void change_grade_son(int K, int id) {
    printf("��������Ҫ�޸�ѧ����ѧ��:");
    int H;
    scanf("%d", &H);
    Link Head = head->next;
    while (Head != NULL) {
        if (H == Head->student.id) break;
        Head = Head->next;
    }
    if (Head == NULL) {
        printf("��ѧ��������!");
        getch();
        change_grade(id);
    }
    printf("�������޸ĺ�ĳɼ�:");
    double F;
    scanf("%lf", &F);
    if (K == 1) Head->student.math1 = F;
    else if (K == 2) Head->student.math2 = F;
    else if (K == 3) Head->student.math3 = F;
    else if (K == 4) Head->student.pro = F;
    printf("�޸ĳɹ�!");
}

// �޸ĳɼ�
void change_grade(int id) {
    clean();
    if (id == 0) {
        printf("ѧ��Ŀ¼\n");
        printf("||1.���Դ���\n");
        printf("||2.΢����\n");
        printf("||3.��ɢ��ѧ\n");
        printf("||4.�������\n");
        printf("||5.����\n");
        printf("��ѡ����Ҫ�޸ĵ�ѧ��:");
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

// ��ӡ�ɼ�
void check_grade(int id) {
    clean();
    Link Head;
    Head = head->next;
    if (id == 0) {
        printf("����\tѧ��\t����\t�Ա�\t���Դ���\t΢����\t\t��ɢ��ѧ\t�������\t��������\n");
        do {
            printf("%s\t%d\t%d\t", Head->student.name, Head->student.id, Head->student.age);
            if (Head->student.sex == 0) printf("Ů\t");
            else printf("��\t");
            printf("%.2lf\t\t", Head->student.math1);
            printf("%.2lf\t\t", Head->student.math2);
            printf("%.2lf\t\t", Head->student.math3);
            printf("%.2lf\t\t", Head->student.pro);
            printf("%.2lf\n", Head->student.score);
            Head = Head->next;
        } while (Head != NULL);
    } else {
        printf("����\tѧ��\t����\t�Ա�\t");
        if (id == 1) printf("���Դ���\n");
        else if (id == 2) printf("΢����\n");
        else if (id == 3) printf("��ɢ��ѧ\n");
        else if (id == 4) printf("�������\n");
        do {
            printf("%s\t%d\t%d\t", Head->student.name, Head->student.id, Head->student.age);
            if (!Head->student.sex) printf("Ů\t");
            else printf("��\t");
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

// ¼������ 
void evaluate(int id) {
    clean();
    printf("������ѧ��id:");
    int sid;
    scanf("%d", &sid);
    int flag = 1;
    Link p;
    for (p = head->next;p != NULL;p = p->next) {
        if (sid == p->student.id) {
            flag = 0;
            getchar();
            printf("������ѧ������:");
            char str[500];
            scanf("%[^\n]", str);
            strcat(p->student.evaluation, str);
            re_st5te();
            printf("¼��ɹ�!");
            getch();
            break;
        }
    }
    if (flag) {
        printf("id������!");
        getch();
        print_te_menu(id);
    }
    print_te_menu(id);
}

// ��������
void reset_password(int id) {
    clean();
    Link p1 = head->next;
    Link2 p2 = head2;
    printf("�������ò˵�\n");
    printf("||1.���õ�������\n");
    printf("||2.������������\n");
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
                printf("�޸ĳɹ�,����������id��ͬ!");
                getch();
                break;
            }
            p2 = p2->next;
        }
        while (p1 != NULL) {
            if (p1->student.id == i) {
                p1->student.password = p1->student.id;
                printf("�޸ĳɹ�,����������id��ͬ!");
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
    } else if (flag == 3) print_op_menu(id);
    else reset_password(id);
    return;
}

// ����˺����� Ĭ���������˺���ͬ
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
        printf("�˺Ż��������,����������!\n");
        return signin(id);
    }
}

// �����ɼ� 
void print_all(int id) {
    clean();
    bubbleSort(id);
    FILE* file;
    char filename[100];
    printf("�����뵼���ļ�����(ע��������ͬ���ļ���ᱻ����):");
    scanf("%s", filename);
    strcat(filename, ".txt");
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("ʧ��");
        return;
    }
    Link p = head->next;
    if (id == 0)  fprintf(file, "����\t\tѧ��\t\t�Ա�\t\t����\t\t���Դ���\t\t΢����\t\t��ɢ��ѧ\t\t�������\t\t��������");
    else if (id == 1)  fprintf(file, "����\t\t\tѧ��\t\t�Ա�\t\t����\t\t���Դ���");
    else if (id == 2)  fprintf(file, "����\t\t\tѧ��\t\t�Ա�\t\t����\t\t΢����");
    else if (id == 3)  fprintf(file, "����\t\t\tѧ��\t\t�Ա�\t\t����\t\t��ɢ��ѧ");
    else if (id == 4)  fprintf(file, "����\t\t\tѧ��\t\t�Ա�\t\t����\t\t�������");
    while (p != NULL) {
        if (id == 0) fprintf(file, file_output_format, file_output_data);
        else if (id == 1) fprintf(file, "\n%s\t\t\t%d\t\t%d\t\t%d\t\t%.2lf", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.math1);
        else if (id == 2) fprintf(file, "\n%s\t\t\t%d\t\t%d\t\t%d\t\t%.2lf", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.math2);
        else if (id == 3) fprintf(file, "\n%s\t\t\t%d\t\t%d\t\t%d\t\t%.2lf", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.math3);
        else if (id == 4) fprintf(file, "\n%s\t\t\t%d\t\t%d\t\t%d\t\t%.2lf", p->student.name, p->student.id, p->student.sex, p->student.age, p->student.pro);
        p = p->next;
    }
    fclose(file);
    printf("�����ɹ�!");
    getch();
    if (id == 0) print_op_menu(id);
    else print_te_menu(id);
}

// ��������
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

// ɾ��ѧ����Ϣ
void delet_student(int id) {
    clean();
    printf("��������Ҫɾ����ѧ����ѧ��:");
    Link NOD;
    NOD = (malloc)(sizeof(Node));
    NOD = head;
    int D;
    scanf("%d", &D);
    while (NOD->next != NULL && NOD->next->student.id != D) {
        NOD = NOD->next;
    }
    if (NOD->next == NULL) printf("��ѧ��������!");
    else {
        NOD->next = NOD->next->next;
        printf("ɾ���ɹ�!");
    }
    re_st5te();
    getch();
    if (id == 0) print_op_menu(id);
    else print_te_menu(id);
}

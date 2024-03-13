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
void reset_password();                                    // ��������
int signin(int* id);                                      // �û���¼
int check(int id, int password);                          // ����˺�����
void print_st_menu(int id);                               // ��ӡѧ���˵�
void print_te_menu(int id);                               // ��ӡ��ʦ�˵�
void print_op_menu(int id);                               // ��ӡ����Ա�˵�  opid:00

// ѧ���ṹ��
typedef struct student {
    char name[50];                  // ��  ��
    int id;                         // ��  ��
    int password;                   // ��  ��
    int sex;                        // ��  ��  ��:1 Ů:0
    int age;                        // ��  ��
    double math1;                   // ���Դ���   teid:01
    double math2;                   // ΢����     teid:02
    double math3;                   // ��ɢ��ѧ   teid:03
    double pro;                     // �������   teid:04
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

// ȫ�ֱ��� ����ͷ
typedef struct Node* Link;
Link head = NULL;
typedef struct Node2* Link2;
Link2 head2 = NULL;
Link tmp;
int Z=0;
// ������ ѡ��˵�
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

// ����
void clean() {
    printf("\033[2J\033[H");
}

// ��ӡ id ��Ӧ����Ϣ
void st_check_grade(int id) {
    clean();
    printf("id:%d\n", id);
    Link p = head;
    for (;p->next == NULL;p = p->next) {
        if (id == p->student.id) {
            printf("����:%s\n", p->student.name);
            printf("�˺�:%d\n", p->student.id);
            printf("�Ա�:%d\n", p->student.sex);
            printf("����:%d\n", p->student.age);
            printf("���Դ����ɼ�:%lf\n", p->student.math1);
            printf("΢���ֳɼ�:%lf\n", p->student.math2);
            printf("��ɢ��ѧ�ɼ�:%lf\n", p->student.math3);
            printf("������Ƴɼ�:%lf\n", p->student.pro);
            getch();
            print_st_menu(id);
        }
    }
}

// �޸� id ��Ӧ������
void change_password(int id) {
    clean();
    printf("id:%d\n", id);
    int newpassword1, newpassword2;
    Link p = head;
    printf("�������µ�����:");
    scanf("%d", &newpassword1);
    printf("��ȷ���µ�����:");
    scanf("%d", &newpassword2);
    if (newpassword1 != newpassword2) {
        printf("�������벻һ�£�����������!");
        getch();
        change_password(id);
    } else {
        for (;p->next == NULL;p = p->next) {
            while (id == p->student.id) {
                p->student.password = newpassword1;
                printf("�޸ĳɹ���\n");
                getch();
                print_st_menu(id);
            }
        }
    }
}

// ��ӡѧ���˵�
void print_st_menu(int id) {
    clean();

    printf("ѧ���˵�\n");
    printf("|1.��ѯ�ɼ�\n");
    printf("|2.�޸�����\n");
    printf("|3.����\n");
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
            main();
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
    printf("���ݼ��سɹ�\n");
    getch();
    print_te_menu(id);
}

// ����¼��
void one_input(int id) {
    clean();
    if (id == 00) {
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
    printf("¼��ɹ���\n");
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

// �޸ĳɼ�
void change_grade(int id) {

    if (id == 00) {
        int K;
        int H;
        printf("�������Աģʽ\n");
        printf("��ѡ����Ҫ�޸ĵ�ѧ�ƣ�\n");
        printf("1.���Դ���\n");
        printf("2.΢����\n");
        printf("3.��ɢ��ѧ\n");
        printf("4.�������\n");
        scanf("%d", &K);
        if (K == 1) {
            printf("���������޸ĵ�ѧ����ѧ��\n");
            scanf("%d", &H);
            Link nod;
            nod = head;
            while (nod->student.id == H) {
                nod = nod->next;
            }
            printf("�������ѧ���޸ĺ�ĳɼ�\n");
            double F;
            scanf("%lf", &F);
            nod->student.math1 = F;
        }
        if (K == 2) {
            printf("���������޸ĵ�ѧ����ѧ��\n");
            scanf("%d", &H);
            Link nod;
            nod = head;
            while (nod->student.id == H) {
                nod = nod->next;
            }
            printf("�������ѧ���޸ĺ�ĳɼ�\n");
            double F;
            scanf("%lf", &F);
            nod->student.math2 = F;
        }
        if (K == 3) {
            printf("���������޸ĵ�ѧ����ѧ��\n");
            scanf("%d", &H);
            Link nod;
            nod = head;
            while (nod->student.id == H) {
                nod = nod->next;
            }
            printf("�������ѧ���޸ĺ�ĳɼ�\n");
            double F;
            scanf("%lf", &F);
            nod->student.math3 = F;
        }
        if (K == 4) {
            printf("���������޸ĵ�ѧ����ѧ��\n");
            scanf("%d", &H);
            Link nod;
            nod = head;
            while (nod->student.id == H) {
                nod = nod->next;
            }
            printf("�������ѧ���޸ĺ�ĳɼ�\n");
            double F;
            scanf("%lf", &F);
            nod->student.pro = F;
        }
    }
    if (id == 01) {
        int H;
        double F;
        printf("������ʦģʽ\n");
        printf("���������޸����Դ����ɼ�\n");
        printf("���������޸ĵ�ѧ����ѧ��\n");
        scanf("%d", &H);
        Link nod;
        nod = head;
        while (nod->student.id == H) {
            nod = nod->next;
        }
        printf("�������ѧ���޸ĺ�ĳɼ�\n");
        scanf("%lf", &F);
        nod->student.math1 = F;
    }
    if (id == 02) {
        int H;
        double F;
        printf("������ʦģʽ\n");
        printf("���������޸�΢���ֳɼ�\n");
        printf("���������޸ĵ�ѧ����ѧ��\n");
        scanf("%d", &H);
        Link nod;
        nod = head;
        while (nod->student.id == H) {
            nod = nod->next;
        }
        printf("�������ѧ���޸ĺ�ĳɼ�\n");
        scanf("%lf", &F);
        nod->student.math2 = F;
    }
    if (id == 03) {
        int H;
        double F;
        printf("������ʦģʽ\n");
        printf("���������޸���ɢ��ѧ�ɼ�\n");
        printf("���������޸ĵ�ѧ����ѧ��\n");
        scanf("%d", &H);
        Link nod;
        nod = head;
        while (nod->student.id == H) {
            nod = nod->next;
        }
        printf("�������ѧ���޸ĺ�ĳɼ�\n");
        scanf("%lf", &F);
        nod->student.math3 = F;
    }
    if (id == 04) {
        int H;
        double F;
        printf("������ʦģʽ\n");
        printf("���������޸ĳ�����Ƴɼ�\n");
        printf("���������޸ĵ�ѧ����ѧ��\n");
        scanf("%d", &H);
        Link nod;
        nod = head;
        while (nod->student.id == H) {
            nod = nod->next;
        }
        printf("�������ѧ���޸ĺ�ĳɼ�\n");
        scanf("%lf", &F);
        nod->student.pro = F;
    }
}

// ��ӡ�ɼ�
void check_grade(int id) {
    Link Head;
    Head = head->next;
    if (id == 00) {
        printf("�������Աģʽ\n");
        printf("ѧ������          ѧ��ѧ��          ѧ������          ѧ���Ա�          ���Դ����ɼ�          ΢���ֳɼ�          ��ɢ��ѧ�ɼ�          ������Ƴɼ�\n");
        do {
            printf("   %s                %d                  %d                 ", Head->student.name, Head->student.id, Head->student.age);
            if (Head->student.sex == 0) {
                printf("Ů                ");
            } else if (Head->student.sex) {
                printf("��                 ");
            }
            printf("%.2lf                ", Head->student.math1);
            printf("%.2lf                ", Head->student.math2);
            printf("%.2lf                   ", Head->student.math3);
            printf("%.2lf\n", Head->student.pro);
            Head = Head->next;
        } while (Head != NULL);
    }
    if (id == 01 || id == 02 || id == 03 || id == 04) {
        printf("������ʦģʽ\n");
        printf("��ǰ���ɲ鿴���Դ����ɼ�\n");
        printf("ѧ������          ѧ��ѧ��          ѧ������          ѧ���Ա�          ");
        if (id == 01) {
            printf("���Դ����ɼ�\n");
        } else if (id == 02) {
            printf("΢���ֳɼ�\n");
        } else if (id == 03) {
            printf("��ɢ��ѧ�ɼ�\n");
        } else if (id == 04) {
            printf("������Ƴɼ�\n");
        }
        do {
            printf("   %s                %d                  %d                 ", Head->student.name, Head->student.id, Head->student.age);
            if (Head->student.sex == 0) {
                printf("Ů                ");
            } else if (Head->student.sex) {
                printf("��                 ");
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

// ��ӡ��ʦ�˵�
void print_te_menu(int id) {
    clean();

    printf("��ʦ�˵�\n");
    printf("|1.¼��ɼ�\n");
    printf("|2.�޸ĳɼ�\n");
    printf("|3.��ѯ�ɼ�\n");
    printf("|4.�޸�����\n");
    printf("|5.�˳�\n");
    printf("��������Ӧ�����ѡ��:");

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

// ��ӡ����Ա�˵�
void print_op_menu(int id) {
    clean();

    printf("����Ա�˵�\n");
    printf("|1.¼��ɼ�\n");
    printf("|2.�޸ĳɼ�\n");
    printf("|3.��ѯ�ɼ�\n");
    printf("|4.��������\n");
    printf("|5.�˳�\n");
    printf("��������Ӧ�����ѡ��:");

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

// ��������
void reset_password(int id) {
    Link p1 = head;
    Link2 p2 = head2;
    printf("---------------------");
    printf("1.������ʦ��ѧ������");
    printf("2.��ʼ����������");
    printf("3.������һ���˵�");
    printf("---------------------");
    int flag;
    scanf("%d", &flag);
    if (flag == 1) {
        printf("��������Ҫ���������id");
        int i;
        scanf("%d", &i);
        for (;1;) {
            if (p2->id == i) {
                printf("����Ҫ���ý�ʦ%d������,����Y��ȷ��", i);
                char qr;
                qr = getchar();
                if (strcmp(&qr, "y") == 0 || strcmp(&qr, "Y") == 0) {
                    p2->password = p2->id;
                    printf("�޸ĳɹ�(��ʼ������id��ͬ)");
                } else {
                    printf("������һ���˵�");
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
                printf("����Ҫ����ѧ��%d������,����Y��ȷ��", i);
                char qr;
                qr = getchar();
                if (strcmp(&qr, "y") == 0 || strcmp(&qr, "Y") == 0) {
                    p1->student.password = p1->student.id;
                    printf("�޸ĳɹ�(��ʼ������id��ͬ)");
                } else {
                    printf("������һ���˵�");
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
        printf("���");
        print_op_menu(id);
    } else if (flag == 3) {
        print_op_menu(id);
    } else {
        printf("��������룬������һ���˵�");
        print_op_menu(id);
    }
    return;
}

// ����˺����� Ĭ���������˺���ͬ
int check(int id, int password) {
    // �жϹ���Ա
    if (id == 00 && password == 00) {
        return 1;
    }

    // �ж���ʦ
    Link2 p2 = head2->next;
    while (NULL != p2) {
        if (p2->id == id && p2->password == password) {
            return 2;
        }
        p2 = p2->next;
    }

    // �ж�ѧ��
    Link p = head->next;
    while (NULL != p) {
        if (p->student.id == id && p->student.password == password) {
            return 3;
        }
        p = p->next;
    }
    // ����
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

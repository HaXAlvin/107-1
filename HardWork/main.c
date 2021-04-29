#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

int keyIn(float score[][6],int k,int which){
    int i;
    switch(which) {
    case 1:
        printf("�п�J��妨�Z:");
        scanf("%f",&score[k][1]);
        if((score[k][1]<0)||(score[k][1]>100)) {
            puts("Error");
            return 1;
        }
        return 0;
    case 2:
        printf("�п�J�^�妨�Z:");
        scanf("%f",&score[k][2]);
        if((score[k][2]<0)||(score[k][2]>100)) {
            puts("Error");
            return 1;
        }
        return 0;
    case 3:
        printf("�п�J�L�n�����Z:");
        scanf("%f",&score[k][3]);
        if((score[k][3]<0)||(score[k][3]>100)) {
            puts("Error");
            return 1;
        }
        return 0;
    case 4:
        printf("�п�J�p�����Z:");
        scanf("%f",&score[k][4]);
        if((score[k][4]<0)||(score[k][4]>100)) {
            puts("Error");
            return 1;
        }
        return 0;
    case 5:
        printf("�п�J���B�^��B�L�n���B�p�����Z:");
        scanf("%f %f %f %f",&score[k][1],&score[k][2],&score[k][3],&score[k][4]);
        for(i=1; i<5; i++) {
            if((score[k][i]<0)||(score[k][i]>100)) {
                puts("Error");
                return 1;
            }
        }
        return 0;
    default:
        puts("�L����ءA�Ъ�^��歫�s���");
        return 1;
    }
}

void sort(float score[][6],char id[][20],char name[][20],int j){
    float tmp[6]={0};
    char tmp2[20]={0};
    memcpy(tmp,score[j],sizeof(score[j]));
    memcpy(score[j],score[j+1],sizeof(score[j+1]));
    memcpy(score[j+1],tmp,sizeof(tmp));
    memcpy(tmp2,id[j],sizeof(id[j]));
    memcpy(id[j],id[j+1],sizeof(id[j+1]));
    memcpy(id[j+1],tmp2,sizeof(tmp2));
    memcpy(tmp2,name[j],sizeof(name[j]));
    memcpy(name[j],name[j+1],sizeof(name[j+1]));
    memcpy(name[j+1],tmp2,sizeof(tmp2));
}

void search(int many,char edit[],float score[][6],char id[][20],char name[][20],char searching[][20]){
    for(int i=0; i<many; i++) {
        if(strcmp(edit,searching[i])==0) {
            int which;
            printf("�d�ߨ���:%s%s ���:%.2f �^��:%.2f �L�n��:%.2f �p��:%.2f\n\n",id[i],name[i],score[i][1],score[i][2],score[i][3],score[i][4]);
            printf("1.���\n2.�^��\n3.�L�n��\n4.�p��\n5.ALL\n�п�ܭק���:");
            scanf("%d",&which);
            if(keyIn(score,i,which)) {
                for(int j=1; j<5; j++) {
                    score[i][j]=-1;
                }
            }else{
                printf("�ק����:%s%s ���:%.2f �^��:%.2f �L�n��:%.2f �p��:%.2f\n\n",id[i],name[i],score[i][1],score[i][2],score[i][3],score[i][4]);
                break;
            }
        } else if(i==many-1) {
            puts("�d�L���H\n");
        }
    }
}

int allFailed(float score[][6],int i,int k,char tmp[]){
    if((score[i][k]<60)&&(score[i][k]>=0)) {
        printf("%20s",tmp);
        return 1;
    } else {
        printf("%20s"," ");
        return 0;
    }
}
void allNoneFailed(int flag){
    if(flag) {
        printf("%20s"," ");
    } else {
        printf("%20s","�L");
    }
}
int main() {
    char id[100][20]= {0},name[100][20]= {0};//�Ǹ��B�m�W
    float score[100][6];//���Z0-�y���� 1~4��^�L�p 5�[�v����
    int menu,many=0,i,j,which;
    for(i=0; i<100; i++) {//��l�Ʀ��Z
        for(j=0; j<19; j++) {
            score[i][j]=-1;
        }
    }
    puts("�w��ϥξǥͦ��Z�޲z�t��\n");
    do {
        int flag=0;
        float chinese=0,english=0,math=0,computer=0;
        printf("1.��J�ǥͦ��Z\n2.�ק�ǥͦ��Z\n3.��ܫ��w��سQ��ǥ�\n4.�̷ӫ��w��رƧǨ���ܦ��Z��\n5.���}�{��\n�п������:");
        scanf("%d",&menu);
        if(menu==1) {//�\��1 ��J���Z
            puts("\n�п�J�ǥ͸��");
            printf("�Ǹ�:");
            scanf("%s",id[many]);
            for(i=0;i<strlen(id[many]);i++){//�Ǹ��p�g���j�g
                if((id[many][i]<=122)&&(id[many][i]>=97)) {
                    id[many][i]-=32;
                }
            }
            for(i=0; i<many; i++) {//�קK�Ǹ�����(�m�W���\����)
                if(strcmp(id[many],id[i])==0) {
                    puts("�����쭫�п�J�A�Шϥ�\"2.�ק�ǥͦ��Z\"\n");
                    memset(id[many],0,sizeof(id[many]));//id���]��null
                    flag=1;
                    break;
                }
            }
            if(!flag) {
                printf("�m�W:");
                scanf("%s",name[many]);
                printf("\n1.���(2)\n2.�^��(2)\n3.�L�n��(3)\n4.�p��(4)\n5.ALL\n�п�ܿ�J���:");
                scanf("%d",&which);
                if(keyIn(score,many,which)) {//�I�skeyIn
                    for(i=1; i<5; i++) {
                        score[many][i]=-1;
                    }
                } else {
                    score[many][0]=many+1;
                    printf("\n���:%s%s ���:%.2f �^��:%.2f �L�n��:%.2f �p��:%.2f ��J����\n(-1��ܵL���)\n\n",id[many],name[many],score[many][1],score[many][2],score[many][3],score[many][4]);
                    many++;
                }
            }
        } else if((menu==2)&&(many>0)) {//�\��2 �ק令�Z
            char edit[20]= {0};
            puts("\n1.�Ǹ�\n2.�m�W");
            printf("�п�J�Q�ק令�Z���ǥ;Ǹ��Ωm�W:");
            scanf("%d",&i);
            if(i==1) {
                printf("�п�J�Ǹ�:");
                scanf("%s",edit);
                for(j=0;j<strlen(edit);j++){
                    if((edit[0]<=122)&&(edit[0]>=97)) {
                        edit[0]-=32;
                    }
                }
                search(many,edit,score,id,name,id);
            } else if(i==2) {
                printf("�п�J�m�W:");
                scanf("%s",edit);
                search(many,edit,score,id,name,name);
            } else {
                puts("Error");
            }
        } else if((menu==3)&&(many>0)) {//�\��3 �d�߳Q��
            printf("\n1.���\n2.�^��\n3.�L�n��\n4.�p��\n5.ALL\n�п�ܬd�߬��:");
            scanf("%d",&which);
            flag=0;
            if((which>=1)&&(which<=4)) {
                if(which==1){
                    puts("\n����Q��ǥ�:");
                }else if(which==2){
                    puts("\n�^���Q��ǥ�:");
                }else if(which==3){
                    puts("\n�L�n���Q��ǥ�:");
                }else if(which==4){
                    puts("\n�p���Q��ǥ�:");
                }
                for(i=0; i<many; i++) {
                    if((score[i][which]<60)&&score[i][which]>=0) {
                        printf("%s%s\n",id[i],name[i]);
                        flag=1;
                    }
                }
                if(!flag) {
                    puts("�L");
                }

            } else if (which==5) {
                chinese=0,english=0,math=0,computer=0;
                puts("\n�Ҧ���سQ��ǥ�:");
                printf("%20s%20s%20s%20s\n","���:","�^��:","�L�n��:","�p��:");
                for(i=0; i<many; i++) {
                    char tmp[40]= {'\0'};
                    strcat(tmp,id[i]);
                    strcat(tmp,name[i]);
                    if(allFailed(score,i,1,tmp))chinese=1;
                    if(allFailed(score,i,2,tmp))english=1;
                    if(allFailed(score,i,3,tmp))math=1;
                    if(allFailed(score,i,4,tmp))computer=1;
                    puts("");
                }
                allNoneFailed(chinese);
                allNoneFailed(english);
                allNoneFailed(math);
                allNoneFailed(computer);
                puts("");
            } else {
                puts("Error");
            }
        } else if((menu==4)&&(many>0)) {//�\��4 �d�ߦ��Z
            printf("\n1.��J����\n2.��妨�Z\n3.�^�妨�Z\n4.�L�n�����Z\n5.�p�����Z\n6.�[�v�������Z\n�п�ܱƧǤ�k:");
            scanf("%d",&which);
            float tmp[6]= {0};
            char tmp2[20]={0};
            for(i=0; i<many; i++) {//�p��[�v
                int num=0,j=0;
                if(score[i][1]!=-1) {
                    num+=(score[i][1]*2);
                    j+=2;
                }
                if(score[i][2]!=-1) {
                    num+=(score[i][1]*2);
                    j+=2;
                }
                if(score[i][3]!=-1) {
                    num+=(score[i][1]*3);
                    j+=3;
                }
                if(score[i][4]!=-1) {
                    num+=(score[i][1]*4);
                    j+=4;
                }
                score[i][5]=(float)num/j;
            }
            for(i=0; i<many; i++) {
                for(j=0; j<many-i-1; j++) {
                    if (which==1){
                        if(score[j][which-1]>score[j+1][which-1]) {
                            sort(score,id,name,j);
                        }
                    }else if((which>=2)&&(which<=6)){
                        if(score[j][which-1]<score[j+1][which-1]) {
                            sort(score,id,name,j);
                        }
                    }
                }
            }
            if ((which<1)||(which>6)){
                puts("Error");
            }else{
                for(i=0; i<many; i++) {
                    char tmp[40]= {'\0'};
                    strcat(tmp,id[i]);
                    strcat(tmp,name[i]);
                    printf("\n%20s%20s%20s%20s%20s%20s\n","�Ǹ��m�W","���(2)","�^��(2)","�L�n��(3)","�p��(4)","�[�v����");
                    printf("%20s%20.2f%20.2f%20.2f%20.2f%20.2f\n",tmp,score[i][1],score[i][2],score[i][3],score[i][4],score[i][5]);
                }
            }
        }else if (menu==5) {//�\��5 ���}
             puts("���±z���ϥ�!");
             break;
        }else if((menu>5)||(menu<1)){
            puts("Error");
        } else if(!many) {//many=0�� �u��ϥ�1or5
            puts("��Ʈw�|����J������");
        }
        puts("\n---��^�D���---");
    } while(1);
    return 0;
}


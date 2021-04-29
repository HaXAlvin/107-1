#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

int keyIn(float score[][6],int k,int which){
    int i;
    switch(which) {
    case 1:
        printf("請輸入國文成績:");
        scanf("%f",&score[k][1]);
        if((score[k][1]<0)||(score[k][1]>100)) {
            puts("Error");
            return 1;
        }
        return 0;
    case 2:
        printf("請輸入英文成績:");
        scanf("%f",&score[k][2]);
        if((score[k][2]<0)||(score[k][2]>100)) {
            puts("Error");
            return 1;
        }
        return 0;
    case 3:
        printf("請輸入微積分成績:");
        scanf("%f",&score[k][3]);
        if((score[k][3]<0)||(score[k][3]>100)) {
            puts("Error");
            return 1;
        }
        return 0;
    case 4:
        printf("請輸入計概成績:");
        scanf("%f",&score[k][4]);
        if((score[k][4]<0)||(score[k][4]>100)) {
            puts("Error");
            return 1;
        }
        return 0;
    case 5:
        printf("請輸入國文、英文、微積分、計概成績:");
        scanf("%f %f %f %f",&score[k][1],&score[k][2],&score[k][3],&score[k][4]);
        for(i=1; i<5; i++) {
            if((score[k][i]<0)||(score[k][i]>100)) {
                puts("Error");
                return 1;
            }
        }
        return 0;
    default:
        puts("無此科目，請返回選單重新選擇");
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
            printf("查詢到資料:%s%s 國文:%.2f 英文:%.2f 微積分:%.2f 計概:%.2f\n\n",id[i],name[i],score[i][1],score[i][2],score[i][3],score[i][4]);
            printf("1.國文\n2.英文\n3.微積分\n4.計概\n5.ALL\n請選擇修改科目:");
            scanf("%d",&which);
            if(keyIn(score,i,which)) {
                for(int j=1; j<5; j++) {
                    score[i][j]=-1;
                }
            }else{
                printf("修改後資料:%s%s 國文:%.2f 英文:%.2f 微積分:%.2f 計概:%.2f\n\n",id[i],name[i],score[i][1],score[i][2],score[i][3],score[i][4]);
                break;
            }
        } else if(i==many-1) {
            puts("查無此人\n");
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
        printf("%20s","無");
    }
}
int main() {
    char id[100][20]= {0},name[100][20]= {0};//學號、姓名
    float score[100][6];//成績0-流水號 1~4國英微計 5加權平均
    int menu,many=0,i,j,which;
    for(i=0; i<100; i++) {//初始化成績
        for(j=0; j<19; j++) {
            score[i][j]=-1;
        }
    }
    puts("歡迎使用學生成績管理系統\n");
    do {
        int flag=0;
        float chinese=0,english=0,math=0,computer=0;
        printf("1.輸入學生成績\n2.修改學生成績\n3.顯示指定科目被當學生\n4.依照指定科目排序並顯示成績單\n5.離開程式\n請選取應用:");
        scanf("%d",&menu);
        if(menu==1) {//功能1 輸入成績
            puts("\n請輸入學生資料");
            printf("學號:");
            scanf("%s",id[many]);
            for(i=0;i<strlen(id[many]);i++){//學號小寫換大寫
                if((id[many][i]<=122)&&(id[many][i]>=97)) {
                    id[many][i]-=32;
                }
            }
            for(i=0; i<many; i++) {//避免學號重複(姓名允許重複)
                if(strcmp(id[many],id[i])==0) {
                    puts("偵測到重覆輸入，請使用\"2.修改學生成績\"\n");
                    memset(id[many],0,sizeof(id[many]));//id重設為null
                    flag=1;
                    break;
                }
            }
            if(!flag) {
                printf("姓名:");
                scanf("%s",name[many]);
                printf("\n1.國文(2)\n2.英文(2)\n3.微積分(3)\n4.計概(4)\n5.ALL\n請選擇輸入科目:");
                scanf("%d",&which);
                if(keyIn(score,many,which)) {//呼叫keyIn
                    for(i=1; i<5; i++) {
                        score[many][i]=-1;
                    }
                } else {
                    score[many][0]=many+1;
                    printf("\n資料:%s%s 國文:%.2f 英文:%.2f 微積分:%.2f 計概:%.2f 輸入完成\n(-1表示無資料)\n\n",id[many],name[many],score[many][1],score[many][2],score[many][3],score[many][4]);
                    many++;
                }
            }
        } else if((menu==2)&&(many>0)) {//功能2 修改成績
            char edit[20]= {0};
            puts("\n1.學號\n2.姓名");
            printf("請輸入想修改成績之學生學號或姓名:");
            scanf("%d",&i);
            if(i==1) {
                printf("請輸入學號:");
                scanf("%s",edit);
                for(j=0;j<strlen(edit);j++){
                    if((edit[0]<=122)&&(edit[0]>=97)) {
                        edit[0]-=32;
                    }
                }
                search(many,edit,score,id,name,id);
            } else if(i==2) {
                printf("請輸入姓名:");
                scanf("%s",edit);
                search(many,edit,score,id,name,name);
            } else {
                puts("Error");
            }
        } else if((menu==3)&&(many>0)) {//功能3 查詢被當
            printf("\n1.國文\n2.英文\n3.微積分\n4.計概\n5.ALL\n請選擇查詢科目:");
            scanf("%d",&which);
            flag=0;
            if((which>=1)&&(which<=4)) {
                if(which==1){
                    puts("\n國文科被當學生:");
                }else if(which==2){
                    puts("\n英文科被當學生:");
                }else if(which==3){
                    puts("\n微積分被當學生:");
                }else if(which==4){
                    puts("\n計概被當學生:");
                }
                for(i=0; i<many; i++) {
                    if((score[i][which]<60)&&score[i][which]>=0) {
                        printf("%s%s\n",id[i],name[i]);
                        flag=1;
                    }
                }
                if(!flag) {
                    puts("無");
                }

            } else if (which==5) {
                chinese=0,english=0,math=0,computer=0;
                puts("\n所有科目被當學生:");
                printf("%20s%20s%20s%20s\n","國文:","英文:","微積分:","計概:");
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
        } else if((menu==4)&&(many>0)) {//功能4 查詢成績
            printf("\n1.輸入順序\n2.國文成績\n3.英文成績\n4.微積分成績\n5.計概成績\n6.加權平均成績\n請選擇排序方法:");
            scanf("%d",&which);
            float tmp[6]= {0};
            char tmp2[20]={0};
            for(i=0; i<many; i++) {//計算加權
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
                    printf("\n%20s%20s%20s%20s%20s%20s\n","學號姓名","國文(2)","英文(2)","微積分(3)","計概(4)","加權平均");
                    printf("%20s%20.2f%20.2f%20.2f%20.2f%20.2f\n",tmp,score[i][1],score[i][2],score[i][3],score[i][4],score[i][5]);
                }
            }
        }else if (menu==5) {//功能5 離開
             puts("謝謝您的使用!");
             break;
        }else if((menu>5)||(menu<1)){
            puts("Error");
        } else if(!many) {//many=0時 只能使用1or5
            puts("資料庫尚未輸入任何資料");
        }
        puts("\n---返回主選單---");
    } while(1);
    return 0;
}


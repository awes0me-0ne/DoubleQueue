#include<stdio.h>
#include<stdlib.h>//malloc用
#define NODATA 0//データ無し
#define EXISTDATA 1//データあり

/*
double型データを保持するセル
キューで用いる
自己参照構造体
 */

struct doubleCell{
  double data;             //データ部
  struct doubleCell * next;//ポインタ部
};

typedef struct doubleCell DoubleCell ;
typedef DoubleCell* Cell_P; //セル型

struct doublequeue{
  DoubleCell * head;//先頭ポインタ
  DoubleCell * tail;//末尾ポインタ
};
  typedef struct doublequeue DoubleQueue; //キュー型

DoubleQueue makeQueue();//キューの作成
void enque(DoubleQueue *queue,double data);//データ挿入
double deque(DoubleQueue *queue);//データ取り出し
double isEmpty(DoubleQueue *queue);//空のテスト
void printQueue(DoubleQueue *queue);//リスト表示
void fscanToQueue(FILE*fp,DoubleQueue *queue);//ファイルからのデータ入力
void forward_fprint(FILE*fp,DoubleQueue *queue);//ファイルへ順方向に出力
Cell_P makeCell(double n);//セル作成

int main(){
  //キューの動作
  DoubleQueue queue;
  DoubleQueue *q_p;
  FILE *fp_in,*fp_out;

  queue=makeQueue();//キュー生成
  q_p=&queue;
  printQueue(q_p);
  
  fp_in=fopen("DoubleData","r");
  fscanToQueue(fp_in,q_p);
  fclose(fp_in);

  printf("キューを表示します。\n");
  printQueue(q_p);

  printf("ファイルへ順に出力します。\n");
  fp_out=fopen("DoubleForward","w");
  forward_fprint(fp_out,q_p);//ファイルへ順に出力
  fclose(fp_out);

  printf("キューを表示します。\n");
  printQueue(q_p);

  return 0;
}

DoubleQueue makeQueue(){
  DoubleQueue queue;
  queue.head=NULL;
  queue.tail=NULL;
  return queue;
}

double isEmpty(DoubleQueue *queue){
  if(queue->head==NULL){
    return NODATA;
  }else{
    return EXISTDATA;
  }
}

Cell_P makeCell(double n){
  Cell_P new =(Cell_P)malloc(sizeof(DoubleCell));
  new->data=n;
  return new;
}

void enque(DoubleQueue *queue,double data){
  Cell_P new_cell=makeCell(data);
  if(isEmpty(queue)==NODATA){
  queue->head=new_cell;
  queue->tail=new_cell;
  }else{
    queue->tail->next=new_cell;
    queue->tail=new_cell;
  }
  return;
}

double deque(DoubleQueue * queue){
  double idata;
  Cell_P remove;
  if(queue->head!=queue->tail){
    remove=queue->head;
    idata=remove->data;
    queue->head=queue->head->next;
    free(remove);
    return idata;
  }else if(queue->head==queue->tail){//最後の一個の削除
    remove=queue->head;
    idata=remove->data;
    queue->head=NULL;
    queue->tail=NULL;
    free(remove);
    return idata;
  }else{
    printf("No data\n");
    return -1;
  }
}

void printQueue(DoubleQueue *queue){
  Cell_P p=queue->head;
  if(queue->head==NULL){
    printf("()\n");
  }else{
    printf("(");
  while(p!=queue->tail){
    printf("%3f,",p->data);
    p=p->next;
  }
  printf("%3f,",p->data);
  printf(")\n");
  }
  return ;
}

void fscanToQueue(FILE *fp,DoubleQueue *queue){
  double idata;
  while(fscanf(fp,"%lf",&idata)!=EOF){
    enque(queue,idata);
  }
  return;
}
void forward_fprint(FILE * fp,DoubleQueue *queue){
  double idata;
  while(isEmpty(queue)==EXISTDATA){
    idata=deque(queue);
    fprintf(fp,"%3f",idata);
  }
  return ;
}

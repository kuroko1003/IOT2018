#include <stdio.h>
#include <stdlib.h>

typedef struct BST{
	int key;
	struct BST *lchild;
	struct BST *rchild;
}BST;

void create(BST **bst, int *key, int n);
int insert(BST **bt, int key);
void inorder(BST *bt);
BST *search(BST *bt, int key);
int delnode(BST **p);
int del(BST **bt, int key);
int destroy(BST *bst);

int main(void){
	int *key;

	int n, i=0;
	int num, search_key, del_key;
	printf("输入二叉排序树元素个数：\n");
	scanf("%d", &n);
	key = (int *)malloc(sizeof(int)*n);
	printf("输入元素:\n");
	for(i=0; i<n; i++){
		scanf("%d", &key[i]);
	}
	//创建
	BST *bst = NULL;
	create(&bst, key, n);//这个数组传入指针即可
	//中序遍历
	printf("中序遍历：\n");
	inorder(bst);
	//删除元素
	printf("输入要删除的元素：\n");
	scanf("%d", &del_key);
	del(&bst, del_key);
	printf("中序遍历：\n");
	inorder(bst);
	//摧毁,摧毁后要想使用必须重建bst
	printf("摧毁二叉排序树\n");
	destroy(bst);
	//printf("*bst = %d\n", *bst);

	return 0;
}
//创建
void create(BST **bst, int *key, int n){
	int i=0;
	for(i=0; i<n; i++){
		insert(bst, key[i]);
	}
}
//插入
int insert(BST **bt, int key){
	if(*bt == NULL){
		*bt = (BST*)malloc(sizeof(BST));
		if(*bt == NULL){
			printf("分配内存失败\n");
			return 0;
		}
		(*bt)->key = key;
		(*bt)->lchild = (*bt)->rchild = NULL;
		//printf("(*bt)->key=%d\n",(*bt)->key);
		return 1;
	}
	if(key == (*bt)->key){//如果已存在，则插入失败
		printf("%d已存在,插入失败\n", key);
		return 0;
	}
	else if(key < (*bt)->key)
		insert(&(*bt)->lchild, key);
	else
		insert(&(*bt)->rchild, key);
	return 0;
}
//查找  返回值是BST指针
BST *search(BST *bt, int key){
	if(bt == NULL){
		printf("查找元素失败,无该元素\n");
		return bt;
	}
	else{
		if(bt->key == key){
			return bt;
		}
		else if(key < bt->key)
			return search(bt->lchild, key);
		else
			return search(bt->rchild, key);
	}
}
//删除节点
int delnode(BST **p){
	//删除节点有4种情况
	BST *s, *q;

	if((*p)->lchild == NULL && (*p)->rchild == NULL){ //左右子树都为空!
		*p = NULL;  //二级指针下，可以直接令*p = NULL
		return 1;
	}
	else if(!(*p)->lchild){//左子树为空
		q = *p;  //让q指向p的右子树，然后把p的右子树挪到p的位置
		*p = (*p)->rchild;
		free(q);
		return 1;
	}
	else if(!(*p)->rchild){//右子树为空
		q = *p;
		*p = (*p)->lchild;
		free(q);
		return 1;
	}
	else{   //左右子树都不为空
		s = (*p)->lchild;
		q = *p;
		while(s->rchild){ //找到中序遍历中p的直接前驱
			q = s;
			s = s->rchild;
		}
		(*p)->key = s->key;  //把前驱的值赋值给p

		if(q != (*p))//如果q = *p，则while没执行，即p->lchild = s
			q->rchild = s->lchild; //叶子节点置空，必须使其父节点指向空，不能直接对叶子结点操作
		else //如果q = s
			q->lchild = s->lchild;//q不存在，p->lchild即为s

		free(s);
	}
	return 1;
}
//删除
int del(BST **bt, int key){
	if(*bt == NULL){
		printf("未找到%d\n", key);
		return 0;
	}
	if((*bt)->key == key){
		if(delnode(&(*bt)))
			printf("已删除%d\n", key);
		return 1;
	}
	else if((*bt)->key > key)
		return del(&(*bt)->lchild, key);//因为bt中的值要改变，所以这里必须传入实值，定义为二级指针
	else
		return del(&(*bt)->rchild, key);
}
//摧毁树
int destroy(BST *bst){
	if(bst == NULL){
		printf("树为空！\n");
		return 0;
	}
	while(bst){
		del(&bst, bst->key);
	}
	free(bst);
	printf("二叉排序树已摧毁\n");
	return 1;
}
//中序遍历
void inorder(BST *bt){
	if(bt!=NULL){
		inorder(bt->lchild);
		printf("%d\n",bt->key);
		inorder(bt->rchild);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define NxN (N*N)
#define TRUE 1
#define FALSE 0

struct node {
	int tiles[N][N];
	int f, g, h;
	short zero_row, zero_column;	/* location (row and colum) of blank tile 0 */
	struct node *next;
	struct node *parent;			/* used to trace back the solution */
};

int goal_rows[NxN];
int goal_columns[NxN];
struct node *start,*goal;
struct node *open = NULL, *closed = NULL;
struct node *succ_nodes[4];

void print_a_node(struct node *pnode) {
	int i,j;
	for (i=0;i<N;i++) {
		for (j=0;j<N;j++) 
			printf("%2d ", pnode->tiles[i][j]);
		printf("\n");
	}
	printf("\n");
}

struct node *initialize(char **argv){
	int i,j,k,index, tile;
	struct node *pnode;

	pnode=(struct node *) malloc(sizeof(struct node));
	index = 1;
	for (j=0;j<N;j++)
		for (k=0;k<N;k++) {
			tile=atoi(argv[index++]);
			pnode->tiles[j][k]=tile;
			if(tile==0) {
				pnode->zero_row=j;
				pnode->zero_column=k;
			}
		}
	pnode->f=0;
	pnode->g=0;
	pnode->h=0;
	pnode->next=NULL;
	pnode->parent=NULL;
	start=pnode;
	printf("initial state\n");
	print_a_node(start);

	pnode=(struct node *) malloc(sizeof(struct node));
	goal_rows[0]=3;
	goal_columns[0]=3;

	for(index=1; index<NxN; index++){
		j=(index-1)/N;
		k=(index-1)%N;
		goal_rows[index]=j;
		goal_columns[index]=k;
		pnode->tiles[j][k]=index;
	}
	pnode->tiles[N-1][N-1]=0;	      /* empty tile=0 */
	pnode->f=0;
	pnode->g=0;
	pnode->h=0;
	pnode->next=NULL;
	goal=pnode; 
	printf("goal state\n");
	print_a_node(goal);

	return start;
}

/* merge the remaining nodes pointed by succ_nodes[] into open list. 
 * Insert nodes based on their f values --- keep f values sorted. */
void merge_to_open() { 
	int count; 
	struct node *pnode;
	struct node *new_list[4];
	for(int i = 0; i < N; i++){
		pnode = succ_nodes[i];
		if (pnode != NULL){
			new_list[count] = succ_nodes[i];
			count++;
		}
	}

	for(int i = 0; i < count - 1; i++){
		for(int j = 0; j < count - i - 1; j++){
			if(new_list[j] -> f > new_list[j + 1] -> f){
				struct node *temp = new_list[j+1];
				new_list[j+1] = new_list[j];
				new_list[j] = temp;
			}
		}
	}

	open = new_list[0];
}

/*swap two tiles in a node*/
void swap(int row1,int column1,int row2,int column2, struct node * pnode){
	int temp = pnode->tiles[row1][column1]; 
	pnode -> tiles[row1][column1] = pnode -> tiles[row2][column2];
	pnode -> tiles[row2][column2] = temp;
}

//need this function for expand, cannot keep selected pointer to be constant
void copy(struct node *one, struct node *two){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			one->tiles[i][j] = two->tiles[i][j];
		}
	}
	one->f = two->f;
	one->g = two->g;
	one->h = two->h;
	one->zero_row = two->zero_row;
	one->zero_column = two->zero_column;
	one->parent = two->parent;
	one->next = two->next;
}

/*update the f,g,h function values for a node */
void update_fgh(int i) {
    struct node *pnode = succ_nodes[i];
    if (pnode == NULL){
        return;
    }
	if (pnode -> parent == NULL){
			pnode -> g = 0;
	}
	else{
			pnode -> g = pnode -> parent -> g + 1;
	}
	
	//understand why we add for all the tiles and not just 0?
	pnode->h = 0;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            int tile = pnode->tiles[row][col];
            if (tile != 0) {
                pnode->h += abs(row - goal_rows[tile]) + abs(col - goal_columns[tile]);
            }
        }
    }

    succ_nodes[i] -> f = pnode -> g + pnode -> h;
}

/* 0 goes down by a row */
void move_down(struct node * pnode){
	int row = pnode -> zero_row;
	int col = pnode -> zero_column;
	swap(row, col, row+1, col, pnode);
	pnode -> zero_row++;
}

/* 0 goes right by a column */
void move_right(struct node * pnode){
	int row = pnode -> zero_row;
	int col = pnode -> zero_column;
	swap(row,col,row,col+1,pnode);
	pnode->zero_column++;
}

/* 0 goes up by a row */
void move_up(struct node * pnode){
	int row = pnode -> zero_row;
	int col = pnode -> zero_column;
	swap(row, col, row-1, col, pnode);
	pnode -> zero_row--;
}

/* 0 goes left by a column */
void move_left(struct node * pnode){
	int row = pnode -> zero_row;
	int col = pnode -> zero_column;
	swap(row,col,row,col-1,pnode);
	pnode->zero_column--;
}

/* expand a node, get its children nodes, and organize the children nodes using
 * array succ_nodes.
 */
void expand(struct node *selected) {
	if(selected -> zero_row != 0){
		struct node *up = (struct node*)malloc(sizeof(struct node));
		copy(up,selected);
		move_up(up);
		succ_nodes[0] = up;
		up->parent = selected;
	}
	if(selected -> zero_row != 3){
		struct node *down = (struct node *)malloc(sizeof(struct node));
		copy(down,selected);
		move_down(down);
		succ_nodes[1] = down;
		down->parent = selected;
	}
	if(selected -> zero_column != 0){
		struct node *left = (struct node *)malloc(sizeof(struct node));
		copy(left,selected);
		move_left(left);
		succ_nodes[2] = left;
		left->parent = selected;
	}
	if(selected -> zero_column != 3){
		struct node *right = (struct node *)malloc(sizeof(struct node));
		copy(right,selected);
		move_right(right);
		succ_nodes[3] = right;
		right->parent = selected;
	}
}

int nodes_same(struct node *a,struct node *b) {
	int flg=FALSE;
	if (memcmp(a->tiles, b->tiles, sizeof(int)*NxN) == 0)
		flg=TRUE;
	return flg;
}

/* Filtering. Some states in the nodes pointed by succ_nodes may already be included in 
 * either open or closed list. There is no need to check these states. Release the 
 * corresponding nodes and set the corresponding pointers in succ_nodes to NULL. This is 
 * important to reduce execution time.
 * This function checks the (i)th node pointed by succ_nodes array. You must call this
 * function in a loop to check all the nodes in succ_nodes. Free the successor node and 
 * set the corresponding pointer to NULL in succ_node[] if a matching node is found in 
 * the list.
 */ 
void filter(int i, struct node *pnode_list){ 
	if(succ_nodes[i] != NULL){
		struct node *pnode = succ_nodes[i];
		struct node *iter = pnode_list;
		while(iter != NULL){
			int test = nodes_same(iter, pnode);
			if(test = 0){
				succ_nodes[i] = NULL;
			}
			iter = iter -> parent;
		}
	}
	
}

int main(int argc,char **argv) {
	int iter,cnt;
	struct node *copen, *cp, *solution_path;
	int ret, i, pathlen=0, index[N-1];

	solution_path=NULL;
	start=initialize(argv);	/* init initial and goal states */
	open=start; 

	iter=0; 
	while (open!=NULL) {	/* Termination cond with a solution is tested in expand. */
		copen=open;
		open=open->next;  /* get the first node from open to expand */
		
		/* DEBUG: print the node (layout) in *copen 
		 * Fix segmentation faults first. If the program cannot produce correct results,
		 * select an initial layout close to the goal layout, and debug the program with it.
		 * gdb is recommended. You may also print data on the screen. But this is not as
		 * convenient as using gdb.
		 * */

		if(nodes_same(copen,goal)){ /* goal is found */
			do{ /* trace back and add the nodes on the path to a list */
				copen->next=solution_path;
				solution_path=copen;
				copen=copen->parent;
				pathlen++;
			} while(copen!=NULL);
			printf("Path (lengh=%d):\n", pathlen); 
			/* print out the nodes on the list */
			while(solution_path != NULL){
				print_a_node(solution_path);
				solution_path = solution_path -> next;
			}
			break;
		}
		expand(copen);       /* Find new successors */

		/* DEBUG: print the layouts/nodes organized by succ_nodes[] */

		for(i=0;i<4;i++){
			filter(i,copen);
			filter(i,closed);
			update_fgh(i);
		}

		/* DEBUG: print the layouts/modes remaining in succ_nodes[] */

		merge_to_open(); /* New open list */

		/* DEBUG: print the layouts/nodes on the open list */

		copen->next=closed;
		closed=copen;		/* New closed */
		/* print out something so that you know your 
		 * program is still making progress 
		 */
		iter++;
		if(iter %1000 == 0)
			printf("iter %d\n", iter);
	}
	return 0;
} /* end of main */
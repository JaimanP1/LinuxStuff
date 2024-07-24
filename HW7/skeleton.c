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
struct node *succ_nodes[N];

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
    //making array to store successor nodes then bubble sorting the array

    // Collect non-NULL nodes from succ_nodes
    for (int i = 0; i < N; i++) {
        if (succ_nodes[i] != NULL) {
            temp_list[count] = succ_nodes[i];
            count++;
        }
    }

    // Bubble sort based on f values
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp_list[j]->f < temp_list[j + 1]->f) {
                struct node *temp = temp_list[j];
                temp_list[j] = temp_list[j + 1];
                temp_list[j + 1] = temp;
            }
        }
    }

    // Merge sorted nodes into the open list 
    for (int i = 0; i < count; i++) {
        temp_list[i]->next = open;
        open = temp_list[i];
    }
}

    for (int j = 0; j < i; j++) {
        for (int k = 0; k < N; k++) {
            if (succ_nodes[k] != NULL && succ_nodes[k]->f == placeholder[j]) {
                *new_open_tail = succ_nodes[k];
                new_open_tail = &((*new_open_tail)->next);
                break;
            }
        }
    }

    // Terminate the new open list
    *new_open_tail = NULL;

    // Update the global open list to point to the new sorted list
    open = new_open;
}


/*swap two tiles in a node*/
void swap(int row1,int column1,int row2,int column2, struct node * pnode){
	int tile = pnode->tiles[row1][column1];
	pnode->tiles[row1][column1]=pnode->tiles[row2][column2];
	pnode->tiles[row2][column2]=tile;
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
	// CHECK TO MAKE SURE THAT ADDING ALL OF THE DIFFERENCES FOR EACH OF THE TILES IS CORRECT!!!
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
	swap(pnode->zero_row, pnode->zero_column, pnode->zero_row+1, pnode->zero_column, pnode); 
	pnode->zero_row++;
}

/* 0 goes right by a column */
void move_right(struct node * pnode){
	swap(pnode->zero_row, pnode->zero_column, pnode->zero_row, pnode->zero_column+1, pnode); 
	pnode->zero_column++;
}

/* 0 goes up by a row */
void move_up(struct node * pnode){
	swap(pnode->zero_row, pnode->zero_column, pnode->zero_row-1, pnode->zero_column, pnode); 
	pnode->zero_row--;
}

/* 0 goes left by a column */
void move_left(struct node * pnode){
	swap(pnode->zero_row, pnode->zero_column, pnode->zero_row, pnode->zero_column-1, pnode); 
	pnode->zero_column--;
}

/* expand a node, get its children nodes, and organize the children nodes using
 * array succ_nodes.
 */
void expand(struct node *selected) {
    short old_zero_row = selected -> zero_row;
    short old_zero_column = selected -> zero_column;
    int new_zero_row, new_zero_column;

    // Initialize succ_nodes to NULL
    for (int i = 0; i < N; i++) {
        succ_nodes[i] = NULL;
    }

    // Possible moves: up, down, left, right
    const int row_options[] = {-1, 1, 0, 0};
    const int col_options[] = {0, 0, -1, 1};

    for (int i = 0; i < N; i++) {
        new_zero_row = old_zero_row + row_options[i];
        new_zero_column = old_zero_column + col_options[i];

        // Check if the move is within bounds
        if (new_zero_row >= 0 && new_zero_row < N && new_zero_column >= 0 && new_zero_column < N) {
            struct node *new_node = (struct node *)malloc(sizeof(struct node));
            if (new_node == NULL) {
                printf("Memory allocation failed\n");
                //exit(EXIT_FAILURE);
            }

            // Copy tiles and swap the zero tile
			for(int j = 0; j < N; j++){
				for(int k = 0; k < N; k++){
					new_node -> tiles[j][k] = selected -> tiles[j][k];
				}
			}
			// CHECK THIS REASSIGNMENT!!!
            new_node -> tiles[old_zero_row][old_zero_column] = new_node -> tiles[new_zero_row][new_zero_column];
            new_node -> tiles[new_zero_row][new_zero_column] = 0;
            new_node -> zero_row = new_zero_row;
            new_node -> zero_column = new_zero_column;

            // Set parent and initialize f, g, h values
            new_node -> parent = selected;
			succ_nodes[i] = new_node;
            update_fgh(i);
        }
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
	struct node *pnode = succ_nodes[i];
	struct node **iterator = pnode_list;
	if (pnode == NULL) {
        return;
    }
	while( *iterator != NULL ){
		int val = nodes_same(iterator, pnode);
		if ( val == 1 ){
			succ_nodes[i] = NULL;
			return;
		}
		else{
			*iterator = pnode_list -> next;
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

        if (nodes_same(copen, goal)) { /* goal is found */
            do { /* trace back and add the nodes on the path to a list */
                copen->next = solution_path;
                solution_path = copen;
                copen = copen->parent;
                pathlen++;
            } while (copen != NULL);
            struct node *iterator = solution_path;
            while (iterator != NULL) {
                print_a_node(iterator);
                iterator = iterator->next;
            }
            printf("Path (length=%d):\n", pathlen);
            break;
        }
        expand(copen); /* Find new successors */

		/* DEBUG: print the layouts/nodes organized by succ_nodes[] */

		for(i=0;i<N;i++){
			filter(i,copen);
			filter(i,closed);
			update_fgh(i);
		}

        copen->next = closed;
        closed = copen; /* New closed */
        iter++;
        if (iter % 1000 == 0){
            printf("iter %d\n", iter);
        }
        if (iter >= 10000){
            printf("Could not find a solution after 10000 iterations, aborting\n");
            return 0;
        }
    }
    return 0;
}
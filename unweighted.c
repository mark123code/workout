#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


//write getsize method

struct queue_node {
	
	int v_no;
	struct queue_node * next;

};

struct head_ptr {

	struct queue_node * next;
	struct queue_node * last;

};

typedef struct {
	int known;
	int distance;
} table_node;


void enqueue (struct head_ptr *Q,int s) {
	
	Q->last->next = malloc(sizeof(struct queue_node));
	Q->last->next->v_no = s;
	Q->last->next->next = NULL;
	Q->last = Q->last->next;

}

int dequeue (struct head_ptr * Q) {
	
	int s = Q->next->v_no;
	struct queue_node * temp = Q->next;
	Q->next = temp->next;
	free(temp);
	return s;

}


int * matrix_read(char *s, int size) {

	int * matrix_array = malloc(sizeof(int) * size * size);
	FILE *fp = fopen(s,"r");
	int i,j;
	i=j=0;
        char line[BUFSIZ];
        int field,n;
	char *start = line;

	
	while(fgets(start, sizeof start, fp))
	{	
		j=0;
		while (sscanf(start, "%d%n", &field, &n)==1) {
               
		 matrix_array[i][j++] = field;
		 start += n;
            }
             i++;
	}
	

	if (i!=j)
		exit(1);
	fclose(fp);

	return matrix_array;

}

void list_read(char *s) {
	
	int *list_array;
	int *buff;
	int fp = open(s,O_RDONLY);

	//read the input into list format

}


void select_method (char **argv) {

	int x = 1;
	if (x==1) 
		matrix_read(argv[3], atoi(argv[2]));
	else if(!x)
		list_read(argv[3]);
	else
		exit(1);
}
	

table_node * initialize_data(int size) {

	table_node * table_array = malloc(sizeof(table_node)*size);
	int i;
	for (i=0;i<size;i++)
	{
	//	table_array[i].v_no = i;
 		table_array[i].distance = -1;
	}
	
	return table_array;
	
}

void find_SP (char *path, int s, int size) {

	//table_node * T = initialize_data(size);
	s--;
	int * array = matrix_read(path, size);
	int i,j,k;
	int T[size];

	for (i=0;i<size;i++)
		T[i] = -1;

	T[s] = 0;
	struct head_ptr * Q = malloc(sizeof(struct head_ptr));
	Q->next = Q->last = malloc(sizeof(struct queue_node));


    // Queuing the first node onto the queue
	Q->next->v_no = s;
	Q->next->next = NULL;
	Q->last = Q->next;


    // Main BFS algo for shortest unweighted path
	while (Q->next) //while Q->next is not NULL
	{
		int vertex_no = dequeue(Q);
		

		/* Enter code for checking the adjacency method */
		/* for (all vertex w adjacent to vertex_no && T[w].distance == -1)
		   
		   {
 			T[w].distance = T[s].distance+1;
			queue(Q,w);
		   }
                */

		for (j=0;j<size;j++)
	 	{

			if (array[vertex_no][j]==1 && T[j] == -1 )
	
		   {
 			T[j] = T[vertex_no] + 1;
			queue(Q,j);
		   }
	
        	}	
       }

}

int main (int argc, char **argv) {


// argv[1] will contain the name of the file and argv[2] will contain the vertex number.

	FILE *fp = fopen(argv[1],"r");
        char line[20];
	fgets(line, sizeof line, fp);
        char *start = line;
        int field,n,count=0;
            
            while (sscanf(start, "%d%n", &field, &n)==1) {
                start += n;
		count++;
            }
                
	fclose(fp);   
	find_SP(argv[1], atoi(argv[2]), count);
	return 0;

}

/**
 * FILE: GRAPHS.C
 * 
 * THIS FILE  CONTAINS EMPTY / DO-NOTHING IMPLEMENTATIONS
 * FOR THE FUNCTIONS REQUIRED FOR THE GRAPHS ASSIGNMENT. 
 *
 * DO NOT RENAME THESE FUNCTIONS OR CHANGE THEIR RETURN
 * TYPES OR INPUT PARAMETERS.
 *
 * YOU NEED TO COMPLETE THE IMPLEMENTATION OF THESE
 * FUNCTIONS BY REPLACING THE CURRENT IMPLEMENTATIONS
 * WITH IMPLEMENTATIONS OF YOUR OWN. 
 *
 * THESE FUNCTIONS RECEIVE INPUT PARAMETERS THAT WILL
 * PROVIDE THEM WITH THE INFORMATION THAT THEY REQUIRE. YOU
 * DO NOT NEED TO USE USER INPUT FUNCTIONS SUCH AS SCANF
 * ETC, TO READ IN VALUES. THE GRAPH FUNCTIONS ARE CALLED
 * FROM A SEPARATE FILE (SEE THE TESTER PROGRAM) AND THE
 * INPUTS TO THE FUNCTIONS ARE PROVIDED THERE. 
 *
 * THE FUNCTIONS RETURN VALUES TO REPRESENT SUCCESS, ERROR,
 * OR, IN SOME CASES, DATA THAT HAS TO BE RETURNED. THE CALLER 
 * OF THESE FUNCTIONS WILL EXPECT TO RECEIVE THESE RETURN VALUES 
 * IN ORDER TO VERIFY THE OUTCOME OF THE FUNCTION CALL. 
 *
 * IF THERE AREANY FUNCTIONS THAT YOU DON'T HAVE TIME TO 
 * IMPLEMENT, PLEASE LEAVE THE EMPTY / DO-NOTHING IMPLEMENTATION
 * FOR THEM IN THIS FILE, OTHERWISE YOUR PROGRAM WON'T COMPILE
 * WHEN IT IS FED INTO OUR TESTER PROGRAM.
 * 
 */

/** 
 * ### INCLUDES
 */
#include <stdio.h>  // required for access to file input-output functions in C
#include <stdlib.h> // may be required for access to memory allocation functions
#include "graphs.h" // required, to include the Graph data structures and function declarations

/** #### FUNCTION IMPLEMENTATIONS ## */

AdjacencyMatrix* createAdjacencyMatrix(int defaultEdgeValue)
{
   	//check input parameters 
	if(defaultEdgeValue < 0){

	return NULL;
	}	

	AdjacencyMatrix *myMatrix;

	myMatrix = (AdjacencyMatrix*)myMalloc(sizeof(AdjacencyMatrix));

	// malloc issue
	    if (myMatrix ==NULL){
		return NULL;
;
	    }

	    //nested loop
		int i;
		int j;
	    //where i is each column and j is each row
	    for (i = 0; i < NUMBER_OF_VERTICES; i++){
		    for (j = 0; j < NUMBER_OF_VERTICES; j++){
			//populate the matrix with the defaultEdgeValue
			myMatrix->matrix[i][j] = defaultEdgeValue;
		    }
		    
	    }
	return myMatrix;

}
int addEdge(AdjacencyMatrix *pMatrix, int src, int dest, int weight)
{
    
    //if invalid inputs 
    if( pMatrix == NULL || src < 0 || dest < 0 || weight < 0){
	    return INVALID_INPUT_PARAMETER;
    }
	

	pMatrix->matrix[src][dest] = weight;
    //record relevant edge in the matrix
	//return error or success code

	return SUCCESS;
}



int addEdges(AdjacencyMatrix *pMatrix, Edge edges[], int edgeNum)
{
   //input validation 
    if( pMatrix == NULL || edges == NULL || edgeNum < 1){
            return INVALID_INPUT_PARAMETER;
    }  
    //initiate variable and start the for loop to add each edge
	int i;

	for(i = 0; i < edgeNum; i++){
		
		//if one of the values from the edges[] array is invalid 
		//fill it with zero 
		if (edges[i].src < 0){	
			pMatrix->matrix[0][edges[i].dest] = edges[i].weight;
		}

		else if (edges[i].dest < 0){
			pMatrix->matrix[edges[i].src][0] = edges[i].weight;
		}
		else if (edges[i].weight < 0){
			pMatrix->matrix[edges[i].src][edges[i].dest] = 0;
		}
		else{
	pMatrix->matrix[edges[i].src][edges[i].dest] = edges[i].weight;
	
		}	
	}
	//return relevant success code
	if(edges[i].src < 0 || edges[i].dest < 0 || edges[i].weight < 0){
		return PARTIAL_SUCCESS;
		}
	else{
		return SUCCESS;
	}
}
/**
 * This function will receive the name of a file on disk which contains the 
 * data for a graph which has been stored in the form of an adjacency matrix. 
 * The function should read the content from the file and use it to populate 
 * the AdjacencyMatrix provided. The file will be formatted thus:
 * 
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 
 * I.e., assuming a graph with 10 vertices, this will require a 10 x 10 matrix.
 * 
 * Each line in the file represents the next row in matrix, indexed from 0 to 9.
 * 
 * Each line will record the weight of the relevant edge in the graph. This will
 * be a value of zero (no edge) or a value of greater than zero (signifying that
 * an edge does exist, and the weight of that edge).
 * 
 * You can assume that the file content will be valid and in the correct format 
 * too, so you do not need to check for this when reading in from the file. 
 * Other validations may be required in the function however.
 * 
 * The function should return SUCCESS or a relevant error code.
 * 
 */
int loadMatrixFromFile(AdjacencyMatrix *pMatrix, char filename[])
{
    // Provide your own implementation here..
	
	// open file
	
	FILE *rfile; 
		rfile=fopen(filename, "r");

	if(rfile == NULL){
		return FILE_IO_ERROR;
	}
	
	int i;
	int j;
	for(i = 0; i < NUMBER_OF_VERTICES; i++){
	
		for(j = 0; j < NUMBER_OF_VERTICES; j++){
			fscanf(rfile, "%d ", &pMatrix->matrix[i][j]);

		}
		fscanf(rfile, "\n");
	}
	fclose(rfile);

	return SUCCESS;
	// if file does not exist return errorr
	

    }     

int doDijsktraAlgorithm(AdjacencyMatrix *pMatrix, DijkstraTable *pTable, int startNode)
{

	//validate inputs
	if(pMatrix == NULL || pTable == NULL || startNode < 0){

		return INVALID_INPUT_PARAMETER;
	}
	//initialise pTable to default values using default values
	
	int i;
	for(i = 0; i < NUMBER_OF_VERTICES; i++){
		pTable->table[i].visited = false;
		pTable->table[i].distance = VERY_LARGE_NUMBER;
		pTable->table[i].predecessor = -1;

	}
	//declare variables
	int currentNode = startNode;
	int j;
	bool finished = false;
	//initialise distance from starting node
	pTable->table[currentNode].distance = 0;
	
	while(finished == false){
	//loop through iterate through the row of adjacency matrix which is the starting node
	for(j = 0; j < NUMBER_OF_VERTICES; j++){
		//if there is an edge and hasn't been visited
		if(pMatrix->matrix[currentNode][j] > 0 && pTable->table[currentNode].visited == false){
			
			//distance to node j 
			int dToNode = pTable->table[currentNode].distance + pMatrix->matrix[currentNode][j];

			//check if new distance found is shorter
                	if(dToNode < pTable->table[j].distance){           
                        	pTable->table[j].distance = dToNode;          
                        	pTable->table[j].predecessor = currentNode;
                	}

		}
		
	}
	//set currentNode to visited
	pTable->table[currentNode].visited = true;

	int shortestSoFar = VERY_LARGE_NUMBER;
	int whichNode = -1;
	
	//for loop to traverse through the nodes on the table 
	for(i = 0; i < NUMBER_OF_VERTICES; i++){
		//if node is not visited and the distance is shorter than the shortestSoFar
		if (pTable->table[i].visited == false && pTable->table[i].distance < shortestSoFar){
			//update values
		shortestSoFar = pTable->table[i].distance;
		whichNode = i;

		}
	}

	//set currentNode to the one just explored
	if(whichNode != -1){
		currentNode = whichNode;
	}
	//otherwise finished becomes true
	else{
		finished = true;
	}

	}
	
	return SUCCESS;
	}

int findShortestPathTo(DijkstraTable *pTable, int nodeFrom, int nodeTo, int pathFound[])
{

	//initiate variables
	int currentNode = 0;
	int nextNode = 0;
	int verticesAdded = 0;

	//set currentNode as the one you want to get to
	currentNode = nodeTo;
	
	//add the first node to the array
	pathFound[verticesAdded] = nodeTo;
	do{
		//nextNode becomes currentNode's predecessor
		nextNode = pTable->table[currentNode].predecessor;
		
		//add nextNode to the array
		verticesAdded += 1;
		pathFound[verticesAdded] = nextNode;
		
		//currentNode becomes nextNode
		currentNode = nextNode;
	}while(currentNode != nodeFrom);

	//remainder of path becomes -1
	pathFound[verticesAdded+1] = -1;
	
	return SUCCESS;
}


int addEdgeToAdjacencyList(AdjacencyList *pList, int src, int dest, int weight)
{

	if(pList == NULL || src < 0 || dest < 0 || weight < 0){
		return INVALID_INPUT_PARAMETER;
	}

//allocate memory for new variable and initialise its fields
   ListNode *tPtr = (ListNode*)myMalloc(sizeof(ListNode)); 
   if (tPtr == NULL){
	return MEMORY_ALLOCATION_ERROR;
   }

	tPtr->destNode = dest;
	tPtr->weight = weight;
	tPtr->next = NULL;

	tPtr->next = pList->adjacencyList[src];

	pList->adjacencyList[src] = tPtr;

	return SUCCESS;
}


int populateAdjacencyList(AdjacencyList *pList, AdjacencyMatrix *pMatrix)
{
 
	//invalid input params
	if(pMatrix == NULL || pList == NULL){
		return INVALID_INPUT_PARAMETER;
	}
//for loops to initaite code
    int i;
    int j;
    for(i = 0; i < NUMBER_OF_VERTICES; i++){
	for(j = 0; j < NUMBER_OF_VERTICES; j++){
	
		if(pMatrix->matrix[i][j] > 0){
		//allocate memory for new variable and initialise its fields
		ListNode *lPtr = (ListNode*)myMalloc(sizeof(ListNode)); 
   		if (lPtr == NULL){
   		     return MEMORY_ALLOCATION_ERROR;
		   }
		
		lPtr->destNode = j;
		lPtr->weight = pMatrix->matrix[i][j];
		lPtr->next = NULL;
		
		//set pointer to the top of the list
		lPtr->next = pList->adjacencyList[i];
		pList->adjacencyList[i] = lPtr;
		}
	}
	
    }
    return SUCCESS;
}

/**
 * In the lectures, we looked at how to use an AdjacencyMatrix representation
 * of a graph as a basis for completing Dijkstra's algorithm. For this function, 
 * see if you can implement the algorithm using an AdjacencyList representation
 * of a graph instead. The AdjacencyList has the exact same content as the 
 * AdjacencyMatrix: it represents all of the nodes on a graph and the edges between 
 * them. It just represents these in a different way. 
 * 
 * To implement this function, you just need to review how you were using the 
 * AdjacencyMatrix during specific stages of the Dijkstra algorithm, and think about
 * how you could swap the AdjacencyList into these stages instead. The main difference
 * is likely to be related to how the edges that are emanating from the 'current'
 * node in the traversal are discovered. With the AdjacencyMatrix, we simply went
 * through the relevant row in the matrix, examining each column one at a time.
 * A similar approach can be taken for the AdjacencyList, but requiring a
 * different form of traversal for the relevant 'row' in the list.
 * 
 * The function will receive a ready-made graph to work with, in the form of 
 * an AdjacencyList. It will also receive an empty DijkstraTable, ready to be 
 * populated. It will also receive the starting node on the graph to 
 * commence the algorithm from. This function should implement the algorithm, 
 * running it on the graph provided and updating the DijkstraTable with the 
 * outcome. After the function is called, the DijkstraTable will be inspected to 
 * determine whether the algorithm has been completed successfully. 
 * 
 * Upon receipt of a valid AdjacencyList, you can assume that the structure and 
 * content of the list will be valid in terms of the edge information it contains,
 * i.e., it will be ready to use. There may be other validations that you need to 
 * consider elsewhere in this function though.
 * 
 * 
 * Upon receipt of a valid DijkstraTable as an input into your function, 
 * the first thing your function must do is initialize the content of the 
 * table ready for use. You will see an example of this in the lectures, 
 * but the initialization is as follows: each node to be marked as 
 * unvisited (visited set to ‘false’); each node to have its distance set 
 * to a large number (there is a constant defined for this: VERY_LARGE_NUMBER); 
 * each node to have no predecessor recorded (set predecessor to -1). 
 * Your function should then commence from there with any preliminary 
 * initializations for the given starting vertex in the graph, 
 * before entering the main algorithm routine. 
 * 
 * The function should return SUCCESS or an error code.
 */
int doDijsktraAlgorithmOnAdjacencyList(AdjacencyList *pList, DijkstraTable *pTable, int startNode)
{
        //validate inputs
        if(pList == NULL || pTable == NULL || startNode < 0){

                return INVALID_INPUT_PARAMETER;
        }
        //initialise pTable to default values using default values
         
        int i;
        for(i = 0; i < NUMBER_OF_VERTICES; i++){
                pTable->table[i].visited = false;
                pTable->table[i].distance = VERY_LARGE_NUMBER;
                pTable->table[i].predecessor = -1;

        }
        //declare variables
        int currentNode = startNode;
        int j;
        bool finished = false;

	//allocate memory for new variable and initialise its fields
	   ListNode *aPtr = (ListNode*)myMalloc(sizeof(ListNode)); 
	   if (aPtr == NULL){
        	return MEMORY_ALLOCATION_ERROR;
   		}


        //initialise distance from starting node
        pTable->table[currentNode].distance = 0;
        
        while(finished == false){
        //loop through iterate through the row of adjacency matrix which is the starting node
        for(j = 0; j < NUMBER_OF_VERTICES; j++){
                //if there is an edge and hasn't been visited
		//
		aPtr = pList->adjacencyList[currentNode];
		do{

		if(aPtr->weight > 0 && pTable->table[currentNode].visited == false){
                        
                        //distance to node j 
                        int dToNode = pTable->table[currentNode].distance + aPtr->weight;

                        //check if new distance found is shorter
                        if(dToNode < pTable->table[j].distance){           
                                pTable->table[j].distance = dToNode;       
                                pTable->table[j].predecessor = currentNode;
                        }
			aPtr = aPtr->next;
			}
                }while(aPtr != NULL);

                
        }
        //set currentNode to visited
        pTable->table[currentNode].visited = true;

        int shortestSoFar = VERY_LARGE_NUMBER;
        int whichNode = -1;
        
        //for loop to traverse through the nodes on the table 
        for(i = 0; i < NUMBER_OF_VERTICES; i++){
                //if node is not visited and the distance is shorter than the shortestSoFar
                if (pTable->table[i].visited == false && pTable->table[i].distance < shortestSoFar){
                        //update values
                shortestSoFar = pTable->table[i].distance;
                whichNode = i;

                }
        
	}
        
 //set currentNode to the one just explored
        if(whichNode != -1){
                currentNode = whichNode;
        }
        //otherwise finished becomes true
        else{
                finished = true;
        	}
	}
        
        
        return SUCCESS;
        
}   

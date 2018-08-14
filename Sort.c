#pragma message("Pragma once? Pragma twice! *wink wink*")

#include <stdio.h>
#include <stdlib.h>

/*All functions sort from min to max, and currently handle only integer numbers. */

void bubblesort(double* l, int size) {
	/*Simplest sorting function. Only compares the number immediately after, and swaps numbers if number after is less. Does this until no iterations are recorded.*/
	int count = -1,i;
	double a;
	while (count != 0) { /*Checks to see if any modifications to the list have been made. If none, exits.*/
		count = 0;
		for (i = 0; i < size-1; i++) {
			if (l[i] > l[i+1]) {
				a = l[i]; //TEMP VAR
				l[i] = l[i+1];
				l[i+1] = a;
				count++;
			}
		}
	}
	puts("Function bubblesort executed\n"); //DEBUG
}

void selectionsort(double* l, int size) {
	int a,b, index;
	double min;
	for (a = 0; a < size-1; a++) {
		min = l[a];
		index = a;
		for (b = a + 1; b < size; b++) {
			if (l[b] < min) {
				min = l[b];
				index = b;
			}
		}
		l[index] = l[a];
		l[a] = min;
	}
	puts("Function selectionsort executed"); //DEBUG
}

void insertionsort(double* l, int size) {
	unsigned short int x, y, increment, size2, z;
	char check1, check2, count;
	double temp, temp2; 
	for (x = 1; x < size; x++) { //Selects an element going through the length of the list.
		//y = x; (DEPRECATED: Old insertionsort algorithm)
		
		y = x / 2; // Start index at middle of sorted part of list (left part)
		increment = (x / 4 == 0? 1: x / 4);  // Ensure increment is at least 1.
		check1 = 0; check2 = 0;
		
		for (increment; y > 0 && y < x; increment = (increment == 1? increment: increment / 2)) {
		// Adjusts index y until suitable place for value in x can be found
			
			if (check1 && check2) { // Check 1 and Check 2 => whether or not binary search found a place within the array for the element to go in.
				break;
			}
			else if (l[x] < l[y]) {
				y -= increment; 
				if (increment == 1) check1++;				
			}
			else if (l[x] > l[y]) {
				y += increment; 
				if (increment == 1) check2++;
			}
			else { //This is for l[y] == l[x]
				break;
			}
		}
		if (x == y) { //Means no changes are necessary and the element is in the right place.
			continue;
		}
		else if (l[x] >= l[y]) { //So there's 1 less element to shift right for case where both equal
		    y++;
		}
		
		/* DEPRECATED: Old insertionsort algorithm; linear search, linear time.
		while (y > 0 && l[y-1] > l[x]) { //Compares the selected element with the ones before it. Cand short-circuit evaluation.
			y--; 
		}
		if (y == x) {
			continue;
		}
		*/
		//Places value in correct slot, and shifts other values right until index x is reached.
		temp = l[y]; //Save the y-value for later assignment.
		l[y] = l[x];//Store the x-value at the y-value position.
		
		count = 0;
		for (z = y+1; z <= x; z++) { 
		/*Need 2 temp variables to handle shifting all the elements 1 unit towards and until the old position of the y-element.*/
			switch (count) {
				case 0:
					temp2 = l[z]; // Simpler method exists, but I prefer this approach since it's more well-structured.
					l[z] = temp;
					count = 1;
					break;
				case 1:
					temp = l[z];
					l[z] = temp2;
					count = 0;
					break;
			}
		}
	}
	puts("Function insertionsort executed"); //DEBUG
}

void mergesort(double *l, int size) {
    /*First part is to divide. 2nd part is to conquer. Uses recursion
	This function also uses insertionsort to merge the arrays together.
	*/
	int size2 = size / 2, i; // Size2 describes the size of the 1st subarray.
	double * arr1, * arr2; // Sub-arrays to sort.
	
	/*
	if (size2 < 1) { // Once there would only be a single element in the array passed through, start combining the arrays.
		return;
	}
	*/
	// Divide. Split arrays into subarrays and pass them recursively back into the function for them to get sorted.
	
	arr1 = (double*) calloc(size2, sizeof(double));
	arr2 = (double*) calloc(size-size2, sizeof(double)); // Handles arrays with odd number of elements.
		
	for (i = 0; i < size2; i++) {// Store values in 1st array.
		arr1[i] = l[i]; 
		printf("%lf ", arr1[i]);//DEBUG
	}
	mergesort(arr1, size2); // Modify the 1st sub-array so it's in sort-order
	
	for (i = size2; i < size; i++) {// Store values in 2nd array.
		arr2[i-size2] = l[i];
		printf("%lf ", arr2[i-size2]);//DEBUG
	}	
	mergesort(arr2, size-size2);// Modify the 2nd sub-array so it's in sort-order

	// Conquer. Take sorted 2nd subarray, compare elements to sorted 1st array elements and modify array based on positioning of subarrays. Use binary search for quick indexing.
	
	int index, j, sizetemp;
	double max = LONG_MIN;
	
	// Inserting elements in 1nd subarray into elements in 1st subarray as convention.
	for (i = 0; i < size2; i++) {// Stores values in 1st subarray into the first few elements of the array.
		l[i] = arr1[i];	
	}
	
	for (i = 0; i < size-size2; i++) {
		
		index = size2; // Reset index.
		
		for (j = size2; j < 1; j/=2) { // Binary Search algorithm. j represents the index offset for the element to be compared.
			//Edge cases
			if (arr2[i] <= arr1[0]) {
				index = 0;
				break;
			}
			else if (arr2[i] >= arr1[size2-1]){
				index = size2-1;
				break;
			}
			
			//Actual binary search
			if (arr1[index] == arr2[i]) {
				index++; // Index + 1 by convention where to insert next value in.
				break; 
			}
			else if (arr1[index] > arr2[i]) {
				index-=j; // If arr2 element is less than arr1 element, move the index left of partition.
			}
			else if (arr1[index] < arr2[i]){ // Move index to right of partition.
				index+=j;
			}
		}
		size2++; // Original array will have more sorted elements for each iteration.
		
	}
	
	//Cleanup
	free(arr1);
	free(arr2);
}

int main(void) {
	int size, i;
	double *list;
	char choice;
	FILE *f = fopen("Sort.txt","a+"); /*r+ gives it permission to write AND read, and a+ = read and append.*/
	if (f == NULL) {
		printf("Cannot find the file specified.");
		return(-1);
	}

	fscanf(f,"%d",&size);

	list = (double*) calloc(size, sizeof(double));

	for (i = 0; i < size; i++) {
		fscanf(f,"%lf",&list[i]);
	}

	puts("Please choose how you want to sort the list ('b' for bubblesort, 's' for selectionsort, 'i' for insertionsort, 'm' for mergesort): ");
	scanf("%c",&choice);

	switch (choice) {
		case 'b':
			bubblesort(list,size);
			break;
		case 's':
			selectionsort(list,size);
			break;
		case 'i':
			insertionsort(list,size);
			break;
		case 'm':
		    mergesort(list,size);
			break;
		default:
			puts("invalid value, please run the program again.");
			return(-1);
	}

	//fflush(f);/*Allows program to change from read mode to append mode. */
	/*rewind(f); Sets the file reader back to the beginning*/

	fseek(f, 1, SEEK_END); /*Tells the program to start writing at this point of the file, on a new line.*/
	fprintf(f,"\n[");//FORMAT
	for (i = 0; i < size; i++) {
		fprintf(f,"%.4lf",list[i]);
		if (i == size-1) {
			break; //FORMAT
		}
		fprintf(f,", ");
	}
	fprintf(f,"]");//FORMAT

	free(list);
	fclose(f);
	return(0);
}
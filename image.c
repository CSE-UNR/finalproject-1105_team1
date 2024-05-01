// Authors: Kassie Jeffery and Manuel Gonzalez
// Date: 4/29/24
// Purpose: Image Processing
#include<stdio.h>
#define CAPACITY 500

void saveImage(FILE* fptr, int rows, int cols, int colCapacity, int image[][colCapacity]);
int loadImage(FILE* fptr, int* cols, int colCapacity, int image[][colCapacity]);
void displayImage(int irow, int cols, int image[][CAPACITY]); 
int editMenu(); 
int cropImage(int cropRowStart, int cropRowEnd, int cropColStart, int cropColEnd, int rows, int* cols, int colCapacity, int image[][colCapacity]);
void dimImage(int irow, int cols, int image[][CAPACITY]);
void brightenImage(int irow, int cols, int image[][CAPACITY]);

int main() {
    int userchoice1,userchoice2, image[CAPACITY][CAPACITY], cols, irow;
    char userfile[50], usersave, usersavedfile[50];	
    FILE *fptr, *fptr2;											//fptr1 = loaded file, fptr2 = user saved file
    
    do{
    printf("**IMAGE PROCESSOR**\n");
    printf("1: Load image\n");
    printf("2: Display image\n");
    printf("3: Edit image\n");
    printf("0: Exit\n\n");
    printf("Choose from one of the options above: ");
    scanf("%d", &userchoice1);
    
    if(userchoice1 == 1){
        printf("What is the name of the image file? ");
        scanf("%s", userfile);
        
        fptr = fopen(userfile, "r");
        if(fptr == NULL){
            printf("Could not find image with that filename.\n");
        }
        else{
        irow = loadImage(fptr, &cols, CAPACITY, image);
        printf("\nImage successfully loaded!\n\n");
        }
    }
    else if(userchoice1 == 2){
         fptr = fopen(userfile, "r");
        if(fptr == NULL){
            printf("Sorry, no image to display\n");
        }
        else{
        displayImage(irow, cols, image); 
        }
    }
    else if(userchoice1 == 3){
        fptr = fopen(userfile, "r");
        if(fptr == NULL){
            printf("Sorry, no image to edit\n");
            
        }
        else{
        userchoice2 = editMenu();
            if(userchoice2 == 1){
                printf("RUN CROP IMAGE FUNCTION HERE\n");
            }
            else if(userchoice2 == 2){
                
                dimImage(irow, cols, image);			  					//Dims the image
                printf("Would you like to save the file? (y/n) ");
                scanf(" %c", &usersave);								//Store users option
               
                if(usersave == 'y'){
                    printf("What do you want to name the image file? (include the extension) ");	//Ask user for file name if they enter 'y'
                    scanf("%s", usersavedfile);								//Save users filename in an array
                    
                    fptr2 = fopen(usersavedfile, "w");							//Open the file for writing
                    if(fptr2 == NULL){									//Best practice
                        printf("Could not open file\n");
                    }
                    saveImage(fptr2, irow, cols, CAPACITY, image);					//Call Save Image function
                    printf("\nImage Successfully saved!\n\n");						//Success Message
                    fclose(fptr2);									//Close the file 
                    irow = loadImage(fptr, &cols, CAPACITY, image);   					//Resets image back to original image
                }
                else{
                    irow = loadImage(fptr, &cols, CAPACITY, image);  					//Resets image back to original image if it is not saved
                }
            }
            else if(userchoice2 == 3){
            
                brightenImage(irow, cols, image);			  				//Dims the image
                printf("Would you like to save the file? (y/n) ");
                scanf(" %c", &usersave);
               
                if(usersave == 'y'){
                    printf("What do you want to name the image file? (include the extension) ");
                    scanf("%s", usersavedfile);
                    
                    fptr2 = fopen(usersavedfile, "w");
                    if(fptr2 == NULL){
                        printf("Could not open file\n");
                    }
                    saveImage(fptr2, irow, cols, CAPACITY, image);
                    printf("\nImage Successfully saved!\n\n");
                    fclose(fptr2);
                    irow = loadImage(fptr, &cols, CAPACITY, image);   					//Resets image back to original image after file is closed
                }
                else{
                    irow = loadImage(fptr, &cols, CAPACITY, image);   					//Resets image back to original image if it is not saved
                }
            }
            else if("RETURN USER BACK TO MAIN MENU\n");	 						//This one was confusing because of how it works in the executable Erin provided
        }
        
    }
    
    }while (userchoice1 != 0);
    fclose(fptr);


//Notes: 4-30-24
   //Using the syntax in the imgdata file you provided the displayImage() function works, but it only works when there is spaces between the numbers. i tried using Erin's executable file example and it only counted it as one single column, so it ended up printing the whole 500x500 array.
   
//I Used the executable Erin provided as the basis for what i coded, so feel free to compare them and change stuff if you notice something is off (i stayed up coding and i was pretty tired so i probably made some mistakes somewhere). 

//From what i tested in the code, so far it works and there are just a couple things to fix so it can match the executable. there are still some parts to finish like implementing the crop function into the main and  converting the numbers into symbols ( such as 0 = space, 2 = the letter o, etc). i will try to work more on it wednesday night but if not for sure thursday night. For the most part though we are almost done.







   /*
   NOTES:
   saveImage(), loadImage(), and cropImage() are all tested and functional
   we forgot to add an editMenu() function but since that was included in our plan for the main function I'll leave that to you
   since file opening is connected with io (prompting for a filename) I left that out of the loading and saving functions
   and since cropImage needs input that should go in the editMenu() function as well
   null termination is no longer implemented in the array so there is both a rows and cols int which store the size of the image
   however, there *is* null termination in the way the file is saved, i.e., at the end of every row there's written a -1
   these values are not used other than the identify row ends but it's important if you want to create your own images for testing
   just see the imgdata.txt file for the syntax
   email me or leave a comment if you need anything
   */   
}

void saveImage(FILE* fptr, int rows, int cols, int colCapacity, int image[][colCapacity]) {
    // Iterate through every pixel
    for (int irow = 0; irow < rows; irow++) {
        for (int icol = 0; icol < cols; icol++) {
            // Store the current pixel brightness value
            fprintf(fptr, "%d ", image[irow][icol]);
        }
        // "null-terminate" with -1's to indicate the end of a row
        fprintf(fptr, "-1\n");
    }
}

int loadImage(FILE* fptr, int* cols, int colCapacity, int image[][colCapacity]) {
    int irow, icol;
    irow = icol = 0;
    // Reads values while they're found
    while (fscanf(fptr, "%d", &image[irow][icol]) == 1) {
        if (image[irow][icol] == -1) {
            // If the end of a row is reached, reset to the start of the next row
            if (irow == 0) {
                // Assigns the new number of columns (checks if it's the first row to avoid multiple assignments)
                *cols = icol;
            }
            icol = 0;
            irow++;
        } else {
            // Otherwise move to the next item in the row
            icol++;
        }
    }
    // Return the new image height
    return irow;
}

void displayImage(int irow, int cols, int image[][CAPACITY]){
    for(int i = 0; i < irow; i++){
        for(int j = 0; j < cols; j++){
            printf("%d", image[i][j]);
        }
        printf("\n");
    }
}
int editMenu(){
    int userchoice2;
    
    printf("**EDITING**\n");
    printf("1: Crop image\n");
    printf("2: Dim image\n");
    printf("3: Brighten image\n");
    printf("0: Return to main menu\n\n");
    
    printf("Choose from one of the options above: ");
    scanf("%d", &userchoice2);
    
    return userchoice2;
    
}

int cropImage(int cropRowStart, int cropRowEnd, int cropColStart, int cropColEnd, int rows, int* cols, int colCapacity, int image[][colCapacity]) {
    // Check to see if the start and end indexes are backwards
    if (cropRowStart >= cropRowEnd || cropColStart >= cropColEnd) {
        printf("Starting rows and columns must come before ending rows and columns!\n");
        printf("Terminating image cropper\n");
        return rows;
    }
    
    // Checks to see if start indexes are less than 0
    if (cropRowStart < 0 || cropColStart < 0) {
        printf("Starting row and column must be at least 1!\n");
        printf("Terminating image cropper\n");
        return rows;
    }
    
    // Checks to see if end indexes are within the image
    if (cropRowEnd > rows || cropColEnd > *cols) {
        printf("Ending row and column must be within the image!\n");
        printf("Terminating image cropper\n");
        return rows;
    }
    
    // Account for 0 indexing (endpoints are exclusive in for loops so those don't need to be corrected)
    cropRowStart--;
    cropColStart--;

    // Calculate some general stats of the new image (namely the new height and width)
    int width, height;
    width = cropColEnd-cropColStart;
    height = cropRowEnd-cropRowStart;
    
    /* This section is slightly unintuitive, essentially it simultaneously iterates in an area the size of the cropped image
    starting at the top left (as with normal 0-indexing) where images are normally stored. While it does so, it reads the
    data from the crop which the user chose to the non-offset section. */
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            image[row][col] = image[row+cropRowStart][col+cropColStart];
        }

    }
    
    // Sets the new number of columns
    *cols = width;
    
    // Return the new number of rows for external use
    return height;
}
void dimImage(int irow, int cols, int image[][CAPACITY]){
    for(int i = 0; i < irow; i++){
        for(int j = 0; j < cols; j++){
            image[i][j]--;					//Subtracts one from each "pixel"
         
        }
    }
    displayImage(irow, cols, image);				//Needs to display "new" image
}
void brightenImage(int irow, int cols, int image[][CAPACITY]){
    for(int i = 0; i < irow; i++){
        for(int j = 0; j < cols; j++){
            image[i][j]++;					//adds one to each "pixel"
         
        }
    }
    displayImage(irow, cols, image);				//Needs to display "new" image
}




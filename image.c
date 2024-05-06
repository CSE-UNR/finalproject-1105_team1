// Authors: Kassie Jeffery and Manuel Gonzalez
// Date: 4/29/24
// Purpose: Image Processing
#include<stdio.h>
#include<stdbool.h>
#define CAPACITY 500
#define FILENAME_SIZE 50

void saveImage(FILE* fptr, int rows, int cols, int image[][CAPACITY]);
int loadImage(FILE* fptr, int* cols, int image[][CAPACITY]);
int brighIntToChar(char brightness);
char pixelChar(int brightness);
void displayImage(int rows, int cols, int image[][CAPACITY]); 
void editMenu(int* rows, int* cols, int image[][CAPACITY]); 
int cropImage(int cropRowStart, int cropRowEnd, int cropColStart, int cropColEnd, int rows, int* cols, int image[][CAPACITY]);
void dimImage(int rows, int cols, int image[][CAPACITY]);
void brightenImage(int rows, int cols, int image[][CAPACITY]);

int main() {
    int selection, image[CAPACITY][CAPACITY], img_cols, img_rows;
    char filename[FILENAME_SIZE];
    bool file_loaded = false;
    FILE* fptr;
    
    do {
        printf("\n *** IMAGE PROCESSOR ***\n");
        printf("1: Load image\n");
        printf("2: Display image\n");
        printf("3: Edit image\n");
        printf("0: Exit\n\n");
        printf("Choose from one of the options above: ");
        scanf("%d", &selection);
        
        if (selection == 1) {
            printf("What is the name of the image file? ");
            scanf("%s", filename);
            
            fptr = fopen(filename, "r");
            if (fptr == NULL) {
                printf("\"%s\" file not found.\n", filename);
                return 1;
            } else{
                img_rows = loadImage(fptr, &img_cols, image);
                fclose(fptr);
                printf("Image successfully loaded\n");
                file_loaded = true;
            }
        } else if (selection != 2 || selection != 3) {
            if (!file_loaded) {
                printf("No image is currently loaded.\n");
            } else if (selection == 2) {
                displayImage(img_rows, img_cols, image);
            } else if (selection == 3) {
                editMenu(&img_rows, &img_cols, image);
            }
        } else if (selection != 0) {
            printf("Invalid input.\n");
        }
    } while (selection != 0);
    printf("Exiting program.\n");
}

void editMenu(int* rows, int* cols, int image[][CAPACITY]){
    int menu_option, cropBounds[4];
    char selection, filename[FILENAME_SIZE];
    FILE* fptr;
    
    do {
        printf("\n *** IMAGE EDITOR ***\n");
        printf("1: Crop image\n");
        printf("2: Dim image\n");
        printf("3: Brighten image\n");
        printf("0: Return to main menu\n\n");
        
        printf("Choose from one of the options above: ");
        scanf("%d", &menu_option);
        
        if (menu_option == 1) {
            printf("Please enter the starting row (1+): ");
            scanf("%d", &cropBounds[0]);
            printf("Please enter the ending row (1+): ");
            scanf("%d", &cropBounds[1]);
            printf("Please enter the starting column (1+): ");
            scanf("%d", &cropBounds[2]);
            printf("Please enter the ending column (1+): ");
            scanf("%d", &cropBounds[3]);
            *rows = cropImage(cropBounds[0], cropBounds[1], cropBounds[2], cropBounds[3], *rows, cols, image);
        } else if (menu_option == 2) {
            dimImage(*rows, *cols, image); //Dims the image
        } else if (menu_option == 3) {
            brightenImage(*rows, *cols, image); //Dims the image
        } else if (menu_option != 0) {
            printf("Invalid input.\n");
        }
        
        // If the image was edited
        if (menu_option == 1 || menu_option == 2 || menu_option == 3) {
            printf("New Image:\n\n");
            displayImage(*rows, *cols, image);
            printf("\nSave changes to a file (y/n)? ");
            scanf(" %c", &selection);
            
            if (selection == 'y') {
                printf("Enter the filename: ");
                scanf("%s", filename);
                
                fptr = fopen(filename, "w");
                if (fptr == NULL) {
                    printf("Couldn't open \"%s\", changes not saved.\n", filename);
                } else {
                    saveImage(fptr, *rows, *cols, image);
                    fclose(fptr);
                    printf("\nImage successfully saved\n");
                }
                
                printf("New Image:\n");
                displayImage(*rows, *cols, image);
                
                printf("Returning to main menu.\n");
                return;
            }
        }
    } while (menu_option != 0);
    printf("Returning to main menu.\n");
}

void saveImage(FILE* fptr, int rows, int cols, int image[][CAPACITY]) {
    // Iterate through every pixel
    for (int irow = 0; irow < rows; irow++) {
        for (int icol = 0; icol < cols; icol++) {
            // Store the current pixel brightness value
            fprintf(fptr, "%d", image[irow][icol]);
        }
        if (irow != rows-1) {
            fprintf(fptr, "\n");
        }
    }
}

int loadImage(FILE* fptr, int* cols, int image[][CAPACITY]) {
    int icol, irow;
    icol = irow = 0;
    char pixel;
    
    // Reads values while they're found
    while (fscanf(fptr, "%c", &pixel) == 1) {
        if (pixel == '\n') {
            if (irow == 0) {
                *cols = icol;
            }
            irow++;
            icol = 0;
        } else {
            image[irow][icol] = brighIntToChar(pixel);
            icol++;
        }
    }
    
    // Return the new image height
    return irow+1;
}

int brighIntToChar(char brightness) {
    switch (brightness) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
    }
}

char pixelChar(int brightness) {
    switch (brightness) {
        case 0:
            return ' ';
        case 1:
            return '.';
        case 2:
            return 'o';
        case 3:
            return 'O';
        case 4:
            return '0';
    }
}

void displayImage(int rows, int cols, int image[][CAPACITY]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%c ", pixelChar(image[i][j]));
        }
        printf("\n");
    }
}

int cropImage(int cropRowStart, int cropRowEnd, int cropColStart, int cropColEnd, int rows, int* cols, int image[][CAPACITY]) {
    // Check to see if the start and end indexes are backwards
    if (cropRowStart >= cropRowEnd || cropColStart >= cropColEnd) {
        printf("Starting rows and columns must come before ending rows and columns!\n");
        printf("Terminating image cropper\n");
        return rows;
    }
    
    // Checks to see if start indexes are less than 0
    if (cropRowStart < 1 || cropColStart < 1) {
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

void dimImage(int rows, int cols, int image[][CAPACITY]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            image[i][j]--; // Decreases the brightness of each pixel
            if (image[i][j] < 0) {
                image[i][j] = 0;
            }
        }
    }
}

void brightenImage(int rows, int cols, int image[][CAPACITY]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            image[i][j]++; // Increases the brightness of each pixel
            if (image[i][j] > 4) {
                image[i][j] = 4;
            }
        }
    }
}




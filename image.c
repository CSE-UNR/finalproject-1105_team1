// Authors: Kassie Jeffery and Manuel Gonzalez
// Date: 4/29/24
// Purpose: Image Processing
#include<stdio.h>
#define CAPACITY 500

void saveImage(FILE* fptr, int rows, int cols, int colCapacity, int image[][colCapacity]);
int loadImage(FILE* fptr, int* cols, int colCapacity, int image[][colCapacity]);
int cropImage(int cropRowStart, int cropRowEnd, int cropColStart, int cropColEnd, int rows, int* cols, int colCapacity, int image[][colCapacity]);

int main() {
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

// Authors: 
// Date: 
// Purpose: Image Processing
#include<stdio.h>

void saveImage(FILE* fptr);
int loadImage(FILE* fptr);
int cropImage(int colCapacity, int image[][colCapacity]);

int main() {

}

void saveImage(FILE* fptr, int rows, int colCapacity, int image[][colCapacity]) {
    for (int irow = 0; irow < rows; irow++) {
        for (int icol = 0; image[irow][icol] != -1; icol++) {
            fprintf("%d ", image[irow][icol]);
        }
        fprintf("-1\n");
    }
}

int loadImage(FILE* fptr, int colCapacity, int image[][colCapacity]) { // Returns the new number of rows in the image
    int irow, icol;
    irow = icol = 0;
    while (fscanf("%d", &image[irow][icol]) != 0) {
        icol++;
        if (image[irow][icol] == -1) {
            icol = 0;
            irow++;
        }
    }
    return irow+1;
}

int cropImage(int colCapacity, int image[][colCapacity]) { // Returns the new number of rows in the image
    int cropRowStart, cropRowEnd, cropColStart, cropColEnd;
    printf("At which row should the cropped image begin? ");
    scanf("%d", &cropRowStart);
    printf("At which row should the cropped image end? ");
    scanf("%d", &cropRowEnd);
    printf("At which column should the cropped image begin? ");
    scanf("%d", &cropColStart);
    printf("At which column should the cropped image end? ");
    scanf("%d", &cropColEnd);
    
    cropRowStart--;
    cropRowEnd--;
    cropColStart--;
    cropColEnd--;

    int width, height;
    width = cropColEnd-cropColStart;
    height = cropRowEnd-cropRowStart;
    
    for (int row = 0; rowOffset < height; rowOffset++) {
        image[row] = image[row+cropRowStart];
        for (int col = 0; colOffset < width; colOffset++) {
            image[row][col] = image[row][col+cropColStart];
        }
        image[row][cropColStart+1] = -1;
    }
    
    return height;
}

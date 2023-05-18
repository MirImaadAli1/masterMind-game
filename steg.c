#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define pic struct Pixel

/* The RGB values of a pixel. */
struct Pixel
{
    int red;
    int green;
    int blue;
};

/* An image loaded from a PPM file. */
struct PPM
{
    // initialising variables
    int width, height, max;
    // creating variable that is a pointer
    pic **pix_details;
    // initialising array of size 3
    char *ppmHeader;

    /* TODO: Question 1 */
};
/* An image loaded from a PPM file. */
struct PPM *getPPM(FILE *f)
{
    // Allocates memory for a struct PPM and assign a pointer to variable 'store'
    struct PPM *store = (struct PPM *)malloc(sizeof(struct PPM));
    store->ppmHeader = (char *)malloc(sizeof(char)*3);
    fscanf(f, "%s", store->ppmHeader);
    // reads from f and stores it in width member of Struct PPM
    fscanf(f, "%d", &store->width);
    // reads from f and stores it in height member of Struct PPM
    fscanf(f, "%d", &store->height);
    // reads from f and stores it in max member of Struct PPM
    fscanf(f, "%d", &store->max);

    // checks if ppmheader is of type P6 and if its true then executes through this loop
    if (strcmp(store->ppmHeader, "P6") == 0)
    {
        //fscanf("P3", "%s", store->ppmHeader);
        store->ppmHeader = "P3";
        // allocates memory for 2d array of pointers with 1 dimension being defined
        //fgets(NULL,1,f);
        //fseek( f,1,SEEK_CUR);
        fscanf("%*c",f);
        fscanf("%*c",f);
        store->pix_details = (pic **)malloc(sizeof(pic *) * store->width);
        // initialising varibles
        int x, y;
        int maxsize = 1;
        if(store->max>=256){
            maxsize = 2;
        }
        // executing for loop to iterate through rows and columns
        for (x = 0; x < store->width; x++)
        {
            store->pix_details[x] = (pic *)malloc(sizeof(pic) * store->height);
            // two-dimensional array of pointers to 'pic' structures, pointed to by 'store->pix_details'.
            for (y = 0; y < store->height; y++)
            {
                // Reads a single byte of data from the file pointed to by 'f', and stores it in the 'red' member of pix_details
                fread(&(store->pix_details[x][y].red), maxsize, 1, f);
                // Reads a single byte of data from the file pointed to by 'f', and stores it in the 'green' member of pix_details
                fread(&(store->pix_details[x][y].green), maxsize, 1, f);
                // Reads a single byte of data from the file pointed to by 'f', and stores it in the 'blue' member of pix_details
                fread(&(store->pix_details[x][y].blue), maxsize, 1, f);
            }
        }
    }
    // checks if ppmheader is of type P3 and if its true then executes through this loop
    else if (strcmp(store->ppmHeader, "P3") == 0)
    {

        // allocates memory for 2d array of pointers with 1 dimension being defined
        store->pix_details = (pic **)malloc(sizeof(pic *) * store->width);
        // initialising varibles
        int x, y;
        // executing for loop to iterate through rows and columns
        for (x = 0; x < store->width; x++)
        {
            store->pix_details[x] = (pic *)malloc(sizeof(pic) * store->height);
            // two-dimensional array of pointers to 'pic' structures, pointed to by 'store->pix_details'.
            for (y = 0; y < store->height; y++)
            {
                // Reads an integer value from the file pointed to by 'f', and stores it in the 'red'
                fscanf(f, "%d", &(store->pix_details[x][y].red));
                // Reads an integer value from the file pointed to by 'f', and stores it in the 'green'
                fscanf(f, "%d", &(store->pix_details[x][y].green));
                // Reads an integer value from the file pointed to by 'f', and stores it in the 'blue'
                fscanf(f, "%d", &(store->pix_details[x][y].blue));
            }
        }
    }
    /* TODO: Question 2a */
    return store;
}

/* Write img to stdout in PPM format. */
void showPPM(const struct PPM *img)
{
    if (img->ppmHeader == NULL)
    {
        printf("Error: PPM header is NULL\n");
        return;
    }
    // prints the value of ppmheader memeber of img
    printf("%s\n", img->ppmHeader);
    // prints the value of width memeber of img
    printf("%d ", img->width);
    // prints the value of height memeber of img
    printf("%d\n", img->height);
    // prints the value of max memeber of img
    printf("%d\n", img->max);

    // executes for loop that iterates over x coordinate
    for (int x = 0; x < img->width; x++)
    { // executes for loop that iterates over y coordinate
        for (int y = 0; y < img->height; y++)
        {
            // makes pixel of type struct Pixel and assigns it the value of the pixel (x,y)
            struct Pixel pixel = img->pix_details[x][y];
            // prints the red, green and blue values of the pixel
            printf("%i %i %i \n", pixel.red, pixel.green, pixel.blue);
        }
    }

    /* TODO: Question 2b */
}

/* Opens and reads a PPM file, returning a pointer to a new struct PPM.
 * On error, prints an error message and returns NULL. */
struct PPM *readPPM(const char *filename)
{
    /* Open the file for reading */
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        fprintf(stderr, "File %s could not be opened.\n", filename);
        return NULL;
    }

    /* Load the image using getPPM */
    struct PPM *img = getPPM(f);

    /* Close the file */
    fclose(f);

    if (img == NULL)
    {
        fprintf(stderr, "File %s could not be read.\n", filename);
        return NULL;
    }

    return img;
}

/* Encode the string text into the red channel of image img.
 * Returns a new struct PPM, or NULL on error. */
struct PPM *encode(const char *text, const struct PPM *img)
{
    //img->ppmHeader[1] = '3';
    int a = rand() % img->width;
    // intialising variable of value 0
    int b = 0;
    // intialising variable of value 0
    int x = 0;
    // // intialising variable of value 0
    int maxSize = 0;

    // executing conditional loop if length of text is equal to 0 then
    if (strlen(text) == 0)
    {
        // print statement
        fprintf(stderr, "Message is empty\n");
        // return null value
        return NULL;
    }

    // executing conditional loop if length of text is more than the max size of img then
    if ((img->width * img->height) < strlen(text))
    {
        // print statement
        fprintf(stderr, "Message is too long \n");
        // return null value
        return NULL;
    }
    else
    {
        // set value of 'maxSize' to max size of the img divided by length of text
        maxSize = (img->width * img->height) / strlen(text);
    }
    // executing while loop based on the condition that the variable 'x' value remains below the length of text
    while (x < strlen(text))
    {
        // executing for loop that will iterate through an array which has a size of 'maxSize' as long as the current character does not signify the end
        for (int y = 0; y < maxSize && text[x] != '\0'; y++)
        {
            // red value of a pixel in an image is assigned to the current character in text
            img->pix_details[a][b].red = text[x];

            // increment to move on to next pixel
            b++;
            // increment to move on to next pixel
            a = (a + 1) % img->width;

            if (a == 0)
            {
                b++;
            }

            // increment to move on to next character
            x++;
        }
        // maxSize is calculated as the maximum number of characters that can still be encoded in the img without going out of bound.
        maxSize = ((img->width * img->height) - b) / (strlen(text) - x + 1);
    }
    // returning img;
    return img;
}

/* Extract the string encoded in the red channel of newimg, by comparing it
 * with oldimg. The two images must have the same size.
 * Returns a new C string, or NULL on error. */
char *decode(const struct PPM *oldimg, const struct PPM *newimg)
{
    
    /* TODO: Question 2d */
    // allocates memory for singular char and assigns it to result
    char *result = (char *)malloc(sizeof(char) * (oldimg->width * oldimg->height));
    // initialising variables and assigns a value of 0
    int x = 0;

    if ((newimg->width * newimg->height) != (oldimg->width * oldimg->height))
    {
        fprintf(stderr, "error");
        return NULL;
    }

    // executing for loop to iterate through rows and columns and every pixel
    for (int i = 0; i < oldimg->width; i++)
    {
        // executing for loop to iterate through columns
        for (int j = 0; j < oldimg->height; j++)
        {
            // if red pixel data of oldimg is not the same as red pixel data of newimg
            if (newimg->pix_details[i][j].red != oldimg->pix_details[i][j].red)
            {
                // assigns result the value of red value of the pixel located at (i,j) as it iterates through the loop
                result[x] = newimg->pix_details[i][j].red;
                // increments
                x++;
            }
        }
    }

    result[x] = '\0';
    return result;
}

/* TODO: Question 3 */
int main(int argc, char *argv[])
{

    /* Initialise the random number generator, using the time as the seed */
    srand(time(NULL));

    /* Parse command-line arguments */
    if (argc == 3 && strcmp(argv[1], "t") == 0)
    {
        /* Mode "t" - test PPM reading and writing */

        struct PPM *img = readPPM(argv[2]);
        showPPM(img);
    }
    else if (argc == 3 && strcmp(argv[1], "e") == 0)
    {
        /* Mode "e" - encode PPM */

        struct PPM *oldimg = readPPM(argv[2]);
        char *message = (char *)malloc(sizeof(char) * (oldimg->width * oldimg->height));
        /* TODO: prompt for a message from the user, and read it into a string */
        fprintf(stderr, "Please enter message\n");
        fgets(message, (oldimg->width * oldimg->height) * sizeof(message), stdin);
        fprintf(stderr, message);
        /* TODO: encode the text into the image with encode, and assign to newimg */
        struct PPM *newimg = encode(message, oldimg);
        showPPM(newimg);
        /* TODO: write the image to stdout with showPPM */
    }
    else if (argc == 4 && strcmp(argv[1], "d") == 0)
    {
        /* Mode "d" - decode PPM */

        /* TODO: get original file filename from argv, load it with
           readPPM, then assign to oldimg */
        struct PPM *oldimg = readPPM(argv[2]);

        /* TODO: get encoded file filename from argv, load it with
           readPPM, then assign to newimg */
        struct PPM *newimg = readPPM(argv[3]);

        /* TODO: decode the encodedPPM with the comparisonPPM and assign to message */
        char *message = malloc(sizeof(char *) * (oldimg->width * oldimg->height));
        message = decode(oldimg, newimg);

        /* TODO: print the decoded message to stdout */
        fprintf(stderr, message);
    }
    else
    {
        fprintf(stderr, "Unrecognised or incomplete command line.\n");
        return 1;
    }

    return 0;
}
# Who I am

- Student ID: <Mir Imaad Ali, e.g. H00379375>

# Program design
Project requires writing a simple steganography program in C, called steg. It can operate in two modes — encode and decode — selected by the first command-line argument being 
e or d. It encodes by iterating through the image , pixel by pixel successively and stores string value in the red value of the pixel. It decodes the ecrypted string by comparing the old image and new generated img and deduces the encryption if they are the sae 

Student has been asked to implement 4 functions in order to achieve 100% functionality, them being:

# Struct pixel 
Delcares and stores variables that in turn store red, green and blue values of a pixel in themselves.

# Struct PPM 
I implement a struct PPM that intialises variables and creates a pointer to a dynamically-allocated array containing the pixel data.
 
# getPPM()
We use fscanf to read values from file 'f' and store it in a dynamically allocated PPM struct. it allocated memory for a PPM struct using malloc() function. It then stores the header, width , height and max value of a PPM image file pointed to by 'store'. It then allocates memory for a 2D array of pointers to 'pic' and defines the first dimension and leaves the second undefined. The code then uses a nested for loop to iterate through each row and column of the image, reading in the red, green, and blue color values for each pixel from the file stream and storing them in the corresponding members of the 'pic' structures in the 2D array pointed to by 'store->pix_details'.

# showPPM()
The function first prints the header information such as ppmheader, width, height, and maximum pixel value. the loop iterates over all the pixels in the image. in each iteration, the function prints the RGB values of the current pixel

# encode()
This function is responsible for encoding the current character in the text file into the red value of a pixel in image. It performs this task by first intialising a variable that has a random value between 0 and the width of the image. We also defined two error conditions to further stabilise and streamline the code. We use a for loop in order to iterate through the array of defined size 'maxSize' which is the total numbers of pixels that can be in an image, we also make sure the loop is only iterated if the current character in text is not the terminating end. We then store the current character in the red value of a pixel of an image, the pixel is picked out randomly. Variables are incremented in order to move to the next pixel and it is made sure that the pixels are successively randomised as shown by ( a = (a + 1) % img->width;), we also increment variable 'x' in order to move to the next character in text file. We also calculate 'maxSize' in the end to find out the maximum number of characters that can still be encoded in the image without it running out of bounds.

# decode()
The function allocates memory for singular character and assigns it to result. It then intialises variable 'x' and assigns it a value of 0. The loop goes through every pixel via iterating through every row and column in 'oldimg' and checks whether the red value of a pixel in 'oldimg' is not the same as the red pixel value of a pixel in newimg. If they are not same , it assigns the red value of the pixel at (i,j) in 'newimg' to the current index of the result array. The function then sets the value of 'result[x]' to '\0' to terminate the string and return the result pointer.

# Choice of data structures and algorithms
2. 2 dimensional based arrays 
2D array contain a grid of values and contain row and columns which i thought would help me implement the functionality better 


1. structs:

they are custom structures that we can use to better define our data. Their properties and structures are easily accessible and implemented

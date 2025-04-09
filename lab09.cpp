// EECS 348 lab 9
// Matrix operator EXPANDED
// INPUT: user file of matrix
// OUT: matrix operations
// Collaborators
    // self (past tense)
// Additionall collaborations
    //GPT or google.
        // if its not specifically stated to be by gpt its by Jordan
// Jordan McCool
/// /3/30/2025


// initial comments
    // need to convert the previous lab with two main changes
    
    // needs to be able to distinguish int vs double (?)
        // double
    // has to be a class instead of a vector ( LAME )
        // not actually sure how classes work in c++
        // iirc its like struct?
            // assignment 5  can be used as a reference for this
    // will likely utilize gpt to speed up the harder sections
        // similar to last assignment, while it would be fun to treat it as a puzzle
            // i cant justify the time commitment to make and THEN test the program
            // when I can just save time having gpt make an initial version and then debug it

// in progress comments
    // since a lot of the functions are the same as the last lab - but just need to be converted to work with this class
        // I am copying their usable lines and modifying them to work with the new class structure
        // I am leaving their original comments too, although it might get a bit confusing ( already is confusing me )

// class comments (pre design - requirements)
    // this class needs to be able to store a matrix in the same way as a 2d vector
        // what if i just make the class consist of a 2d vector? is that allowed?
        // im stuck on this part, if we cant use vectors (2d list) how can we store a dynamic sized array
    // this class ( I THINK ) shouldnt open the file itself when initialized, but needs to be handed it
        // nope !
    // there is a difference between double and int ... 
        // double is just float
            // noted
    // solution to stuckness:
        // im just going to make the class contain a vector as a private variable
            // seems to be what the instructions are getting at
        // also, seems that we can treat the variables as doubles by default

#include <iostream>
        // "declares objects and functions that enable programs to interact with input/output devices like the console"
#include <fstream>
        // Allows file input and output operations
#include <string> // google says i need this for reading string inputs
#include <vector>
        // "a dynamic array - a sequence container that can change in size during runtime - similar to C arrays"
#include <sstream>
        // Allows a method of treating strings as input or output streams
#include <algorithm>
        // includes various prebuilt algorithms
    
        // these are taken from assignment 5, not sure which ones I will use at this point       



#include <iomanip> // this is new to this lab
    // iomanip
        // google:
            // allows for input/output manipulators
            // used here for setw and setprecision
        // neat


// these are just copied from previous labs

// gpt
class Matrix {
    private: // declares the private variable that each instance of the class will have
    int size; // this is just going to be size N
    std::vector<std::vector<double>> data; // the matrix will locally be called data

    public: // these will be the public values 
    Matrix(int n) : size(n), data(n, std::vector<double>(n)) {}
    // initially i wasnt sure how to store double vs int. but instructions seem to say the output can be double
        // and static_cast<double> I THINK should allow us to store an int as a double
        // so it wont matter I THINK

    void set(int i, int j, double value){ // this will be used to write data to the matrix
        data[i][j] = value; // writes a value to the matrix
    }

    double get(int i, int j) const { // this will be used to read a value from the matrix
        return data[i][j]; // reads a value from the matrix
    }

    int getSize() const{ // allows public access to size value
        return size; // returns the size
    }

    // not sure, need comments
    void print() const { // will be used to print the matrix
        for (int i = 0; i < size; ++i) { // for loop
            for (int j = 0; j < size; ++j) { // nested for loop to go through entire matrix
                std::cout << std::setw(8) << std::fixed << std::setprecision(2) << data[i][j]; // what is this
                // from iomanip - says it helps with formatting
                // setw(8)
                    // sets the minimum width of the output field to 8 characters
                        // neat
                // std::fixed
                    // sets cout to display floating numbers as fixed point notation instead of scientific notation
                // std::setprecision(2)
                    // sets the precision of decimal points to 2
                // neat !
            }
            std::cout << std::endl; // iirc this is just a newline
        }
    }
    

    //gpt
    Matrix operator+(const Matrix& other) const { // overloader ?
        // other will be the other matrix
        if (size != other.size) { // checks that the sizes match
            std::cerr << "\nMatrix size mismatch for addition.\n" << std::endl; // error message
            exit(EXIT_FAILURE); // exit if error
        }
    
        Matrix result(size); // creates a result matrix
        for (int i = 0; i < size; ++i) { // 
            for (int j = 0; j < size; ++j) { // nested for loop to go through each value and add them
                result.set(i, j, this->get(i, j) + other.get(i, j)); // uses the operations above to read/write the matrix
            // interesting
                // this is the first matrix input, other is the other one. neat
            }
        }
        return result; // returns the resulting matrix
    }
    // gpt

    Matrix operator*(const Matrix& other) const { // declares * as a matrix operator
        if (size != other.size) { // this ensures that the sizes match
            // technically its rows/column thing needs to match, but since these will both be squares that is irrelevant
            std::cerr << "\nMatrix size mismatch for multiplication.\n" << std::endl; // message
            exit(EXIT_FAILURE); // exits dishonorably
        }
    
        Matrix result(size); // Creates a new matrix for the result - gpt
        // the result size thing allows us to create a blank matrix of the same size

        for (int i = 0; i < size; ++i) { // for loop to fill the result matrix
            for (int j = 0; j < size; ++j) {  // nested loop
                double sum = 0.0; // cross product is the sum of products (basically)
                for (int k = 0; k < size; ++k) { // gets the sums of products of the row vs column
                    sum += this->get(i, k) * other.get(k, j); // math to do so, syntax is explained/similar to operator+
                }
                result.set(i, j, sum); // sets that value to the result matrix
            }
        }
    
        return result; // returns the result
    }
    // 

    // THIS is what will read the file
    // gpt
    static void readfile(Matrix& matrixA, Matrix& matrixB) {
        // needs to be given a .txt file
            // changed this, now this GETS a filename
        //
        std::string filename; // initializes the variable
        std::cout << "\nEnter the name of the file WITH .txt extenstion\n";
        std::getline(std::cin, filename); // stores that input as user

    // above code me - basically taken from lab8
        // gets a input file 
    //
        // and two matrices
            // instructions say the file format will have two matrices as opposed to the one from the previous lab
        std::ifstream file(filename); // creates a (file?) stream from the text file
        if (!file) { // ensures that we find the file
            std::cerr << "\nCannot open file: " << filename << std::endl; // error message
            exit(EXIT_FAILURE); // return failure
        }

        int N, typeFlag; // initializes the two variables we need
        // n is size
        // typeflag is the data type
        file >> N >> typeFlag;
        // reads the first two values from the file, size and type


        if (N <= 0) { // handles a potential eror
            std::cerr << "\nInvalid matrix size.\n" << std::endl; // error message
            exit(EXIT_FAILURE); // exit failure
        }

        matrixA = Matrix(N); //
        matrixB = Matrix(N); //
        // the instructions say the file will have two matrices 


        for (int i = 0; i < N; ++i) { // reads matrix 1
            for (int j = 0; j < N; ++j) { // for loop to go through entire matrix
                if (typeFlag == 0) { // checks value type
                    // 0 is integer type
                    int val; // val will be an integer
                    file >> val; // reads the value from file into val
                    matrixA.set(i, j, static_cast<double>(val)); // writes to the matrix
                    // static_cast<double>
                        // this is a type conversion that allows storing an int into the double
                    // .set allows us to write to the matrix
                } else { // runs if its a double 
                    double val; // assigns val to be a double
                    file >> val; // reads from the file into double
                    matrixA.set(i, j, val); // writes to the matrix
                }
            }
        }

        for (int i = 0; i < N; ++i) { // reads matrix 2
            for (int j = 0; j < N; ++j) { // for loop to go through entire matrix
                if (typeFlag == 0) { // checks value type
                    // 0 is integer type
                    int val; // val will be an integer
                    file >> val; // reads the value from file into val
                    matrixB.set(i, j, static_cast<double>(val));
                    // static_cast<double>
                        // need comment
                    // .set allows us to write to the matrix
                } else { // runs if its a double 
                    double val; // assigns val to be a double
                    file >> val; // reads from the file into double
                    matrixB.set(i, j, val); // writes to the matrix
                }
            }
        }

        file.close(); // closes the file
    }
};

// what is operator overloading ?
    // gpt - is a special function in a class that allows you to redefine how operators work
        // no idea what that means


void add_func(){} // did not need
    // operator overloading ?
    
void mult_func(){} // probably wont need this either
    // operator overloading ?

// jordan and gpt and past self
void sum_diag_func(){
    std::cout << "\nNote: these functions assume you are inputting a file with 2 distinct matrices\n" << std::endl;
    // will be basically the same as lab8
    Matrix A(0), B(0); // "placeholders that allow us to initialize them"
    Matrix::readfile(A, B); // runs the read file thing

    int N = A.getSize();
     // i wonder if int N is going to cause issues with other points where its referred to as N
    int sum1 = 0;
    // I can NOT tell if we are printing the sumS (as in PLURAL) of the two diagonals, or the SUM of the two diagonals
    int sum2 = 0;
    //for (int i = 0; i < N; ++i){
    //    for (int j = 0; j < N; ++j){
    //        if (i == j){
    //            sum1 = sum1 + mat1[i][j];
    //        }
    //    } // in hindsight, i dont even think i need this second loop. could have just done mat1[i][i]
    //} // doing that instead
    for (int i = 0; i < N; ++i){ // gets first diag
        // shape is "\"
        sum1 = sum1 + A.get(i, i); // GOOD catch :)))))))))
        
        // i left the comments from the last lab here, but i dont remember what this means
    }
    for (int i = 0; i < N; ++i){ // gets second  diagonal
        // shape is /
        //sum2 = sum2 + mat1[i][-(i+1)]; this doesnt work :(
            // negative indices dont work like in python
        sum2 = sum2 + A.get(i, N-(i+1)); // actual way to get that last index
    }
    int sum3 = sum1 + sum2; // see above comment about not being sure what exactly it means by sum of diagonals
    std::cout << "\nSum of diagonal 1 from matrix 1 (backslash shape): " << sum1 << std::endl; // cant do "\" in the text string
    std::cout << "\nSum of diagonal 2 from matrix 1 (/ shape): " << sum2 << std::endl;
    std::cout << "\nSum of both:" << sum3 << std::endl; // these print the results

    // above gets the first matrix

    // below is the second matrix
    N = B.getSize();
     // i wonder if int N is going to cause issues with other points where its referred to as N
    sum3 = 0;
    // I can NOT tell if we are printing the sumS (as in PLURAL) of the two diagonals, or the SUM of the two diagonals
    int sum4 = 0;
    //for (int i = 0; i < N; ++i){
    //    for (int j = 0; j < N; ++j){
    //        if (i == j){
    //            sum1 = sum1 + mat1[i][j];
    //        }
    //    } // in hindsight, i dont even think i need this second loop. could have just done mat1[i][i]
    //} // doing that instead
    for (int i = 0; i < N; ++i){ // gets first diag
        // shape is "\"
        sum3 = sum3 + B.get(i, i); // GOOD catch :)))))))))
        
        // i left the comments from the last lab here, but i dont remember what this means
    }
    for (int i = 0; i < N; ++i){ // gets second  diagonal
        // shape is /
        //sum2 = sum2 + mat1[i][-(i+1)]; this doesnt work :(
            // negative indices dont work like in python
        sum4 = sum4 + B.get(i, N-(i+1)); // actual way to get that last index
    }
    int sum5 = sum3 + sum4; // see above comment about not being sure what exactly it means by sum of diagonals
    std::cout << "\nSum of diagonal 1 from matrix 2 (backslash shape): " << sum3 << std::endl; // cant do "\" in the text string
    std::cout << "\nSum of diagonal 2 from matrix 2 (/ shape): " << sum4 << std::endl;
    std::cout << "\nSum of both:" << sum5 << std::endl; // these print the results
    // i think that works
}

// jordan
void swap_rows_func(){
    // lets begin !
    // need polymorphism?
        // the way i have the class set up though means it would work without one ( I THINK )
        // so i think this already works
    
    // i set up the matrix class to use double casts
    // which seems to work similarly to a polymorphism?

    std::cout << "\nNote: This assumes you are inputting two matrices\n Also, this will swap the rows BEWTEEN the two matrices\n" << std::endl;
    Matrix A(0), B(0); // "placeholders that allow us to initialize them"
    Matrix::readfile(A, B); // runs the read file thing

    int row1; // will be used to store value
    int row2; // same
    std::cout << "\nEnter the row of Matrix 1 (0 to N-1):\n" << std::endl;
    std::cin >> row1; // gets the row

    if (row1 < 0 || row1 >= A.getSize()){ // handles index errors
        std::cerr << "\nInvalid index for row1\n";
        return;
    }

    std::cout << "\nEnter the row of Matrix 2 (0 to N-1):\n" << std::endl;
    std::cin >> row2; // gets the row

    if (row2 < 0 || row2 >= B.getSize()){ // handles errors
        std::cerr << "\nInvalid index for row2\n";
        return;
    }
    if (A.getSize() != B.getSize()){ // handles an error
        std::cerr << "\nTheir sizes do not match, cannot swap between the two matrices\n";
        // META COMMENT
            // see these \n that i added here, and then proceeded to add everywhere? this is what made me realize lab08 wasnt working

        return;
    }

    // need a blank matrix
        // nvm
        // just need to store the values of one
        std::vector<double> hold; // gpt, will be used to store the row so it wont be overwritten
    for (int i = 0; i < A.getSize(); ++i){ 
        hold.push_back(A.get(row1, i)); // gpt
        // push_back is a method that allows us to insert a value into the vector
        // functions exactly like .append in python lists
         
        // QUESTION
            // does pushback mean that hold is backwards relative to A? does that matter?
    }
    // now that we have that row from A safely store, we can proceed with overwritting rowA

    for (int i = 0; i < A.getSize(); ++i){
        A.set(row1, i, B.get(row2, i)); // overwrites the value of A with the value of B
    }
    for (int i = 0; i < A.getSize(); ++i){ 
        B.set(row2, i, hold[i]); // uses the saved value to write to B
    }
    std::cout << "\nBelow is the new matrix A\n" << std::endl; // next few lines print the result
    A.print();
    std::cout << "\nBelow is the new matrix B\n" << std::endl;
    B.print();
    return;
}
void swap_col_func(){
    // will be basically the same as swap rows
    // outright just copying it from row function ( i really am not learning my lesson - see lab08 NOTES.txt for context )
    std::cout << "\nNote: This assumes you are inputting two matrices\n Also, this will swap the columns BEWTEEN the two matrices\n" << std::endl;
    Matrix A(0), B(0); // "placeholders that allow us to initialize them"
    Matrix::readfile(A, B); // runs the read file thing

    int col1; // will be used to store value
    int col2; // same
    std::cout << "\nEnter the column of Matrix 1 (0 to N-1):\n" << std::endl;
    std::cin >> col1; // gets the row

    if (col1 < 0 || col1 >= A.getSize()){ // handles index errors
        std::cerr << "\nInvalid index for col1\n";
        return;
    }

    std::cout << "\nEnter the column of Matrix 2 (0 to N-1):\n" << std::endl;
    std::cin >> col2; // gets the row

    if (col2 < 0 || col2 >= B.getSize()){ // handles errors
        std::cerr << "\nInvalid index for col2\n";
        return;
    }
    if (A.getSize() != B.getSize()){ // handles an error
        std::cerr << "\nTheir sizes do not match, cannot swap between the two matrices\n";
        // META COMMENT
            // see these \n that i added here, and then proceeded to add everywhere? this is what made me realize lab08 wasnt working
        // im leaving this comment here, to show that this is just copied from row function
            // but i think this gives insight into how lab08 could have been messed up via overwriting (NOTES.txt for context)
            return;
    }

    // need a blank matrix
        // nvm
        // just need to store the values of one
        std::vector<double> hold; // gpt, will be used to store the row so it wont be overwritten
    for (int i = 0; i < A.getSize(); ++i){ 
        hold.push_back(A.get(i, col1)); // gpt
        // push_back is a method that allows us to insert a value into the vector
        // functions exactly like .append in python lists
         
        // QUESTION
            // does pushback mean that hold is backwards relative to A? does that matter?
    }
    // now that we have that row from A safely store, we can proceed with overwritting rowA

    for (int i = 0; i < A.getSize(); ++i){
        A.set(i, col1, B.get(i, col2)); // overwrites the value of A with the value of B
    }
    for (int i = 0; i < A.getSize(); ++i){ 
        B.set(i, col2, hold[i]); // uses the saved value to write to B
    }
    std::cout << "\nBelow is the new matrix A\n" << std::endl; // next few lines print the result
    A.print();
    std::cout << "\nBelow is the new matrix B\n" << std::endl;
    B.print();
    return;
}
void underminer(){
    // needs to overwrite a value of the matrix
    std::cout << "\nNote: This assumes you are inputting two matrices\n" << std::endl;
    Matrix A(0), B(0); // "placeholders that allow us to initialize them"
    Matrix::readfile(A, B); // runs the read file thing
    int row; //
    int col; // these are for the choice
    double value; // will be used to store value
    int choice; // below block is picking which matrix
    std::cout << "Which Matrix are you writing to? (0 for A 1 for B)\n" << std::endl;
    std::cin >> choice;
    // now we get the index and value
    std::cout << "What is the row you are writing to (0 to N-1)\n" << std::endl;
    std::cin >> row;
    std::cout << "What is the column you are writing to (0 to N-1)\n" << std::endl;
    std::cin >> col;
    std::cout << "What is the value\n" << std::endl;
    std::cin >> value; // now we have everything we need
    

    if (choice == 0){ // performs the action on matrix A
        if (row < 0 || row >= A.getSize() || col < 0 || col >= A.getSize()){ // handles an error
            std::cerr << "Invalid index";
            return;
        }
        A.set(row, col, value);
        A.print();
        return;
    }
    if (choice == 1){ // performs the action on matrix B
        if (row < 0 || row >= B.getSize() || col < 0 || col >= B.getSize()){ // handles an error
            std::cerr << "Invalid index";
            return;
        }
        B.set(row, col, value);
        B.print();
        return;
    }
    return; // runs if for some reason the others didnt run
    // 

}
int main(){ 
    // BARK BARK BARK
        // now that i have your attention, this function is directly copied from the version i had of lab08
            // which I have now realized doesnt work correctly
    int choice;
    while (1 == 1){ // loops
        printf("\n1.) Add matrices\n" // prints options
        "2.) Multiply matrices\n"
        "3.) Get sum of diagonals\n"
        "4.) Swap rows\n"
        "5.) Swap columns\n"
        "6.) Update matrix\n"
        "Enter selction(number):\n");
        scanf("%d", &choice); // locks in the choice
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // this is needed to fix the issue in lab08
        //
        // ^^ using gpt as a debugger, says this is odd
            // basically wrote main() a few days before the rest of this assignment and i DONT wanna rewrite it
            // hopefully that doesnt cause issues :)))))))))))))
        //
        // the above comment block is left unedited from lab08
        // i am filled with seething rage
        if (choice == 1) {
            Matrix A(0), B(0); // "placeholders that allow us to initialize them"
            Matrix::readfile(A, B); // runs the read file thing
            Matrix C = A + B; // uses operator overloading 
            C.print(); // prints
        ;} // add function !!
        if (choice == 2) { // saving this for last, matrix multiplication is a long thing
            Matrix A(0), B(0); // initializes them
            Matrix::readfile(A, B); // fills them with data
            Matrix C = A * B; // performs the operation
            C.print(); // prints the matrix

        } 
        if (choice == 3) { sum_diag_func() ;}
        if (choice == 4) { swap_rows_func() ;}
        if (choice == 5) { swap_col_func() ;}
        if (choice == 6) { underminer() ;} // these are self explainatory, just runs the function based on input
    }
    return 0; // wont ever run, doesnt seem necessary
}
// this is mostly just copied from the last lab
// but i cannot tell if the two matrices need to be store FIRST or if each function stores their own??
// going to assume that each function gets its own

// finished
    // debugging comments
        // actually it seems to work fine as is???
        // wow WEEE
    // post-comments
        // im so upset about the lab08 thing how did i miss that
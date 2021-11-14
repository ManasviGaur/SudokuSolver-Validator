#include<iostream>
class SudokuFrame{

    int sudokuFrame[9][9];
    int editableFrame[9][9];
    public:SudokuFrame(){
        display_menu();
    }

    private:void display_menu(){

        std::cout<<"\n======================\n";
        std::cout<<"  Sudoku Solver And validator\n";
        std::cout<<"======================\n\n";

        std::cout<<"Welcome to the Sudoku Solver And Validator!\n";
        std::cout<<"Before we start, you will have to input the puzzle into this program.\n\n";
        std::cout<<"You can :-\n";
        std::cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";

        std::cout<<"\t   Blank cells must be filled in as 0 (For example; 3 0 1 0 0 0 ...).\n";
        std::cout<<"\t   --> ";

        int option;
        std::cin>>option;

        if(option==1) readFrameValues();
        else{
            while(true){
                std::cout<<"\nOops!! You have entered an invalid option. Try again.\n";
                std::cout<<"\t   --> ";
                std::cin>>option;

                if(option==1) readFrameValues();
                else continue;

                break;
            }
        }
    }

    private:void readFrameValues(){
        std::cout<<"\nEnter the specified values.\n";
        std::cout<<"Enter 0 if cell is empty.\n\n";

        int row_val, col_val;

        for(row_val=0; row_val<9; row_val++){
            for(col_val=0; col_val<9; col_val++){
                int value;

                std::cout<<"Enter the value for cell["<<row_val+1<<"]["<<col_val+1<<"] --> ";
                std::cin>>value;

                if(!(value>=0 && value<=9)){
                    while(true){
                        std::cout<<"Oops! You have entered a wrong value! Try again.\n";
                        std::cout<<"Enter the value for cell ["<<row_val+1<<"]["<<col_val+1<<"] --> ";
                        std::cin>>value;

                        if(value>=0 && value<=9) break;
                    }
                }

                sudokuFrame[row_val][col_val]=value;

                if(value==0) editableFrame[row_val][col_val]=0;
                else editableFrame[row_val][col_val]=1;
            }
            std::cout<<"-------\n";
        }
    }


    public:void setCellValue(int row, int col, int num){
        if(editableFrame[row][col]==0) sudokuFrame[row][col]=num;
    }


    public:int getCellVal(int row, int col){
        int cellValue=sudokuFrame[row][col];
        return cellValue;
    }


    public:int isEditable(int row, int col){
        return (editableFrame[row][col]-1)*(-1);
    }

    public:void clearFrameFrom(int row, int col){
        int jcount=0;
        int row_val, col_val;

        for(row_val=row; row_val<9; row_val++){

            if(jcount==0) col_val=col;
            else col_val=0;

            for(; col_val<9; col_val++){
                if(editableFrame[row_val][col_val]==0) sudokuFrame[row_val][col_val]=0;
            }

            jcount++;

        }
    }

    public:void displayFrame(){

        std::cout<<"==========================================";
        int row_val, col_val;

        for(row_val=0; row_val<9; row_val++){
            int cellIter=1;

            std::cout<<"\n";
            for(col_val=0; col_val<9; col_val++){
                if(cellIter==3){
                    std::cout<<sudokuFrame[row_val][col_val]<<"   ||   ";
                    cellIter=1;
                }
                else{
                    std::cout<<sudokuFrame[row_val][col_val]<<"  ";
                    cellIter++;
                }
            }

            if(row_val%3!=2) std::cout<<"\n";
            else std::cout<<"\n==========================================";
        }

    }

};

#include "validator.cpp"

int main(){
    int choice;
    std::cout<<"Please Enter your choice\n ";
    std::cout<<"You can :-\n";
    std::cout<<"\t1.To Solve a Sudoku. (Enter 1)\n";

    std::cout<<"\t2.To Check the validity of an existing sudoku.(Enter 2)\n";
    std::cout<<"\t   --> ";
    std::cin>>choice;
    if(choice==1)
    {
        SudokuSolver s;
    }
    else if(choice==2)
    {
        SudokuValidator s;
        if(s.checkValidity()){
            std::cout << "Your puzzle is valid!\n";
        }else{
            std::cout << "Your puzzle is invalid\n";
        }
    }
    else{
        while(true){
            std::cout<<"\nOops!! You have entered an invalid choice. Please Try again.\n";
            std::cout<<"\t   --> ";
            std::cin>>choice;

            if(choice==1){
                SudokuSolver s;
                break;
            }
            else if (choice==2){
                SudokuValidator s;
                if(s.checkValidity()){
                    std::cout << "Your puzzle is valid!\n";
                }else{
                    std::cout << "Your puzzle is invalid\n";
                }
                break;
            }
        }
    }
    return 0;
}

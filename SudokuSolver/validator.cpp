#include "possibilities.cpp"
#include <set>

class SudokuValidator{
    public: SudokuFrame frame;

    public:SudokuValidator(){
            //validateFrame();
    }
    public:bool checkValidity(){
        return validateFrame();
    }
    private:bool validateFrame(){
        if(valuesAreValid())
            if(rowsAreValid())
                if(columnsAreValid())
                    if(ThreeByThreeSquaresAreValid())
                        return true;
        return false;
    }
    private:bool valuesAreValid(){
        int row_val, col_val;

        for(row_val=0; row_val<9; row_val++){
            for(col_val=0; col_val<9; col_val++){
                int cellValue=frame.getCellVal(row_val,col_val);
                if(cellValue<0 || cellValue>9) return false;
            }
        }

        return true;
    }
    private:bool rowsAreValid(){
        for(int row_val = 0; row_val < 9; row_val++){
            std::set<int> s;
            for(int col_val = 0; col_val < 9; col_val++){
                int cellVal = frame.getCellVal(row_val, col_val);
                if(cellVal != 0){
                    if(s.find(cellVal) != s.end()) return false;
                    s.insert(cellVal);
                }
            }
        }
        return true;
    }
    private:bool columnsAreValid(){
        for(int col = 0; col < 9; col++){
            std::set<int> s;
            for(int row = 0; row < 9; row++){
                int cellVal = frame.getCellVal(row, col);
                if(cellVal != 0){
                    if(s.find(cellVal) != s.end()) return false;
                    s.insert(cellVal);
                }
            }
        }
        return true;
    }
    private:bool ThreeByThreeSquaresAreValid(){
            for(int i = 0; i < 9; i+=3){
                for(int j = 0; j < 9; j+=3){
                    std::set<int> s;
                    for(int row = i; row < i+3; row++){
                        for(int col = j; col < j + 3; col++){
                            int cellVal = frame.getCellVal(row, col);
                            if(cellVal != 0){
                                if(s.find(cellVal) != s.end()) return false;
                                s.insert(cellVal);
                            }
                        }
                    }
                }
            }
            return true;
        }
};

class SudokuSolver: public SudokuValidator{
    int recursiveCount;
    public: SudokuSolver(){
        if(!checkValidity()){
            std::cout << "Invalid Problem\n";
        }else{
            recursiveCount=0;
            solve();
            std::cout<<" Yay! Your puzzle has been solved!\n\n";
            displayFrame();
            std::cout<<"\n\n";
        }
    }

    private:bool cellValueValid(int row, int col, int currentValue){
        int row_val, col_val;

        for(row_val=0; row_val<9; row_val++){
            if(row_val!=row){
                int comparingVal=frame.getCellVal(row_val,col);
                if(comparingVal==currentValue) return false;
            }
        }

        for(col_val=0; col_val<9; col_val++){
            if(col_val!=col){
                int comparingVal=frame.getCellVal(row,col_val);
                if(comparingVal==currentValue) return false;
            }
        }
        if(ThreeByThreeGridValid(row,col,currentValue)==false) return false;

        return true;
    }

    private:bool ThreeByThreeGridValid(int row, int col, int currentValue){
        int rowStart=(row/3)*3;
        int rowEnd=(rowStart+2);

        int colStart=(col/3)*3;
        int colEnd=(colStart+2);

        int row_val, col_val;

        for(row_val=rowStart; row_val<=rowEnd; row_val++){
            for(col_val=colStart; col_val<=colEnd; col_val++){
                if(frame.getCellVal(row_val,col_val)==currentValue) return false;
            }
        }

        return true;
    }

    private:Possibilities getCellPossibilities(int row, int col){
        int iter=0;

        Possibilities possibilities;

        for(iter=1; iter<=9; iter++){
            if(cellValueValid(row,col,iter)==true)
                possibilities.append(iter);
        }

        return possibilities;
    }

    private:int singleCellSolve(int row, int col){

        statsIncrement();

        if(frame.isEditable(row,col)==true){

            Possibilities possibilities;
            possibilities.copy(getCellPossibilities(row,col));

            int posLength=possibilities.length();
            int posIter=0, newRow=row, newCol=col;

            for(posIter=0; posIter<posLength; posIter++){
                int possibility=possibilities[posIter];
                frame.setCellValue(row,col,possibility);

                if(col<8) newCol=col+1;
                else if(col==8){
                    if(row==8) return 1;
                    newRow=row+1;
                    newCol=0;
                }

                {

                    if(singleCellSolve(newRow,newCol)==0){
                        frame.clearFrameFrom(newRow,newCol);
                    }
                    else return 1;

                }

            }

            return 0;

        }
        else{

            int newRow=row, newCol=col;

            if(col<8) newCol=col+1;
            else if(col==8){
                if(row==8) return 1;
                newRow=row+1;
                newCol=0;
            }

            return singleCellSolve(newRow,newCol);

        }

    }
    private:void solve(){
        int success=singleCellSolve(0,0);
    }

    private:void displayFrame(){
        frame.displayFrame();
    }

    private:void statsIncrement(){
        recursiveCount++;
    }

};

/**********************************************************************************************
 * NIU CSCI 340 Section 0003                                                                  *
 * Assignment 5                                                                              *
 * Phoenix Chheav - Z1966108 - phoenixchh                                                     *
 *                                                                                            *
 *   I certify that everything I am submitting is either provided by the professor for use in *
 * the assignment, or work done by me personally. I understand that if I am caught submitting *
 * the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic    *
 * Misconduct and will be punished as such.                                                   *
 *                                                                                            *
 **********************************************************************************************/
// Implementations of the sudoku functions go in this file
// Details can be found in README.md

// This will be compiled to sudoku.o by the Makefile and linked when needed

#include "settings.h"
#include "sudoku.h"
#include <vector>
#include "grids.h"

/**
 * @brief Set the sudoku cell known object
 * 
 * @param grid the SUKODU grid to use
 * @param row the row of the cell we're marking
 * @param col the column of the cell we're marking
 * @param solution the value we're marking for the cell
 */
void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution) {
  std::set<int> known;
  known.insert(solution);
  grid.atrc(row,col) = known;
}

/**
 * @brief Set the sudoku cell unknown object
 * 
 * @param grid the `SUDOKUGRID` to use
 * @param row the row of the cell we're marking
 * @param col the column of the cell we're marking
 */
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col) {
 std::set<int> possibilities = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  grid.atrc(row, col) = possibilities;
}

/**
 * @brief remove a specific possibility from the sudoku cell given
 * 
 * @param grid the `SUDOKUGRID` to use
 * @param row the row of the cell we're removing an option from
 * @param col the column of the cell we're removing an option from
 * @param value the value to be removed
 */
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value) {
  //check if there is invalid row
  if(row < 0 || row >= 9){
    std::cerr << "Error: Invalid row\n";
  }

  //check if there is invalid column
  if(col < 0 || col >= 9){
    std::cerr << "Error: Invalid column\n";
  }

  //check if cell is known
  if(grid.atrc(row, col).size() == 1){
    std::cout << "Known cell\n";
  }
  
  //remove the value from the set of possibilities for the cell
  grid.atrc(row, col).erase(value);
}

/**
 * @brief This function prints the grid to the `ost` output stream in a neat format. 
 *
 * each cell has one space before its value and one space after
 * each $3\times 3$ subgrid will be divided by vertical lines drawn with `|` and horizontal lines drawn with `-`.
 * 
 * @param ost output stream to print to
 * @param grid `SUDOKUGRID` containing the grid information
 * @param unknown The character used for a cell with an unknown value. The default is `' '` 
 * @param impossible The character used when a cell has no remaining possibilities. The default is `'x'`
 */
void print_sudoku_grid(std::ostream & ost, const SUDOKUGRID &grid, char unknown, char impossible) {
  
  //loop through row
  for(int i = 0; i < 9; ++i){
    //horizontal lines
    if(i > 0 && i % 3 == 0){
      ost << "---------|---------|---------" << std::endl;
    }

    //loop through column
    for(int j = 0; j < 9; ++j){
      //vertical lines
      if(j > 0 && j % 3 == 0){
        ost << "|";
      }

      ost << " ";
      if(grid.atrc(i,j).size() == 1){//check for known cell

        ost << *grid.atrc(i, j).begin();

      }else if(grid.atrc(i, j).empty()){//check for unkown cell

        ost << impossible;

      }else{ //unknown cell that contian possibilities
        ost << unknown;
      }
      ost << " ";
    }

    //end of row
    ost << std::endl;
  }
}

////////////////////////////////////////////////////////////////////////////////
// This one is provided. You do not need to change it.
////////////////////////////////////////////////////////////////////////////////
int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col) {
  int count = 0;

  count += handle_row_for_cell(grid, row, col); 
  count += handle_col_for_cell(grid, row, col); 
  count += handle_subgrid_for_cell(grid, row, col); 

  return count; 
}

/**
 * @brief If the cell at (row,col) is known (only one possibility remaining),
 *        remove its value from the possibilities of all of the *other* cells in the same row. 
 *        If unknown, do nothing for now.
 * 
 * @param grid the `SUDOKUGRID` to use
 * @param row the row of the cell we're handling
 * @param col the column of the cell we're handling 
 * @return the value that will be changed
 */
int handle_row_for_cell(SUDOKUGRID &grid, int row, int col) {
  int value = 0;
  int count = 0;
  //check if cell is already known
  if(grid.atrc(row, col).size() == 1){
    int known_value = *grid.atrc(row, col).begin();

    //loop through the cell in same row
    for(int it = 0; it < 9; ++it){
      
      //skip current cell
      if(it == col){
        continue;
      }else{
        //remove the known value if it is in the possibilities
        // grid.atrc(row, it).erase(known_value);
        // ++value;
        value = grid.atrc(row, it).erase(known_value);
        if(value > 0){
          count++;
        }
      }
    }
  }

  return count;
}

/**
 * @brief If the cell at (row,col) is known (only one possibility remaining), 
 *        remove its value from the possibilities of all of the *other* cells in the same column. 
 *        If unknown, do nothing for now.
 * 
 * @param grid the `SUDOKUGRID` to use
 * @param row the row of the cell we're handling
 * @param col the column of the cell we're handling 
 * @return the value that will be changed 
 */
int handle_col_for_cell(SUDOKUGRID &grid, int row, int col) {
  int value = 0;
  int count = 0;
  //check if cell is already known
  if(grid.atrc(row, col).size() == 1){
    int known_value = *grid.atrc(row, col).begin();

    //loop through the cell in same row
    for(int it = 0; it < 9; ++it){
      
      //skip the current cell
      if(it == row){
        continue;
      }else {
        //remove the known value if it is in the possibilities
        // grid.atrc(it, col).erase(known_value);
        // ++value;
        value = grid.atrc(it, col).erase(known_value);
        if(value){
          count++;
        }        
      }
    }
  }

  return count;
}

/**
 * @brief If the cell at (row,col) is known (only one possibility remaining), 
 *        remove its value from the possibilities of all of the *other* cells in the same $3\times 3$ subgrid. 
 *        If unknown, do nothing for now.
 * 
 * @param grid the `SUDOKUGRID` to use
 * @param row the row of the cell we're handling
 * @param col the column of the cell we're handling
 * @return the value that will be changed 
 */
int handle_subgrid_for_cell(SUDOKUGRID &grid, int row, int col) {
  int value = 0;
  int count = 0;

  if(grid.atrc(row, col).size() == 1){
    int known_value = *grid.atrc(row, col).begin();
    //calculate the starts of row and col in subgrid
    int row_start = (row / 3) * 3;
    int col_start = (col / 3) * 3;

    //loop through the cells in the same 3x3 subgrid
    for(int i = row_start; i < row_start + 3; ++i){
      for(int j = col_start; j < col_start + 3; ++j){
        //skip current cell
        if(i == row && j == col){
          continue;
        }else{
          //remove known value in the possibilities
          // grid.atrc(i, j).erase(known_value);
          // ++value;  
          value = grid.atrc(i, j).erase(known_value);
          if(value){
            count++;
          }     
        }
      }
    }
  }
  return count;
}

/**
 * @brief This function reads in the Sudoku data from a file. 
 *        The data is stored in the same format as was used to store files for the `grid_row_major`. 
 *        The values will be integers from $0-9$. $0$ will indicate that the cell was blank, and needs to be solved for. 
 *        The numbers $1-9$ indicate the known value for the cell.
 * 
 * @param filename filename of the grid file that's storing our Sudoku grid
 * @param grid the `SUDOKUGRID` that will be populated based on the input data
 * @return true if file can be opened and the dimension is 9x9
 * @return false if files cannot be opened or if the dimension of input file are not 9x9
 */
bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid) {
    std::fstream file(filename);

  if(!file.is_open()){
    std::cerr << "Error: Cannot open file: " << filename << std::endl; 
    return false;
  }
  int width = 0;
  int height = 0;

  if(!(file >> width >> height) || width != 9 || height != 9){
    std::cerr << "Error: Invalid grid dimensions.\n";
    return false;
  }
  initialize_grid(grid);
  int value;
  for(int row = 0; row < 9; ++row){
    for(int col = 0; col < 9; ++col){
      if(!(file >> value)){
        std::cerr<< "Error: Invalid data from file: " << filename << " to read.\n";
        return false;
      }else{
        if(value < 0 || value > 9){
          std::cerr << "Error: Invalid value in file.\n";
          return false;
        }
        if(value != 0){
          grid.atrc(row, col).clear();
          grid.atrc(row, col).insert(value);
        }else{
          std::set<int> possibilities = {1, 2, 3, 4 ,5 ,6 ,7, 8, 9};
          grid.atrc(row, col) = possibilities;
        }
      }
    }
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// This is what the implementation looks like for grid_row_major,
//   if you're using another SUDOKUGRID type, you will likely have to change it.
////////////////////////////////////////////////////////////////////////////////
void initialize_grid(SUDOKUGRID &grid) {
  grid.resize(9,9);
}


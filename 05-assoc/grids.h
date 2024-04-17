/**********************************************************************************************
 * NIU CSCI 340 Section 0003                                                                  *
 * Assignment 3                                                                               *
 * Phoenix Chheav - Z1966108 - phoenixchh                                                     *
 *                                                                                            *
 *   I certify that everything I am submitting is either provided by the professor for use in *
 * the assignment, or work done by me personally. I understand that if I am caught submitting *
 * the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic    *
 * Misconduct and will be punished as such.                                                   *
 *                                                                                            *
 **********************************************************************************************/
#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// include the declarations needed for this
#include <iostream>
#include <fstream>
#include "grids.decl.h"

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

using std::out_of_range;

/**
 * @brief check bounds of x and y
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param x axis coordinate
 * @param y ordinate coordinate
 * @return true if x and y are in bounds
 * @return false  if x and y are not in bounds
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckxy(int x, int y) const {
  if(x >= 0 && y >= 0 && x < _width && y < _height){
    return true;
  }
  return false;
}

/**
 * @brief check column and row bounds
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @param col 
 * @return true if col and row are inside the bounds
 * @return false if col and row are not in the bounds
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckrc(int row, int col) const {
  if(row >= 0 && col >= 0 && row < _height && col < _width){
    return true;
  }
  return false;
}

/**
 * @brief method to check if there are any elements in grid
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @return true if there is no elements
 * @return false if there are elements
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::empty() const {
  if(width() != 0 || height() != 0){
    return false;
  }
  return true;
}

/**
 * @brief get rid of all elements that was stored, changed width and height accordingly
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T,RA_CONTAINER>::clear() {
  _height = 0;
  _width = 0;
}

/**
 * @brief takes screen x, y coordinates, this is commonly used when doing graphic on a computer screen
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param x 
 * @param y 
 * @return T& 
 */
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) {
    if(x < 0 || x >= _width || y < 0 || y >= _height){
      throw out_of_range("x and y are out of bounds.");
  }
  return data[y * _width + x];
}

template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) const {
    if(x < 0 || x >= _width || y < 0 || y >= _height){
      throw out_of_range("x and y are out of bounds.");
  }
  return data[y * _width + x];
}

/**
 * @brief takes row, column coordinates
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @param col 
 * @return T& 
 */
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) {
  if(row < 0 || row >= _height || col < 0 || col >= _width){
    throw out_of_range("row and col are out of bounds.");
  }
  return data[row * _width + col];
}

/**
 * @brief takes const row and col
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @param col 
 * @return const T& 
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) const {
  if(row < 0 || row >= _height || col < 0 || col >= _width){
    throw out_of_range("row and col are out of bounds.");
  }
  return data[row * _width + col];
}

/**
 * @brief method to return width
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @return width of grid
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::width() const {
  return _width;
}

/**
 * @brief method to return height
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @return return height of the grid 
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::height() const {
  return _height;
}

/**
 * @brief overwrite grid by copying contents of grid with source's
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @tparam OTHER_CONTAINER 
 * @param source 
 * @return grid_row_major <T, RA_CONTAINER>& 
 */
template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major <T, RA_CONTAINER> & grid_row_major<T, RA_CONTAINER>::operator = (const grid_row_major<T, OTHER_CONTAINER> & source) {
  if(this != &source){
    _width = source._width; //replace with source's _width 
    _height = source._height; //replace with source's _height

    for(int i = 0; i < _width*height; ++i){
      data[i] = source.data[i]; //replace data with source's data
    }
  }
  return *this;
}

/**
 * @brief point to the first element in row
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @return 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) {
  return data.begin() + row * _width;
}

/**
 * @brief points just past the last element on row
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @return 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) {
   int a_row = row + 1;
  return data.begin() + a_row * _width;
}

/**
 * @brief point to the first element in row
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @return
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) const {
  return data.begin() + row * _width;
}

/**
 * @brief points just past the last element on row
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @return 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) const {
  int a_row = row + 1;
  return data.begin() + a_row * _width;
}

/**
 * @brief method that point to first element in column
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param col 
 * @return iterator that point to first element in column
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colbegin(int col) {
  if(col >= 0 && col < _width){
      return col_iterator(data.begin() + col, _width);
  }else{
    throw out_of_range("Column out of range");
  }

}

/**
 * @brief method that return a column that point to the position that we would get
 *        to after iterating one time past the last valid element in column
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param col 
 * @return return column iterator that point to the position that we'd get to after iterating
 *         one time past the last valid element on column
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colend(int col) {
  if(col >= 0 && col < _width){
    int size = _height * _width;
    return col_iterator(data.begin() + size + col, _width);
  }else{
    throw out_of_range("Column out of range");
  }
}

/**
 * @brief This method will be used to resize the grif to make it big enough for the new height and width
 *        and change the size of both height and width to the new size
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param new_width 
 * @param new_height 
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {

  _height = new_height; // change height to new size
  _width = new_width; // change width to new size
  data.resize(_width * _height); //reize the grid
}

/**
 * @brief method that try to replace the content of grid with data from the specified files
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param filename 
 * @return true 
 * @return false 
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::load_from_file(const std::string & filename) {
  
  //open filename
  std::fstream file(filename);

  int new_width = 0;
  int new_height = 0;
  int read = 0;

  //read data from the file
  file >> new_width >> new_height;

  resize(new_width, new_height);

  

  //read values in *row order*
  for(int i = 0; i < new_height; ++i){
    for(int j = 0; j < new_width; ++j){
      if(!(file >> data[i * new_width + j])){
        std::cerr << "There is too little data in the file. Reading stopped...";
        return false;
      }
      read++;
    }
  }

  T more_data;
  while(file >> more_data){
    read++;
  }

  int size = new_width * new_height;

  if(read > size){
    std::cerr << "There is too much data in the file. Stopped reading...";
  }

  return true; // nothing loaded, because you haven't implemented this yet
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief method for matrix multiplication
 * 
 * @tparam GRID1 template parameter
 * @tparam GRID2 template parameter
 * @tparam GRID3 template parameter
 * @param lhs grid to be used as the left hand side of the matrix multiplication
 * @param rhs grid to be used as the right hand side of the matrix multiplication
 * @param result grid that will be used to store the result.
 * @return true 
 * @return false 
 */
template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result) {
  double dot_product = 0;
  result.resize(lhs.width(), rhs.height());
    if(lhs.width() == rhs.height()){
      for(int i = 0; i < lhs.height(); ++i){//row of lhs
        for( int j = 0; j < rhs.width(); ++j){ //col of rhs
          dot_product = 0;
          for(int k = 0; k < lhs.width(); ++k){
            dot_product += lhs.atrc(i,k) * rhs.atrc(k,j);
          }
          result.atrc(i,j) = dot_product;
        }
      }
      return true;
    }

  return false; // report that it's not working, because it's not implemented yet
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//    These are for the col_iterator class I provided for you. Feel free to
// implement these to use that for your column iterators, or you can implement
// it in another way if you prefer that.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief a preincrement method to move the position of element to the next position
 * 
 * @tparam ITERATOR 
 * @return current iterator at new position 
 */
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator ++ () { // preincrement
  pos += width;
  return *this;
}

/**
 * @brief a preincrement method to move the position of element to the next position
 * 
 * @tparam ITERATOR 
 * @return another iterator that points to the original node position
 */
template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator ++ (int) { // postincrement
  col_iterator<ITERATOR> temp = *this;
  pos += width;
  return temp;
}

/**
 * @brief method to move the iterator to n position
 * 
 * @tparam ITERATOR 
 * @param n 
 * @return col_iterator <ITERATOR> 
 */
template <typename ITERATOR>
col_iterator <ITERATOR> col_iterator<ITERATOR>::operator + (int n) const {
  //create a temp of the current iterator
  col_iterator<ITERATOR> temp = *this;
  //move the copy n columns forward
  for(int i = 0; i < n; ++i){
    ++temp.pos;
  }
  // temp.pos += n;
  //return new iterator
  return temp;
}

/**
 * @brief method to access element at n index in the column
 * 
 * @tparam ITERATOR 
 * @param n 
 * @return *index
 */
template <typename ITERATOR>
auto & col_iterator <ITERATOR>::operator [] (int n) {
  ITERATOR index = pos;
  for(int i = 0; i < n; ++i){
    ++index;
  }
  return *index;
}

/**
 * @brief method to access element at n index in the column
 * 
 * @tparam ITERATOR 
 * @param n 
 * @return *index
 */
template <typename ITERATOR>
const auto & col_iterator <ITERATOR>::operator [] (int n) const {
  ITERATOR index = pos;
  for(int i = 0; i < n; ++i){
    ++index;
  }
  return *index;
}
    
/**
 * @brief method to dereference the iterator
 * 
 * @tparam ITERATOR 
 * @param n 
 * @return *pos
 */
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator * () {
  return *pos;
}

/**
 * @brief method to dereference the iterator
 * 
 * @tparam ITERATOR 
 * @param n 
 * @return *pos
 */
template <typename ITERATOR>
const auto & col_iterator<ITERATOR>::operator * () const {
  return *pos;
}

/**
 * @brief method to compare whether they are in the same position
 * 
 * @tparam ITERATOR 
 * @param other 
 * @return true 
 * @return false 
 */
template <typename ITERATOR>
bool col_iterator <ITERATOR>::operator == (const col_iterator <ITERATOR> &other) {
  if(pos == other.pos){
    return true;
  }
  return false;
}

#endif

#include "scp_matrix.h"


std::vector<std::string> scp_split(const std::string &txt) {
  std::vector<std::string> result;
	uint begin = 0;
	for (uint64_t i=0; i < txt.size(); i++) {
		if (txt[i] == ' ' or txt[i] == '\n') {
			if (i > begin)
				result.push_back( txt.substr(begin, i-begin) );
			begin = i+1;
		}
	}
	result.push_back( txt.substr(begin, txt.size()) );
  for (uint64_t i=0; i < result.size(); i++) {
    if (result[i] == "" or result[i] == " " or result[i] == "\n") {
      result.erase(result.cbegin()+i);
      i--;
    }
  }
	return result;
}


matrix::matrix(size_t num_rows, size_t num_columns)
: num_rows(num_rows), num_columns(num_columns) {
  this->weights = (float *) malloc(sizeof(float) * num_columns);
  this->values = (bool *) malloc(sizeof(bool) * num_columns * num_rows);
  for (unsigned i = 0; i < num_rows*num_columns; i++) {
    this->values[i] = false;
  }
  for (unsigned i = 0; i < num_columns; i++) {
    this->weights[i] = 0.0f;
  }
}

matrix::matrix(std::ifstream& inputfile) {
  if (inputfile.is_open()) {
    inputfile >> this->num_rows >> this->num_columns;
    this->weights = (float *) malloc(sizeof(float) * num_columns);
    this->values = (bool *) malloc(sizeof(bool) * num_columns * num_rows);
    // Define todos os valores da matriz como false
    for (unsigned i = 0; i < num_rows*num_columns; i++) {
      this->values[i] = false;
    }

    std::string *fileContent = new std::string(
      std::istreambuf_iterator<char>(inputfile),
      std::istreambuf_iterator<char>());
    auto fileContentVec = scp_split(*fileContent);
    
    size_t index = 0;
    for (; index < this->num_columns; index++) {
      this->weights[index] = std::stof(fileContentVec[index]);
    }

    size_t columnIndex = 0;
    while (index < fileContentVec.size()) {
      size_t coverageSize = std::stoul(fileContentVec[index++]);
      size_t currentIndex = index;

      for (; index < currentIndex+coverageSize; index++) {
        size_t rowIndex = std::stoul(fileContentVec[index]) -1;
        this->set(rowIndex, columnIndex);
      }
      columnIndex++;
    }

    free(fileContent);
  }
}

bool matrix::get(size_t i, size_t k) {
  ASSERT_THROW( i < this->num_rows, "Row index is greater" );
  ASSERT_THROW( k < this->num_columns, "Column index is greater");
  return this->values[ i*this->num_columns + k ];
}

void matrix::set(size_t i, size_t k) {
  ASSERT_THROW( i < this->num_rows, "Row index is greater" );
  ASSERT_THROW( k < this->num_columns, "Column index is greater");
  this->values[ i*this->num_columns + k ] = true;
}

void matrix::flip(size_t i, size_t k) {
  ASSERT_THROW( i < this->num_rows, "Row index is greater" );
  ASSERT_THROW( k < this->num_columns, "Column index is greater");
  this->values[i*this->num_columns + k] = !this->values[i*this->num_columns + k];
}

float matrix::get_weight(size_t k) {
  ASSERT_THROW( k < this->num_columns, "Column index is greater" );
  return this->weights[k];
}

void matrix::set_weight(size_t k, float value) {
  ASSERT_THROW( k < this->num_columns, "Column index is greater" );
  this->weights[k] = value;
}

std::ostream& operator<<(std::ostream &os, matrix &m) {
  os << m.num_rows << "x" << m.num_columns << "\n";
  if (m.num_columns <= 60) {
    for (size_t i = 0; i < m.num_rows; i++) {
      for (size_t k = 0; k < m.num_columns; k++) {
#       ifdef __unix__
        if (m.get(i, k)) {
          os <<"\e[38;5;46m"<< m.get(i, k) << "\e[0m ";
        } else {
          os << m.get(i, k) << " ";
        }
#       else
        os << m.get(i, k) << " ";
#       endif
      }
      os << "\n";
    }
    os << "Weights:\n";
    for (size_t i = 0; i < m.num_columns; i++) {
      os << m.get_weight(i) << " ";
    }
  }
  os << std::endl;
  return os;
}

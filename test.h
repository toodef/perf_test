#pragma once

#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <memory>

#include <boost/program_options.hpp>

using namespace std;

namespace po = boost::program_options;

struct time_res_t
{
   time_res_t() :
        computing_time_   (0)
      , mem_allocate_time_(0)
   {}
   
   size_t   computing_time_
          , mem_allocate_time_;
};

class test_unit_t
{
public:
   typedef time_res_t(* calc_func_t)  ( int size, const double * a, const double * b, double * c );
   typedef void      (* limits_func_t)( size_t & matrix_size_limit );
   
   test_unit_t(const string & test_name, const calc_func_t & calc_func, const string & output_file_name
              ,const string & cmd_line_par_name );
   
   const string & check_file  () const;
   const string & name        () const;
   const string & cmd_line_par() const;

   calc_func_t calc_func;
   
   test_unit_t & operator=(test_unit_t const & test_unit)
   {
      calc_func          = test_unit.calc_func;
      test_name_         = test_unit.test_name_;
      output_file_       = test_unit.output_file_;
      cmd_line_par_name_ = test_unit.cmd_line_par_name_;
      
      return *this;
   }
   
private:
   string   test_name_
          , output_file_
          , cmd_line_par_name_;
};

class test_t
{
public:
   test_t( int argc, char ** argv, const vector<test_unit_t> & tests );
   
   void start();
   
private:
   vector<test_unit_t> tests_;
   
   string output_file_name_;

   size_t   max_matr_size_
          , matr_size_limit_ // maximum matrix size in bytes
          , measurement_cnt_;
};
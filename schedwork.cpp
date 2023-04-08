#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& work,
    size_t row,
    size_t col);

bool isValid(vector<Worker_T> temp, Worker_T curr);



// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t n = avail.size();
    size_t k = avail[0].size();
    for(size_t i = 0; i < n; i++){
        vector<Worker_T> temp(dailyNeed, k);
        sched.push_back(temp);
    }

    vector<size_t> work;
    for (size_t i = 0; i < avail[0].size(); ++i) {
        work.push_back(0);
    }

    return helper(avail, dailyNeed, maxShifts, sched, work, 0, 0);

bool helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& work,
    size_t row,
    size_t col){  

    //base case: schedule is complete
    if(col == dailyNeed){
        row++;
        col = 0;
    }

    //if current day is complete move to next day
    if(row == avail.size()){
      return true;
    }
    
    for (Worker_T i = 0; i < avail[row].size(); i++) {
      // if the worker id is valid or its the first on schedule
      if (isValid(sched[row], i) || col == 0) {
        // whether the worker is still available to work 
        if (avail[row][i] == 1)
          if(work[i] < maxShifts){
            // assign the worker to the current spot 
            sched[row][col] = i;
            work[i]++;
            if (helper(avail, dailyNeed, maxShifts, sched, work, row, col + 1)) {
                return true;
            }
          work[i]--;
        }
      }
    }

    // noone can be assigned to the current shift
    return false;
}


bool isValid(vector<Worker_T> temp, Worker_T curr){
  //determine whether the search for the current is successful
  return std::find(temp.begin(), temp.end(), curr) != temp.end();
}



}


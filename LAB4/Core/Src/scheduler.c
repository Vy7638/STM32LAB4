/*
 * scheduler.c
 *
 *  Created on: Nov 23, 2023
 *      Author: ADMIN
 */



#include "scheduler.h"

void SCH_Init(void){
	unsigned char i;
    for (i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_Delete_Tasks(i);
    }
}
void SCH_Update(void){
	int i = 0;
	    // NOTE: calculations are in *TICKS* (not milliseconds)
	    for (i = 0; i < counter; i++) {
	        // Check if there is a task at this location
	        //if (SCH_tasks_G[Index].pTask){
	            if (SCH_tasks_G[i].Delay == 0) {
	                // The task is due to run
	                // Inc. the 'RunMe' flag
	                SCH_tasks_G[i].RunMe += 1;
	                if (SCH_tasks_G[i].Period != 0) {
	                    // Schedule periodic tasks to run again
	                    SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
	                }
	            }
	            else {
	                // Not yet ready to run: just decrement the delay
	                SCH_tasks_G[i].Delay -= 1;
	            }
	    }
}
void SCH_Dispatch_Tasks(void){
	    // Dispatches (runs) the next task (if one is ready)
	    for (int i = 0; i < counter; i++){
	        if (SCH_tasks_G[i].RunMe > 0){
	            (*SCH_tasks_G[i].pTask)(); // Run the task
	            SCH_tasks_G[i].RunMe -= 1; // Reset / reduce RunMe flag
	            // Periodic tasks will automatically run again
	            // - if this is a 'one shot' task, remove it from the array
	            if (SCH_tasks_G[i].Period == 0){
	                SCH_Delete_Tasks(i);
	            }
	        }
	    }
	    HAL_Delay(10);
}
uint32_t SCH_Add_Tasks(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	    // Have we reached the end of the list?
	    if (counter >= SCH_MAX_TASKS){
	        return SCH_MAX_TASKS;
	    }
	    // If we're here, there is a space in the task array
	    SCH_tasks_G[counter].pTask = pFunction;
	    SCH_tasks_G[counter].Delay = DELAY;
	    SCH_tasks_G[counter].Period = PERIOD;
	    SCH_tasks_G[counter].RunMe = 0;
	    // return position of task (to allow later deletion)
	    counter++;
	    return counter;
}
uint8_t SCH_Delete_Tasks(uint32_t taskID){
	if (taskID < counter - 1){
		SCH_Shift_Tasks(taskID);
		return taskID;
	}
	else if (taskID == counter){
	    SCH_tasks_G[taskID].pTask = 0x0000;
	    SCH_tasks_G[taskID].Delay = 0;
	    SCH_tasks_G[taskID].Period = 0;
	    SCH_tasks_G[taskID].RunMe = 0;
	    counter--;
	    return 0; // return status
	}
}
void SCH_Shift_Tasks(uint32_t taskID){
	while (taskID < counter - 1){
		SCH_tasks_G[taskID] = SCH_tasks_G[taskID + 1];
		taskID++;
	}
    SCH_tasks_G[taskID].pTask = 0x0000;
    SCH_tasks_G[taskID].Delay = 0;
    SCH_tasks_G[taskID].Period = 0;
    SCH_tasks_G[taskID].RunMe = 0;
    counter--;
}
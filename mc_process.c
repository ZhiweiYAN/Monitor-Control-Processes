/*
 * =====================================================================================
 *
 *       Filename:  mc_process.c
 *
 *    Description:  For server program, monitor the process, and kill them who mis-behaviors.
 *
 *        Version:  1.0
 *        Created:  10/13/2011 4:42:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */


#include	"mc_process.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Insert_pid_process_table
 *  Description:  Put the data of a process into the process table
 * =====================================================================================
 */
int Insert_pid_process_table(int table, pid_t pid, int deadline, enum ProcessType type)
{
    void * mem_ptr = NULL;
    int success = 0;
    int semid = 0;
    semid = GetExistedSemphore(table_id);
    success = AcquireAccessRight(semid);
    mem_ptr = MappingShareMemOwnSpace(table_id);

    /*  insert the pid of the process into the table */
    success = Register_process_into_process_table(((struct ShareMemProcess *)mem_ptr)->process_table,MAX_PROCESS_NUMBRER,pid,deadline,type);

    /* Free memory control handler */
    success = UnmappingShareMem((void*)mem_ptr);
    success = ReleaseAccessRight(semid);

    return success;
}


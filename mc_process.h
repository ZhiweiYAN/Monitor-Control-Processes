/*
 * =====================================================================================
 *
 *       Filename:  mc_process.h
 *
 *    Description:  For server program, monitor the process, and kill them who mis-behaviors.
 *
 *        Version:  1.0
 *        Created:  10/13/2011 4:44:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

/*
 * Maintance a pid table which includes pid, deadline, lifetime etc.
 * Every process has its item in the table.
 * A kill process (called killer) keeps an eye on it, and kill some process whose life time exceeds its deadline.
 * Of course, these processes update their statuses periodly to avoid be killed by the killer.
 * */

enum ProcessType {
    NORMAL_PROCESS=0, SYNC_PROCESS,
    RECORD_PROCESS, VIEW_PROCESS,
    CAS_PROCESS, HEART_BEAT_SEND_PROCESS,
    HEART_BEAT_RECV_PROCESS
};

/* the two function will be exported for outside users. */
int Insert_pid_process_table(pid_t pid, int deadline, enum ProcessType type);
int Remove_pid_process_table(pid_t pid);

/* the two function for real actions */
int Register_process_into_process_table(struct ChildProcessStatus *ptr, int prcs_num,pid_t pid,int deadline,enum ProcessType type);
int Unregister_process_from_process_table(struct ChildProcessStatus *ptr, int prcs_num,pid_t pid);

int Increase_process_life_time(struct ChildProcessStatus *ptr, int prcs_num);

int Kill_invalid_process(struct ChildProcessStatus *ptr, int prcs_num);

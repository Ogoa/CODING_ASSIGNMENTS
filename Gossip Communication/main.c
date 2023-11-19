#include "main.h"

/**
 * main - Execute the gossip algorithm
 *
 * Return: ALways 0 (Successful exit)
 */
int main(void)
{
        Process **processes;
        int i, j, count;

        processes = init_nodes();

        /* Process 0 is connected to 1, 2 and 3 */
        processes[0]->connected = malloc(sizeof(Process *) * 3);
        processes[0]->connected[0] = processes[1];
        processes[0]->connected[1] = processes[2];
        processes[0]->connected[2] = processes[3];

        /* Process 1 is connected to 0, 2 and 4 */
        processes[1]->connected = malloc(sizeof(Process *) * 3);
        processes[1]->connected[0] = processes[0];
        processes[1]->connected[1] = processes[2];
        processes[1]->connected[2] = processes[4];

        /* Process 2 is connected to 0 and 1 */
        processes[2]->connected = malloc(sizeof(Process *) * 2);
        processes[2]->connected[0] = processes[0];
        processes[2]->connected[1] = processes[1];

        /* Process 3 is connected to 4 */
        processes[3]->connected = malloc(sizeof(Process *) * 1);
        processes[3]->connected[0] = processes[4];

        /* Process 4 is connected to 0, 1 and 4 */
        processes[4]->connected = malloc(sizeof(Process *) * 3);
        processes[4]->connected[0] = processes[0];
        processes[4]->connected[1] = processes[1];
        processes[4]->connected[2] = processes[4];

        /* Starting process 0 as the parent node */
        processes[0]->msg = strdup("I am infected\n");

        for (i = 0; i < MAX_NODES; i++)
        {
                count = 0;
                for (j = 0; j < sizeof(processes[i]->connected)  && !count; j++)
                {
                        if (!(processes[i]->connected[j]->msg) && !count)
                        {
                                setup_server(processes[i]);
                                setup_client((processes[i]->connected[j]));
                                count++;
                        }
                }
        }
        for (i = 0; i < MAX_NODES; i++)
        {
                free(processes[i]->msg);
                free(processes[i]->connected);
                free(processes[i]);
        }
        free(processes);
        return (0);
}

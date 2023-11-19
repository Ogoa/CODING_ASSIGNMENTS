#include "main.h"

/**
 * init_nodes - Creates the nodes that are processes within the distributed
 * system
 *
 * Return: Pointer to an array of nodes(processes)
 */
Process **init_nodes(void)
{
    int i, j;
    Process **processes;

    processes = malloc(sizeof(Process *) * MAX_NODES);
    if (!processes)
    {
        perror("Malloc failed");
        return NULL;
    }

    for (i = 0; i < MAX_NODES; i++)
    {
        processes[i] = malloc(sizeof(Process));
        if (!processes[i])
        {
            perror("Malloc failed");
            return NULL;
        }

        processes[i]->id = i;
        processes[i]->ip = strdup("127.0.0.1");
        processes[i]->port = BASE_PORT + i;
        processes[i]->fd = create_socket();

        // Initialize the connected array
        processes[i]->connected = malloc(sizeof(Process *) * MAX_NODES);
        if (!processes[i]->connected)
        {
            perror("Malloc failed");
            return NULL;
        }

        // Initialize the visited array
        for (j = 0; j < MAX_NODES; j++)
        {
            processes[i]->connected[j] = NULL;
            processes[i]->visited[j] = -1;
        }
    }

    return processes;
}

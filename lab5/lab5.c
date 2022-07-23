#include "lab5.h"

// ARE WE RESPONSIBLE FOR RESETTING COSTS

int Vnode_exists(Graph *gr, char *station)
{
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0) // check to make sure -> is right
        {
            return 1;
        }
    }

    return 0;
}

int Vnode_index(Graph *gr, char *station)
{
    int i;

    for (i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            return i;
        }
    }
}

char **plan_route(Graph *gr, char *start, char *dest)
{

    // Set starting Vnode
    Vnode *curr = gr->adj_list[Vnode_index(gr, start)];
    curr->cost = 0;

    while (curr != NULL && strcmp(curr->station, dest) != 0)
    {
        // update all neighbour nodes to min value
        Enode *edge = curr->edges;
        while (edge != NULL)
        {
            Vnode *neighbour = gr->adj_list[Vnode_index(gr, edge->vertex)];

            if (curr->cost + edge->weight < neighbour->cost)
            {
                neighbour->cost = curr->cost + edge->weight;
                neighbour->prev = curr; // SET PREVIOUS PATH CONNECTION
                neighbour->visited = 0; // RESETS TO LOOK AGAIN?
            }

            edge = edge->next;
        }

        // update Vnode to explored
        curr->visited = 1;

        // find min path of all unexplored nodes
        int lowest_ind = 0;
        int lowest_cost = 100000000;

        for (int i = 0; i < gr->count; i++)
        {
            Vnode *temp = gr->adj_list[i];
            if (temp->visited == 0 && temp->cost < lowest_cost)
            {
                lowest_ind = i;
                lowest_cost = temp->cost;
            }
        }

        // set curr to null if there is nothing left
        // else update curr node and curr update previous
        if (lowest_cost == 100000000)
        {
            curr = NULL;
        }
        else // CAUSES UNCONNECTED PATHS, need if statement to see if edges of curr have adj_list[lowest] ind in them
        {
            Vnode *temp = curr;
            curr = gr->adj_list[lowest_ind];
        }
    }

    // check if destination or null reached reached
    if (curr == NULL)
    {
        return NULL;
    }

    // start building ptr back through prev
    char **path = malloc(sizeof(char *) * gr->count);
    int level = 0;

    while (curr != NULL)
    {
        path[level] = malloc(sizeof(char) * MAX_LEN);
        strcpy(path[level], curr->station);

        curr = curr->prev;
        level++;
    }

    // resize array
    path = realloc(path, sizeof(char *) * level);

    // reset starting values;

    for (int j = 0; j < gr->count; j++)
    {
        gr->adj_list[j]->cost = 100000000;
        gr->adj_list[j]->prev = NULL;
        gr->adj_list[j]->visited = 0;
    }

    return path;
}

void add(Graph *gr, char *station)
{
    // check if station already exits
    if (Vnode_exists(gr, station) == 1)
    {
        return;
    }

    // malloc a new Vnode, set everything in there properly (should have no neighbours)
    Vnode *vnode = malloc(sizeof(Vnode));
    strcpy(vnode->station, station);
    vnode->edges = NULL;
    vnode->cost = 100000000;
    vnode->visited = 0;
    vnode->prev = NULL;

    // make adj list if the graph is empty
    if (gr->count == 0)
    {
        gr->adj_list = (Vnode **)malloc(sizeof(Vnode *));
    }
    else
    {
        gr->adj_list = realloc(gr->adj_list, (gr->count + 1) * sizeof(Vnode *)); // NEEDS TO RESIZE FOR NUMBER OF VNODE POINTERS
    }

    // update gr->count, and update adj_list, need to malloc/realloc the adj list every time -> add the vertex to the adj_list
    gr->adj_list[gr->count] = vnode;
    gr->count++;
}

void update(Graph *gr, char *start, char *dest, int weight)
{
    // create start and dest if they do not exist
    add(gr, start);
    add(gr, dest);

    // get start node
    Vnode *vstart = gr->adj_list[Vnode_index(gr, start)];

    // if weight is 0, remove edge between start and dest
    if (weight == 0)
    {
        Enode *curr = vstart->edges;
        Enode *prev = NULL;

        while (curr != NULL)
        {
            if (strcmp(curr->vertex, dest) == 0)
            {
                // checks if first node needs to be removed, updates vstart edges
                if (prev == NULL)
                {
                    vstart->edges = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }

                free(curr);
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }
    else
    {
        // if edges is null, update vnode edges
        if (vstart->edges == NULL)
        {
            Enode *enode = malloc(sizeof(Enode));
            strcpy(enode->vertex, dest);
            enode->next = NULL;
            enode->weight = weight;
            vstart->edges = enode;
            return;
        }

        Enode *curr = vstart->edges;
        Enode *prev = NULL;

        // update edge node weight if exits
        while (curr != NULL)
        {
            if (strcmp(curr->vertex, dest) == 0)
            {
                curr->weight = weight;
                return;
            }

            prev = curr;
            curr = curr->next;
        }

        // else create edge node struct, searching through till null
        Enode *enode = malloc(sizeof(Enode));
        strcpy(enode->vertex, dest);
        enode->next = NULL;
        enode->weight = weight;
        prev->next = enode;
    }
}

void disrupt(Graph *gr, char *station)
{
    // check if station exists, if not then return
    if (Vnode_exists(gr, station) == 0)
    {
        return;
    }

    // remove all edges that have station as destination in other start nodes
    for (int i = 0; i < gr->count; i++)
    {
        update(gr, gr->adj_list[i]->station, station, 0);
    }

    // remove all enodes in edges
    Vnode *vnode = gr->adj_list[Vnode_index(gr, station)];
    Enode *curr = vnode->edges;

    while (curr != NULL)
    {
        Enode *temp = curr;
        curr = curr->next;
        free(temp);
    }

    vnode->edges = NULL;

    // remove vertex from adj list
    int ind = Vnode_index(gr, station);
    free(gr->adj_list[ind]);

    // move everything right of station to the left
    for (ind; ind < gr->count - 1; ind++)
    {
        gr->adj_list[ind] = gr->adj_list[ind + 1]; // check if assigning addresses of vnodes
    }

    // update and resize adj list
    gr->count--;

    if (gr->count == 0)
    {
        free(gr->adj_list);
        gr->adj_list = NULL;
    }
    else
    {
        gr->adj_list = realloc(gr->adj_list, (gr->count) * sizeof(Vnode *));
    }
}
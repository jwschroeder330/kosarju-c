/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "group.h"



int _leader_in_groups(vertex * leader, garray * groups) {
    for(int i = 0; i < groups->glen; i ++) {
        int leader_int = atoi(leader->label);
        vertex * g_leader = groups->groups[i]->leader;
        int group_leader_int = atoi(g_leader->label);
        if (leader_int == group_leader_int) {
            groups->groups[i]->len = groups->groups[i]->len + 1;
            return 1;
        }
    }
    return 0;
}


garray * _group_initialize(vertex * leader, garray * groups) {
    group * gr = malloc(sizeof(group *));
    gr->leader = leader;
    gr->len = 1;
    
    groups->glen = groups->glen + 1;
    groups->groups = realloc(groups->groups, sizeof(group *) * groups->glen);
    groups->groups[groups->glen - 1] = gr;
    return groups;
} 


garray * groups_from_graph(graph * g) {
    garray * groups = malloc(sizeof(garray*));
    groups->groups = malloc(sizeof(group *));
    groups->glen = 0;
    int glen = 0;
    for(int i = 0; i < g->vlen; i ++) {
        vertex * leader = g->vertices[i]->leader;
        int present = _leader_in_groups(leader, groups);
        if (present == 0) {
            groups = _group_initialize(leader, groups);
        }
    }
    return groups;
}

// TODO: fix this struct comparison function
int _compare_groups_by_size(const void * a, const void * b) {
    group * x = *((group **)a);
    group * y = *((group **)b);
    return (y->len - x->len);
}


void sort_groups_by_size(garray * groups) {
    int nmemb = groups->glen;
    group ** grps = groups->groups;
    size_t size = sizeof(grps[0]);
    qsort(grps, nmemb, size, _compare_groups_by_size);
}
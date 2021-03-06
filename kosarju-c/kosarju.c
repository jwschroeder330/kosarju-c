/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include <string.h>
#include "graph.h"


void kosarju_dfs(graph * g, vertex * v, vertex * s) {
    // mark as discovered
    v->discovered = 1;
    
    // set leader to s 
    // note: isLeader is true if the leader label is equal to v label
    long long label = atoll(v->label);
    long long s_label = atoll(s->label);
    v->is_leader = label == s_label;
    v->leader = s;
    
    for(long long i = 0; i < v->elen; i ++) {
        edge * e = v->edges[i];
        // if v is the head then this is an eligible outgoing edge to look
        // for unexplored vertices
        long long head_label = atoll(e->head->label);
        if (head_label == label) {
            if(e->tail->discovered == 0) {
                kosarju_dfs(g, e->tail, s);
            }
        }
    }
}



void kosarju_dfs_loop(graph * g) {
    // global counter (# of nodes processed) for finishing times in first pass
    long long t = 0;
    
    // global counter (current source vertex) for leaders in second pass
    vertex * s;
    
    long long n = g->vlen - 1;
    for(long long i = n; i >= 0; i --) {
        vertex * v = g->vertices[i];
        if(v->discovered == 0) {
            s = v;
            kosarju_dfs(g, v, s);
            t ++;
            v->finish_time = t;
        }
    }
}


void kosarju_scc_twopass(graph * g) {
    
    // run dfs-loop on g-rev
    reverse_graph(g);
    kosarju_dfs_loop(g);
    
    // run dfs-loop on g
    reverse_graph(g);
    kosarju_dfs_loop(g);
}

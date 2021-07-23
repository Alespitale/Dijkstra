#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "set.h"

vertex_t minimo(cost_t *results, set Vertices){
	vertex_t min, aux;
	set copy;
	copy= set_copy(Vertices);	// Hago una copia del conjunto Vertices
	aux = cost_inf();	// Inicializo la variable en el valor neutro del minimo para realizar la primer comparacion
	while(!set_is_empty(copy)){
		vertex_t k;
		k = set_get(copy);	// Tomo un elemento del conjunto
		if (cost_le(results[k], aux)){	// Comparo los costos entre ambas variables
			min = k;		// Le asigno a min el vertice con menor costo
			aux = results[k];	// Actualizo el valor de aux para que en la proxima iteracion compare con el siguiente elemento
			copy= set_elim(copy, k); // Elimino el vertice que ya compare del conjunto
		}else{
			copy= set_elim(copy,k);
		}
	}
	copy = set_destroy(copy); // Libero el conjunto copy
return min;
}

cost_t min_cost(cost_t l, cost_t k){
	cost_t minimo;
	if (cost_lt(l,k)){
		minimo = l;
	}else{
		minimo = k;
	} 
return minimo;
}

cost_t *dijkstra(graph_t graph, vertex_t init) {
	unsigned int size=graph_max_size(graph);
	set Vertices = set_empty();
	cost_t *results;	//Array con los costos de los vertices
	results = calloc(size,sizeof(cost_t));
	vertex_t c;
	for(unsigned int i=0; i < size; ++i){
		Vertices = set_add(Vertices,i); // Agrego al conjunto Vertices todos los vertices del grafo
	}
	Vertices = set_elim(Vertices,init);	// Elimino del conjunto el vertice inicial porque se que su costo es 0
	for(vertex_t j=0; j < size; ++j){
		results[j] = graph_get_cost(graph, init, j); // Agrego al array lo que me cuesta ir desde el vertice inicial hacia cada uno de los demas vertices
	}
	while(!set_is_empty(Vertices)){
		c = minimo(results, Vertices); // Busco cual es el vertice con menor costo en results
		Vertices = set_elim(Vertices,c); // Elimino el vertice con menor costo del conjunto Vertices
		for (vertex_t j =0; j < size; ++j){	
			results[j] = min_cost(results[j], cost_sum(results[c],graph_get_cost(graph, c, j))); // Actualizo los costos de todos los vertices
		}
	}
	Vertices = set_destroy(Vertices); // Libero el conjunto Vertices
return results;
}

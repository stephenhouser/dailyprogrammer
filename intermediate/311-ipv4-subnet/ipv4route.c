#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <list.h>

typedef struct _ipv4route {
	uint32_t ip;
	uint8_t netmask_bits;
} IPv4Route;

IPv4Route *route_create() {
	IPv4Route *route = malloc(sizeof(IPv4Route));
	return route;
}

IPv4Route *route_copy(IPv4Route *route) {
	assert(route != NULL);

	IPv4Route *copy = route_create();
	if (copy != NULL) {
		memcpy(copy, route, sizeof(IPv4Route));
	}

	return copy;
}

bool route_parse(char *line, IPv4Route *route) {
	assert(line != NULL);
	assert(route != NULL);

	unsigned int b0, b1, b2, b3, netmask;
	
	int scanned = sscanf(line, "%u.%u.%u.%u/%u", &b3, &b2, &b1, &b0, &netmask);
	if (scanned != 5) {
		return false;
	}

	route->ip = b3 << 24 | b2 << 16 | b1 << 8 | b0;
	route->netmask_bits = netmask;
	return true;
}

void route_print(void *void_route) {
	assert(void_route != NULL);

	IPv4Route *route = (IPv4Route *)void_route;
	printf("%u.%u.%u.%u/%u",
		(route->ip >> 24) & 0x0FF,
		(route->ip >> 16) & 0x0FF,
		(route->ip >> 8 ) & 0x0FF,
		(route->ip      ) & 0x0FF,
		route->netmask_bits);
}

void route_print_nl(void *void_route) {
	assert(void_route != NULL);

	IPv4Route *route = (IPv4Route *)void_route;
	route_print(route);
	printf("\n");
}

// large_network = small netmask
// small_network = large netmask
int route_covers_route(IPv4Route *subject_route, IPv4Route *object_route) {
	unsigned int netmask = 0xFFFFFFFF << (32 - subject_route->netmask_bits);
	return (subject_route->ip & netmask) == (object_route->ip & netmask);
}

/*
 * Add new route to list of routes if it is uniqie or covers other routes
 * already in the list. Remove any covered routes already in the list.
 */
bool list_add_route(List *routes, IPv4Route *route) {
	assert(routes != NULL);
	assert(route != NULL);

	IPv4Route *existing_route;
	ListIter route_iterator;

	list_iter_init(&route_iterator, routes);
	while (list_iter_next(&route_iterator, (void **)&existing_route) != CC_ITER_END) {
		if (route_covers_route(route, existing_route)) {
			/* Remove covered route(s). */
			list_iter_remove(&route_iterator, NULL); 
		}  else if (route_covers_route(existing_route, route)) {
			/* There is already a route that covers the new one. */
			return false; 
		}
	}	

	list_add(routes, route_copy(route));
	return true;
}

int read_number_of_routes() {
	char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);

	if (read <= 0) {
		return read;
	}

	int route_count = atoi(line);
	return route_count;
}

int load_routes(List *routes) {
	assert(routes != NULL);

	char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
	int routes_loaded = 0;

    while ((read = getline(&line, &len, stdin)) != -1) {
		IPv4Route *route = malloc(sizeof(IPv4Route));
		if (route_parse(line, route)) {
			list_add(routes, route);
			routes_loaded++;
		}
	}

	free(line);
	return routes_loaded;
}

List *minimal_routes(List *routes) {
	assert(routes != NULL);

	List *minimal_routes = NULL;
	if (list_new(&minimal_routes) == CC_OK) {
		IPv4Route *route;
		ListIter route_iterator;

		list_iter_init(&route_iterator, routes);
		while (list_iter_next(&route_iterator, (void **)&route) != CC_ITER_END) {
			list_add_route(minimal_routes, route);
		}
	}

	return minimal_routes;
}

void print_route_list(List *routes) {
	assert(routes != NULL);

	list_foreach(routes, route_print_nl);
}

int main(int argc, char **argv) {
	int route_count = read_number_of_routes();
	if (route_count <= 0) {
		fprintf(stderr, "ERROR: Invalid number of IPv4 routes given.");
		return 1;
	}

	List *routes;
	list_new(&routes);
	if (load_routes(routes) == route_count) {
		List *min_routes = minimal_routes(routes);
		if (min_routes != NULL) {
			print_route_list(min_routes);
			list_destroy_free(min_routes);
		}
	}

	list_destroy_free(routes);
	return 0;
}

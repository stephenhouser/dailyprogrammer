#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <strings.h>

#include <list.h>

#define SUCCESS	0

typedef struct _ipv4_route {
	uint32_t ip;
	uint8_t netmask_bits;
} ipv4_route;

int get_number_of_routes() {
	char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);

	if (read <= 0) {
		return read;
	}

	int route_count = atoi(line);
	return route_count;
}

bool parse_route(char *line, ipv4_route *route) {
	unsigned int b0, b1, b2, b3, netmask;

	if (line == NULL || route == NULL) {
		return false;
	}

	int scanned = sscanf(line, "%u.%u.%u.%u/%u", &b3, &b2, &b1, &b0, &netmask);
	if (scanned != 5) {
		return false;
	}

	route->ip = b3 << 24 | b2 << 16 | b1 << 8 | b0;
	route->netmask_bits = netmask;
	return true;
}

unsigned int netmask_of_bits(size_t bits) {
	return 0xFFFFFFFF << (32 - bits);
}

int load_routes(List *routes) {
	char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
	int routes_loaded = 0;

    while ((read = getline(&line, &len, stdin)) != -1) {
		ipv4_route *route = malloc(sizeof(ipv4_route));
		if (parse_route(line, route)) {
			list_add(routes, route);
			routes_loaded++;
		}
	}

	free(line);
	return routes_loaded;
}

void print_route(void *void_route) {
	ipv4_route *route = (ipv4_route *)void_route;
	printf("%u.%u.%u.%u/%u",
		(route->ip >> 24) & 0x0FF,
		(route->ip >> 16) & 0x0FF,
		(route->ip >> 8 ) & 0x0FF,
		(route->ip      ) & 0x0FF,
		route->netmask_bits);
}

void print_route_nl(void *void_route) {
	ipv4_route *route = (ipv4_route *)void_route;
	print_route(route);
	printf("\n");
}

void print_routes(List *routes) {
	list_foreach(routes, print_route_nl);
}

// large_network = small netmask
// small_network = large netmask
int is_network_prefix(ipv4_route *large_network, ipv4_route *small_network) {
	unsigned int mask = netmask_of_bits(large_network->netmask_bits);
	return (large_network->ip & mask) == (small_network->ip & mask);
}

ipv4_route *route_create() {
	ipv4_route *route = malloc(sizeof(ipv4_route));
	return route;
}

ipv4_route *route_copy(ipv4_route *route) {
	if (route == NULL) {
		return NULL;
	}

	ipv4_route *copy = route_create();
	if (copy != NULL) {
		memcpy(copy, route, sizeof(ipv4_route));
	}

	return copy;
}

bool add_route(List *routes, ipv4_route *route) {
	ListIter route_iterator;
	list_iter_init(&route_iterator, routes);

	ipv4_route *compare_route;
	while (list_iter_next(&route_iterator, (void **)&compare_route) != CC_ITER_END) {
		if (compare_route->netmask_bits > route->netmask_bits) {
			if (is_network_prefix(route, compare_route)) {
				// new route will consume this one
				list_iter_remove(&route_iterator, NULL);
			}
		} else if (compare_route->netmask_bits < route->netmask_bits) {
			if (is_network_prefix(compare_route, route)) {
				// ignore route, we already have a larger prefix
				return false;
			}
		}
	}	

	list_add(routes, route_copy(route));
	return true;
}

List *minimal_routes(List *routes) {
	List *minimal_routes;
	list_new(&minimal_routes);

	ListIter route_iterator;
	list_iter_init(&route_iterator, routes);

	ipv4_route *route;
	while (list_iter_next(&route_iterator, (void **)&route) != CC_ITER_END) {
		add_route(minimal_routes, route);
	}

	return minimal_routes;
}

int main(int argc, char **argv) {
	int route_count = get_number_of_routes();
	if (route_count <= 0) {
		fprintf(stderr, "ERROR: Invalid number of IPv4 routes given.");
		return 1;
	}

	List *routes;
	list_new(&routes);
	if (load_routes(routes) == route_count) {
		List *min_routes = minimal_routes(routes);
		if (min_routes != NULL) {
			print_routes(min_routes);
			list_destroy_free(min_routes);
		}
	}

	list_destroy_free(routes);
	return SUCCESS;
}

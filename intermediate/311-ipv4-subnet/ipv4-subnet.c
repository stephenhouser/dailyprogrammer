#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <strings.h>
#include <array.h>

#define SUCCESS	0

typedef struct _ipv4_route {
	uint32_t ip;
	uint8_t net_bits;
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

uint32_t ipv42l(char *ipv4_string) {
	uint32_t ipv4;
	unsigned int b0, b1, b2, b3;

	int quads = sscanf(ipv4_string, "%u.%u.%u.%u", &b3, &b2, &b1, &b0);
	if (quads != 4) {
		return 0;
	}

	ipv4 = b3 << 24 | b2 << 16 | b1 << 8 | b0;
	return ipv4;
}

ipv4_route *parse_route(char *line) {
	chomp(line);
	trim(line);
	char *ip_string = strtok(line, "/");
	char *net_string = strtok(NULL, "/");
	if (ip_string == NULL || net_string == NULL) {
		return NULL;
	}

	ipv4_route *route = malloc(sizeof(ipv4_route));
	if (route == NULL) {
		return NULL;
	}

	route->ip = ipv42l(ip_string);
	route->net_bits = atoi(net_string);
	return route;
}

int load_routes(array_t *routes, int route_count) {
	char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

	int route_index = 0;

	// read ipv4 subnet specifications
    while ((read = getline(&line, &len, stdin)) != -1) {
		ipv4_route *route = parse_route(line);
		array_set(routes, route_index++, route);
	}

	free(line);
	return route_index;
}

void print_route(ipv4_route *route) {
	printf("%u.%u.%u.%u/%u",
		(route->ip >> 24) & 0x0FF,
		(route->ip >> 16) & 0x0FF,
		(route->ip >> 8 ) & 0x0FF,
		(route->ip      ) & 0x0FF,
		route->net_bits);
}

void print_routes(array_t *routes) {
	for (int i = 0; i < array_size(routes); i++) {
		ipv4_route *route = array_get(routes, i);
		print_route(route);
		printf("\n");
	}
}

int covers_route(ipv4_route *parent, ipv4_route *child) {
	if (parent->net_bits > child->net_bits) {
		return 0;
	}

	unsigned int mask = 0xFFFFFFFE << parent->net_bits;
	return (parent->ip & mask) == (child->ip & mask);
}

void minimize_routes(array_t *routes) {
	for (int parent_index = 0; parent_index < array_size(routes); parent_index++) {
		ipv4_route *parent = array_get(routes, parent_index);
		if (parent != NULL) {
			for (int child_index = 0; child_index < array_size(routes); child_index++) {
				if (parent_index == child_index) {
					continue;
				}

				ipv4_route *child = array_get(routes, child_index);
				if (child != NULL) {
					printf("Cover? ");
					print_route(parent);
					printf(" - ");
					print_route(child);
					if (covers_route(parent, child)) {
						printf(" YES!");
						free(child);
						array_set(routes, child_index, NULL);
					}
					printf("\n");
				}
			}
		}
	}	
}

int main(int argc, char **argv) {
	int route_count = get_number_of_routes();
	if (route_count <= 0) {
		fprintf(stderr, "ERROR: Invalid number of IPv4 routes given.");
		return 1;
	}

	array_t routes;
	array_init(&routes, route_count);

	if (load_routes(&routes, route_count)) {
		minimize_routes(&routes);
		print_routes(&routes);
	}

	// free routes
	for (int i = 0; i < array_size(&routes); i++) {
		ipv4_route *route = array_get(&routes, i);
		array_set(&routes, i, NULL);
		free(route);
	}
	array_destroy(&routes);

	return SUCCESS;
}

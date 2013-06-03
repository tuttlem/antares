
#ifndef __ant_map_h_

#define __ant_map_h_

#include <stdlib.h>
#include <string.h>

#include "defs.h"

/** Allocates a map structure and initializes it */
struct _t_ant_map* ant_map_allocate(int width, int height);

/** Destroys an already allocated structure */
void ant_map_destroy(struct _t_ant_map **map);

#endif /* __ant_map_h_ */

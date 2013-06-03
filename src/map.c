
#include "map.h"

/** Allocates a map structure and initializes it */
struct _t_ant_map* ant_map_allocate(int width, int height) {

   struct _t_ant_map *map = malloc(sizeof(struct _t_ant_map));

   /* bug out if we couldn't allocate */
   if (!map) {
      return NULL;
   }

   map->w = width;
   map->h = height;

   /* allocate the cells */
   map->cells = calloc(width * height, sizeof(struct _t_ant_cell));

   /* test for a failed alloc */
   if (!map->cells) {
      /* clean up before leaving! */
      free(map);
      return NULL;
   }

   /* initialize the cells */
   memset(map->cells, width * height, sizeof(struct _t_ant_cell));

   return map;
}

/** Destroys an already allocated structure */
void ant_map_destroy(struct _t_ant_map **map) {

   /* sanity check the arguments */
   if (!map || !(*map)) {
      return ;
   }

   /* check if the cells need to be freed */
   if ((*map)->cells) {
      free((*map)->cells);
      (*map)->cells = NULL;
   }

   /* free the main structure */
   free(*map);
   *map = NULL;

}


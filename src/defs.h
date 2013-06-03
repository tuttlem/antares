
#ifndef __ant_defs_h_

#define __ant_defs_h_

#define ANT_CT_NONE     0x0000000

/* no significant bits set, can do anything */
#define ANT_CT_SAND     0x0000001
#define ANT_CT_DIRT     0x0000002
#define ANT_CT_MUD      0x0000003
#define ANT_CT_GRASS    0x0000004
#define ANT_CT_PATH     0x0000005

/* 32nd bit set, can't walk on/through these things */
#define ANT_CT_WATER    0x8000000
#define ANT_CT_BUSH     0x8000001
#define ANT_CT_TREE     0x8000002
#define ANT_CT_BOULDER  0x8000003

/* 31st bit set, can walk on, but causes damage */
#define ANT_CT_LAVA     0x4000000
#define ANT_CT_THORNS   0x4000001

#define ant_cell_damage(c)      (c & 0x40000000)
#define ant_cell_blocked(c)     (c & 0x80000000)
#define ant_map_cell(map, x, y) (map->cells[x + (y * map->w)])

/** Defines a player in-game */
struct _t_ant_player {
   char *name;          /* the name of the player */
   int   health;        /* yes - negative, in case we want them to turn
                           zombie and make their way back to alive! */

   /* inventory (orbs, weapons, etc) */
   /* money */
};

/** Defines a map of cells */
struct _t_ant_map {
   int                 w, h;  /* x-y dims for the map */
   struct _t_ant_cell *cells; /* the map data itself */
};

/** Defines a single cell within any map */
struct _t_ant_cell {
   unsigned int type;      /* the type of map cell that this is */
   int          val;       /* the value of the cell (how much damage) */
} ant_cell;


#endif /* __ant_defs_h_ */

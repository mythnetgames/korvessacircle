#ifndef KORVESSA_DEFS_H
#define KORVESSA_DEFS_H

#include "structs.h"

/* Races */
typedef enum {
    RACE_HUMAN,
    RACE_DWARF,
    RACE_ELF,
    RACE_HALFLING,
    RACE_ORC,
    RACE_OTHER,
    NUM_KORVESSA_RACES
} korvessa_race_t;

extern const char *korvessa_race_names[NUM_KORVESSA_RACES];

/* Personalities */
typedef enum {
    PERS_STALWART,
    PERS_SHARPEYED,
    PERS_ARTIFICER,
    PERS_SILVERTONGUED,
    PERS_HIDDEN,
    PERS_DEVOTED,
    PERS_INSIGHTFUL,
    PERS_FREEHANDS,
    NUM_KORVESSA_PERSONALITIES
} korvessa_personality_t;

extern const char *korvessa_personality_names[NUM_KORVESSA_PERSONALITIES];

/* Factions */
typedef enum {
    FACTION_CIVIC_ORDER,
    FACTION_LABORERS,
    FACTION_MERCHANTS,
    FACTION_NOBILITY,
    FACTION_UNDERBELLY,
    FACTION_WATCHER_CULT,
    FACTION_SCHOLARS,
    FACTION_FEYLIKS_FREEFOLK,
    NUM_KORVESSA_FACTIONS
} korvessa_faction_t;

extern const char *korvessa_faction_names[NUM_KORVESSA_FACTIONS];

/* Personality bonus struct */
typedef struct {
    int stat_bonus[6]; /* STR, DEX, CON, INT, WIS, CHA */
    int skill_bonus[10]; /* Example: up to 10 skills */
    int standing_bonus[NUM_KORVESSA_FACTIONS];
    /* Add passives as needed */
} personality_bonus_t;

/* Prototypes for chargen logic */
int validate_race(const char *input);
int validate_personality(const char *input);
void apply_personality_bonuses(struct char_data *ch, korvessa_personality_t pers);

#endif /* KORVESSA_DEFS_H */

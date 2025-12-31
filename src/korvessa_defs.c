#include "korvessa_defs.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Race names */
const char *korvessa_race_names[NUM_KORVESSA_RACES] = {
    "Human", "Dwarf", "Elf", "Halfling", "Orc", "Other"
};

/* Personality names */
const char *korvessa_personality_names[NUM_KORVESSA_PERSONALITIES] = {
    "Stalwart", "Sharpeyed", "Artificer", "Silvertongued", "Hidden", "Devoted", "Insightful", "Freehands"
};

/* Faction names */
const char *korvessa_faction_names[NUM_KORVESSA_FACTIONS] = {
    "Civic Order", "Laborers", "Merchants", "Nobility", "Underbelly", "Watcher Cult", "Scholars", "Feyliks Freefolk"
};

/* Example: Simple validation for race by name (case-insensitive) */
int validate_race(const char *input) {
    for (int i = 0; i < NUM_KORVESSA_RACES; ++i) {
        if (input && korvessa_race_names[i] && strcasecmp(input, korvessa_race_names[i]) == 0)
            return i;
    }
    return -1;
}

int validate_personality(const char *input) {
    for (int i = 0; i < NUM_KORVESSA_PERSONALITIES; ++i) {
        if (input && korvessa_personality_names[i] && strcasecmp(input, korvessa_personality_names[i]) == 0)
            return i;
    }
    return -1;
}

/* Apply personality bonuses to a character (stub, to be expanded) */
void apply_personality_bonuses(struct char_data *ch, korvessa_personality_t pers) {
    /* TODO: Implement stat/skill/standing bonuses based on personality */
    (void)ch;
    (void)pers;
}

/* TODO: Add validation and application for standing, public knowledge, background as needed */

#ifndef KORVESSA_SKILLS_H
#define KORVESSA_SKILLS_H

#include "structs.h"

/* Returns a skill check result for crafting (uses INT/DEX) */
int crafting_skill_check(struct char_data *ch, int skill_num);

/* Returns a skill check result for social skills (uses CHA) */
int social_skill_check(struct char_data *ch, int skill_num);

#endif /* KORVESSA_SKILLS_H */

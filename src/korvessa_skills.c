#include "korvessa_skills.h"
#include "utils.h"

/* Crafting skill check: base skill + INT and DEX modifiers */
int crafting_skill_check(struct char_data *ch, int skill_num) {
    int int_mod = (GET_INT(ch) - 10) / 2;
    int dex_mod = (GET_DEX(ch) - 10) / 2;
    return GET_SKILL(ch, skill_num) + int_mod + dex_mod;
}

/* Social skill check: base skill + CHA modifier */
int social_skill_check(struct char_data *ch, int skill_num) {
    int cha_mod = (GET_CHA(ch) - 10) / 2;
    return GET_SKILL(ch, skill_num) + cha_mod * 2;
}

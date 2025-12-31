/* ************************************************************************
*   File: act.korvessa.c                                  Korvessa Custom *
*  Usage: Example crafting and social commands for KorvessaRPI            *
************************************************************************ */

#include "conf.h"
#include "sysdep.h"
#include "structs.h"
#include "utils.h"
#include "comm.h"
#include "interpreter.h"
#include "korvessa_skills.h"

/* Example: Craft command (uses INT/DEX) */
ACMD(do_craft)
{
    int skill_num = SKILL_CRAFT; /* Replace with actual skill number */
    int result = crafting_skill_check(ch, skill_num);
    int roll = rand_number(1, 100);
    if (roll <= result) {
        send_to_char(ch, "You successfully craft the item!\r\n");
        /* Add item creation logic here */
    } else {
        send_to_char(ch, "You fail to craft the item.\r\n");
    }
}

/* Example: Persuade command (uses CHA) */
ACMD(do_persuade)
{
    int skill_num = SKILL_PERSUADE; /* Replace with actual skill number */
    int result = social_skill_check(ch, skill_num);
    int roll = rand_number(1, 100);
    if (roll <= result) {
        send_to_char(ch, "You successfully persuade your target!\r\n");
        /* Add persuasion effect logic here */
    } else {
        send_to_char(ch, "Your attempt at persuasion fails.\r\n");
    }
}

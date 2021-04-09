// molianspells.c 【太乙仙法】
inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
	if( (int)me->query_skill("spells", 1) < 10 
		|| (int)me->query_skill("spells", 1) <= (int)me->query_skill("molianspells", 1) )
		return notify_fail("你的法术修为还不够高深，无法学习魔莲法。\n");
	return 1;
}

string cast_spell_file(string spell)
{
        return CLASS_D("mojie") + "/molian-spells/" + spell;
}

string type() { return "magic";} 

mixed base_damage(){ return 170;}
// buddhism.c

inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
	if( (int)me->query_skill("spells") <= (int)me->query_skill("buddhism") )
		return notify_fail("你的法术修为还不够高深，无法学习大乘佛法。\n");
	if( (int)me->query("bellicosity") > 100 )
		return notify_fail("你的杀气太重，无法修炼大乘佛法。\n");
	return 1;
}

string cast_spell_file(string spell)
	{
return CLASS_D("putuo") + "/buddhism/" + spell;

	}

string type() { return "magic";}

mixed base_damage(){ return 190;}
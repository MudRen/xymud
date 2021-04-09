
inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
       if ( me->query("class")!="human") return notify_fail("你非人族，无法学习。\n");
	if( (int)me->query_skill("spells", 1) < 10 
		|| (int)me->query_skill("spells", 1) <= (int)me->query_skill("mahayana", 1) )
		return notify_fail("你的法术修为还不够高深，无法学习大乘涅磐功。\n");
	return 1;
}

string cast_spell_file(string spell)
{
        return CLASS_D("emei") + "/mahayana/" + spell;
}

string type() { return "magic";} 

mixed base_damage(){ return 160;}
//天师符法 蜀山法术

inherit SKILL;
string type() { return "spells"; }
int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
        if( me->query("family/family_name") != "蜀山派" )
        	return notify_fail("天师符法只有蜀山的人才可以学。\n");
        if( (int)me->query_skill("spells",1) < 20 )
        	return notify_fail("你的法术修为还不够高深，无法学习天师符法。\n");
        return 1;
}

string cast_spell_file(string spell)
{
        return CLASS_D("shushan") + "/tianshi-fufa/" + spell;
}

mixed base_damage(){ return 160;}
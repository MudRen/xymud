inherit SKILL;
int valid_enable(string usage) { return usage=="spells"; }
int valid_learn(object me)
{
       if ( me->query("class")!="yao" && !me->samsara_check("xiuluo-yinshagong"))         return notify_fail("你非妖族弟子，无法习得！\n");
        if( (int)me->query_skill("spells", 1) < 20
        ||      (int)me->query_skill("spells",1) <= (int)me->query_skill("xiuluo-yinshagong",1) )
                return
notify_fail("你的法术修为还不够高深，无法学习修罗阴煞功．\n");
        return 1;
}
string cast_spell_file(string spell)
{
        return CLASS_D("wudu") + "/xiuluo-yinshagong/" + spell;
}
string type() { return "magic"; }

mixed base_damage(){ return 170;}
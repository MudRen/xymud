// ice_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
	int damage_kee=10, damage_sen=10;

	if(me->query("max_kee")>200)
		damage_kee=me->query("max_kee")/15;
	if(me->query("max_sen")>200)
		damage_sen=me->query("max_sen")/15;
        if(damage_kee > 80) damage_kee = 80;
        if(damage_sen > 80) damage_sen = 80;
                                                	
	me->receive_wound("sen", damage_sen);
	me->receive_wound("kee", damage_kee);
	me->set_temp("death_msg","寒毒发作死了。\n");
	me->apply_condition("ice_poison", duration - 1);

	if( (int)me->query("kee") < (int)me->query("max_kee")/4 )
		message_vision("$N嘴唇乌青发亮，浑身抖个不停，不知道中了什么邪。\n", me);
	else if( (int)me->query("kee") < (int)me->query("max_kee")/2 )
		message_vision("$N嘴唇发青，身子微微发抖，好象冷得厉害。\n", me);		
	else 
		message_vision("$N打了个寒颤。\n", me);
		
	if( duration < 1 ) return 0;
	return 1;
}

int no_apply(object who)
{
	string fam;
	if( !who || !living(who) )
		return 0;
	fam = who->query("family/family_name");
	if( !fam || fam!="火云洞" )
		return 0;
	if( random(who->query("max_force"))<350 )
		return 0;
	message_vision(HIR"$N"HIR"身上隐约火光一闪，结果腾起一阵水雾，身上的寒毒一扫而空。\n"NOR,who);
	return 1;
}				
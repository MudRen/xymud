#include <skill.h>
#include <combat.h>
#include <ansi.h>
inherit __DIR__"seal.c";
#include <combat.h>

void create()
{
	set_name("神霄电法符", ({"light seal", "seal", "paper"}));
	set_weight(100);
	if(clonep())
        set_default_object(__FILE__);
	else    
	{
        	set("long","一张画上了符咒的桃符纸，中央有个大大的“电”字。\n");
        	set("unit", "叠");
        	set("base_unit", "张");
        	set("value", 0);
        	set("no_put",1);
        	set("no_sell",1);
        }
	set_amount(1);
	setup();
}

int ji_ob(object victim)
{
	object seal=this_object();
	object me=this_player();
	object where=environment(me);
	
	int ap,dp,damage;
	
	if(me->is_busy())
        	return err_msg("你正忙着呢，无法祭神霄电法符。\n");
	if( !victim )
		return err_msg("你想祭的人不在这里。\n");
	if( where->query("no_magic"))
        	return err_msg("这里不能祭神霄电法符。\n");
	if( !me->is_fighting(victim))
        	return err_msg("只有战斗中才能祭神霄电法符。\n");
	if( (int)me->query("mana") < 100 )
	        return err_msg("你的法力不能控制神霄电法符。\n");
	if( (int)me->query("sen") < 100 )
        	return err_msg("你的精神不足，很难驾驭神霄电法符。\n");

	ap = COMBAT_D->skill_power(me,"spells",SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(me,"victim",SKILL_USAGE_DEFENSE);
	damage = me->query_skill("spells");
	damage = damage*(me->query_spi()/3);
	damage+= (15/10)*(me->query("mana_factor"));
	damage-= (int)victim->query_temp("apply/armor_vs_spells")/5;
	if( damage<0 )
		damage = 150;
	me->add("mana", -50);
	
	message_vision(HIC "\n$N"HIC"大喊一声“着”，手一挥，祭出了一张神霄电法符！\n神霄电法符「呼」地一下飞到半空，只听几声霹雳后，闪出一道银光射向$n"HIC"。\n" NOR,me,victim);
	if( random(ap+dp)>=dp/2 )
	{
		if( !me->query("env/brief_message") && !victim->query("env/brief_message") )
			message_vision(HIR "\n$n"HIR"躲闪不及，银光电般透体而过，拖出一条长长的血箭。\n" NOR,me,victim);
		if( me->query("mana_factor") )
		{
			victim->receive_damage("kee", damage/3, me,"cast");
			COMBAT_D->report_status(victim,1);
		}
		victim->receive_damage("kee", damage, me,"cast");
		COMBAT_D->report_status(victim);
	}
	else if( random(ap+dp)<dp/2 )
	{
		if( !me->query("env/brief_message") && !victim->query("env/brief_message") )
			message_vision(HIC "但是$n"HIC"伸指一弹，银光一暗，神霄电法符反向$N"HIC"贴去！\n" NOR, me,victim);
		if( random(ap+dp)>=ap )
		{
			if( !me->query("env/brief_message") && !victim->query("env/brief_message") )
				message_vision(HIR "结果扑！地一声神霄电法符在$n"HIR"身上烧了起来！\n" NOR,victim,me);
			me->receive_damage("kee", damage/5, victim,"cast");
			COMBAT_D->report_status(me);
		}
		else
		{
			if( !me->query("env/brief_message") && !victim->query("env/brief_message") )
				message_vision(HIC "\n$n"HIC"猛退几步，躲了过去。\n" NOR, victim,me);
		}	
	}						
	else
	{
		if( !me->query("env/brief_message") && !victim->query("env/brief_message") )
			message_vision(HIC "\n$n"HIC"猛退几步，躲了过去。\n" NOR, me,victim);
	}
			
	me->set_temp("no_cast",time());
	me->set_temp("jjf_ji_seal",time());
	me->set_temp("no_cast_time",5); 
	if ( seal->query_amount()>1 )  seal->add_amount(-1);
	else destruct(seal);
	return 1;
}


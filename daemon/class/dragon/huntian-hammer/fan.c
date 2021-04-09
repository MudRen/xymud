#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

void remove_effect(object me)
{
	if( me )
	{
		me->delete_temp("pfm_action");
		me->delete_temp("sea_fan");
		me->set_temp("sea_fan_end",time());
		tell_object(me,"你收起了「翻江倒海」状态。\n");
	}
}

varargs void fan(object me,object target,object weapon,int damage)
{
	object *armor,ob;
	mapping temp;
	string msg;
	int p,succ;
	
        if( !me ) 
                return;
	if( !me->query_temp("sea_fan") )
	{
		remove_effect(me);
		return;
	}
	if( !weapon )
		weapon = me->query_temp("weapon");
	if( !weapon )
	{
		remove_effect(me);
		return;
	}
	if( !target )  target = offensive_target(me);
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me 
 	 || !me->is_fighting(target) 
 	 || !living(me) )
		return; 
	if( time()<me->query_temp("last_pfm_action")+2 )
		return;
	me->set_temp("last_pfm_action",time());	
	succ = COMBAT_D->attack_percent(me,target,TYPE_PERFORM);
	if( succ<1 )	
		return;	

	temp = target->query_temp("armor");
	if( temp && mapp(temp) )
	{
		armor = values(temp);
		if( armor && arrayp(armor) && sizeof(armor)>0 )
		{
			ob = armor[random(sizeof(armor))];
			if( ob )
			{
				
				message("vision",HIY"\n"+weapon->name()+HIY"上冲出一道金光，将"+target->name()+HIY"身上的"+ob->name()+HIY"打的灵气全无，失去了作用！\n"NOR,environment(me),({target}));
				tell_object(target,HIY"\n"+weapon->name()+HIY"上冲出一道金光，将你的"+ob->name()+HIY"打的灵气全无，失去了作用！\n"NOR);
				me->add("force",-50);
				ob->unequip();
				if( ob->query("changed") && ob->query("owner_id")==target )
     				{
     					if( ob->query("exp")>=500 )
     					{
     						ob->add("exp",-500);
     						message_combatd(HIC+ob->name()+HIC"上闪了一闪，居然恢复了。\n"NOR,me,target);
					}
					else	ob->set("breaked",1);
				}	
				else	ob->set("breaked",1);
			}
		}
	}
} 

int perform(object me, object target)
{
        object weapon;

	if( me->query_level()<15 )
		return notify_fail("你的人物等级不够。\n");
	if((int)me->query_skill("huntian-hammer", 1)<150)
        	return notify_fail("你的混天锤级别还不够，使用这一招会有困难！\n");
	if((int)me->query_skill("hammer", 1)<150)
        	return notify_fail("你的锤法还不够熟练！\n");
        if( me->query("family/family_name") != "东海龙宫" )
                return notify_fail("「翻江倒海」是龙宫不传之密！\n"); 
        if(me->query_skill("force",1) < 150)
                return notify_fail("你的内功底子不足。\n");
	if((string)me->query_skill_mapped("force")!="dragonforce")
                return notify_fail("「翻江倒海」必须以龙神心功为底子。\n");
        if(me->query("force") < 500 )
                return notify_fail("你的内力不足。\n");      
	if( time()<me->query_temp("sea_fan_end")+10 )
		return notify_fail("这招不能频繁使用。\n");
        weapon = me->query_temp("weapon");
        if( !weapon 
	 || (weapon->query("skill_type")!="hammer"
	  && weapon->query("use_apply_skill")!="hammer") )
		return notify_fail("你的锤子呢？\n");
	if( me->query_temp("sea_fan") )
		return notify_fail("你现在已经「翻江倒海」了。\n");
	
	message_vision(HIC"$N"HIC"舞动"+weapon->name()+HIC"，顿时天地变色，$P周身好似被厚郁的水气包围，背后隐现巨涛骇浪异象。\n"NOR,me);
	me->add("force",-200);
	me->set_temp("sea_fan",1);
	me->set_temp("pfm_action", "lg_fan");
	me->start_call_out( (: call_other, "/daemon/class/dragon/huntian-hammer/fan.c", "remove_effect", me:),me->query_skill("huntian-hammer")/10);
	me->start_busy(2);
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：翻江倒海
        外功所属：混天锤
        外功效果：一定时期内使自身处于翻江倒海状态
        	  此状态下，战斗中有几率出现「破甲」效果
        	  (使防具的损耗甚至损坏，需修复后才能重新装备)
        	  「破甲」几率可通过领悟提高
        	  翻江倒海状态下支持其他类型的武器	
                  状态结束后冷却10秒
                  施展后自身busy 2 秒
        外功条件：
                  龙宫弟子
        	  人物等级15级	
                  内力500点，消耗200点，每次「破甲」消耗50点
                  基本内功150级并激发龙神心法
                  基本锤法150级并激发混天锤
                  混天锤150级

LONG;
me->start_more(str);
return 1;
}

void remove()
{
	int i;
	object me,*usr = users();
	if( i=sizeof(usr)>0 )
	{
		while(i--)
		{
			if( !usr[i] || !environment(usr[i])
			 || !objectp(usr[i]) )
				continue;
			if( usr[i]->query_temp("sea_fan") )
			{
				me = usr[i];
				me->delete_temp("pfm_action");
				me->delete_temp("sea_fan");
				me->set_temp("sea_fan_end",time());
				tell_object(me,"你收起了「翻江倒海」状态。\n");
			}
		}
	}
}
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object *armor,ob, weapon;
	int damage,i;
	mapping temp;
	string msg,succ_msg;
	
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
    	if( time()-(int)me->query_temp("sea_break")<20 )
        	return notify_fail("绝招用多就不灵了！\n"); 
    	if((int)me->query("force") < 500 )
        	return notify_fail("你的内力不足！\n");
    	if((int)me->query("kee") < 500 )
        	return notify_fail("你的气血不足，没法子施用外功！\n");
    	if((int)me->query_skill("huntian-hammer", 1)<100)
        	return notify_fail("你的混天锤级别还不够，使用这一招会有困难！\n");
	weapon = me->query_temp("weapon");
	if( !weapon
	 || ( weapon->query("skill_type")!="hammer"
	   && weapon->query("use_apply_skill")!="hammer" ) )	
		return notify_fail("你手里的锤子呢？\n");
		
    	if( !target ) target = offensive_target(me);
	if( !target
 	 || !target->is_character()        
 	 || target->is_corpse()
 	 || target==me
 	 || !me->is_fighting(target) )
        	return notify_fail("你要对谁施展这一招「混元一破」？\n");

    	msg = HIY"$N"HIY"吐出一口鲜血，浑身泛起一层龙鳞，双眸中闪出一道银芒，但见$w"HIY"上带着隐隐风雷之声，对着$n"HIY"发出了全力一击！\n"NOR;
    	succ_msg = HIR"$n"HIR"躲闪不及，被打个正着！\n"NOR;
    	
    	if( !target->is_killing(me->query("id")) )
        	target->kill_ob(me);
    	me->add("force", -350);
    	me->receive_damage("kee",300);
    	me->set_temp("sea_break",time());

	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg);
	me->set_temp("pfm_msg",0);
	
	if( damage<1 )
	{
		message_combatd(HIY"却被$n"HIY"躲开了！\n"NOR,me,target);
		me->start_busy(5);
		return 1;
	}
	if( target && me->is_fighting(target) )
	{
		temp = target->query_temp("armor");
		if( temp && mapp(temp) )
		{
			armor = values(temp);
			if( armor && arrayp(armor) && sizeof(armor)>0 )
			{
				for(i=0;i<sizeof(armor);i++)
				{
					ob = armor[i];
					if( !ob )
						continue;
					ob->unequip();	
					message_vision(HIY"$n"HIY"身上的"+ob->name()+HIY"打的灵气全无，失去了作用！\n"NOR,me,target);
					if( ob->query("changed") && ob->query("owner_id")==target )
     					{
     						if( ob->query("exp")>=500 )
     						{
     							ob->add("exp",-500);
     							message_vision(HIC+ob->name()+HIC"上闪了一闪，居然恢复了。\n"NOR,me,target);
     						}
     						else	ob->set("breaked",1);
     					}	
					else	ob->set("breaked",1);
				}
			}
		}	
	}
    	me->start_busy(3);
    	return 1;
}

int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
        外功名称：混元一破
        外功所属：混天锤
        外功效果：将龙神之力附加在武器之上，猛烈攻击对方
                  造成对方防具的损耗甚至损坏(需修复后才能重新装备)
                  施展后自身busy 3 秒，冷却时间10秒，不中则自身busy 5 秒 
        外功条件：
        	  人物等级10级
                  内力500点，消耗350点
                  气血500点，消耗300点
                  混天锤100级
LONG;
me->start_more(str);
return 1;
}
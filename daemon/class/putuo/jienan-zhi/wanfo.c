// last updated by qingxia 9-14-2002
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	string msg,succ_msg;   
	int damage,flag=0;
	object armor,*ars;
	mapping ar;
      
      	if( me->query_level()<25 )
      		return notify_fail("你的人物等级不够。\n");
	if( !target ) target = offensive_target(me);
		if( !target        
 	 || !target->is_character()        
 	 || target->is_corpse()        
 	 || !me->is_fighting(target) )
    		return notify_fail("「万佛朝宗」只能在战斗中对对手使用。\n");        
	if(me->query("family/family_name") != "南海普陀山" ) 
        	return notify_fail("你是哪儿偷学来的武功！\n");
	if( (int)me->query_skill("jienan-zhi",1) < 200 )
        	return notify_fail("你的劫难指法不够娴熟，不会使用佛门神功「万佛朝宗」！\n");
	if( (int)me->query_skill("lotusforce",1) < 200 )
        	return notify_fail("你的莲台心法等级不够，不能使用「万佛朝宗」！\n");  
	if( (int)me->query("force") < 800 )
        	return notify_fail("你的内力太少了，无法使用出「万佛朝宗」！\n");   
     
	msg = HIY"$N"HIY"忽作怒目金刚状，双手结印，一式「万佛朝宗」朝向$n"HIY"胸前按去！\n"NOR;
	succ_msg = HIR"$n"HIR"只觉得霍的胸口一阵剧痛，已经被拍中了前胸！$P一口鲜血狂喷而出！\n"NOR;
	me->set_temp("pfm_msg",1);
	me->add_temp("apply/attack",50);
	me->add("force",-150); 
	damage = 800;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,damage);
	me->delete_temp("pfm_msg");
	me->add_temp("apply/attack",-50);
     	if( damage>0 )
     	{
		if( !target->query_condition("dashouyin"))
			target->apply_condition("dashouyin",me->query_skill("jienan-zhi")/4);
     		ar = target->query_temp("armor");
                if( ar && mapp(ar) && sizeof(ar)>0 )
     		{
     			ars = values(ar);
                        if( ars && arrayp(ars) && sizeof(ars)>0 )
     			{
     				armor = ars[random(sizeof(ars))];
     				if( armor )
     					flag = 1;
     			}
     		}
     		if( flag>0 && armor )
     		{
     			message_combatd(HIY"只见这斗大的佛印正好印在$n"HIY"的"+armor->name()+HIY"上，越变越大，竟将它震得灵气全无！\n"NOR, me,target);
     			if( armor->query("changed") && armor->query("owner_id")==target )
     			{
     				if( armor->query("exp")>=500 )
     				{
     					armor->add("exp",-500);
     					message_combatd(HIC+armor->name()+HIC"上闪了一闪，居然恢复了。\n"NOR,me,target);
     				}
				else
				{
		     			armor->unequip();
     					armor->set("breaked",1);
				}
     			}
     			else
     			{
	     			armor->unequip();
     				armor->set("breaked",1);
     			}
     		}
     		me->start_busy(1);				
	}
	else	
	{
		message_vision(HIY"结果给$n"HIY"闪开了。\n"NOR,me,target);
		me->start_busy(1+random(2));
	}      
	return 1;
}


int help(object me)
{
string str;
if ( !me )      return 0;
str = @LONG
        外功名称：万佛朝宗
        外功所属：劫难指法
        外功效果：以佛印对敌一击，使对方中大手印内伤(状态不可叠加)
        	  命中则对使对方防具损坏一件(需修复后才能重新装备)
        	  已绑定的防具如果经验大于500，则不会损坏，但会扣除500点经验
                  使用后自身busy 1 秒，失败则自身busy 1-2 秒
        外功条件：
        	  普陀弟子
        	  人物等级25级
                  内力800点，消耗150点
                  劫难指法200级
                  莲台心法200级
LONG;
me->start_more(str);
return 1;
}


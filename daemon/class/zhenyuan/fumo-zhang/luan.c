#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

void remove_effect(object me)
{
	if( me )
	{
		me->delete_temp("pfm_action");
		me->delete_temp("wzg_luan");
		me->set_temp("wzg_luanpifeng",time());
		message_vision("$N收起了「乱披风」状态。\n",me);
	}
}

varargs void luanpifeng(object me,object target,object weapon,int damage)
{
	mapping action;
	string msg;
        if( !me ) 
                return;
	if( !me->query_temp("wzg_luan") )
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
	if( time()<me->query_temp("last_pfm_action")+1 )
		return;
	me->set_temp("last_pfm_action",time());	
	if( random(me->query("force"))<50 )
		return;	
	action = me->query("actions");
	if( !action || !mapp(action) || undefinedp(action["action"]) )
		return;
					                 
	msg = "\n$N内息澎湃，身随气引，";
	msg+= action["action"]+"\n";
	msg = COLOR_D->clean_color(msg);
	msg = COLOR_D->replace_color(HIY+msg+NOR,1);
	msg = replace_string(msg,"$N","$N"HIY);
	msg = replace_string(msg,"$n","$n"HIY);
	msg = replace_string(msg,"$w","$w"HIY);
	msg = replace_string(msg,"$W","$W"HIY);
	me->set_temp("pfm_msg",1);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_QUICK,msg);
	me->set_temp("pfm_msg",0);
} 

int perform(object me, object target)
{
        string msg;
        int extra,i,lmt;
        object weapon;

	if( me->query_level()<20 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query_skill("fumo-zhang",1)<180 )
		return notify_fail("你的伏魔杖法还不够纯熟！\n");
	if( me->query_skill("staff",1)<180 )
		return notify_fail("你的基本杖法还不够纯熟！\n");	
        if( me->query("family/family_name") != "五庄观" )
                return notify_fail("「乱披风」是五庄观不传之密！\n"); 
        if(me->query_skill("force",1) < 180)
                return notify_fail("你的内功底子不足，无法运杖如风，施展不出乱披风。\n");
	if((string)me->query_skill_mapped("force")!="zhenyuan-force")
                return notify_fail("「乱披风」必须以镇元神功为底子。\n");
        if(me->query("force") < 500 )
                return notify_fail("你的内力不足，难以随意挥动一把禅杖。\n");      
	if( time()<me->query_temp("wzg_luanpifeng")+4 )
		return notify_fail("你刚刚运杖如风结束，还是歇歇再说。\n");
		                  	
        weapon = me->query_temp("weapon");
        if( !weapon 
	 || (weapon->query("skill_type")!="staff"
	  && weapon->query("use_apply_skill")!="staff") )
		return notify_fail("「乱披风」是伏魔杖法的绝技。\n");
	if( me->query_temp("wzg_luan") )
		return notify_fail("你现在已经运杖如风了。\n");
	
	msg = HIY"$N"HIY"运杖如风，地面随之起伏一降狂风，手中"+ weapon->name()+HIY"舞得泼水不进。\n" NOR;
	message_vision(msg,me,target);
	me->add("force",-150);
	me->set_temp("wzg_luan",1);
	me->set_temp("pfm_action", (: call_other, __FILE__, "luanpifeng" :));
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), me->query_skill("staff")/6);
			          
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return 1;

	me->add("force",-150);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM);
	
	if( me->query_skill("fumo-zhang",1)>=200 )
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM);
	
	if( me->query_skill("fumo-zhang",1)>=300 )	
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM);
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：乱披风
        外功所属：伏魔杖法
        外功效果：一定时期内使自身处于乱披风状态
        	  战斗中使用将对敌进行最多三次的物理攻击
        	  乱披风状态支持其他类型的武器	
                  状态结束后冷却4秒
        外功条件：
                  五庄观弟子
        	  人物等级20级	
                  内力500点，消耗150点，战斗中使用增加消耗150点
                  基本杖法180级并激发伏魔杖法
                  基本内功180级并激发镇元神功
		  伏魔杖法180级

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
			if( usr[i]->query_temp("wzg_luan") )
			{
				me = usr[i];
				me->delete_temp("pfm_action");
				me->delete_temp("wzg_luan");
				me->set_temp("wzg_luanpifeng",time());
				message_vision("$N收起了「乱披风」状态。\n",me);
			}
		}
	}
}
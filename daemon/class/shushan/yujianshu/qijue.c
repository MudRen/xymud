//七诀剑气	以指代剑，发出裂地剑气 敌方全体 剑 	
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object weapon,*enemy;
	int i;
        string msg,succ_msg;
        int damage,p;

      	if( me->query_level()<20 )
      		return notify_fail("你的人物等级不够。\n");
        if((int)me->query("force") < 600 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query_skill("yujianshu",1) < 200
         ||(string)me->query_skill_mapped("sword")!="yujianshu" ) 
                return notify_fail("你的御剑术火候还不到，使用这一招会有困难！\n");
        if((int)me->query_skill("zuixian-wangyue",1) < 200)
        	return notify_fail("你的身法还不够轻灵！\n");
    	        
	me->clean_up_enemy();                
        if( !me->is_fighting() )
        	return notify_fail("「七诀剑气」只能战斗中使用。\n");
	enemy = me->query_enemy();
	if( !intp(i=sizeof(enemy)) 
	 || i<1 )
		return notify_fail("「七诀剑气」只能战斗中使用。\n");
	
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || ( weapon->query("skill_type")!="sword" && weapon->query("use_apply_skill")!="sword" ) )
		return notify_fail("你的剑呢？\n");
	msg = HIY"$N"HIY"大叫一声“赦”，掌中"+weapon->name()+HIY"顿时凌空飞起，霞光一闪，层层剑气从上迸发，发出阵阵轰鸣之声！\n"NOR;
	message_vision(msg,me);
	me->add("force",-200);
	p = me->query_skill("sword")/10;
	me->add_temp("apply/attack",p);
	me->set_temp("pfm_color",HIY);
	me->set_temp("pfm_msg",1);
	i = 7;
	while(i--)
	{
		target = enemy[random(sizeof(enemy))];
		if( !target || !target->is_character()
         	  || target->is_corpse()
         	  || target==me
         	  || !me->is_fighting(target) )
			continue;
		succ_msg = "$n闪避不及，$l被裂地剑气掠体而过，带出一路鲜血，脸色顿时一白！\n";
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,"",succ_msg,0,me->query_skill("sword")/10);
	}	
	me->delete_temp("pfm_color");
	me->delete_temp("pfm_msg");
	me->add_temp("apply/attack",-p);
	me->start_busy(2);
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：七诀剑气
        外功所属：御剑术
        外功效果：发出七道裂地剑气攻击全体敌方
		  自身busy 2 秒
        外功条件：
        	  人物等级20级	
                  内力600点，消耗100-250点
                  御剑术200级并激发
                  醉仙望月步200级
LONG;
me->start_more(str);
return 1;
} 

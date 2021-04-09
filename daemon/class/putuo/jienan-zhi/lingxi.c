#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	int i,damage;
	string msg,succ_msg;

	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name") != "南海普陀山" 
	 && me->query("chushi/chushi_putuo")!="yes" )
    		return notify_fail("你是哪儿偷学来的武功！\n");
	if((int)me->query("force") < 50 )
    		return notify_fail("你的内力不足！\n");
	i=(int)me->query_skill("jienan-zhi",1);
	if( i < 45)
    		return notify_fail("你的劫难指级别还不够，使用这一招会有困难！\n");
	if( time()-(int)me->query_temp("putuo_lingxi")<5 )
    		return notify_fail("你现在内息不顺！\n");
      
	if( !target ) target = offensive_target(me);
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me 
 	 || !me->is_fighting(target) ) 
		return notify_fail("你要对谁施展这一招「灵犀一指」？\n");
    		
	msg = HIY"$N"HIY"心悟佛法，灵犀所至，缓缓伸出右手食指向$n"HIY"凌空一点，一股阳和的气流向$n"HIY"$l直逼过去。\n"NOR;
	succ_msg = HIR"只听见「嗤」的一声轻响，$N"HIR"右手食指已经在$n"HIR"$l戳出一个血窟窿。\n"NOR;
	me->set_temp("pfm_msg",1);
	me->set_temp("putuo_lingxi",time());
	me->add("force",-15);
    	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,200);
    	me->delete_temp("pfm_msg");
    	if( damage<=0 )
    	{
    		message_combatd(HIC"$N"HIC"识得厉害，连忙使一个鹞子翻身躲开了！\n"NOR, target);
    		me->add("force",-5);
    	}	
    	else if( !target->is_busy() )
    	{
		message_combatd(HIY"$N"HIY"的指力正打在$n"HIY"的穴道上，$p登时浑身酸麻动弹不得。\n"NOR,me,target);
            	target->start_busy(2+random(4));
    	}	
	return 1;
}

int help(object me)
{
string str;
if( !me )      return 0;       
str = @LONG
        外功名称：灵犀一指
        外功所属：劫难指法
        外功效果：以阳刚之气聚于指尖，打击对方的气血
        	  固定伤害200点
                  命中后会使对方 busy 2-5 秒
                  使完后，冷却 5 秒
                  失败则内力消耗增加5点
        外功条件：
        	  普陀(出师)弟子
        	  人物等级5级
                  内力50点，消耗15点
                  劫难指法45级
LONG;
me->start_more(str);
return 1;
}


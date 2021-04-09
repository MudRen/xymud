#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

void jiutian(object me,object target)
{
	string msg;
	int damage;
	if( !me )
		return;
	me->delete_temp("leidong");	
	me->set_temp("sea_leidong",time());	         		
	if( !living(me) || me->query("force")<200 )
		return;			
	if( !target )	
		target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
		return;
	damage = me->query_skill("unarmed")/2;
	me->add("force",-100);	
	msg = MAG "\n只见$N"MAG"衣袍鼓起，猎猎飞舞，一声「九天」，拳风“哗”的化出九个光圈，居高临下，直向$n"MAG"$l逼来。\n" NOR;
	me->set_temp("pfm_msg",1);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,"胸口",damage);
	me->set_temp("pfm_msg",0);
}

int perform(object me, object target)
{       
	object weapon;
	string msg;
	int damage;
	
	if( me->query_level()<8 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query("family/family_name")!="东海龙宫") 
        	return notify_fail("非龙宫弟子不能用「雷动九天」！\n"); 
	if( me->query_skill("dragonfight", 1) < 80 
  	 || me->query_skill("unarmed", 1) < 80 )
        	return notify_fail("你有的功夫还不够娴熟，不会使用「雷动九天」。\n");
	if( me->query_skill_mapped("unarmed")!="dragonfight")
	        return notify_fail("「雷动九天」必须靠龙形搏击发出。\n");	
	if( me->query_skill("force", 1) <80)
        	return notify_fail("以你现在的内功修为还使不出「雷动九天」。\n");        
	if( me->query("force") < 200 )
        	return notify_fail("你的真气不够！\n");
	if( time()-(int)me->query_temp("sea_leidong") < 6 )
        	return notify_fail("绝招用多就不灵了！\n");
        if( me->query_temp("leidong") )
        	return notify_fail("你正在蓄力中。\n");
	weapon = me->query_temp("weapon");
	if( weapon )
	{
		if( weapon->query("skill_type")!="unarmed"
		 && weapon->query("use_apply_skill")!="unarmed" )
		 	return notify_fail("『雷动九天』是拳脚上的功夫。\n");
	}        		
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
         	return notify_fail("「雷动九天」只能在战斗中使用。\n");

	msg = RED "突然$N"RED"大喝一声:「雷动」,面色唰的变得通红,须发皆飞,浑身上下充满杀气。\n" NOR;
	message_vision(msg, me); 
	me->set_temp("leidong",1);
        me->set_temp("sea_leidong",time());
	me->add("force",-50);
	damage = me->query_skill("unarmed");
	damage/= 2;
	msg = HIR "        “嗡”的一声，一掌凌空击中$n"HIR"的胸口！\n" NOR;
	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,msg,"胸口",damage);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(YEL"可是$n"YEL"伏地一滚，躲开了$N"YEL"的攻击。\n"NOR,me,target);
	if( me->query_skill("dragonfight",1)>=120 
	 && me->query("force")>100 
	 && target && me->is_fighting(target) )
		me->start_call_out( (: call_other, __FILE__, "jiutian", me,target:),1+random(3));
        else    me->delete_temp("leidong"); 
	return 1;
}	

void remove()
{
       object *obj = livings();
       int i;
       for(i=0;i<sizeof(obj);i++)
             if( obj[i] && objectp(obj[i])
                 && environment(obj[i]) 
                 && obj[i]->query_temp("leidong") )
            {
                  message_vision(HIM"$N"HIM"收起了「雷动九天」的蓄力。\n"NOR,obj[i]);
                  obj[i]->delete_temp("leidong");
            }
}
int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
        外功名称：雷动九天
        外功所属：龙形搏击
        外功效果：给予对方一次带固定伤害的攻击，并蓄力
        	  当龙形搏击120级，则将所蓄之力发出
                  使用后冷却6秒
        外功条件：
        	  龙宫弟子
        	  人物等级8级
                  内力200点，消耗50点，蓄力后攻击消耗150点
                  龙形搏击80级
                  扑击格斗80级
                  内功心法80级
LONG;
me->start_more(str);
return 1;
}


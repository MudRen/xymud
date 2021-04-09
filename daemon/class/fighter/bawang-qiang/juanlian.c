#include <ansi.h>
#include <combat.h>
inherit SSERVER;
		
int perform(object me, object target)
{
        string msg;
        int damage;
        object weapon;
        
        if( me->query_level()<25 )
        	return notify_fail("你的人物等级不够。\n");
        if(me->query("family/family_name")!="将军府")   
                return notify_fail("你不是将军府弟子，不能使用这项技能！\n"); 
        if( (int)me->query_skill("lengquan-force", 1) < 250 )
                return notify_fail("你的冷泉心法还差些火候。\n");
        if( (int)me->query_skill("yanxing-steps", 1) < 250 )
                return notify_fail("你的雁行步法无法配合不攻。\n");
        if( (int)me->query_skill("bawang-qiang", 1) < 250 )
                return notify_fail("你的霸王枪法不够娴熟。\n");
	if(me->query_skill_mapped("spear")!="bawang-qiang")
		return notify_fail("你的霸王枪法不够娴熟。\n");
        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");
	if( me->query("kee")<200 )
		return notify_fail("你气血不平，难以使用此招。\n");                
	if(time()<me->query_temp("jjf_juanlian")+5 ) 
                return notify_fail("绝招使多就不灵了！\n");
                	
        weapon = me->query_temp("weapon");
        if( !weapon
	 || ( weapon->query("skill_type")!="spear"
	   && weapon->query("use_apply_skill")!="spear" ) )
		return notify_fail("难道你已达手中无枪心中有枪的境界？！\n");
        
        if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) )
                return notify_fail("你要对谁施展这一招「珍珠倒卷帘」？\n");
        
        me->receive_damage("kee",100,me);
        me->add("force", -200);
        me->set_temp("jjf_juanlian",time());
        me->set_temp("JL_perform",1);
        
        msg = HIC"\n$N"HIC"将手中$w"HIC"一抖，由下而上翻将上来，一股大力向$n"HIC"狂涌而至，如流沙河水，天幕倒垂！\n"NOR;
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
        if( damage<=0 )
                msg = HIC"\n$N"HIC"见$n"HIC"闪过次招，双手交错，$w"HIC"似巨蟒般倒卷而回！\n"NOR;
        else    msg = HIC"\n$N"HIC"一招得手，顺势双手交错，$w"HIC"似巨蟒般倒卷而回！\n"NOR;     
        damage+= COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_QUICK,msg);
        msg = HIC"\n$N"HIC"两枪出完，$w"HIC"并不罢休，$w"HIC"斗出绚丽的枪花直扑$n"HIC"$l！\n"NOR;
        damage+= COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_QUICK,msg);
        me->set_temp("JL_perform",0);
        
        
        if( (int)me->query_skill("bawang-qiang",1)>500
         && COMBAT_D->check_level(me,target)!=-1  
	 && (me->is_knowing("jjf_juanlian")>10 || wizardp(me) || !userp(me) ) )
           
        {
                damage+= me->query_combat_damage()/10*me->query("str");
                msg = HIC"\n三枪出罢，将个"+target->name()+HIC"刺得遍体鳞伤，鲜血直冒！\n"NOR;
                if( target->query("env/brief_message")==2 || me->query("env/brief_message")==2 )
                        msg = sprintf(HIC"结果造成"HIR"%d"HIC"点气血减少。\n"NOR,damage);
                else if( target->query("env/brief_message")==3 || me->query("env/brief_message")==3 )
                        msg = "";
                message_vision(msg,me,target);
                target->receive_damage("kee",damage,me,TYPE_PERFORM);
                COMBAT_D->report_status(target);
        }
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：珍珠倒卷帘
        外功所属：霸王枪法
        外功效果：根据霸王枪的等级而定对敌进行三连击
                  如此招领悟过高，则再加一击必中攻击
                  冷却时间 5 秒
        外功条件：
                  将军府弟子
                  人物等级25级
                  内力500点，消耗200点
                  气血200点，消耗100点
                  霸王枪法250级
                  冷泉心法250级
                  雁行步法250级
LONG;
me->start_more(str);
return 1;
}       

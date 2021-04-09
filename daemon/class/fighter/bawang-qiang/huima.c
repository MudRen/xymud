// huima.c 霸王枪法之回马
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon,ride;
        string msg;
        int damage,p;
        
        if( me->query_level()<20 )
        	return notify_fail("你的人物等级不够。\n");
        if( me->query("force")<800 ) 
                return notify_fail("你的内力太少。\n");
        if( me->query("family/family_name") != "将军府" )
                return notify_fail("你是哪儿偷学来的武功！\n");
        if( (int)me->query_skill("lengquan-force", 1) < 200 )
                return notify_fail("你的冷泉心法还差些火候。\n");
        if( (int)me->query_skill("yanxing-steps", 1) < 200 )
                return notify_fail("你的雁行步法无法配合不攻。\n");
        if( (int)me->query_skill("bawang-qiang", 1) < 200 )
                return notify_fail("你的霸王枪法不够娴熟。\n");
	if(me->query_skill_mapped("spear")!="bawang-qiang")
		return notify_fail("你的霸王枪法不够娴熟。\n");
        if( time()<me->query_temp("jjf_huima")+8 )
                return notify_fail("回马枪乃是疑兵之计，不能频繁使用。\n");
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
                return notify_fail("回马枪只能对战斗中的对手使用。\n");
        
	p = me->query_skill("dodge")/50;
        ride = me->query_temp("ridee");
	if( ride )
		p = p*2;
	damage = (me->query_skill("spear")+me->query_skill("dodge"))/60;
	damage+= me->is_knowing("jjf_huima")*8;
	
        me->add("force",-300);
        me->set_temp("jjf_huima",time());     
        msg = YEL"战罢多时，";
        if( ride ) 
                msg+= "$N"YEL"一带缰绳，"+(ride->query("ride/msg")?ride->query("ride/msg"):"驾")+"着"+ride->name()+ YEL"抽身便退。\n";
        else    msg+= "$N"YEL"虚晃一枪，拎着$w"YEL"转身就退，";        
        msg+= YEL"$n"YEL"浑然不知其中诡秘，果真迎头追了上去。\n只见$N"YEL"突然勒马一个回身急转，以迅雷不及掩耳之势，回身对着$n"YEL"$l就是一枪！\n"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,damage);
	return 1;
}               
                                
int help(object me)
{
string str;     
if( !me )      return 0;
str = @LONG
        外功名称：回马枪
        外功所属：霸王枪法
        外功效果：以回马之技对敌进行带固定伤害的物理攻击
        	  有坐骑，命中加倍，固定伤害随技能等级以及领悟而提高
                  冷却时间 8 秒
        外功条件：
        	  将军府弟子
        	  人物等级20级
                  内力800点，消耗300点
                  霸王枪法200级
                  冷泉心法200级
                  雁行步法200级
LONG;
me->start_more(str);
return 1;
}       


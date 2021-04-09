#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,*msgs;
        int lvl,i,damage;
        object weapon;
        
        if( me->query_level()<30 )
        	return notify_fail("你的人物等级不够。\n");
        if( me->query_skill("bingpo-blade",1)<300
         || me->query_skill("blade",1)<300 )
		return notify_fail("你的刀法太差。\n");
	if( me->query_skill_mapped("blade")!="bingpo-blade" )
		return notify_fail("你必须使用冰魄寒刀。\n");
        if( me->query_skill("ningxie-force",1)<300
         || me->query_skill("force",1)<300 )
		return notify_fail("你的内功太差。\n");
	if( me->query_skill_mapped("force")!="ningxie-force" )
		return notify_fail("你必须通过冰谷凝血功抵制寒刀之毒。\n");
        if( me->query_skill("xiaoyaoyou",1)<300
         || me->query_skill("dodge",1)<300 )
		return notify_fail("你的轻功太差。\n");
	if( me->query_skill_mapped("dodge")!="xiaoyaoyou" )
		return notify_fail("你需要逍遥游的配合。\n");
        if(me->query("family/family_name")!="大雪山")
                return notify_fail("非雪山不能用「千蛇出洞」！\n");
	if( time()<me->query_temp("xueshan_qianshe")+6 )
	        return notify_fail("绝招用多就不灵了。\n");        
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )
		return notify_fail("你没有刀，如何能发出「千蛇出洞」？\n");	
	if( me->query("force")<1000 )
		return notify_fail("你的内力不足。\n");
	
	if( !target ) target = offensive_target(me);

	if( !target
	||  !target->is_character()
	||  target->is_corpse()
	||  target==me
	|| !me->is_fighting(target) )
		return notify_fail("你要对谁施展「千蛇出洞」？\n");

	msgs = ({
		HIG"青蛇欲探头！$N"HIG"手中$w"HIG"直刺$n"HIG"$l！\n" NOR,
		HIW"白蛇戏许仙！$w"HIW"化作漫天刀影直抽$n"HIW"！\n"NOR,	
		HIR"赤练闹苏杭！$w"HIR"上血气冲天，狠狠砍向$n"HIR"！\n"NOR,
		HIB"毒蝮吐孽瘴！$w"HIB"上毒气熏天，朝着$n"HIB"$l劈去！\n"NOR,			
		HIY"金蛇微吐芯！$N"HIY"手中$w"HIY"斜劈$n"HIY"$l！\n"NOR,
		HIM"妖蛇啮八方！$N"HIM"手中$w"HIM"猛劈$n"HIM"$l！\n" NOR,
		HIC"仙蛇云里游！$N"HIC"手中$w"HIC"反撩$n"HIC"$l！\n" NOR,
		HIG"百蛇翻身搏！$N"HIG"手中$w"HIG"横劈$n"HIG"$l！\n"NOR,		
		MAG"千蛇戏三界！$w"MAG"在$n"MAG"周身上下飞舞！\n"NOR,
	});        
	
	message_vision(WHT"$N"WHT"手中的"NOR RED+weapon->name()+NOR WHT"幻出千朵刀花使出冰魄寒刀的不传绝学 ---千-蛇-出-洞--- ！	\n"NOR,me,target);
        me->add("force",-300);
        me->set_temp("xueshan_qianshe",time());
	me->set_temp("pfm_msg",1);
	if( me->query_temp("ningxie") || me->query_temp("pfm_action") )
		("/daemon/class/xueshan/bingpo-blade/ningxie.c")->remove_effect(me);
	       
        lvl = me->query_level()/10+1;	
        if( lvl>sizeof(msgs) || wizardp(me) )
        	lvl = sizeof(msgs);
        for(i=0;i<lvl;i++)
	{
		if( !me || !living(me) || !target || !me->is_fighting(target)
		 || !living(target) )
			break;
		if( me->query("force")<100 )
		{
			tell_object(me,"你内息不顺，停住了攻击。\n");
			break;
		}
		damage = (i+1)*5;
		me->add("force",-30);
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msgs[i]);
	}
	me->set_temp("pfm_msg",0);
	return 1;
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：千蛇出洞
              外功所属：冰魄寒刀  
              外功效果：连续攻击对方，固定伤害递增
              		最多九次攻击
              		冷却时间 6 秒
              		使用此招会自动清除「冰谷凝血」状态 
              外功条件：
              		雪山弟子
              		人物等级30级
              		基本内功300级
              		冰谷凝血功300级
              		基本刀法300级
                        冰魄寒刀300级
                        基本轻功300级
                        逍遥游300级
                        内力1000点，消耗300点，每次攻击增加消耗30点
LONG; 
me->start_more(str); 
return 1; 
} 

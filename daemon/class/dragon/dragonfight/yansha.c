//黑龙炎杀
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,succ_msg;
        int dodge,unarmed,force,spells,damage,n=0;
        
        if( me->query_level()<40 )
        	return notify_fail("你的人物等级不够。\n");
	if( me->query("family/family_name")!="东海龙宫" )  
        	return notify_fail("你不能使用这项技能！\n");        	
        if( time()<me->query_temp("sea_yansha")+8 )
                return notify_fail("你的双拳尚未凝结足够的真龙战气。\n");
        if( (int)me->query_skill("spells", 1 ) < 400 )
                return notify_fail("你的法术基础太低。\n");	
        if( (int)me->query_skill("seashentong", 1 ) < 400 )
                return notify_fail("你的碧海神通修为不够。\n");	
        if( me->query_skill_mapped("spells")!="seashentong" )
                return notify_fail("你需要碧海神通的支持。\n");
        if( (int)me->query_skill("force", 1 ) < 400 )
                return notify_fail("你的内功底子太差。\n");	
        if( (int)me->query_skill("dragonforce", 1 ) < 400 )
                return notify_fail("你的龙神心法修为不够。\n");	
        if( me->query_skill_mapped("force")!="dragonforce" )
                return notify_fail("你需要龙神心法的支持。\n");
        if( (int)me->query_skill("dragonfight", 1 ) < 400 )
                return notify_fail("你的龙形搏击修为不够。\n");	
        if( (int)me->query_skill("unarmed", 1 ) < 400 )
                return notify_fail("你的空手功夫不够精深。\n");	
        if( me->query_skill_mapped("unarmed")!="dragonfight" )
                return notify_fail("你需要龙形搏击的支持。\n");
	if( me->query_skill("dodge",1)<400 )
		return notify_fail("你的身形太过笨拙。\n");
	if( me->query_skill("dragonstep",1)<400 )
		return notify_fail("你的龙神身法不够精深。\n");
        if( me->query_skill_mapped("dodge")!="dragonstep" )
                return notify_fail("你需要龙神身法的支持。\n");
                
	if( me->query("force")<2000 )
		return notify_fail("你的内力不够。\n");
	if( me->query("kee")<800 )
		return notify_fail("你的气血不顺。\n"); 
	if( !target )	
		target = offensive_target(me);	        
        if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me 
 	 || !me->is_fighting(target) )
                return notify_fail("你要对谁施展？\n");

	dodge = me->query_skill("dodge")/60;
	msg = HBBLU"$N"HBBLU"身后隐隐现出一个狰狞的黑龙龙首,双拳间凝聚的妖气浓烈至极点,天地间为之一滞突然间，$N"HBBLU"双拳一抖，震开了幽冥之间的阻隔。
一条黑炎形成的黑龙咆哮一声，从双拳间撕裂的缝隙中咆哮而出！\n"NOR;
	message_vision(msg,me);	
	me->add_temp("apply/attack",dodge);	
	me->set_temp("sea_yansha",time());
	me->add("force",-800);
	me->receive_damage("kee", 300,me);

	unarmed = me->query_skill("unarmed")/3;
	
	msg = WHT"\n黑龙穿梭战局之中，随着一声咆哮，一股使人望之便欲堕落的黑炎似错根乱藤般缠向$n"WHT"$l！\n"NOR;
	succ_msg = HIB"只听一阵“咯嘣”声，$n"HIB"$l处传来一声疑似骨折之声！\n"NOR;
	me->set_temp("pfm_msg",1);
	damage=COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,unarmed);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(HIB"$n"HIB"勉力挡住黑龙一击，全身骨骼爆裂作响。\n" NOR,me,target);
	else	n++;
	
	msg = HIB"\n黑龙在半空盘旋回转，龙尾卷起千层乌云雷雨，恶狠狠抽向$n"HIB"$l！\n"NOR;
	succ_msg = HIR"结果「啪」地一声爆响！这一下好厉害，只抽得$n"HIR"皮开肉绽，血花飞溅！\n"NOR;
	me->set_temp("pfm_msg",1);
	damage=COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,unarmed*2/3);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(HIB"$n"HIB"勉力闪住黑龙一击，脚下一道触目惊心的焦痕。\n" NOR,me,target);
	else	n++;
		
	msg = HIM"\n黑龙龙威大作，张口吐出一道粗长的黑炎，所过之处，一片焦黑，直喷$n"HIM"$l！\n"NOR;
	succ_msg = HIR"结果龙炎在$l"HIR"造成了一串血肉模糊的燎泡，$n"HIR"惨叫连连！\n"NOR;
	me->set_temp("pfm_msg",1);
	damage=COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,unarmed*2);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(HIB"$n"HIB"勉力闪开，却也留下了一道触目惊心的焦痕。\n" NOR,me,target);
	else	n++;
			
	msg = CYN"\n黑龙穿梭战局之中，张开巨大的龙爪，恶狠狠抓向$n"CYN"$l，带起一阵阵疾风！\n"NOR;
	succ_msg = HIR"结果只见$n"HIR"闷哼一声，连连后退，$l"HIR"衣襟破碎，血肉模糊，！\n"NOR;
	me->set_temp("pfm_msg",1);
	damage=COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,unarmed*3);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(HIB"$n"HIB"奋力架开，却也惊了一身冷汗。\n" NOR,me,target);
	else	n++;
			
	msg = YEL"\n黑龙穿梭战局之中，拱起身形，瞬间弹出，携带万丈黑炎冲向$n"YEL"心口！\n" NOR;
	succ_msg = HIR "结果$n"HIR"躲闪不及，黑龙穿胸而过，喷射而出的鲜血瞬间被蒸发干净！\n" NOR;
	me->set_temp("pfm_msg",1);
	damage=COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,"胸口",unarmed*4);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(HIB"$n"HIB"极力闪开，虽未受伤，额头却也咋现汗迹。\n" NOR,me,target);
	else	n++;	
	me->add_temp("apply/attack",-dodge);
        if(n>0)
                message_vision(HIW "\n$n"HIW"全身被黑龙击中"+chinese_number(n)+HIW"次，身上多处被烧得烟熏火燎一般。\n" NOR,me,target);
        else    
        {
                message_vision(HIW "$n"HIW"在这一连番的攻击中居然毫发无损！\n" NOR,me,target);
                me->start_busy(3);
        }
        return 1;
}

int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
        外功名称：黑龙炎杀
        外功所属：龙形搏击
        外功效果：连续的给予对方带高命中、高固定伤害的物理攻击
                  使用后冷却8秒
                  如全部未中，则自身busy 3 秒
        外功条件：
        	  龙宫弟子
        	  人物等级40级
                  内力2000点，消耗800点
                  气血800点，消耗300点
                  龙形搏击400级
                  龙神心法400级
                  龙神身法400级
                  碧海神通400级
                  扑击格斗400级，并激发龙形搏击
                  内功心法400级，并激发龙神心法
                  基本法术400级，并激发碧海神通
                  基本轻功400级，并激发龙神身法
LONG;
me->start_more(str);
return 1;
}
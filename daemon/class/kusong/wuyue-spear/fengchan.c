// /daemon/class/yaomo/kusong/wuyue-spear/fengchan  五岳封禅
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	string msg, succ_msg;
	object weapon;
	int damage,ap,dp,pp;
	
	if( me->query_level()<40 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="火云洞")
		return notify_fail("“五岳封禅”只有火云洞门人才可以用！\n");
	if( (int)me->query_skill("wuyue-spear",1)<400 )
		return notify_fail("你的五岳神枪还不够纯熟！\n");	
	if( (int)me->query_skill("pingtian-dafa",1)<400 )
		return notify_fail("你的平天大法还不够纯熟！\n");
	if( (int)me->query_skill("literate",1)<400 )
		return notify_fail("你的读书识字还不够纯熟！\n");
	if( (int)me->query_skill("moshenbu",1)<400 )
		return notify_fail("你的魔神步法还不够纯熟！\n");
	if( (int)me->query_skill("huomoforce",1)<400 )
		return notify_fail("你的火魔心法还不够纯熟！\n");
	if((int)me->query("force")<500) 
        	return notify_fail("你的内力不够了。\n");
	if( time()<me->query_temp("kusong_fengchan")+6 )
		return notify_fail("你不能频繁使用此招。\n");
		        	
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || ( weapon->query("skill_type")!="spear" && weapon->query("use_apply_skill")!="spear" ) )
		return notify_fail("你手里都没枪。\n");	
	if( me->query_skill_mapped("force")!="huomoforce" )
        	return notify_fail("此招必须配合火魔心法才能使用。\n");
	if( me->query_skill_mapped("dodge")!="moshenbu" )
        	return notify_fail("此招必须配合魔神步法才能使用。\n");
        if( me->query_skill_mapped("spear")!="wuyue-spear" )
        	return notify_fail("此招乃是五岳神枪的精髓。\n");
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
		return notify_fail("「五岳封禅」只能对战斗中的对手使用。\n");
	
	pp = (me->query_int()-30);
	if( pp<5 )
		pp = 5;
		
	me->add_temp("apply/attack",pp);
	me->add("force",-200);
    	me->set_temp("kusong_fengchan",time());

	msg = HIC "$N神功妙悟，$w"HIC"砸出一式\n";
    	msg +=HIC "┏━━━━┓\n";
    	msg +=HIC "┃正气岱宗┃ 一股浩然正气已笼罩$n"HIC"全身！\n";
    	msg +=HIC "┗━━━━┛\n"NOR;
    	me->set_temp("pfm_msg",1);
	me->set_temp("pfm_color",HIC);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,me->query_skill("spear")/5);    	
    	me->set_temp("pfm_color",0);
    	me->delete_temp("pfm_msg");
    	if( damage<1 )
    	{
    		me->add_temp("apply/attack",-pp);
		return 1;
	}

        msg = HIB"\n$N"HIB"枪势斗转，$w"HIB"发出摄人心魄的呼啸刺来，瞬间锋锐的枪尖已到了$n"HIB"的咽喉！\n"NOR;
        msg +=HIB "┏━━━━┓\n";
	msg +=HIB "┃忠勇西岳┃  这式犹如华山一条道直取$n"HIB"要害！\n"NOR;
        msg +=HIB "┗━━━━┛\n"NOR;
        succ_msg = HIB"结果$n"HIB"咽喉一麻，差点喘不过气来。\n" NOR;
        me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,"颈部",me->query_skill("spear")/3);
	me->delete_temp("pfm_msg");
        if( damage<1 )
        	message_combatd(HIB"结果被$p灵巧挡开了。\n" NOR,me,target);
        	
        msg = HIW "\n紧跟着$N"HIW"到转$w"HIW"尾刺向$n"HIW"的大腿，同时长啸高吟“恒溪风流禅月明”。\n"NOR;
        msg +=HIW "┏━━━━┓\n";
        msg +=HIW "┃恒岭儒雅┃  这式俊秀倜傥，迅疾如电，直取$n"HIW"的腿部！\n";
        msg +=HIW "┗━━━━┛\n"NOR;
        succ_msg = HIW"$n"HIW"闪避不及，结果腿部被划开深深的一道口子。\n"NOR;
        me->set_temp("pfm_msg",1);
        me->add_temp("apply/attack",10);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,({"左腿", "右腿"})[random(2)],me->query_skill("spear")*2/3);    	
	me->add_temp("apply/attack",-10);
	me->delete_temp("pfm_msg");
        if( damage<1 )
               message_combatd(HIW"$n"HIW"看准来势，挫身闪开了。\n"NOR,me,target);
        
        msg = HIM "\n$N"HIM"接着顺势连人带$w"HIM"撞向$n"HIM"，仿佛如椽巨笔饱墨临纸，令人肝胆俱裂！\n" NOR;
        msg +=HIM "┏━━━━┓\n";
	msg +=HIM "┃文章衡峰┃  这式深得“如椽健笔意纵横”的神髓！\n"NOR;
        msg +=HIM "┗━━━━┛\n"NOR;
	succ_msg = HIM"结果$n"HIM"神智迷糊，差点晕倒。\n" NOR;
	me->add_temp("apply/attack",20);
        me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_CAST,msg,succ_msg,0,me->query_skill("spear"));
	me->add_temp("apply/attack",-20);
	me->delete_temp("pfm_msg");
	if( damage<1 )
               message_combatd(HIM"结果$n"HIM"一个踉跄，却没摔倒。\n" NOR,me,target);

	msg = HIY "\n$N"HIY"枪意绵绵，$w"HIY"平平正正，直取中路刺向$n"HIY"，叫人揣摩莫测，不知如何应付！\n" NOR;
	msg +=HIY "┏━━━━┓\n";
        msg +=HIY "┃平冲中庸┃  这式登堂入室，把基本枪法的“中平”一式发挥到妙到毫巅！\n";
        msg +=HIY "┗━━━━┛\n"NOR;
        succ_msg = HIR"结果“噗！”的一声，$n"HIR"胸口被搠出个大窟窿！\n" NOR;
        me->add_temp("apply/attack",30);
        me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_CAST,msg,succ_msg,0,me->query_skill("spear")*3/2);
	me->add_temp("apply/attack",-30);
	me->delete_temp("pfm_msg");
        
        me->add_temp("apply/attack",-pp);
        
        ap = COMBAT_D->skill_power(me, "wuyue-spear", SKILL_USAGE_ATTACK);
        dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);
        dp+= COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);
        dp/= 2;
        if( COMBAT_D->check_level(me,target)==1 )
        	dp = 0;
        else if( COMBAT_D->check_level(me,target)==-1 )	
        	ap = 0;
        
// 此招一出，必死(*)
// ap2+pp>pp
// 有效等级大于300，读书识字大于180
// 300随机值大于297
// 随机福缘大于25
// 同时满足，概率极其微小
        if( random(ap+dp)>dp && random(300)>100 
         && random(me->query_kar())>target->query("kar")
         && me->query("force")>300 )
	{
		msg = HIG "\n$N"HIG"脸上露出恐惧之色，手中长枪竟然不听使唤，犹如妖魔控制一般，在枪意已尽，劲势已灭之际，又生新力，又续杀机，死神般活跃！\n" NOR;
            	msg +=HIG "┏━━━━━━━┓\n";
            	msg +=HIG "┃五岳归来不看山┃  这式真是鬼泣神啼，天地顿时失色！\n"NOR;
            	msg +=HIG "┗━━━━━━━┛\n"NOR;
            	msg +=HIR"$n"HIR"只觉得眼前一花，咽喉已被对穿而过！一股血箭喷涌而出。。。。$n"HIR"的眼睛死鱼般的突了出来。。。。\n"NOR;
            	if( userp(target) )
            	{
            		if( environment(me)->query("leitai")
            		 || environment(me)->query("broadcast") )
				damage = target->query_maxkee()/2+10;
			else	damage = target->query_maxkee()+10;
            	}
            	else
            	{
            		if( target->is_boss() || target->query("任务")
            		 || target->query("no_bisha") )
				damage = target->query_maxkee()/3+10;
			else	damage = target->query_maxkee()+10;
            	}
		message_combatd(msg,me,target);
		target->receive_damage("kee",damage,me,TYPE_PERFORM);
		target->receive_wound("kee",damage,me,TYPE_PERFORM);
		COMBAT_D->report_status(target);
		COMBAT_D->report_status(target,1);
	}       
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：五岳封禅
        外功所属：五岳神枪
        外功效果：连续对对方进行5次带固定伤害的攻击
                  会有一定几率出现「五岳归来不看山」
                  擂台上或对boss类怪物使用为伤害其最大气血的30%-50%
                  其他情况下此招必杀
		  冷却时间6秒
        外功条件：
        	  火云洞弟子
        	  人物等级40级	
        	  内力500点，消耗200点
                  火魔心法400级并激发
                  五岳神枪400级并激发
                  魔神步法400级并激发
		  平天大法400级并激发
		  读书识字400级
STR;
        me->start_more(str);
        return 1;
}
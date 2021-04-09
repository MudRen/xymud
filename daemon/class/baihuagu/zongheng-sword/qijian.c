// qijian.c 纵横七剑
//great 2004-10-01 
//snowtu 2007-05 修正不合理设定
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{    
        int damage,t;
        string msg,succ_msg;        

	if( me->query_level()<40 )
        	return notify_fail("你的人物等级不够。\n");
        if((string)me->query("family/family_name")!="百花谷")
                return notify_fail("只有百花谷弟子才能使用此招！\n"); 
        if ( (int)me->query("force")<800 ) 
                return notify_fail("你的内力不足！\n");        
        if( (int)me->query_skill("zongheng-sword",1) < 400
	 || (string)me->query_skill_mapped("sword")!="zongheng-sword" )             
                return notify_fail("你的纵横剑法等级还不够!!\n");
	if( (int)me->query_skill("brightjade-force",1) < 400
	 || (string)me->query_skill_mapped("force")!="brightjade-force" )             
        	return notify_fail("你的『明玉神功』等级不够。\n");                
        if ( time()<me->query_temp("bhg_qijian")+5 )
                return notify_fail("你身上明玉神功气劲尚未囤积够。\n");       
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) ) 
                return notify_fail("你要对谁施展这一招「纵横七绝」?\n");        

	msg = HIY"\n$N"HIY"大开大阖，囤积身上明玉神功气劲，只见无数光点渐渐往$N"HIY"身上聚集。转眼间，$N"HIY"耀上天空，身上明玉神功气劲瞬间转移到配剑中.只听$P大喊:
                            "HIW"‘"HIC"～禁     断～"HIW"’
              "HIG"‘"HIR"    破 ＊ 体 ＊ 纵 ＊ 横 ＊ 七 ＊ 绝 ＊ 斩  "HIG"’\n"NOR;
	message_vision(msg,me,target);
	msg = "
		              
                                      "WHT"██"NOR"
                                       "RED"█"NOR"
                               "WHT"██    "RED"█    "WHT"██"NOR"
                                "RED"█     "RED"█     "RED"█"NOR"
                         "WHT"██   "RED"█  "CYN"◢██◣  "RED"█   "WHT"██"NOR"
                          "RED"█    "RED"█   "HIY"｜啸｜"NOR"   "RED"█    "RED"█"NOR"
                   "WHT"██   "RED"█  "CYN"◢█◣ "HIY"｜剑｜"NOR" "CYN"◢█◣  "RED"█   "WHT"██"NOR"
                    "RED"█    "RED"█  "HIC"｜灵｜ "HIY" ◣◢  "HIM"｜天｜"NOR"  "RED"█    "RED"█"NOR"
                    "RED"█  "CYN"◢█◣"HIC"｜剑｜ "HIY" ██  "HIM"｜剑｜"NOR""CYN"◢█◣  "RED"█"NOR"
                    "RED"█  "HIW"｜威｜"HIC"｜  ｜ "HIY" ██  "HIM"｜  ｜"HIG"｜御｜"NOR"  "RED"█"NOR"
                  "CYN"◢█◣"HIW"｜剑｜"HIC"｜  ｜ "HIY" ██  "HIM"｜  ｜"HIG"｜剑｜"NOR""CYN"◢█◣"NOR"
                  "HIR"｜烈｜"HIW"｜  ｜"HIC"｜  ｜ "HIY" ██  "HIM"｜  ｜"HIG"｜  ｜"HIB"｜残｜"NOR"
                  "HIR"｜剑｜"HIW"｜  ｜"HIC"｜  ｜ "HIY" ██  "HIM"｜  ｜"HIG"｜  ｜"HIB"｜剑｜"NOR"
                  "HIR"｜  ｜"HIW"｜  ｜"HIC"｜  ｜ "HIY" ██  "HIM"｜  ｜"HIG"｜  ｜"HIB"｜  ｜"NOR"
                  "HIR"｜  ｜"HIW"｜  ｜"HIC"｜  ｜ "HIY" ██  "HIM"｜  ｜"HIG"｜  ｜"HIB"｜  ｜"NOR"
                  "HIR"｜  ｜"HIW"｜  ｜"HIC"｜  ｜  "HIY"◥◤  "HIM"｜  ｜"HIG"｜  ｜"HIB"｜  ｜"NOR"
                  "HIR"｜  ｜"HIW"｜  ｜"HIC"｜  ｜        "HIM"｜  ｜"HIG"｜  ｜"HIB"｜  ｜"NOR"
                  "HIR"｜  ｜"HIW"｜  ｜"HIC" ＼／         "HIM" ＼／ "HIG"｜  ｜"HIB"｜  ｜"NOR"
                  "HIR"｜  ｜"HIW"｜  ｜                    "HIG"｜  ｜"HIB"｜  ｜"NOR"
                  "HIR"｜  ｜ "HIW"＼／                     "HIG" ＼／ "HIB"｜  ｜"NOR"
                  "HIR"｜  ｜                                "HIB"｜  ｜"NOR"
                   "HIR"＼／                                 "HIB" ＼／
"NOR;
        message_combatd(msg,me,target);	
	me->add("force", -200);
	me->set_temp("bhg_qijian",time());
	me->add_temp("apply/attack",50);
	me->set_temp("pfm_msg",1);
	t = 0;
	if( me->is_knowing("bhg_zongheng")==2 ) //1横2纵，横打前，纵打后
		me->set_temp("ZHJ",1);
	else	me->delete_temp("ZHJ");
	msg = NOR""REV RED" 烈剑 "NOR HIR"如昊天烈日，带着一股炽热的剑气直射$n"HIR"$l！\n"NOR;
	succ_msg = ({
		HIR"结果「噗」地一声刺进$n"HIR"的$l，使$p不由自主地退了步！\n"NOR,
        	HIR"结果「噗嗤」地一声，烈剑已在$p$l刺出一个血肉模糊的血窟窿！\n"NOR,
        	HIR"结果只听见$n"NOR"一声惨嚎，烈剑已在$p的$l对穿而出，鲜血溅得满地！\n"NOR,
        })[random(3)];
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,50);
        if( damage<1 )
        	t++;
        	
	if( me->is_knowing("bhg_zongheng")==2 ) //2
		me->set_temp("ZHJ",2);
	else	me->delete_temp("ZHJ");
	msg = NOR""REV HIY" 威剑 "NOR HIY"似剑中王者，带着一股浩然皇气直刺$n"HIY"$l！\n"NOR;
	succ_msg = ({
		HIR"结果「噗」地一声刺进$n"HIR"的$l，使$p不由自主地退了步！\n"NOR,
        	HIR"结果「噗嗤」地一声，威剑已在$p$l刺出一个血肉模糊的血窟窿！\n"NOR,
        	HIR"结果只听见$n"NOR"一声惨嚎，威剑已在$p的$l对穿而出，鲜血溅得满地！\n"NOR,
        })[random(3)];
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,60);
	if( damage<1 )
        	t++;
	
	if( me->is_knowing("bhg_zongheng")==2 ) //3
		me->set_temp("ZHJ",3);
	else	me->delete_temp("ZHJ");
	msg = NOR""REV HIM" 灵剑 "NOR HIM"光华灵动，疾如闪电般刺向$n"HIM"$l！\n"NOR;
	succ_msg = ({
		HIR"结果「噗」地一声刺进$n"HIR"的$l，使$p不由自主地退了步！\n"NOR,
        	HIR"结果「噗嗤」地一声，灵剑已在$p$l刺出一个血肉模糊的血窟窿！\n"NOR,
        	HIR"结果只听见$n"NOR"一声惨嚎，灵剑已在$p的$l对穿而出，鲜血溅得满地！\n"NOR,
        })[random(3)];
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,70);
        if( damage<1 )
        	t++;
	
	if( me->is_knowing("bhg_zongheng")==2 ) //4
		me->set_temp("ZHJ",4);
	else	me->delete_temp("ZHJ");
	msg = NOR""REV HIC" 啸剑 "NOR HIC"声如天雷，气势磅礴地刺向$n"HIC"$l！\n"NOR;
	succ_msg = ({
		HIR"结果「噗」地一声刺进$n"HIR"的$l，使$p不由自主地退了步！\n"NOR,
        	HIR"结果「噗嗤」地一声，啸剑已在$p$l刺出一个血肉模糊的血窟窿！\n"NOR,
        	HIR"结果只听见$n"NOR"一声惨嚎，啸剑已在$p的$l对穿而出，鲜血溅得满地！\n"NOR,
        })[random(3)];
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,80);
        if( damage<1 )
        	t++;
        
	if( me->is_knowing("bhg_zongheng")==2 ) //5
		me->set_temp("ZHJ",4);
	else	me->delete_temp("ZHJ");
	msg = NOR""REV HIW" 天剑 "NOR HIW"霞光四溢，带着惊天仙气射向$n"HIW"$l！\n"NOR;
	succ_msg = ({
		HIR"结果「噗」地一声刺进$n"HIR"的$l，使$p不由自主地退了步！\n"NOR,
        	HIR"结果「噗嗤」地一声，天剑已在$p$l刺出一个血肉模糊的血窟窿！\n"NOR,
        	HIR"结果只听见$n"NOR"一声惨嚎，天剑已在$p的$l对穿而出，鲜血溅得满地！\n"NOR,
        })[random(3)];
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,90);        
        if( damage<1 )
        	t++;

	if( me->is_knowing("bhg_zongheng")==2 ) //6
		me->set_temp("ZHJ",4);
	else	me->delete_temp("ZHJ");
	msg = NOR""REV HIG" 御剑 "NOR HIG"轨迹灵动，如指臂使般直刺$n"HIG"$l！\n"NOR;
	succ_msg = ({
		HIR"结果「噗」地一声刺进$n"HIR"的$l，使$p不由自主地退了步！\n"NOR,
        	HIR"结果「噗嗤」地一声，御剑已在$p$l刺出一个血肉模糊的血窟窿！\n"NOR,
        	HIR"结果只听见$n"NOR"一声惨嚎，御剑已在$p的$l对穿而出，鲜血溅得满地！\n"NOR,
        })[random(3)];
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,100);        
        if( damage<1 )
        	t++;
        
	if( me->is_knowing("bhg_zongheng")==2 ) //7
		me->set_temp("ZHJ",4);
	else	me->delete_temp("ZHJ");
	msg = NOR""REV HIR" 残剑 "NOR HIR"煞气冲天，带着一抹血光射向$n"HIR"$l！\n"NOR;
	succ_msg = ({
		HIR"结果「噗」地一声刺进$n"HIR"的$l，使$p不由自主地退了步！\n"NOR,
        	HIR"结果「噗嗤」地一声，残剑已在$p$l刺出一个血肉模糊的血窟窿！\n"NOR,
        	HIR"结果只听见$n"NOR"一声惨嚎，残剑已在$p的$l对穿而出，鲜血溅得满地！\n"NOR,
        })[random(3)];
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,100);                
        me->query_skill("zongheng-sword",1)/2;
        
	if( t>3 )
		t = 3;
	me->add_temp("bhg_qijian",t);	
	me->add_temp("apply/attack",-50);
        return 1;
}

int help(object me)
{
string str;     
if( !me )      return 0;
str = @LONG
        外功名称：纵横七剑 
        外功所属：纵横剑法
        外功效果：虚化七剑对敌攻击
                  使用后冷却5秒，每一剑不中增加冷却1秒，最多增加3秒
        外功条件：
                  人物等级40级
                  内力800点，消耗200点
                  纵横剑法400级并激发
                  无忧步法400级并激发
                  明玉神功400级并激发
LONG;
me->start_more(str);
return 1;
}
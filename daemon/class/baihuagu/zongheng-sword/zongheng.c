// 纵横四海 Zongheng.c
// Cracked by 凌惊雪 5.4.2003 
//snowtu重写于 2009
#include <combat.h>
#include <ansi.h>
inherit SSERVER;

mapping *action = ({
        ([      
                "name"          : "横斩",
                "action"        : HIG"$N"HIG"手中$w"HIG"划出一道奇异的轨迹，径直横扫$n，正是「横剑"HIR"·"HIM"斩式"HIG"」。"NOR,
                "dodge"         : -20,
                "parry"         : -30,
                "damage"        : 150,
                "damage_type"   : "劈伤"
        ]),
        ([      
                "name"          : "横扫",
                "action"        : HIY"$N"HIY"挥舞间，剑式大开大阖，$w"HIY"发出强烈的剑气，「横剑"HIR"·"HIM"扫式"HIY"」一出，$n"HIY"被浓烈的剑气笼罩着！"NOR,
                "dodge"         : -60,
                "parry"         : -50,
                "damage"        : 260,
                "damage_type"   : "重伤"
        ]),
        ([      
                "name"          : "横剑山河",
                "action"        : HIY"$N"HIY"$w"HIY"舞动出似天河一般壮丽的气势，「横剑三式」最后一式「横扫山河」一出，道道剑风劈向$n"HIY"$l"NOR,
                "dodge"         : -60,
                "parry"         : -60,
                "damage"        : 370,
                "weapon"        : "剑风",
                "damage_type"   : "鞭伤"
        ]),
});

int perform(object me, object target)
{
        int dodge;
        string msg;
        object weapon;
        
        if( me->query_level()<30 )
                return notify_fail("你的人物等级不够。\n");
        if((int)me->query_skill("zongheng-sword", 1) < 300
         || (string)me->query_skill_mapped("sword")!="zongheng-sword" )
                return notify_fail("你的纵横剑法等级还不够!!\n");
        if( time()-(int)me->query_temp("bhg_zongheng") < 6 )
                return notify_fail("绝招用多就不灵了！\n");
        if( me->query("force")<800 )
                return notify_fail("你的内力不够了。\n");      
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) ) 
                return notify_fail("「纵横四海」只能对战斗中的对手使用。\n");

        weapon = me->query_temp("weapon");
        message_vision(HIM"$N"HIM"剑法一变，风声乍起，使出『纵横剑法』绝技－「纵横四海」，向$n"HIM"“刷刷刷”便是四剑！\n"NOR,me,target);
        me->set_temp("bhg_zongheng",time());
       
        me->add("force",-100);
        msg = "                   "NOR REV HIC"    风云天下    "NOR"\n";
        me->set_temp("ZHJ",1);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,0,"kee");
        
        msg = "\n                   "NOR REV HIY"    日月同辉    "NOR"\n";
        me->set_temp("ZHJ",2);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,0,"kee");
        
        msg = "\n                   "NOR REV HIR"    横扫六合    "NOR"\n";
        me->set_temp("ZHJ",3);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,0,"kee");
        
        msg = "\n                   "NOR REV HIG"    纵横四海    "NOR"\n";
        me->set_temp("ZHJ",4);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,0,"kee");
        
        me->delete_temp("ZHJ");
        me->add_temp("apply/attack",-dodge);
        if( me->query("betray/count")>=1 || me->query_skill("zongheng-sword",1)<500
         || random(me->query_skill("zongheng-sword",1))<250 
         || !me || !target || !target->is_killing(me->query("id"))
         || me->query("force")<200 ) 
                return 1;
        me->add_temp("apply/attack",dodge);
        if( me->is_knowing("bhg_zongheng")==1 )
        {
                msg = HIM"\n$N"HIM"运起明玉神功，一股劲道传入手中的"+weapon->name()+HIM"，陡然间用出百花谷失传多年的绝技"HIG"「横剑」"HIM"!!\n"NOR;
                message_vision(msg, me, target);
                me->set("actions",action[0]);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,0,0,0,0,"kee");
        
                me->set("actions",action[1]);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,0,0,0,0,"kee");
        
                me->set("actions",action[2]);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,0,0,0,0,"kee");
                me->reset_action();
        }
        else 
        {       
                msg = HIM"\n$N"HIM"运起明玉神功，一股劲道传入手中的"+weapon->name()+HIM"，陡然间用出百花谷失传多年的绝技"HIG"「纵剑」"HIM"。\n"NOR;
                message_vision(msg,me,target);
                me->set_temp("ZHJ", 5);
                me->add("force", -100);
                me->set_temp("bhg_pfm_zong",time());
                me->set_temp("pfm_color",HIM);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,0,0,0,0,"kee");
                me->set_temp("action_flag",1);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,0,0,0,0,"kee");
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,0,0,0,0,"kee");
                me->set_temp("pfm_color",0);
                me->set_temp("action_flag",0);
                me->delete_temp("ZHJ"); 
        } 
        return 1;
}

int help(object me)
{
        string str;     
        if( !me )      
                return 0;
        str = @LONG
        外功名称：纵横四海
        外功所属：纵横剑法
        外功效果：对对手造成四次法术攻击的气血伤害
                  冷却时间 6 秒
                  纵横剑法600级后，未叛师者使用，如已领悟「横剑」，则追加「横剑」攻击
                  否则追加「纵剑」攻击
                  fight下追加攻击不会出现
        外功条件：
                  人物等级30级
                  内力800点，消耗150点
                  纵横剑法300级并激发
LONG;
        me->start_more(str);
        return 1;
}


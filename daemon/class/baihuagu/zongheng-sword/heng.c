// Heng.c 横剑Cracked by 凌惊雪 5-4-2003
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

mapping *action = ({
        ([      
                "name"          : "横斩",
                "action"        : HIG"$N"HIG"手中$w"HIG"划出一道奇异的轨迹，径直横扫$n，正是「横剑"HIR"·"HIM"斩式"HIG"」。\n"NOR,
                "dodge"         : -20,
                "parry"         : -30,
                "damage"        : 200,
                "damage_type"   : "劈伤"
        ]),
        ([      
                "name"          : "横扫",
                "action"        : HIC"$N"HIC"挥舞间，剑式大开大阖，$w"HIC"发出强烈的剑气，「横剑"HIR"·"HIM"扫式"HIC"」一出，$n"HIC"被浓烈的剑气笼罩着！\n"NOR,
                "dodge"         : -60,
                "parry"         : -50,
                "damage"        : 300,
                "damage_type"   : "重伤"
        ]),
        ([      
                "name"          : "横剑山河",
                "action"        : HIW"$N"HIW"$w"HIW"舞动出似天河一般壮丽的气势，「横剑三式」最后一式「横扫山河」一出，道道剑风劈向$n"HIW"$l！\n"NOR,
                "dodge"         : -60,
                "parry"         : -60,
                "damage"        : 400,
                "weapon"        : "剑风",
                "damage_type"   : "鞭伤"
        ]),
});

int perform(object me, object target)
{
        object weapon;
        string msg; 
        int extra,damage,dd;
        
        if( me->query_level()<30 )
                return notify_fail("你的人物等级不够。\n");
        if(me->query("family/family_name")!="百花谷")
                return notify_fail("「横剑」只有百花谷门人才可以用！\n");
        if( userp(me) && !wizardp(me) && me->is_knowing("bhg_zongheng")!=1 )  //1为横2为纵
                return notify_fail("你不会这一招的用法!!\n");
        if((int)me->query("force") < 600 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query_skill("zongheng-sword", 1) < 300
         || (string)me->query_skill_mapped("sword")!="zongheng-sword" )
                return notify_fail("你的纵横剑法等级还不够!!\n");
        if((int)me->query_skill("brightjade-force", 1) < 300)
                return notify_fail("你的明玉神功等级还不够!!\n");
        if( me->query_temp("bhg_pfm_zong") )
                return 0;
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) ) 
                return notify_fail("你要对谁施展「横剑」?\n");
        
        weapon = me->query_temp("weapon");
        msg = HIY"\n$N"HIY"运起明玉神功，一股劲道传入手中的"+weapon->name()+HIY"，陡然间用出百花谷失传多年的绝技"HIG"「横剑」"HIY"!!\n"NOR;
        message_vision(msg, me, target);
        extra = me->query_kill("zongheng-sword",1);
        extra/= 4;
        me->add("force", -150);
        me->add_temp("apply/attack",50);
        me->add_temp("apply/combat_damage",extra);
        
        dd = me->query_skill("sword");
        if( !target->is_busy() )
                dd = dd*3/2;
                
        me->set("actions",action[0]);
        damage = COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_CAST,0,0,0,300,"kee");
        
        me->set("actions",action[1]);
        damage+= COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_CAST,0,0,0,500,"kee");
        
        me->set("actions",action[2]);
        damage+= COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_CAST,0,0,0,dd,"kee");
        
        me->add_temp("apply/attack",-50);
        me->add_temp("apply/combat_damage",-extra);
        me->reset_action();
        
        if( damage>100 && random(me->query("force_factor"))>100 && (int)!target->is_busy() )
        {
                msg=HIY"$N"HIY"竟然用出失传多年的"HIG"「横剑」"HIY"绝技，剑气犹如海天一线、无懈可击，$n"HIY"竟无从出手！\n"NOR;
                message_combatd(msg, me, target);
                target->start_busy(3+random(4));
        }   
        me->start_busy(3);
        me->set_temp("pfm_heng_flag",1);
        return 1;
}

int help(object me)
{
string str;     
if( !me )      return 0;
str = @LONG
        外功名称：横剑
        外功所属：纵横剑法
        外功效果：对对手造成三次法术攻击的气血伤害
                  同时有一定的几率使对手busy 3-6 秒
                  使用完后自身busy 3 秒
                  本连击以度敌为主，不损伤对方的气血后限
                  需领悟，「纵剑」与「横剑」只能领悟一种
        外功条件：
                  百花谷弟子
                  人物等级30级
                  内力600点，消耗150点
                  纵横剑法300级并激发
                  明玉神功300级并激发
LONG;
me->start_more(str);
return 1;
}       



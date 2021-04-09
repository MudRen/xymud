#include <ansi.h>
#include <combat.h>
inherit SSERVER;

string *msgs = ({
        "无常","判官","阎罗","追魂","夺魄",
});

int perform(object me, object target)
{
        string msg;
        int extra,i,lmt,flag=0;
        object weapon;
	if( me->query_level()<50 )
		return notify_fail("你的人物等级不够。\n");
	return notify_fail("暂未开放。\n");	
        
        extra = me->query_skill("zhuihun-sword",1);
        if ( extra < 80) return notify_fail("你的[追魂剑]还不够纯熟！\n");
        extra = me->query_skill("tonsillit",1);
        if ( extra < 80) return notify_fail("你的[摄气诀]还不够纯熟，无法发挥追魂剑的威力！\n");
        if( !target ) target = offensive_target(me);
        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("［夺命追魂连环剑］只能对战斗中的对手使用。\n");
        if ( me->query("force")<800 )  
                return notify_fail("你的内力不够了。\n");

        if( time()-(int)me->query_temp("hell_duoming") < 3+random(3) )
                return notify_fail("绝招用多就不灵了！\n");

        extra+=me->query("cor");
        if ( me->query_temp("yunwu") )
                me->delete_temp("yunwu");
        weapon = me->query_temp("weapon");
        message_vision(HIY"\n$N"HIY"凶性大发，手中的"+weapon->name()+HIY"狂风暴雨般地向$n"HIY"袭来！\n" NOR,me,target);
        message_combatd(HIY"$N"HIY"使出夺命追魂连环剑绝招，一连五招向$n"HIY"连环攻出！\n" NOR,me,target);
        me->add("force",-300);
        me->set_temp("hell_duoming",time());
        i = 1;
        msg = sprintf(BRED+HIB"         第%s剑『%s』！         \n"NOR,chinese_number(i),msgs[i-1]);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
        i = 2;
        msg = sprintf(BRED+HIB"         第%s剑『%s』！         \n"NOR,chinese_number(i),msgs[i-1],10);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
        i = 3;
        msg = sprintf(BRED+HIB"         第%s剑『%s』！         \n"NOR,chinese_number(i),msgs[i-1],15);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);

        me->add_temp("apply/attack",extra/3);
        me->add_temp("apply/damage",extra/3);
        i = 4;
        msg = sprintf(BRED+HIB"         第%s剑『%s』！         \n"NOR,chinese_number(i),msgs[i-1],20);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
        i = 5;
        msg = sprintf(BRED+HIB"         第%s剑『%s』！         \n"NOR,chinese_number(i),msgs[i-1],50);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
        me->add_temp("apply/attack",-extra/3);
        me->add_temp("apply/damage",-extra/3);

        return 1;
}

int help(object me)
{
string str;
if ( !me )      return 0;
	if( me->query_level()<50 )
		return notify_fail("你的人物等级不够。\n");
	return notify_fail("暂未开放。\n");	

str = @LONG
        外功名称：夺命追魂连环剑
        外功所属：追 魂 剑
        外功效果：疯狂攻击敌人5次
        外功条件：
                  追 魂 剑 80 级
                  摄 气 诀 80 级
                  内力800点，消耗100-180点
                  气血200点，消耗100点
LONG;
me->start_more(str);
return 1;
}


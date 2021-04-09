// ji.c 祭法宝
#include <ansi.h>
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	int cost;
	string msg;
	object fabao;
	
	if( environment(me)->query("no_magic") 
	 || environment(me)->query("no_fight") ) 
        	return notify_fail("安全区禁止祭法宝。\n");
	if( environment(me)->query("no_fabao") )
		return notify_fail("这里禁止祭法宝。\n");
	if( me->query("mana")<50 )
		return notify_fail("你法力不够充足。\n");				
	if( !arg ) 
        	return notify_fail("你要祭哪样法宝？\n");
	fabao = present(arg,me);
	if( !fabao )
		return notify_fail("你身上没有"+arg+"这样法宝。\n");
	if( fabao!=me->query_temp("armor/Fabao") )
		return notify_fail(arg+"不是你目前装备的法宝。\n");
	if( fabao->query_temp("jiing") )
		return notify_fail(arg+"已经祭出了。\n");	
	if( time()<fabao->query("ji_time")+fabao->query("last_ji") )
		return notify_fail("你不能频繁祭出"+arg+"。\n");
	if( !intp(cost=fabao->query("fabao/cost"))
	 || cost<300 )
	 	cost = 300;	
	if( me->query("mana") < cost )
		return notify_fail("你的法力不能控制"+arg+"。\n");
	if( me->query("sen")<200 )
		return notify_fail("你现在神智不清，无法控制法宝。\n");		
	
	if( !stringp(msg=fabao->query("fabao/ji_msg")) 
	 || strlen(msg)<2 )
	 	msg = HIC"\n$N"HIC"抖足精神，口中念叨咒语，大喝一声“看法宝！”，只见$n"HIC"「呼」地一下飞到半空！\n"NOR;
	message_vision(msg,me,fabao);
        fabao->set_temp("jiing",1);
        me->add("mana", -cost);
        me->receive_damage("sen", 100,me);
	return 1;	
}

int help(object me)
{
    write(@HELP
指令格式 : ji <法宝名称> 

这个指令可以让你祭一项法宝。
法宝只有在装备的状态下才能祭出，你只能装备一件法宝
法宝只有在祭出的情况下，才会起效。
每次祭出将消耗100点精神以及至少300点法力

每件法宝的攻防分别对应对方、对方法宝两个方面。
对敌攻防是战斗中对敌方的伤害以及抵御对方伤害，主要涉及自身安全以及对敌伤害；
对敌法宝攻防则是与敌方的法宝相互争斗时，法宝自身的攻防，主要涉及对对方法宝的压制与收取成功率。
每个攻防属性又分最大属性和当前属性两种。
最大属性是法宝产生时即生成的，可以通过道具来升级，
当前属性则需要使用者用自身的法力温养来提高，当提高到最大属性时即不能再提高了。
法宝温养命令格式：charge <法宝id>'s <属性>
温养属性
	对敌气血伤害	: combat_damage
	对敌精神伤害	: spells_damage
	对敌气血保护	: combat_def
	对敌精神保护	: spells_def
	法宝自身伤害	: self_damage
	法宝自身防御	: self_def

HELP
            );
             return 1;
}


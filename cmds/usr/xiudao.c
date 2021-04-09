// xiudao.c
#include <skill.h>
#include <ansi.h>
inherit F_CLEAN_UP;
#include <obstacle.h>

void finish(object me, int pot_gain);

int main(object me, string arg)
{
	int busy_time,xiudao_lvl,cost,pot_gain;
	object where;

	seteuid(getuid());
	where = environment(me);
	
	if( me->query_level()<10 )
		return notify_fail("你还没到达「炼气入体」的境界。\n");
	if( where->query("no_fight") || where->query("no_magic") )
	     return notify_fail("安全区内禁止练功。\n");
	if( me->is_busy() || me->query_temp("pending/exercising")
         || me->query_temp("pending/xiudao")
         || me->query_temp("pending/respirate") )
		return notify_fail("你现在正忙着呢。\n");
	if( me->is_fighting() )
		return notify_fail("战斗中修道，找死啊？！\n");
	if( (int)me->query("sen") * 100 / (int)me->query_maxsen() < 50 )
		return notify_fail("你现在神智不清，再炼恐怕要走火入魔！\n");
	if( (int)me->query("kee") * 100 / (int)me->query_maxkee() < 50 )
		return notify_fail("你现在体力不够，再练就要累死了！\n");
	if( (xiudao_lvl = me->query_skill("spells")) < 20 ) 
		return notify_fail("你法术修为太低，不能行功修炼！\n");
	if( me->query("food")<5 || me->query("water")<5 )
		return notify_fail("你得补充点饮食，方能坐关。\n");
	if( me->query("potential")-me->query("learned_points")<100 )
		return notify_fail("你需要消耗100点潜能来坐关。\n");
	
	pot_gain = 100;
	busy_time = random(90)/pot_gain/5+3;
	pot_gain = 1 + random(pot_gain*2);
	busy_time*= pot_gain;
  	if( where->query("maze") )
  		pot_gain+= random(pot_gain/2)+1;
	cost = 200-me->query_int()-me->query_spi();
	if( cost<50 )
		cost = 50;
	if(me->query("food") + me->query("water") < 20) 
		busy_time *= 2;
        busy_time = busy_time/10+1;
	if( wizardp(me) )
		tell_object(me,"time="+busy_time+" p="+pot_gain+"\n");		
  	message_vision(HIY "$N闭上眼睛，盘膝坐下，嘴里默默念念不知在说些什么。\n" NOR, me);
	me->start_busy(busy_time+1);
	me->add("potential",-100);
	me->receive_damage("sen", cost);
	me->receive_damage("kee", cost);
	me->set_temp("pending/xiudao",1);
	if( wizardp(me) )
		busy_time = 1+random(3);
	call_out("finish",busy_time, me, pot_gain);
	return 1;
}

void finish(object me, int pot_gain)
{
	int succ = 0;
	if( !me || !me->query_temp("pending/xiudao") )
		return;
	me->delete_temp("pending/xiudao");
    	if(MISC_D->random_capture(me,3000,0)) 
    		return;
	message_vision(HIY "$N缓缓睁开眼睛，长舒一口气站了起来。\n" NOR, me);
	if( wizardp(me) )
		tell_object(me,"人物最大支持道行为"+me->query_max_daoxing()+"\n");
	if( me->query("daoxing")>=me->query_max_daoxing() )
		tell_object(me, HIC "你虽有领悟，怎奈境界不够，无法深刻领会其间的奥妙。\n"NOR);
	else	tell_object(me, HIC "你的道行增加了" + COMBAT_D->chinese_daoxing(pot_gain) + "。\n" NOR);
	me->add("daoxing", pot_gain);
	me->stop_busy();
	if( me->query_level()==19 
         && me->query("combat_exp")>=1300000 )
	 	succ = 1;
	if( time()<me->query("maze/tupo20-1")+900 )
		succ = 0;	 	
	if( wizardp(me) && me->query("env/test") )
	 	succ = 1;
  	if( environment(me)->query("maze") )
		succ = 0;
	if( succ==1 )		
	{
		me->delete_temp("maze");
		if( MAZE_D->enter_maze(me, "tupo20-1") )
		{
        		me->set_temp("maze/tupo20-1",1);
        		me->set("maze/tupo20-1",time());
        		tell_object(me,HIC"你于坐关之际，忽福至心灵，心神按捺不住，但见眼前景色一变，却是心处高山流水之间。\n"NOR);
		}
	}
}

int help(object me)
{
        write(@HELP
指令格式 : xiudao

静坐修炼以提高道行或于瓶颈时神游万里以寻契机。
HELP
        );
        return 1;
}

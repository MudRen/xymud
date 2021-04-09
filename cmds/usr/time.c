// 此文件禁止随意移动和更改
#include <command.h>
#include <ansi.h>
inherit F_CLEAN_UP;

int time_exp(object ob)
{
	int tt,t,t2;	
	if( !ob )
		return 0;
	tt = ob->query_temp("login_data/time");
	tt = time()-tt;
 	tt/= 60;
 	if( tt<1 ) tt = 1;
        t = ob->query("combat_exp")-ob->query_temp("login_data/exp");
	t = t/tt;
	if( t<0 ) t = 0;
	return t;
}

int time_dx(object ob)
{
	int tt,t,t2;	
	if( !ob )
		return 0;
	tt = ob->query_temp("login_data/time");
	tt = time()-tt;
 	tt/= 60;
 	if( tt<1 ) tt = 1;
	t2 = ob->query("daoxing")-ob->query_temp("login_data/dx");
	t2 = t2/tt;
	if( t2<0 ) t2 = 0;
	return t;
}		

int main(object me, string arg)
{
	string str;
	object ob;      
	int t,time,tt;     
	if ( !arg )
        	ob = me;
	else    {
        	ob = find_player(arg);
        	if ( !ob || ( ob!=me && !wizardp(me) ) )
                	return notify_fail("没有这个人。\n");
        }       
	tt = ob->query_temp("login_data/time");
	tt = time()-tt;
 	str = "现在是"HIR"贞观"NOR + NATURE_D->game_time() + "。\n";
 	str+= (me==ob?"你":ob->name(1))+"本次登入，已经游戏了"+CHINESE_D->chtime(tt)+"。";
	str+= "平均每分钟 武学增长"+time_exp(ob)+"点，";
	t = time_dx(ob);
	str+= "道行增长"+(t>0?COMBAT_D->chinese_daoxing(t):0)+"\n";
if( wizardp(me) )  str+= "现在时间为"+time()+"。\n";
	write(str);
	return 1;
}

int help(object me)
{
     write(@HELP

指令格式: time

这个指令让你知道西游记现在游戏中的国家时辰。

相关信息：uptime，bjtime

HELP
    );
    return 1;
}


// exert.c
#include <skill.h>
#include <ansi.h>
#include "/cmds/std/valid_kill.h";
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string force,msg;
	int result;
	object weapon, target,pfm;
	string martial, skill, perf,tmp;
    
	seteuid(getuid());

	if( me->is_busy() )
        	return notify_fail("( 你上一个动作还没有完成，不能施用内功。)\n");
	if( !arg ) return notify_fail("你要用内功做什么？(吸气：exert recover，凝神：exert refresh)\n");
	
	if( time()<(me->query_temp("no_exert/start")+me->query_temp("no_exert/time")) )
        {
        	if( stringp(msg=me->query_temp("no_exert/msg")) )
                	return notify_fail(msg+"\n"NOR);
        }
	tmp = arg;
	if( sscanf(arg, "%s on %s", perf, arg)==2 ) 
        {
        	target = present(arg, environment(me));
        	if( !target ) target = present(arg, me);
        	if( !target ) return notify_fail("这里没有 " + arg + "。\n");
        	if(!valid_kill(me,target,0)) return 0;//Add by beeby. Check ghost.
        	if(target->is_ghost())
                	return notify_fail("对方已经是鬼了.....\n");
        	if( userp(me) && userp(target) && target->query_temp("netdead") )
                	return notify_fail("对方正在断线中，不能对其施用外功。\n");
        	arg = perf+" "+arg;
        	tmp = perf;
        } 
	else if(sscanf(arg, "%s %s", perf, arg)==2 ) 
        {//so can't use: perform vision id but have to use: perform vision on id
        	arg=perf;
        	tmp = perf;
        }
	else	tmp = arg; 
	martial = me->query_skill_mapped("force");
	if( !martial || !stringp(martial) )
		return notify_fail("你请先用 enable 指令选择你要使用的内功。\n");
	if( wizardp(me) && me->query("env/test") )
        	write("tmp = "+tmp+"   martial = "+martial+"  arg="+arg+"\n");         
/*自创内功        	
	if( me->query("new_exert/"+tmp) && me->query("new_exert/"+tmp)==martial 
  	&& ("/cmds/usr/zzperform.c")->check_pfm(me) )
        {
        	message_vision("$N在战斗中似乎有多感悟,一招一式间开始显露宗师风范。\n",me);
        	pfm = new("/obj/perform");
        	pfm->set("owner_id",me->query("id"));
        	pfm->set("ids",tmp);
     		pfm->setup();
        	if( pfm->restore() )
                {
                	if( !pfm->do_perform(me,arg) )
                		message_vision("可惜微妙之处还是有些走样。。。\n",me);
                }
        	else    message_vision("可惜暂时没有发挥的余地。\n",me);
        	if( pfm )
        		destruct(pfm);
        	return 1;
        }
*/
	if( stringp(martial = me->query_skill_mapped("force")) ) 
        {
        	notify_fail("你所学的内功中没有这种功能。\n");
        	if( SKILL_D(martial)->exert_function(me, arg) ) 
                {
                	if( random(120) < (int)me->query_skill("force") )
                        	me->improve_skill(martial, 1, 1);
                	return 1;
        	} 
        	else if( SKILL_D("force")->exert_function(me, arg) ) 
                {
                	if( random(120) < (int)me->query_skill("force", 1) )
                        	me->improve_skill("force", 1, 1);
                	return 1;
                }
        	return 0;
        }
	return notify_fail("你请先用 enable 指令选择你要使用的内功。\n");
}

int help (object me)
{
write(@HELP
指令格式：exert <功能名称> [<施用对象>]

用内力进行一些特异功能，你必需要指定<功能名称>，<施用对象>则可有可无。
在你使用某一种内功的特异功能之前，你必须先用 enable 指令来指定你要使用
的内功。

请参考 help force 可得知一些大部分内功都有的功能，至于你所用的内功到底
有没有该功能，试一试或参考其他说明便知。

注：如果你改变自己的内功，你原本蓄积的内力并不能直接转换过去，必须
    从 0 开始。
 
HELP
        );
return 1;
}


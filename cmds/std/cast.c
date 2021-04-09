// cast.c
#include <skill.h>
#include <ansi.h>
#include "/cmds/std/valid_kill.h";
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object weapon, target,pfm;
	string martial, skill, perf,msg,tmp;
    
	seteuid(getuid());
    
	if((int)me->query_temp("in_qingwang")==1)
        	return notify_fail(MAG"你眼前出现那个熟悉的身影，搅的你心烦气燥，似离情，剪不断，理还乱。\n"NOR);
	if( me->is_busy() )
        	return notify_fail("( 你上一个动作还没有完成，不能施展法术。)\n");
	if( !arg ) return notify_fail("你要用法术做什么？\n");
	if( !wizardp(me) && environment(me)->query("no_fight")) 
		return notify_fail("这里不能施展法术。\n");
	if( time()<(me->query_temp("no_cast/start")+me->query_temp("no_cast/time")) )
        {
        	if( stringp(msg=me->query_temp("no_cast/msg")) )
                	return notify_fail(msg+"\n"NOR);
                else	return notify_fail("你现在不能施展法术。\n");	
        }
	//snowtu加入封魔设定 070403
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
                	return notify_fail("对方正在断线中，不能对其施展法术。\n");
        	arg = perf+" "+arg;
        	tmp = perf;
        } 
	else if(sscanf(arg, "%s %s", perf, arg)==2 ) 
        {//so can't use: perform vision id but have to use: perform vision on id
        	arg=perf;
        	tmp = perf;
        }
	else	tmp = arg;              
	martial = "spells";	
	if( wizardp(me) && me->query("env/test") )
        	write("tmp = "+tmp+" martial = "+martial+"\n");     
	/*        	    
	if( me->query("new_cast/"+tmp) && me->query("new_cast/"+tmp)==martial 
  	&& ("/cmds/usr/zzcast.c")->check_cast(me) )
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
	if( stringp(skill = me->query_skill_mapped(martial)) ) 
        {
        	notify_fail("你所使用的法术中没有这种功能。\n");
        	if( SKILL_D(skill)->cast_spell(me, arg) ) 
                {
                	if( random(120) < (int)me->query_skill(skill) )
                        	me->improve_skill(skill, 1, 1);
                	return 1;
                } 
        	else if( SKILL_D(martial)->cast_spell(me, arg) ) 
                {
                	if( random(120) < (int)me->query_skill(martial, 1) )
                        	me->improve_skill(martial, 1, 1);
                	return 1;
                }
        	return 0;
        }
	return notify_fail("你请先用 enable 指令选择你要使用的法术。\n");
}

int help (object me)
{
        write(@HELP
指令格式：cast <咒文名称> [on <施咒对象>]
 
施法，你必需要指定<咒文名称>，<施咒对象>则可有可无。
在你使用某一个咒文之前，你必须先用 enable 指令来指定你要使用的咒文系。
 
注：如果你改变自己的咒文系，你原本蓄积的法力并不能直接转换过去，必须
    从 0 开始。
 
HELP
        );
return 1;
}


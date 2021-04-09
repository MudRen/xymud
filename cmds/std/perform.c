//modified by vikee
//2000.10
//Jingxue 2002.12 加入了轻功可以放pfm
//snowtu 2007.05 加入对自制pfm的支持
// perform.c
#include <ansi.h>
#include <skill.h>
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
        	return notify_fail("( 你上一个动作还没有完成，不能施用外功。)\n");
	if( !arg ) return notify_fail("你要用外功做什么？\n");
	if( !wizardp(me) && environment(me)->query("no_fight")) 
		return notify_fail("这里不能施用外功。\n");
	if( time()<(me->query_temp("no_perform/start")+me->query_temp("no_perform/time")) )
        {
        	if( stringp(msg=me->query_temp("no_perform/msg")) )
                	return notify_fail(msg+"\n"NOR);
                else	return notify_fail("你现在不能施展外功。\n");	
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
                	return notify_fail("对方正在断线中，不能对其施用外功。\n");
        	arg = perf+" "+arg;
        	tmp = perf;
        } 
	else if(sscanf(arg, "%s %s", perf, arg)==2 ) 
        {//so can't use: perform vision id but have to use: perform vision on id
        	arg=perf;
        	tmp = perf;
        }

	if( sscanf(arg, "%s.%s", martial, arg)!=2 ) 
        {
        	if( weapon = me->query_temp("weapon") )
                	martial = weapon->query("skill_type");
        	else    martial = "unarmed";
        }
	else    
	{
        	if( martial == "axe" || martial == "blade" 
         	 || martial == "dagger" || martial == "fork" 
         	 || martial == "hammer" || martial == "unarmed" 
         	 || martial == "staff" || martial == "sword"
         	 || martial == "spear" || martial == "mace" 
         	 || martial == "stick" || martial == "whip" ) 
			return notify_fail("这种外功不需指定武功种类！\n");
        	tmp = arg;              
        } 
	if( wizardp(me) && me->query("env/test") )
        	write("tmp = "+tmp+" martial = "+martial+"\n");         
	if( me->query("new_pfm/"+tmp) && me->query("new_pfm/"+tmp)==martial 
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

	else if( stringp(skill = me->query_skill_mapped(martial)) ) 
        {
        	notify_fail("你所使用的外功中没有这种功能。\n");
        	if( SKILL_D(skill)->perform_action(me, arg) ) 
                {
                	if( random(120) < (int)me->query_skill(skill) )
                        	me->improve_skill(skill, 1, 1);
                	return 1;
                } 
        	else if( SKILL_D(martial)->perform_action(me, arg) ) 
                {
                	if( random(120) < (int)me->query_skill(martial, 1) )
                        	me->improve_skill(martial, 1, 1);
                	return 1;
                }
        	return 0;
        }
	return notify_fail("你请先用 enable 指令选择你要使用的外功。\n");
}

int help (object me)
{
        write(@HELP
指令格式：perfrom [<武功种类>.]<招式名称> [<施用对象>]

如果你所学的外功(拳脚、剑法、刀法....)有一些特殊的攻击方式或招式，可以
用这个指令来使用，你必须先用 enable 指令指定你使用的武功，不指定武功种
类时，空手的外功是指你的拳脚功夫，使用武器时则是兵刃的武功。


换句话说，只要是 enable 中的武功有特殊招式的，都可以用这个指令使用。
HELP
        );
return 1;
}


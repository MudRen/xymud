#include <ansi.h>
#include "/cmds/std/block_tell.h";
inherit F_CLEAN_UP;
 
int main(object me, string str)
{
string clr;     
if(!block_tell(me)) return 1;
if (!str) 
        {
        write(CYN"你看起来表情丰富。\n"NOR);
        tell_room(environment(me), CYN+(string)me->name()+"看起来表情丰富。\n" +NOR, me);
        return 1;
        }
if ( !wizardp(me) )
        {       
        write(CYN"你"+str+"\n"NOR);
        tell_room(environment(me), CYN+(wizardp(me)? "":"->")+(string)me->name()+str+"\n"+NOR, me);
        }
if ( sscanf(str,"%s %s",clr,str)==2 )
        {
        str = clr+str+NOR;
        str = COLOR_D->replace_color(str,2);
        write(str+"\n"NOR);
        tell_room(environment(me), str+"\n"+NOR, me);                           
        }
else    {
        str = COLOR_D->replace_color(str,2);
        write(CYN"你"+str+"\n"NOR);
        tell_room(environment(me), CYN+(wizardp(me)? "":"->")+(string)me->name()+str+"\n"+NOR, me);                  
        }
return 1;
}
 
int help(object me)
{
        write(@HELP
指令格式: emote <动作词>

这个指令可以让你表达一个系统没有预设的动作词, 系统会将你所输入
的文字加上你的姓名后显示给所有在同一个地方的生物看. 为了避免造
成困扰, 玩家所输入的词句前面会加上 -> 以供区别. (巫师则不在此
限.)

□例: emote 坐了下来。
你会看见: 你坐了下来。
其他人会看到: ->包子坐了下来。

其中, 包子就是你的名字.

相关指令: semote
HELP
        );
        return 1;
}


//jiangli.c  By snowtu
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me,string arg)
{
object who,board,obj;
string reson,file,str;
mapping note,*notes;;
if ( !arg )
        return notify_fail("你要奖励谁？\n");
if ( sscanf(arg,"%s %s for %s",arg,file,reson)!=3 )
        return notify_fail("命令格式: jiangli <id> <file> for <reson>\n");
board = find_object("/obj/board/gift_b.c");
if ( !board )
        return notify_fail("没有找到bug汇报板.\n");
who = find_player(arg);
if ( !who || !living(who) )
        return notify_fail(arg+"是错误的对象。\n");
obj = new(file);
if ( !obj )
        return notify_fail("奖励物品不存在。\n");
str = sprintf("    %s(%s) 于 %s 奖励 %s(%s) \n%O %d%s\n    原因：%s\n"NOR,
                me->name(1),
                capitalize(me->query("id")),
                ctime(time()),
                who->name(1),
                capitalize(who->query("id")),
                obj,
                obj->query_amount()>0?(obj->query_amount()):1,
                obj->query("unit")?obj->query("unit"):"个",
                reson,
                );
str = COLOR_D->clean_color(str);
str = HIR+str+NOR;
note = allocate_mapping(5);
note["title"] = HIR"奖励通告"NOR;
note["sx"] = "◆";
note["author"] = NOR HIW"系统奖励"NOR;
note["time"] = time();
note["ip"] = query_ip_name(me);
note["msg"] = str;
note["time"] = time();
notes = board->query("notes");
if( !pointerp(notes) || !sizeof(notes) )
        notes = ({ note });
else    notes += ({ note });
board->set("notes", notes);
board->save();
tell_object(me, "留言完毕。\n");
if ( !obj->move(who) )   return notify_fail("奖励失败。\n");
tell_object(who,"你被奖励了一"+obj->name()+".\n");
if ( !wizardp(who) )
        message("shout",HIR"【奖励精灵】"+str+NOR,users());
write("OK\n");
return 1;       
}

int help(object me)
{
write(@HELP
指令格式 : 
        jiangli <id> <档案名> for <原因>
    这个指令是专门奖励用的
HELP
);
return 1;
}


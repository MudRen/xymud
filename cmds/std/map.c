#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me)
{
object where;    
string tmp,str,*arg,name;
where=environment(me);
if ( !where )
        return notify_fail("你不知你现在身在何处。\n");
if ( me->query("kee")<50 )
                return notify_fail("你的体力不太好了，先休息一下吧！\n");
me->add("kee",-30);
        tmp = base_name(where);
        arg = explode(tmp,"/");
        tmp = arg[sizeof(arg)-2];
notify_fail("目前暂无您所在地的地图。\n");
arg = explode(tmp,"/");
tmp = arg[sizeof(arg)-1];
if ( !tmp )
        return 0;
if ( tmp=="lingtai" )  tmp = "fangcun";
else if ( tmp=="sea" )  tmp = "longgong";
else if ( tmp=="city" )  tmp = "changan";
else if ( tmp=="changan" )  tmp = "changan-south";
else if ( tmp=="westway" )  tmp = "changan-west";
else if ( tmp=="黄风楼" )  tmp = "hudiegu";
else if ( tmp=="bmw" )  tmp = "sky";
else if ( tmp=="baigudong" )  tmp = "baoxiang";
tmp = "/doc/help/maps/map-"+tmp;
if ( !tmp || file_size(tmp)<1 )
        return 0;
str = read_file(tmp);
str = COLOR_D->replace_color(str);
name = where->query("short");
name = COLOR_D->replace_color(name);
str = replace_string(str,name,NOR REV YEL+name+NOR);
me->start_more(str);    
return 1;
}

int help()
{
write(@HELP
        命令用法：map 
本命令帮助玩家了解周围的房间地图的分布状况，并标志出房间之间的连接情况。

HELP);
return 1;
}



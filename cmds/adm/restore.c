#include <ansi.h>
inherit F_CLEAN_UP;

string CP = "/cmds/wiz/cp.c";

int main(object me, string arg)
{
	string id,tt,dir,dir2,old,old2,str,str2;
	if( wizhood(me) != "(admin)" )
		return notify_fail("你没有这个权限。\n");
	if( !arg 
	 || sscanf(arg,"%s %s",id,tt)!=2 )
		return notify_fail("命令格式 restore <id> <备份日期>\n");
	dir = tt;			
	dir = sprintf("/backup/%s/login/%c/%s.o",dir,id[0],id);
	old = sprintf("/data/login/%c/%s.o",id[0],id);	
	if( file_size(dir)<=0 )
		return notify_fail(id+"的备份login数据不存在。\n");
	
	dir2 = 	sprintf("/backup/%s/user/%c/%s.o",dir,id[0],id);
	old2 = 	sprintf("/data/user/%c/%s.o",id[0],id);
	if( file_size(dir)<=0 )
		return notify_fail(id+"的备份user数据不存在。\n");
	
	
	str = sprintf("-f %s %s",dir,old);
	CP->main(me,str);
	write(id+"的login文件恢复成功。\n");
	
	str = sprintf("-f %s %s",dir2,old2);
	CP->main(me,str2);
	write(id+"的user文件恢复成功。\n");

	shout(HIR"【恢复精灵】"HIY+me->query("id")+HIR+"将"HIY+id+"的数据恢复为"HIY+tt+HIR+"时的。\n"NOR);
	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : restore <id> <备份日期>
 
这个指令可以将出错的id数据恢复到指定时期的。
HELP
    );
    return 1;
}
#include "/doc/help.h"
#include <ansi.h>
#include <login.h>
inherit F_CLEAN_UP;

int found;
int search_dir(string *dirs, string arg, object me, int wildcard, int wizp);
int find_sub(mixed *filename);

void show_help_site(object who)
{
	string arg;
	if( !who || !living(who) )
		return;
	arg = read_file(HELP_SITES);
	if( !arg || !stringp(arg) )
		return;
	arg = COLOR_D->replace_color(arg,2);
	tell_object(who,arg);
}


int main(object me, string arg)
{
	int i;
	string newarg,str1,str2,file, *search;
	string *default_search,skill,pfm,tmp;
	int wildcard;

// If no topic specified, give the topics.
	if( !arg ) 
        {
        	me->start_more( COLOR_D->replace_color(read_file(HELP_DIR + "help/topics"),2) );
        	show_help_site(me);
        	return 1;
        }
	if( sscanf(arg,"%s_%s",skill,pfm) )
        {
        	if( userp(me) )
                {
        	        file = "/daemon/skill/"+skill+".c";
                	if( file_size(file)>1 )
                        {
                        	tmp = file->perform_action_file(pfm);
	                        if( tmp && stringp(tmp) && file_size(tmp+".c")>1 )
        	                        return tmp->help(me);
                	        tmp = file->exert_function_file(pfm);
                        	if( tmp && stringp(tmp) && file_size(tmp+".c")>1 )
                                	return tmp->help(me);
	                        tmp = file->cast_spell_file(pfm);
        	                if( tmp && stringp(tmp) && file_size(tmp+".c")>1 )
                	                return tmp->help(me);
                        }                               
                }
        }
	seteuid(getuid());
	if( stringp(file = me->find_command(arg)) ) 
        {
        	notify_fail("有这个指令存在，但是并没有详细的说明文件。\n");
        	return file->help(me);
        }
	if( stringp(file=me->find_command(ALIAS_D->process_global_alias(arg))) ) 
        {
        	notify_fail("有这个指令存在，但是并没有详细的说明文件。\n");
        	return file->help(me);
        }
	if( pointerp(search = me->query("help_search_path")) ) 
        {
        	i = sizeof(search);
        	while(i--) if( file_size(search[i] + arg)>0 ) 
                {
                	me->start_more( COLOR_D->replace_color(read_file(search[i] + arg),2) );
                	show_help_site(me);
                	return 1;
                }
        }
	sscanf(arg, "%s()", arg);
	arg=replace_string(arg, "/", "");
	if(strsrch(arg,"*")>=0 || strsrch(arg,"?")>=0) wildcard=1;
	else    wildcard=0;
	found=0;
	write("\n");
	if(wizardp(me))
        	default_search = DEFAULT_SEARCH_PATHS;
	else    default_search = DEFAULT_PLAYER_SEARCH_PATHS;
	if( pointerp(default_search) ) 
        {
        	if(search_dir(default_search, arg, me, wildcard, wizardp(me))>0) 
                {
	                if(wildcard) write("找到"+chinese_number(found)+"个相关主题。\n");
        	                return 1;
                }
        }
	return notify_fail("没有针对这项主题的说明文件。\n");
}

int search_dir(string *dirs, string arg, object me, int wildcard, int wizp)
{
int i = sizeof(dirs), j;
mixed *filenames, *sub_dir;

while(i--) 
        {
        filenames=get_dir(dirs[i] + arg, -1);
        if(pointerp(filenames) && sizeof(filenames)) 
                {
                if(!wildcard && filenames[0][1]>0) 
                        {
                        me->start_more( COLOR_D->replace_color(read_file(dirs[i] + arg),2) );
                        show_help_site(me);
                        return 1;
                        }
                if(wildcard) 
                        {
                        j=sizeof(filenames);
                        while(j--) {
                                if(filenames[j][1]>0) 
                                        {
                                        write("help "+filenames[j][0]+(wizp?"     ("+dirs[i]+")":"")+ "\n");
                                        found++;
                                        }
                                }
                        }
                }
        if(pointerp(filenames=get_dir(dirs[i], -1))) 
                {
                if(pointerp(sub_dir=filter_array(filenames, "find_sub"))) 
                        {
                        string *dirs1=({});
                        j=sizeof(sub_dir);
                        while(j--) 
                                dirs1+=({dirs[i]+sub_dir[j][0]+"/"}); 
                        if(search_dir(dirs1, arg, me, wildcard, wizp)==1 
                        && !wildcard) 
                                return 1;
                        }
                }
        }
return (wildcard*found);
}

int find_sub(mixed *filename)
{
return (filename[1]==-2);
}

int help(object me)
{
    write(@HELP
指令格式：help <主题>              例如： help cmds
          help <函数名称>()        例如： help call_out()

这个指令提供你针对某一主题的详细说明文件，若是不指定主题，则提供你有关
主题的文件。

除了有关指令名(command)的说明以外，在主题名称中 Help 支持 wildcards 
如 '?' 和 '*'，例如： help map-m*。

HELP
    );
    return 1;
}


#include <ansi.h>
inherit F_DBASE;

void create()
{
	seteuid(getuid());
	set("channel_id", "礼物精灵");
}

int clean_up()
{
	return 1;
}

int update_level(object who)
{
	return 0;
}

int first_log(object who,string type,string msg)
{
	mapping date;
	string t,file;
	if( !who || !userp(who) )
		return 0;
	if( type!="System" && type!=who->query("id") )
		return 0;
	if( type=="System" )
	{
		file = "/log/system/sys";
		msg = sprintf("%s(%s)%s",who->query("name"),capitalize(who->query("id")),msg);
	}
	else	file = sprintf("/log/user/%c/%s",who->query("id")[0],who->query("id"));
	date=XYJTIME_D->check_time(time());
	t = date["YEAR"]+date["MONTH"]+date["DAY"];
	msg = t+msg;
	seteuid(ROOT_UID);
	log_file(file,msg);
	seteuid(getuid());
	return 1;
}	
				
// fingerd.c
// Modify by Jingxue for XYCQ 6.10.2003

//#include <net/dns.h>
#include <ansi.h>
#include <command.h>

void create() 
{ 
	seteuid( getuid() ); 
}

string age_string(int time)
{
	int month, day, hour, min, sec;

	sec = time % 60;
	time /= 60;
	min = time % 60;
	time /= 60;
	hour = time % 24;
	time /= 24;
	day = time % 30;
	month = time / 30;
	return (month?chinese_number(month) + "月":"") + (day?chinese_number(day) + "天":"") + 
	(hour?chinese_number(hour) + "小时":"") + chinese_number(min) + "分钟";
}

string finger_all()
{
	object *ob;
	string msg, fip;
	int i;

	ob = users();
	msg = "";
	if ( !wizardp(this_player()) )  // player finger
	{
		for(i=0; i<sizeof(ob); i++) {
			if( this_player() && !this_player()->visible(ob[i]) ) continue;
			if( this_player() && !wizardp(this_player()) && ob[i]->query("id")=="jingxue" ) continue;
			if( this_player() && ob[i]->query("id")=="lunar" ) continue;
			msg = sprintf("%s%-14s%-14s%-14s\n",
				msg, ob[i]->query("name"), ob[i]->query("id"),
				query_idle(ob[i]) + "s");
		}
		return "★"+MUD_NAME+"★ \n" + 
		"━━━━━━━━━━━━━━━━━━\n"
		+ "姓名          帐号          发呆\n" +
		"━━━━━━━━━━━━━━━━━━\n"
		+ msg +
		"━━━━━━━━━━━━━━━━━━\n";
	} else  	// wizard finger
	{
		for(i=0; i<sizeof(ob); i++) {
			if( this_player() && !this_player()->visible(ob[i]) ) continue;
			if( this_player() && !wizardp(this_player()) && ob[i]->query("id")=="jingxue" ) continue;
			if( this_player() && ob[i]->query("id")=="lunar" ) continue;
			msg = sprintf("%s%-14s%-10s%-4s%-14s%-7s%s\n",
				msg, ob[i]->query("name"), ob[i]->query("id"),
				ob[i]->query_encoding()?"B5":"GB",
				 chinese_number(ob[i]->query("age")), 
				query_idle(ob[i]) + "s", query_ip_number(ob[i]));
		}
		return "★"+MUD_NAME+"★   \n" + 
"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
+ "姓名          帐号          年龄          发呆   连线\n" +
"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
+ msg +
"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	}
}
	
string finger_user(string name)
{
	object ob, body;
	string msg, mud;
	int public_flag;

	if( sscanf(name, "%s@%s", name, mud)==2 ) {
		//GFINGER_Q->send_gfinger_q(mud, name, this_player(1));
		return "网路指令传送过程可能需要一些时间，请稍候。\n";
	}

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() ) {
	  	destruct(ob);
	  	return "没有这个玩家。\n";
        }	

	if( name == "lunar" && this_player()->query("id") != "jingxue" ) {
	  	return "没有这个玩家。\n";
        }	
	
	if (!this_player() || !wizardp(this_player()) )  // player finger
	// !this_player() is used for inter-mud finger.
	// in that case, this_player() is not defined, so treat as player.
	// mon 8/27/97
	{
	
		if( objectp(body = find_player(name)) && geteuid(body)==name )
		{
			public_flag = body->query("env/public")?1:0;
		} else 
		{
			body = LOGIN_D->make_body(ob);
			if( !body || !body->restore() ) {
			  	destruct(body);
			  	destruct(ob);
			  	return "没有这个玩家。\n";
                        }
			public_flag = body->query("env/public")?1:0;
			destruct(body);
		}		
        	
        	msg = sprintf("\n┏━ 玩家档案 ━━━━━━━━━━━━━━━━━━┓\n");
                msg += sprintf("┃游戏中文姓名：%-34s┃\n", ob->query("name") );
		if( objectp(body = find_player(name)) 
			&& interactive(body)
			&& geteuid(body)==name ) 
		msg += sprintf("┃游戏现用姓名：%-34s┃\n", body->name(1) );
                msg += sprintf("┃游戏英文代号：%-34s┃\n", ob->query("id") );
                msg += sprintf("┃游戏权限等级：%-34s┃\n", SECURITY_D->get_status(name) );
                msg += sprintf("┃电子邮件地址：%-34s┃\n", public_flag?ob->query("email"):"不告诉你");
                msg += sprintf("┃上次连线时间：%-34s┃\n", BJTIME_CMD->chinese_time(1, ctime(ob->query("last_on"))) );
		if( objectp(body = find_player(name)) 
			&& geteuid(body)==name 
			&& interactive(body)
			&& (!wizardp(body) || 
				!body->query("env/invisibility")) ) {
		    // can only query_idle on an interactive player.
		        int idle=query_idle(body);
		if (idle>60)
		msg += sprintf("┃目前连线状况：%-34s┃\n","已发呆"+query_idle(body)+"秒钟。");
		else
		msg += sprintf("┃目前连线状况：%-34s┃\n","正在游戏中。");
		}
                msg += sprintf("┗━━━━━━━━━━━━━━━━━━ "+MUD_NAME+" ━┛\n"NOR);

		
	} else  	// wizard finger
	{
        	msg = sprintf("\n┏━ 玩家档案 ━━━━━━━━━━━━━━━━━━┓\n");
                msg += sprintf("┃游戏原始姓名：%-34s┃\n", ob->query("name") );
		if( objectp(body = find_player(name)) 
			&& interactive(body)
			&& geteuid(body)==name ) 
		msg += sprintf("┃游戏现用姓名：%-34s┃\n", body->name(1) );
                msg += sprintf("┃游戏英文代号：%-34s┃\n", ob->query("id") );
                msg += sprintf("┃游戏权限等级：%-34s┃\n", SECURITY_D->get_status(name) );
                msg += sprintf("┃电子邮件地址：%-34s┃\n", ob->query("email"));
                msg += sprintf("┃上次连线地址：%-34s┃\n", ob->query("last_from"));
                msg += sprintf("┃上次连线时间：%-34s┃\n", BJTIME_CMD->chinese_time(1, ctime(ob->query("last_on"))) );

		if( objectp(body = find_player(name)) 
			&& interactive(body)
			&& geteuid(body)==name ) {
		msg += sprintf("┃目前连线状况：%-34s┃\n","已发呆"+query_idle(body)+"秒钟。");
		msg += sprintf("┃玩家游戏年龄：%-34s┃\n",age_string((int)body->query("mud_age")));
		msg += sprintf("┃目前连线地址：%-34s┃\n",query_ip_number(body));
		}

                msg += sprintf("┗━━━━━━━━━━━━━━━━━━ "+MUD_NAME+" ━┛\n"NOR);
	}
	
	destruct(ob);
	return msg;
}

//this function is not used.  remote finger still use finger_user.
//mon 3/7/98
varargs string remote_finger_user(string name, int chinese_flag)
{
	object ob, body;
	string msg;

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() ) {
	        destruct(ob);
		return chinese_flag ? "没有这个玩家。\n" : "No such user.\n";
        }
	if( chinese_flag ) msg =  sprintf(
		"\n英文代号：\t%s\n姓    名：\t%s\n权限等级：\t%s\n"
		"电子邮件地址：\t%s\n上次连线地址：\t%s( %s )\n\n",
		ob->query("id"),
		ob->query("name"),
		SECURITY_D->get_status(name),
		ob->query("email"),
		ob->query("last_from"),
		ctime(ob->query("last_on"))
	);
	else msg =  sprintf(
		"\nName\t: %s\nStatus\t: %s\nEmail\t: %s\nLastOn\t: %s( %s )\n\n",
		capitalize(ob->query("id")),
		SECURITY_D->get_status(name),
		ob->query("email"),
		ob->query("last_from"),
		ctime(ob->query("last_on"))
	);
	if( body = find_player(name) ) {
		if( !this_player() || this_player()->visible(body) )
			msg += chinese_flag ?
				("\n" + ob->query("name") + "目前正在线上。\n"):
				("\n" + capitalize(name) + " is currently connected.\n");
	}

	destruct(ob);
	return msg;
}

object acquire_login_ob(string id)
{
	object ob;

	if( ob = find_player(id) ) {
		// Check if the player is linkdead
		if( ob->query_temp("link_ob") )
			return ob->query_temp("link_ob");
	}
	ob = new(LOGIN_OB);
	ob->set("id", id);
	if(ob->restore()) return ob;
	else {
	  destruct(ob);
	  return 0;
        }
}


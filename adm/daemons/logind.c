// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <mudlib.h>     // for GB_AND_BIG5 define.
#define FileName "/adm/daemons/UserNumber" // by canoe
inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;

string *banned_name = ({ });

string *default_name=({
	"猴子","狐狸", "老鼠", "蜻蜓","甲虫","蝴蝶","蝈蝈",
	"螳螂","瓢虫","蝗虫","蟋蟀","牛", "老虎", "兔子",
	"狗","猫咪","羊","猪","骆驼","乌龟","蛇","鱼儿",
	"鹿","马","犀牛",
});

string *default_prefix=({
	"小","大","老","白","黄","黑","花","灰","纸","木头","石头","泥",
});

void logind_user_log(); // mon 11/5/98
int total_count;
int howmany_user();
private void encoding(string arg, object ob);
private void if_young(string arg, object ob);
private void get_id(string arg, object ob);
private void confirm_id(string yn, object ob);
private void get_nresp(string arg, object ob, object user);
object make_body(object ob);
private void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
string dis_attr(int value);
private void confirm_gift(string yn,object ob,object user);
private void judge_freeze(object ob); //函数原形 用来判断账号是否被冻结
int do_counter(); // 总共登陆人数统计
int check_legal_password(object ob,string arg); // 验证密码可行性

int howmany_user()
{
	int i,j,reg_cnt;
	string *dir , *ppls, name;
	mixed info;
	seteuid(getuid());
	reg_cnt=0;
	dir=get_dir(DATA_DIR+"login/");
	for(i=0; i<sizeof(dir);i++)	
	{
		reset_eval_cost();
		ppls=get_dir(DATA_DIR+"login/"+dir[i]+"/");
		reg_cnt+=sizeof(ppls);
	}
	return reg_cnt;
}

void init_banner_name()
{
	int i;
	string b_file,*b_names;
	banned_name = ({
		"你", "我", "他", "她", "它", "江泽民", "邓小平", "李鹏", "朱榕基","习近平",
        	"自己", "某人", "尸体", "大家","爸","他妈的", "去你的", "毛泽东", 
        	"巫师", "他奶奶的","眠兔","眠免","眼兔","阿枚","小雨",
	});
	b_file = read_file("/doc/npc");
	if( b_file )
	{
		b_names = explode(b_file,"\n");
		if( b_names && arrayp(b_names) )
		{
			for(i=0;i<sizeof(b_names);i++)
				if( b_names[i] && strlen(b_names[i])>3 )
					banned_name+= ({b_names[i]});
		}
		CHANNEL_D->do_channel(this_object(),"sys","用户名过滤已启用。");
	}	
}

void create() 
{
	seteuid(getuid());
	set("channel_id", "连线精灵");
	set("id", "logind");
	init_banner_name();
}

// mon 11/7/98
void logind_user_log()
{
	int user=sizeof(users());
	int total;

	remove_call_out("logind_user_log");
	rm("/log/user_count");    
	log_file("user_count",""+((total=total_count)?total:user)+"\n"+user+"\n"+UPTIME_CMD->report_str()+"\n"+"小雨西游\n");
	remove_call_out("logind_user_log");
	call_out("logind_user_log",600);
}

// added by snowcat Mar 11 1998
void logon(object ob)
{
	// by canoe 防止恶意reconnet造成系统崩溃
	object *online_user;
	int logon_cnt;
	int i;
	if(uptime() < 30)
    	{
    		write(HIY"\n\t\t驱动程序正在启动过程中，请稍候再来。\n\n"NOR,);
        	destruct(ob);
        	return;
	}
	online_user = filter_array(children(LOGIN_OB), (: interactive :));
	i = sizeof(online_user);
	logon_cnt = 0;
	while (i--) 
	{  
		if(query_ip_number(online_user[i]) == query_ip_number(ob))
			logon_cnt = logon_cnt + 1 ;
	}
	if(logon_cnt > 15 ) 
	{
		log_file( "login", sprintf("%s:恶意reconnet:%s\n" , ctime(time()) , query_ip_number(ob) ) );
		write(HIW"请你稍候再进入本MUD...... \n"NOR);
		destruct(ob);
		return;
        }
// by canoe 防止恶意reconnet造成系统崩溃
	cat(WELCOME);
	write("       请选择你要使用的内码("HIW"gb/big5"NOR")！使用国标码的玩家请键入：gb\n");
	write("       Welcome to "BLINK HIY"XYCQ!"NOR" Select 国标码 GB or き絏 BIG5 (gb/big5):\n\n\n");
	input_to( (: encoding :), ob );
}

private void encoding(string arg, object ob)
{
	object *usr;
	int i, ttl_cnt, wiz_cnt, ppl_cnt, login_cnt, max_online,avg_online;
	string ip_name, ip_number, online_num;
	int ii;
	mixed info;
	int encode;
	string msg;

	if(!arg || arg=="") 
	{
		write("\nSelect 国标码 GB or き絏 BIG5 (gb/big5):");
		input_to( (: encoding :), ob );
		return;
	} 
	else if(arg[0..0]=="g" || arg[0..0]=="G")
		encode=0;
	else if(arg[0..0]=="b" || arg[0..0]=="B")
		encode=1;
	else	
	{
		write("\nSelect 国标码 GB or き絏 BIG5 (gb/big5):");
		input_to( (: encoding :), ob );
		return;
	}
	if(encode==1){
		set_encoding("big5");
	}
	else{
	set_encoding("GBK");
       }
	ip_name = query_ip_number(ob);
	ip_number = query_ip_number(ob);

// snowcat dec 10 1997
// try strict ban here...weiqi.
	if("/adm/daemons/band"->is_strict_banned(query_ip_number(ob)) == 1) 
	{
		write(HIR"您的地址在本 MUD 之信誉被人破坏了。\n请联系管理元申诉。\n"NOR);
		destruct(ob);
		log_file( "allcont", sprintf("kicked out, strict_banned\n"));
		return;
	}
// try not accept "name" as IP
	if(!ip_name) 
	{
		destruct(ob);
		log_file( "allcont", sprintf("kicked out, No IP\n"));
		return;
	}
	for(ii=0; ii<sizeof(ip_number); ii++) 
	{
		if( (ip_number[ii] != '.')&&(ip_number[ii]>'9') )
		{
			destruct(ob);
			log_file( "allcont", sprintf("kicked out, Non_number\n"));
			return;
		}
	}
	write(CLR);
	cat(WELCOME);
	//cat(NEW_PLAYER_INFO);

// children will show both netdead and interactive users.
	usr = children(USER_OB);
	wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
	for(i=0; i<sizeof(usr); i++) 
	{
		if( !environment(usr[i]) ) 
			login_cnt++;
		else if( (wizardp(usr[i]) && (string)wizhood(usr[i])!="(elder)")
	      	&& !usr[i]->query("env/invisibility") ) 
			wiz_cnt++;
		else	ppl_cnt++;
	}
	max_online = atoi(read_file(__DIR__"maxonline",1));
	avg_online = atoi(read_file(__DIR__"avguser",1));
	if(ppl_cnt > max_online)
	{
		online_num = sprintf("%d",ppl_cnt);
		write_file(__DIR__"maxonline",online_num,1);
	}
	msg = NOR"西游记类泥潭"GRNBLU"『小雨西游Ⅱ』"NOR"站点创建时间："YEL"2013年12月30日\n";
	msg += NOR"西游记类泥潭"GRNBLU"『小雨西游Ⅱ』"NOR"目前使用版本："YEL"3.0\n"NOR;
	msg += NOR"西游记类泥潭"GRNBLU"『小雨西游Ⅱ』"NOR"目前奖励基数："NOR HIR+QUEST_D->query_job_p()+"%"NOR"\n";
	msg += NOR"目前本站共有" YEL+ (string)chinese_number(wiz_cnt) + NOR"位巫师、" HIC+ (string)chinese_number(ppl_cnt);
	msg += NOR"位玩家在线上，以及" HIG+ (string)chinese_number(login_cnt) + NOR"位使用者尝试连线中。\n";
	write(msg);
	rm("/log/counter_for_web");
	log_file("counter_for_web",sprintf("目前共有%s位巫师、%s位玩家在线上，以及%s位使用者尝试连线中",chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) ));
	UPTIME_CMD->report();
	login_cnt = 0;
// mon 11/7/98
//check whether user_log still running.
	info = filter_array(call_out_info(), (: $1[1]=="logind_user_log" :));
	if(!sizeof(info)) logind_user_log();
	if(ob) ob->set_temp("id_count",0);
	write(NOR"小雨西游提醒您：多谢你看一看上面的游戏建议。祝你游戏愉快。\n"NOR);
	write(NOR"请您做出选择：① 进入游戏(Enter)  ② 立即退出(Exit)");
	input_to( (: if_young :), ob );
}

private void if_young(string arg, object ob)
{
	string msg;	
	int id_count;
	id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id.
	id_count++;
	ob->set_temp("id_count",id_count);
	if(id_count>3) 
	{
		destruct(ob);
		log_file( "allcont", sprintf("kicked out, illegal ID.\n"));
		return;
	}
	if( !arg ) 
	{
		write(NOR"请您做出选择：① 进入游戏(Enter)  ② 立即退出(Exit)");
		input_to( (: if_young :), ob );
		return;
	}
	if( arg[0..0] == "2" )
	{
		write("\n很好，很高兴您能认识到网络游戏的危害，再见。。\n");
		destruct(ob);
		return;
	}
	//msg = read_file(XYJ_SITES);
	if( msg && stringp(msg) )
	{
		msg = COLOR_D->replace_color(msg,1);
		write(msg);
	}	
	write("\n您的英文名字[ID]：（新玩家请键入 "HIW"new"NOR" 注册）"NOR);
	input_to( (: get_id :), ob);
}

private void get_id(string arg, object ob)
{
	object ppl, *usr = children(USER_OB);
	int id_count;
	int NowLogin, MaxLimit, login_site, i;
	string my_ip, new_ip;
//end edw

	if(!ob) return;
	id_count=ob->query_temp("id_count");
	id_count++;
	ob->set_temp("id_count",id_count);
	if(id_count>6) 
	{
		destruct(ob);
		log_file( "allcont", sprintf("kicked out, illegal ID.\n"));
		return;
        }
	arg = lower_case(arg);
	if( !check_legal_id(arg)) 
	{
		write("您的英文名字："NOR);
		input_to("get_id", ob);
		return;
	}
	ppl = find_body(arg);

#ifdef MAX_USERS
	if( (string)SECURITY_D->get_status(arg)=="(player)"
	  && sizeof(users()) >= MAX_USERS ) 
	{
		if( !ppl ) 
		{
			write("对不起，小雨西游的玩家已经太多了，请待会儿再来。\n");
			destruct(ob);
			return;
		} 
	}
#endif

	if( wiz_level(arg) < wiz_lock_level ) 
	{
        	write("对不起，" + MUD_NAME + "目前限制巫师等级 " + WIZ_LOCK_LEVEL+ " 以上的人才能连线。\n");
		destruct(ob);
	        return;
        }
	
#ifdef MAX_LOGIN
	if(!ppl) 
	{
		my_ip=query_ip_number(ob);
		MaxLimit="/adm/daemons/band"->allow_multi_login(my_ip);
      		if(!MaxLimit) MaxLimit=MAX_LOGIN;
#ifdef LOGIN_SITE
		login_site=LOGIN_SITE;
#else
	  	login_site=0;
#endif
		if(my_ip && login_site==0) // ignore the last field of the IP
			my_ip=my_ip[0..strsrch(my_ip, ".", -1)];
		NowLogin=0;
		for(i=0;i<sizeof(usr);i++) 
			if(ob!=usr[i]) 
			{
				new_ip=query_ip_number(usr[i]);
				if(!new_ip && !interactive(usr[i]))
					new_ip=usr[i]->query_temp("netdead_ip");
				if(new_ip && login_site==0)
					new_ip=new_ip[0..strsrch(new_ip, ".", -1)];
				if(my_ip==new_ip) 
					NowLogin++;
			}
		if(NowLogin>=50) 
		{
			write(sprintf("对不起，从你的IP地址不能同时登录%s位人物。\n",chinese_number(MaxLimit+1)));
			destruct(ob);
	        	return;
		} 
	}
#endif

	if( (string)ob->set("id", arg) != arg ) 
	{
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}
	else if(arg=="new")  // new player login
	{
		write("\n请您给自己取一个英文名字："NOR);
		input_to("get_new_id",ob);
		return;
	} 
	else if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 ) 
	{
		if( ob->restore() ) 
		{
			judge_freeze(ob);  
			write("\n请输入密码(管理密码或登陆密码)："NOR);
			input_to("get_passwd", 1, ob);
			return;
		}
		write("您的人物储存档出了一些问题，请利用别的人物通知巫师处理。\n");
		destruct(ob);
		return;
	} 
	write("没有这个玩家．．．\n"NOR);
	write("\n您的英文名字[ID]：（新玩家请键入 "HIW"new"NOR" 注册）"NOR);
	input_to("get_id", ob);
	return;
}

private void judge_freeze(object ob)
{
	int freeze_time;        
	freeze_time=ob->query("freeze_time");
	if( time() < freeze_time ) 
	{
		write ("对不起，这个账号已经被冻结,还有"+(freeze_time+3600-time())/3600 +"小时才能使用。 \n");
		destruct(ob);
		return;
        }       
}                      

private void get_new_id(string arg, object ob)
{
	mixed foo;
	object ppl, *body;  
	int id_count, i, nb=0;  
	if(!ob) return;
	id_count=ob->query_temp("id_count");

	id_count++;
	ob->set_temp("id_count",id_count);
	if(id_count>6) 
	{
		destruct(ob);
		log_file( "allcont", sprintf("kicked out, illegal ID.\n"));
		return;
        }
	if(!arg) 
	{
        	write("\n请您给自己取一个英文名字："NOR);
		input_to("get_new_id", ob);
		return;
        }
	arg = lower_case(arg);
	if( !check_legal_id(arg)) 
	{
        	write("\n请您给自己取一个英文名字："NOR);
		input_to("get_new_id", ob);
		return;
	}
	if( (string)ob->set("id", arg) != arg ) 
	{
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}
	ppl = find_body(arg);
	if(ppl || arg=="guest" || arg=="new") 
	{
		write("这个名字已经被别的玩家使用了．．．"NOR);
        	write("\n请您给自己取一个英文名字："NOR);
		input_to("get_new_id",ob);
		return;
	}
	if( file_size(ob->query_save_file()+ __SAVE_EXTENSION__) >= 0 ) 
	{
		write("这个名字已经被别的玩家使用了．．．"NOR);
        	write("\n请您给自己取一个英文名字："NOR);
		input_to("get_new_id",ob);
		return;
	} 
	foo = NAME_D->valid_id(arg);
	if( foo && stringp(foo) )
	{
		write("对不起，英文名字中不能带 "HIR+foo+" "NOR"\n");
	        write("\n请您给自己取一个英文名字："NOR);
		input_to("get_new_id",ob);
		return;
	}	
	ob->set("new_player", 1);  
	body = children(LOGIN_OB);  
	i = sizeof(body);  
	while (i--) 
	{   
		if( clonep(body[i]) && body[i]->query("id")==arg  
	 	&& body[i]->query("new_player")==1 ) 
			nb++;  
		if( nb>1 ) 
		{  
			write("对不起，已经有人在用这个英文名字创造人物了．．．\n"NOR);  
			write("\n请您给自己取一个英文名字："NOR);  
			ob->delete("new_player");  
			input_to("get_new_id",ob);  
			return;  
		}  
	}  

	confirm_id("Yes", ob);
	return;
}

private void get_passwd(string pass, object ob)
{
	string my_pass,id;
	object user;
        int pwdflag=0; 
	write("\n");
	my_pass = ob->query("password");
	
	if( crypt(pass, my_pass) == my_pass)
	{
		write("\n您使用了登陆密码成功登陆！\n"NOR);
		pwdflag=1;
	} 
	my_pass=ob->query("super_password");
	if( !pwdflag
         && crypt(pass, my_pass) ==my_pass )
	{
		write("\n您使用了管理密码成功登陆！\n我们建议您只有在密码被盗等情况下才使用管理密码登陆！\n"NOR);
		pwdflag=1;
	}
	if( !pwdflag
         ||!SECURITY_D->match_wiz_site(ob, query_ip_number(ob)) )
	{
		write(HIR"密码错误！"NOR);
		if((id=ob->query("id")) && member_array(id,SECURITY_D->get_wizlist())!=-1)
			log_file("wizlogin",ctime(time())+" "+id+" failed login from "+query_ip_number(ob)+"\n");
		else	log_file("login",ctime(time())+" "+id+" failed login from "+query_ip_number(ob)+"\n");
		ob->add_temp("err_passwd",1);
		if( ob->query_temp("err_passwd")<=3 )
		{
			write("\n请输入密码(管理密码或登陆密码)："NOR);	
			input_to("get_passwd", 1, ob);
			return;
		}
		else	
		{
			write("请重新连线，键入正确的密码或另取一个新的英文名字。\n"NOR);
			destruct(ob);
			return;
		}
	}// end
	if(time()-(int)ob->query("kickout_time") < 600)
	{
		write("你现在没有进入〖小雨西游〗的权利，请十分钟后再联线。\n");
		destruct(ob);
		return;
	}// end
	user = find_body(ob->query("id"));
	if(user) 
	{
		if( !interactive(user) ) 
		{
			reconnect(ob, user);
			return;
		}
		write(HIY"您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)"NOR);
		input_to("confirm_relogin", ob, user);
		return;
	}
	if( ob && objectp(user = make_body(ob)) ) 
	{
		if( user->restore() ) 
		{
			enter_world(ob, user,0);
			return;
		} 
		else	destruct(user);
	}
	write("请您重新创造这个人物。\n"NOR);
	confirm_id("y", ob);
}

private void confirm_relogin(string yn, object ob, object user)
{
	object old_link;
	if( yn=="" ) 
	{
		write(HIG"您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)"NOR);
		input_to("confirm_relogin", ob, user);
		return;
	}	
	if( (yn[0]!='y' && yn[0]!='Y') || !user ) 
	{
		write("好吧，欢迎下次再来。\n");
		destruct(ob);
		return;
	} 
	else	
	{
		tell_object(user, "有人从别处( " + query_ip_number(ob)+ " )连线取代你所控制的人物。\n");
		log_file( "usage", sprintf("%s(%s) replaced by %s (%s)\n",user->query("name"), user->query("id"),query_ip_number(ob), ctime(time()) ) );
	}
	old_link = user->query_temp("link_ob");
	if( old_link && interactive(user)) 
	{
	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());
	exec(old_link, user);
	}
if(old_link)      // mon 9/14/98
	destruct(old_link);
reconnect(ob, user);	
}

private void confirm_id(string yn, object ob)
{
write( @TEXT

请您给自己想一个符合〖西游记〗中国神话世界的中文名字。这
个名字将代表你在小雨西游中的人物，而且往后将不能再更改。
请不要取一些不雅或是容易造成他人困扰的名字。

TEXT);
write("您的中文名字：");
ob->set_temp("get_name",0);
input_to("get_name", ob);
}

private void get_name(string arg, object ob)
{
	arg = CONVERT_D->input(arg,ob);
	if( !check_legal_name(arg) ) 
	{
		ob->add_temp("get_name",1);
		if(ob->query_temp("get_name")>2) 
		{// the user can't input proper chinese name.assign one for him/her.    mon 4/19/98
			arg = default_prefix[random(sizeof(default_prefix))]+default_name[random(sizeof(default_name))];
			write("因为你不能输入适当的中文名字，系统指定你的名字为："+arg+"\n");
			write("请在进入游戏可找长安国子监的长孙无忌修改。\n");
		} 
		else	
		{
			write("您的中文名字：");
			input_to("get_name", ob);
			return;
		}
	}
// by canoe for suppwd
	printf("%O\n", ob);
	ob->set("name", arg);
	write(HIG"\n注意：人物口令修改、档案备份、自杀等需要管理密码；\n\n"NOR);
	write(HIR"      一般情况下不予更改，请务必妥善保存。\n\n"NOR);
	write(HIY"请设定您的管理密码："NOR);
	input_to("get_super_password", 1, ob);
}

private void get_super_password(string pass, object ob)
{
	write("\n");
	if( !check_legal_password(ob,pass)) 
	{
		write(HIW"请重新设定您的密码：");
        	input_to("get_super_password", 1, ob);
		return;
	}
	ob->set("super_password", crypt(pass,0) );
	write(HIR"请再输入一次您的管理密码，以确认您没记错："NOR);
	input_to("confirm_super_password", 1, ob);
}

private void confirm_super_password(string pass, object ob)
{
	string old_pass;
	write("\n");
	old_pass = ob->query("super_password");
	if( crypt(pass, old_pass)!=old_pass ) 
	{
		write(HIY"您两次输入的管理密码并不一样，请重新设定一次管理密码："NOR);
		input_to("get_super_password", 1, ob);
		return;
	}
	write(HIC"游戏登陆密码是指您每次进入游戏时必须输入的密码。\n\n"NOR);
	write(HIG"请设定您的游戏登陆密码："NOR);
	input_to("new_password", 1, ob);
}

private void new_password(string pass, object ob)
{
	write("\n");
	if( strlen(pass)<5 ) 
	{
		write("密码至少要由五个字符组成，请重设您的密码：");
		input_to("new_password", 1, ob);
		return;
	}
	if( crypt(pass, ob->query("super_password"))==ob->query("super_password") ) 
	{
		write("您的登陆密码不能和管理密码一样，请重设您的密码：");
		input_to("new_password", 1, ob);
		return;
	}
	ob->set("password", crypt(pass,0) );
	write(HIY"请再输入一次您的密码，以确认您没记错："NOR);
	input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) 
	{
		write("您两次输入的密码并不一样，请重新设定一次登陆密码：");
		input_to("new_password", 1, ob);
		return;
	}
	write("您的电子邮件地址：");
	input_to("get_email",  ob);
}

private void get_email(string email, object ob)
{
	object user;
	string id,addr;
	write("\n");
	if(email=="" || strsrch(email,".")==-1 
  	|| sscanf(email,"%s@%s",id,addr) !=2)
	{
		write(HIC"电子邮件地址需要是 id@dtxy.net 的格式。\n"NOR);
		write(HIR" 请正确填写，当您的档案出现意外时，此地址是巫师与您联系的唯一正式途径\n"NOR);
		write(HIW"您的电子邮件地址："NOR);
		input_to("get_email", ob);
		return;
	}
	ob->set("email", email);//end
	ob->set("body", USER_OB);
	if( !objectp(user = make_body(ob)) ) 
	{
		if(ob) destruct(ob);
		return;
	}
	write("您要扮演男性(m)的角色或女性(f)的角色？");
	input_to("get_gender", ob, user);
}

private void get_gender(string gender, object ob, object user)
{
	if( gender=="" ) 
	{
		write("您要扮演男性(m)的角色或女性(f)的角色？");
		input_to("get_gender", ob, user);
		return;
	}
	if( gender[0]=='m' || gender[0]=='M' )
		user->set("gender", "男性");
	else if( gender[0]=='f' || gender[0]=='F' )
		user->set("gender", "女性" );
	else	
	{
		write("对不起，您只能选择男性(m)或女性(f)的角色：");
		input_to("get_gender", ob, user);
		return;
	}
	confirm_gift("n",ob,user);	
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

	if(!ob || !ob->query("body")) 
		return 0;
	user = new(ob->query("body"));
	if(!user) 
	{
		write("现在可能有人正在修改玩家物件的程式，无法进行复制。\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name( ob->query("name"), ({ ob->query("id")}) );
	return user;
}

private void confirm_gift(string yn, object ob, object user)
{
	if(!ob || !user) 
	{
        	if(user) 
			destruct(user);
		if(ob)	destruct(ob);
		return;
        }
	user->set("kar", 20 );
	user->set("str", 20 );
	user->set("cps", 20 );
	user->set("int", 25 );
	user->set("cor", 20 );
	user->set("con", 20 );
	user->set("spi", 25 );
	user->set("per", 20 );
// mon 3/21/99 allow players to choose gift after login.
	user->set("no_gift",1);
	CHAR_D->setup_char(user); //setup user weight. mon 11/7/97
	user->set("title", "普通百姓");
	user->set("birthday", time() );
	user->set("potential", 99);
	user->set("food", user->max_food_capacity());
	user->set("water", user->max_water_capacity());
	user->set("channels", ({ "chat","rumor","xyj","sldh","es" }) );
//log_file( "usage", sprintf("%s was created from %s (%s)\n", user->query("id"),query_ip_number(ob), ctime(time()) ) );
	ob->set("last_from",query_ip_number(ob));
	ob->set("last_on",time());
// edit by canoe
//修改多重登陆新人
	ob->delete("new_player");  
//over
	return enter_world(ob, user,0);
}

string dis_attr(int value)
{       
	int gift=20;
	if( value > gift ) return sprintf( HIY "%3d" NOR, value );
	else if( value < gift ) return sprintf( CYN "%3d" NOR, value );
	else return sprintf("%3d", value);
}

varargs void enter_world(object ob, object user, int silent)
{
	object cloth, room, mbx;
	string startroom="";
	string ip_from;
	int num;

	reset_eval_cost();
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
// 5/11/98 mon
	user->set_encoding(ob->query_encoding());
	exec(user, ob);
	write("\n目前权限：" + wizhood(user) + "\n");
	user->setup();
	user->set("last_save", time());
	user->set_temp("login_data/time", time());
	user->set_temp("login_data/exp", (int)user->query("combat_exp"));
	user->set_temp("login_data/dx",(int)user->query("daoxing"));
	ob->save();
	if( !silent ) 
	{
		if(file_size(MOTD)>0)
			user->start_more(read_file(MOTD));
		if(user->query("no_gift")) 
			user->move("/d/wiz/init",1);
		else	
		{
			if( user->is_ghost() )
				startroom = DEATH_ROOM;
			else if( strlen(startroom = user->query("startroom"))<2 )
				startroom = START_ROOM;
			if(!wizardp(user) && startroom[0..2]=="/u/") 
			{
				startroom = START_ROOM;
				user->set("startroom",startroom);
			}
                //added by mon 10/27/97
			if( ( ("/adm/daemons/band")->create_char_banned(query_ip_number(user))==1 
		    	 || ("/adm/daemons/band")->is_banned(query_ip_number(user))==1 ) 
		  	 && !wizardp(user) ) 
			{
				user->move("/d/wiz/guest");
				log_file( "allcont", sprintf("from banned site\n"));
			}
			else if(  ("/adm/daemons/band")->ban_name(user) 
		  	 && !wizardp(user) ) 
			{
				user->move("/d/wiz/guest");
				user->set("startroom", "/d/wiz/guest");
			}				
			else if( !catch(load_object(startroom)) )
				user->move(startroom);
			else	
			{
				user->move(START_ROOM);
				startroom = START_ROOM;
				user->set("startroom", START_ROOM);
			}
			if( !environment(user) )
			{
				user->move(START_ROOM);
				startroom = START_ROOM;
				user->set("startroom", START_ROOM);
			}
			if( !wizardp(user) || (!user->query("env/invisibility")&&!user->is_yinshen()) )
				tell_room(startroom, user->query("name") + "连线进入这个世界。\n",({user}));
		}
		//write(NOR BLINK HIR"\n\n\t小雨西游指南"HIY"http://bbs.xymud.com/viewthread.php?tid=8398&extra=page%3D1\n\n"NOR);
		mbx=ob->query_temp("mbox_ob");
		if(!mbx) 
		{
			mbx=new(MAILBOX_OB);
			mbx->set_owner(ob->query("id"));
		}
		num=mbx->query_new_mail();
        	if( num>0 ) 
			write( GRN + "\n千里眼告诉你：有您"+chinese_number(num)+"封信！请到南城客栈来一趟．．．\n\n" + NOR);
		destruct(mbx);
	      	ip_from="/adm/daemons/ipd"->seek_ip_address(query_ip_number(user));
   		CHANNEL_D->do_channel( this_object(),wizardp(user)?"wiz":"sys",sprintf(NOR WHT "%s连线进入游戏。"NOR,user->name()+"("+capitalize(user->query("id")) + ")")); 
	}

	user->update_age();
	UPDATE_D->check_user(user, 0);
	TOPTEN_D->topten_checkplayer(user);
	("/adm/daemons/newsd")->prompt_user(user); 
}

varargs void reconnect(object ob, object user, int silent)
{
object old_link;
	
// mon 9/15/98
old_link=user->query_temp("link_ob");
if(old_link && old_link!=ob)
	destruct(old_link);
user->set_temp("link_ob", ob);
ob->set_temp("body_ob", user);
// 5/11/98 mon
user->set_encoding(ob->query_encoding());
exec(user, ob);
user->reconnect();
if( !silent && !user->query("env/invisibility")) 
	{
	tell_room(environment(user), user->query("name") + "重新连线回到这个世界。\n",({user}));
	CHANNEL_D->do_channel( this_object(),(wizardp(user)?"wiz" :"sys"),sprintf("%s重新连线进入游戏。", user->query("name")+"(" + user->query("id") + ")") );
	}
UPDATE_D->check_user(user, 1); // this is for reconnect.
}

int check_legal_id(string id)
{
	int i;
	string *legalid;
	i = strlen(id);
	
	if( (strlen(id) < 3) || (strlen(id) > 8 ) ) 
	{
		write("对不起，你的英文名字必须是 3 到 8 个英文字母。\n");
		return 0;
	}
	while(i--)
	if( id[i]<'a' || id[i]>'z' ) 
	{
		write("对不起，你的英文名字只能用英文字母。\n");
		return 0;
	}
	legalid = explode(read_file(BANNED_ID), "\n");
	for(i=0; i<sizeof(legalid); i++)   
	{
		if( id == legalid[i] )   
		{
			write("对不起，这种名字会造成其他人的困扰。\n");
			return 0;
		}
	}
	return 1;
}

int check_legal_name(string name)
{
	int i;
	i = strlen(name);
	if( (strlen(name) < 2) || (strlen(name) > 4 ) ) 
	{
		write("对不起，你的中文名字必须是2-4个中文字符。\n");
		return 0;
	}
	while(i--) 
	{
		if( name[i]<=' ' ) 
		{
			write("对不起，你的中文名字不能用控制字符。\n");
			return 0;
		}
		if( !is_chinese(name) ) 
		{
			write("对不起，请您用「中文」取名字。\n");
			return 0;
		}
	}
	if( member_array(name, banned_name)!=-1 ) 
	{
		write("对不起，这种名字会造成其他人的困扰。\n");
		return 0;
	}
	reset_eval_cost();
	for(i=0;i<sizeof(banned_name);i++)
	{
		if( strsrch(name,banned_name[i])!=-1 )
		{
			write("对不起，「"+banned_name[i]+"」为敏感字，会造成其他人的困扰。\n");
			return 0;
		}
	}
	return 1;
}

object find_body(string name)
{
object ob, *body;

if( objectp(ob = find_player(name)) )
	return ob;
body = children(USER_OB);
for(int i=0; i<sizeof(body); i++) 
	{
        ob=body[i];
	if( clonep(ob) && getuid(ob)==name )
		return ob;
        }
return 0;
}

int set_wizlock(int level)
{
if( wiz_level(this_player(1)) <= level )
	return 0;
if( geteuid(previous_object()) != ROOT_UID )
	return 0;
wiz_lock_level = level;
return 1;
}
// by canoe
int do_counter()
{       
int number;
string file;
file = read_file(FileName);
sscanf(file,"%d",number);
number++;
file=sprintf("%d",number);
write_file(FileName,file,1);
return number;
}

int check_legal_password(object ob,string pass)
{
int i;
int bigletter=0;
int smlletter=0;
int number=0;
string id;
i = strlen(pass);
if( strlen(pass) <= 6)   
	{
	write(WHT"对不起，你的管理密码必须最少七个字符。\n");
	return 0;
        }
id= ob->query("id");	
if( strsrch(id, pass) != -1 || strsrch(pass,id) != -1)
	{
	write(WHT"对不起，你的管理密码和你的英文名字太象了。\n"NOR);
	return 0;
        }
while(i--) 
	{
	if( pass[i]<='Z' && pass[i] >='A' ) bigletter++;
	if( pass[i]<='z' && pass[i] >='a' ) smlletter++;
        }
if( bigletter == 0 || smlletter == 0 
 || bigletter+smlletter == strlen(pass))
	{
        write(WHT"您的管理密码必需包含大写" + RED"和" + WHT"小写英文字母"+ RED"和" + WHT"其它特殊符号（数字，标点）。\n"NOR);
	return 0;
	}
return 1;
//end
}

// bigeye.c
#include <ansi.h>
inherit NPC_SAVE;

string send_mail();
string receive_mail();
string xin_job();
nosave int i;

string *dirs = ({
        "/d/city","/d/westway","/d/kaifeng","/d/lingtai","/d/moon",
        "/d/gao","/d/sea","/d/nanhai","/d/eastway","/d/ourhome/honglou", 
        "/d/qujing/wuzhuang","/d/shushan","/d/sea","/d/jjf",
        
});

void create()
{   
	reload("jiangrobot");
	set_name("千里眼", ({"qianli yan", "bigeye", "youchai","chai" }) );
	set("title", "邮差");
	set("gender", "男性" );
	set("age", 30);
	set("long","前玉皇大帝亲信。因为偷看玉女出浴而被罚为邮差。\n他本来是和顺风耳一起呆在花果山仙石处的，\n后因嫌不够热闹跑到长安来了。\n");
	set_level(80); 
	set("attitude", "friendly");
	set("inquiry", ([
        	"name"		: "连我你都不认识？大名鼎鼎的千里眼就是我。", 
        	"here"		: "鬼知道这是什么地方！我只负责收信发信。",
        	"玉女"  	: "嘿嘿．．．不错。就算砍头我也划算了。",
        	"玉皇大帝" 	: "你别提他！一提我就有气．．．只许州官放火，不许百姓点灯。",
        	"发信"  	: (: send_mail :),
        	"收信"  	: (: receive_mail :),
        	"信件"  	: (: receive_mail :),
        	"信"    	: (: receive_mail :),
        	"mail"  	: (: receive_mail :),
        	"mailbox" 	: (: receive_mail :),
        	"送信"		: (: xin_job :),
	]) );
	set_skill("literate", 700);
	set_skill("dodge", 500);
	set_skill("unarmed", 400);
	set("per", 25);
	setup();
	if( !clonep() ) 
        {
        	add_money("coin", 70);
        	carry_object("/d/ourhome/obj/linen")->wear();
        	CHANNEL_D->register_relay_channel("rumor");
        }
}

void relay_channel(object ob, string channel, string msg)
{
	string who;
	if( !userp(ob) || (channel != "rumor") )       
        	return;
	if( wizardp(ob) ) 
        	return;
	who = ob->query("id");
	if( ob==this_object() )
        	return;
	if( msg!="" )
        {
        	i+=1;
        	if(i>10) i=1;
        	delete("memory/"+i);
        	add("memory/"+i+"/"+who,({ msg }));
        }
	else    return 0;
}

string send_mail()
{
	object mbox;

	if( this_player()->query_temp("mbox_ob") )
        	return "你的信箱还在吧？用信箱就可以寄信了。\n";
	if( !environment()
  	||  base_name(environment()) != query("startroom") )
		return "等一下到南城客栈来找我吧。\n";
	seteuid(getuid());
	mbox = new(MAILBOX_OB);
	mbox->move(this_player());
	return "哦．．．要寄信是吗？这是你的信箱，寄信的方法信箱上有说明。\n";
}

string receive_mail()
{
	object mbox;
	if( this_player()->query_temp("mbox_ob") )
        	return "你的信箱还在吧？你所有的信都在里面。\n";
	if( !environment()
  	 || base_name(environment()) != query("startroom") )
        	return "等一下到南城客栈来找我吧。\n";
	seteuid(getuid());
	mbox = new(MAILBOX_OB);
	mbox->move(this_player());
	return "好，待我找找．．．有了，你的信箱在这，慢慢看吧，不打搅你了。\n";
}

void init()
{
	if( !environment()  ||  base_name(environment()) != query("startroom") )
        	return;
	add_action("give_quest", "quest");
}

string time_period(int timep, object me)
{
	string time;
	time = CHINESE_D->chtime(timep);
	return "在" + time + "内";
}

int give_quest()
{
	return err_msg(HIG"千里眼在你耳边悄声说道：向我打听(ask)关于「送信」的事即可。\n"NOR);
}

string query_dir(string arg)
{
	string *f;
	int i;
	if( !arg )
		return 0;
	f = explode(arg,"/");
	arg = "/";
	for(i=0;i<(sizeof(f)-1);i++)	
	{
		arg+= f[i];
		if( i<sizeof(f)-2 )
			arg+= "/";
	}
	return arg;
}

string query_name(object who)
{
	string str1,str2,str3,str4,name,clr,*color;
	int i;
	if( !who || !environment(who) )
		return 0;
	color = ({HIW,HIB,HIM,HIC,HIR,HIY,WHT,BLU,MAG,CYN,RED,YEL});	
	clr = color[random(sizeof(color))];
		
	str1 = MISC_D->find_place(environment(who));
	str1 = COLOR_D->clean_color(str1);
	i = strlen(str1);
	i = random(i/2)*2;
	name = sprintf("%s",str1[i..i+1]);
	str1 = replace_string(str1,name,NOR+REV+color[random(sizeof(color))]+"  "NOR+clr);

	str2 = COLOR_D->clean_color(who->name());
	str3 = capitalize(who->parse_command_id_list()[0]);
	str4 = COLOR_D->clean_color(who->short());
	i = strlen(str2);
	i = random(i/2)*2;
	name = sprintf("%s",str2[i..i+1]);
	str4 = replace_string(str4,name,NOR+REV+color[random(sizeof(color))]+"  "NOR+clr);
	
	i = strlen(str3);
	i = random(i/2)*2;
	name = sprintf("%s",str3[i..i+1]);
	str4 = replace_string(str4,name,NOR+REV+color[random(sizeof(color))]+"  "NOR+clr);

	str2 = COLOR_D->clean_color(who->short());
	str2 = replace_string(str2,who->name(),"");
	str2 = replace_string(str2,capitalize(who->parse_command_id_list()[0]),""); 
	i = strlen(str2);
	i = random(i/2)*2;
	name = sprintf("%s",str2[i..i+1]);
	str4 = replace_string(str4,name,NOR+REV+color[random(sizeof(color))]+"  "NOR+clr);
	
	return clr+str1+clr+"的"+str4+NOR;	
}

string xin_job()
{
	object me,letter;
	object who,*ob=livings();
	int i,lvl,timep;
	mixed foo;
	string msg,name,id,str;
	
	me = this_player();
	
        if( time()<me->query("jobs/last_letter")+5 )
		return "你刚刚送过信，还是歇歇再去吧。";
	
	foo = me->doing_job("送信任务");
	if( foo )
	{
		if( time()>me->query_temp("letter_time") )
		{
			foo = me->cancel_job("送信任务");
			if( !foo || !stringp(foo) )
				return 0;
			return foo;
		}	
		else if( stringp(foo) )
			return foo;
		else	return "你不是已经接了吗？";	
	} 
	
	message_vision("千里眼对$N说：你来得正好，我这儿刚好有一封信要送出去。\n",me);
	timep = random(200) + 180;
	i=random(sizeof(ob));
	reset_eval_cost();
	while (1)
        {
        	i++;
        	if(i==sizeof(ob))
        		i=random(sizeof(ob));
        	if(ob[i]==me)  
                	continue;
        	if(!environment(ob[i])) 
        		continue;
        	if(ob[i]->is_ghost())  
        		continue;
        	if( wizardp(ob[i]) )
        		continue;
        	if( userp(ob[i]) && ob[i]->query_level()<3 )
        		continue;		
        	if( sscanf(base_name(ob[i]),"/u/%*s" )
        	 || sscanf(base_name(ob[i]),"/d/wiz/%*s" ) ) 
                	continue;
                if( me->query_level()<80 
                 && sscanf(base_name(ob[i]),"/d/qujing/%*s") )
                	continue;
		if( !environment(ob[i])->query("exits") )
			continue;
		if( base_name(environment(ob[i]))=="/d/kaifeng/ground"
		 || base_name(environment(ob[i]))=="/d/kaifeng/ground0"
		 || base_name(environment(ob[i]))=="/d/kaifeng/wanshou"
		 || base_name(environment(ob[i]))=="/d/xueshan/dixiashi"
		 || base_name(environment(ob[i]))=="/d/xueshan/mishi"
		 || base_name(environment(ob[i]))=="/d/xueshan/anshi" 
		 || environment(ob[i])->query("maze") 
		 || environment(ob[i])->query("virtual_room") )
		 	continue;
		if( environment(ob[i])->is_character() )
		 	continue;
		if( me->query_level()<40 
		  && member_array(query_dir(base_name(environment(ob[i]))),dirs)==-1 )
		  	continue;
		if( wizardp(me) )
			tell_object(me,query_dir(base_name(environment(ob[i])))+"\n");
                who = ob[i];		 
                break;
        }
        if( !who || !environment(who) )
        	return "你且下去歇歇，现在暂时没信需要送。";
        str = query_name(who);
        if( !str )
        	return "你且下去歇歇，现在暂时没信需要送。";
	msg = time_period(timep,me);
	msg+= "把信送给『"NOR +str+ NOR+CYN +"』你的任务就完成了。" NOR;
	
	letter = new(__DIR__+"obj/letter");
	letter->set_owner(me->query("id"));
//        letter->set("long",sprintf(letter->query("long"),me->name(),MISC_D->find_place(environment(who)),who->name()));
	if( letter->move(me) )
		message_vision("$N给了$n一封信。\n",this_object(),me);
	else
	{
		destruct(letter);
		return "你身上物什太多了吧。";
	}
	me->set_temp("letter_time", (int)time() + timep);
	lvl = me->query_job_level("送信任务");
	if( lvl>10 )
		lvl = 0;
	lvl+= 1;
	me->set_job_level("送信任务",lvl);
	name = who->query("name");
	id = who->query("id");
	return me->get_job("送信任务",({name,id,msg,who,lvl}));	
}

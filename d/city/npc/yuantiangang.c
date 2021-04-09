#include <ansi.h>
inherit NPC;

string work_me();
string cancel_me();

string *ygs = ({
	"baihuagu","xueshan","shushan","putuo","moon","dragon","wudidong","hyd",
	//"fangcun","hell","jjf","pansi","wzg",
});	

string job_level()
{
	object me = this_player();
	if( me->query_temp("yuan_level") )
		return "少说多做，你觉得噩梦太难了，想换回普通的，你想好了没有(agree)？";
	else	return "少说多做，你觉得普通太简单了，想换噩梦的，你想好了没有(agree)？";
}

void create()
{
	set_name("袁天罡", ({"yuan tiangang", "yuan"}));
	set("gender", "男性" );
	set_level(31);
	set("age", 33);
	set("long","袁天罡是天监台总管，听说他法术高深。他为人正直仗义，脸上总是一股忧国忧民的神情。\n");
	set("int", 30);
	set("per", 25);
	set("daoxing", 800000);
	set("eff_dx",1000);
	set("nkgain",1);
	set("env/wimpy",100);
	set("attitude", "friendly");
	create_family("将军府",3,"");
	set("title", "天监台正先生");
	set_skill("unarmed", 260);
	set_skill("dodge", 250);
	set_skill("parry", 250);
	set_skill("spells", 300);
	set_skill("baguazhou", 300);
	set_skill("literate", 250);
	set_skill("sword", 260);  
	set_skill("changquan", 250);  
	map_skill("spells", "baguazhou");
	map_skill("unarmed", "changquan");
	set("per", 30);
	set("force_factor", 10);
	set("mana_factor", 100);
	seteuid(getuid());
	set("inquiry", ([
      		"kill": (: work_me :),
      		"官府任务": (: work_me :),
      		"cancel" : (: cancel_me :),
      		"噩梦"  : (: job_level :),
        ]));
        set("no_bian",1);
        set_temp("apply/max_kee",10000);
        set_temp("apply/max_sen",10000);
	setup();
	carry_object("/d/obj/cloth/baguapao")->wear();
	carry_object("/d/obj/weapon/sword/taomujian")->wield();
}

int accept_fight(object me)
{
	write("袁天罡凛然道：学武乃是为了强身，不是打打杀杀！\n");
	return 0;
}

string work_me()
{
	int lvl;
	string where,msg,name,id,title;
	object ghost;
	mixed foo = this_player()->doing_job("袁天罡任务");
	
	if( this_player()->query_level()<5 )
		return "不放心让你去。";
	if( this_player()->query_skill("force",2)<1 )
		return "你先去学点技能吧。";
	if( foo )
	{
		if( stringp(foo) )
			return foo;
		else	return "你不是已经接了吗？";	
	}
	
	if( this_player()->query_level()<40 )
	{
		if( !this_player()->query_temp("yuan_level") )
			ghost = new(sprintf("/d/city/npc/yg/yg-%s",ygs[random(sizeof(ygs))]));
		else	ghost = new(sprintf("/d/city/npc/yg2/yg-%s",ygs[random(sizeof(ygs))]));	
	}
	else
	{
		if( this_player()->query_temp("yuan_level") )
			ghost = new(sprintf("/d/city/npc/yg40-2/yg-%s",ygs[random(sizeof(ygs))]));	
		else	ghost = new(sprintf("/d/city/npc/yg40/yg-%s",ygs[random(sizeof(ygs))]));	
	}	
	if( !ghost )
		return "无怪可杀。";
	lvl = this_player()->query_job_level("袁天罡任务");
	if( lvl>=10 )
		lvl = 0;
	lvl+= 1;
	where=ghost->invocation(this_player(), lvl);
	if( !where || !stringp(where) )
		return "无怪可杀。";
	this_player()->set_job_level("袁天罡任务",lvl);		
	title = ghost->query("title");
	name = ghost->query("name");
	id = ghost->query("id");
	title = COLOR_D->clean_color(title);
	if( this_player()->query_level()<40 )
		msg = "今有"+sprintf("%s%s为非作歹，速去将其伏法！\n",title,where);
	else	msg = "今有"+sprintf("%s%s兴风作浪，速去将其降服！\n",title,where);	
	return this_player()->get_job("袁天罡任务",({name,id,msg,ghost,lvl}));
}

string cancel_me()
{
	mixed foo = this_player()->cancel_job("袁天罡任务");
	if( !foo || !stringp(foo) )
		return 0;
	return foo;	
}

int accept_object(object who,object ob)
{
        if (ob->query("id")=="fan he")
        {
		command("say 多谢多谢，我正饿着哪！");
                EMOTE_D->do_emote(this_object(), "thank",geteuid(who),CYN,0,0,0);
                if( (wizardp(who) && who->query("env/test"))
                 || ( time()>=who->query("maze/beiyin")+1800 
                   && who->query_level()>10 && who->query_level()<25 ) ) 
		{
			who->set_temp("maze/beiyin_asked",1);
			command("say 难得遇到"+RANK_D->query_respect(who)+"这么热心的人呐，以后看到老人跌倒肯定主动去扶。");
			tell_object(who,CYN+name()+CYN"说道：贱内这几日好似有什么烦心事，问了也不说，还望帮本官打听打听。\n"NOR);
		}                
                return 1;
	}
        return 0;
}

void kill_ob(object who)
{
        remove_all_killer();
        all_inventory(environment())->remove_killer(this_object());
        return;
}

void init()
{
	add_action("do_agree","agree");
}

int do_agree()
{
	object me = this_player();
	if( !userp(me) || me->query("gin")<5 )
		return 0;
	me->add("gin",-5);
	if( me->query_temp("yuan_level") )
	{
		me->delete_temp("yuan_level");
		me->set_job_level("袁天罡任务",0);
		write("你变更袁天罡任务为普通级别。\n");
		return 1;
	}
	if( time()>=me->query("last_rumor")+3600 )
	{
		me->set("last_rumor",time());
		CHANNEL_D->do_channel(this_object(),"rumor","听说"HIY+me->name()+HIM"将自己的官府任务难度提升为"NOR RED"噩梦"NOR HIM"级！"NOR);
	}
	me->set_temp("yuan_level",1);
	me->set_job_level("袁天罡任务",0);
	write("你变更袁天罡任务为噩梦级别。\n");
	return 1;
}
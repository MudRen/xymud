//modified by vikee for xlqy-zq station
//2000-12-2 1:34

inherit NPC;
#include <ansi.h>
#include <obstacle.h>

string *ygs = ({
	"baihuagu","dragon","fangcun","hell","hyd",
	"jjf","moon","pansi","putuo","shushan","wudidong",
	"wzg","xueshan",
});	

int work_me();
int cancel_me();
 
void create()
{
	set_name("李靖", ({ "li jing", "jing", "li" }) );
	set("gender", "男性" );
	set("long", "托塔李天王乃是天界元帅，麾下十万天兵天将，法力无边。\n");
	set("age",40);
	set_level(170);
	set("title", "托塔天王");
	set("class", "xian");
	set("attitude", "heroism");
	set("daoxing", 8000000);
	set("force_factor", 500);
	set("mana_factor", 550);

	set("eff_dx", 600000);
	set("nkgain", 600);

	set_skill("spells", 1700);
        set_skill("dao", 1700);
        set_skill("unarmed", 1700);
        set_skill("yinfeng-zhua", 1700);
        set_skill("dodge", 1700);
        set_skill("blade", 1700);
        set_skill("kugu-blade", 1700);
        set_skill("yaofa", 1700);
        set_skill("lingfu-steps", 1700);
        set_skill("parry", 1700);
        set_skill("force", 1700);
        set_skill("huntian-qigong", 1700);
        set_skill("blade", 1700);
        set_skill("sword", 1700);
        set_skill("qixiu-jian", 1700);
        map_skill("spells", "dao");
        map_skill("unarmed", "yinfeng-zhua");
        map_skill("parry", "huoyun-qiang");
        map_skill("sword", "qixiu-jian");
        map_skill("dodge", "lingfu-steps");
        map_skill("force", "huntian-qigong");
	
	set("chat_chance",1);
	set("chat_msg", ({
		    name()+"说道：哪位大仙可愿去下界灭妖？\n",
		    }));

        seteuid(getuid());

	set("inquiry", ([
		"kill": (: work_me :),
		"灭妖": (: work_me :),
		"放弃": (: cancel_me :),
		"cancel": (: cancel_me :),
	]));

	setup();
	carry_object("/d/obj/fabao/huangjin-baota");
	carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/sky/obj/zhanyaojian")->wield();
}


int cancel_me()
{
	mixed foo = this_player()->cancel_job("李靖任务");
	if( !foo || !stringp(foo) )
		return 0;
	tell_object(this_player(),HIC"李靖说道："+foo+NOR"\n");	
	return 1;
}
 
int work_me()
{
	int lvl;
	string where,msg,name,id,title;
	object ghost;
	mixed foo;
	if( this_player()->query_level()<80 )
	{
		tell_object(this_player(),HIC"李靖说道："+RANK_D->query_respect(this_player())+"勇气可嘉，不过现在去，老夫总以为是送死的赶脚。"NOR"\n");	
		return 1;
	}
	foo = this_player()->doing_job("李靖任务");
	if( foo )
	{
		if( stringp(foo) )
			tell_object(this_player(),HIC"李靖说道："+foo+NOR"\n");	
		else	tell_object(this_player(),HIC"李靖说道：你不是已经接了吗？"NOR"\n");	
		return 1;
	}
	if( time()<this_player()->query_temp("last_lijing_job")+90 )
	{
		tell_object(this_player(),HIC"李靖说道："+RANK_D->query_respect(this_player())+"为天庭降妖除魔，劳苦功高，先下去歇歇。"NOR"\n");	
		return 1;
	}
	if( !this_player()->query_temp("lijing_level") )
		ghost = new(sprintf("/quest/lijing/yg/yg-%s",ygs[random(sizeof(ygs))]));
	else	ghost = new(sprintf("/quest/lijing/yg2/yg-%s",ygs[random(sizeof(ygs))]));
	if( !ghost )
	{
		tell_object(this_player(),HIC"李靖说道：你且下去休息休息。"NOR"\n");
		return 1;
	}	
	lvl = this_player()->query_job_level("李靖任务");
	if( lvl>=10 )
		lvl = 0;
	lvl+= 1;
	where=ghost->invocation(this_player(), lvl);
	if( !where || !stringp(where) )
	{
		tell_object(this_player(),HIC"李靖说道：你且下去休息休息。"NOR"\n");
		return 1;
	}
	this_player()->set_job_level("李靖任务",lvl);		
	title = ghost->query("title");
	name = ghost->query("name");
	id = ghost->query("id");
	msg = "今有"+sprintf("%s%s为非作歹，速去将其降服！\n",title,where);
	foo = this_player()->get_job("李靖任务",({name,id,msg,ghost,lvl}));
	if( !foo || !stringp(foo) )
	{
		tell_object(this_player(),HIC"李靖说道：你且下去休息休息。"NOR"\n");
		return 1;
	}
	tell_object(this_player(),HIC"李靖说道："+foo+NOR"\n");	
	this_player()->set_temp("last_lijing_job",time());
	return 1;
}

void unconcious ()
{
	die ();
}
  
void die()
{
        object ob;
        message_vision("\n$N哼了一声。\n", this_object());
	powerup();
	this_object()->clear_condition();
} 

void init()
{
	::init();
}

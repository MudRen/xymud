#include <ansi.h>
inherit SUPER_NPC;

int give_me(object ob);
int delete_ask(object ob);
int create_pai(object ob);

void create()
{
	set_name("鲸无敌", ({"jing wudi", "jing"}));
	set_level(59);
	set("long","身高八丈，膀大腰圆。号称东海第一勇士。水族需有他发的腰牌才能自由出入于水晶宫中。\n");
       	set("gender", "男性");
       	set("age", 56);
       	create_family("东海龙宫", 3, "水族");
        set("title", HIR"东海八百万水族大将军"NOR);
        set("per", 10);
       	set("attitude", "heroism");

	set_skill("unarmed",590);
       	set_skill("dodge",590);
	set_skill("fork", 590);
	set_skill("parry", 590);
	set_skill("force", 590);
	set_skill("spells", 590);
	set_skill("seashentong", 590);
	set_skill("dragonforce", 590);
	set_skill("dragonstep", 590);
	set_skill("literate", 590);
	set_skill("dragonfight", 590);
	map_skill("unarmed", "dragonfight");
	set_skill("fengbo-cha", 590);
	map_skill("fork", "fengbo-cha");
	map_skill("parry", "fengbo-cha");
	map_skill("force", "dragonforce");
	map_skill("dodge", "dragonstep");
	map_skill("spells", "seashentong");
	set_skill("jiefeng",590);
	set("force_factor", 40);
	set("mana_factor", 40);
	set("have", 3);
	
        set("inquiry", ([
                "腰牌": (: give_me :),
                "pai": (: give_me :),
        ]) );
        set("env/test","HIY");
	set_temp("weapon_level",30);
	set_temp("armor_level",30);
	setup();
  	carry_object(0,"armor",random(3))->wear();
  	carry_object(0,"cloth",random(3))->wear();
  	carry_object(0,"kui",random(3))->wear();
  	carry_object(0,"shield",random(3))->wear();
  	carry_object(0,"shoes",random(3))->wear();
  	carry_object(0,"fork",random(3))->wield();	
  	carry_object("/d/sea/obj/pai");
  	powerup(0,1);
        remove_call_out("create_pai");
        call_out("create_pai",920,this_object());
}

void attempt_apprentice(object ob)
{
	if( ob->query_level()>60 )
	{
		EMOTE_D->do_emote(this_object(), "pa",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：" + RANK_D->query_respect(ob) +"是我的前辈，还是去找龙子龙女吧。\n"NOR);
		return;
	}
	if( ob->query("class") && ob->query("class")!="dragon" )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你是啥来头啊？带艺拜师，还是去找主母奶奶询问「带艺拜师」一事吧。\n"NOR);
		return;
	}
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们龙宫发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","龙宫又多了一个弟子  "+ob->name(1)+HIW"\n                                 东海龙宫的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "dragon");
}

int give_me(object ob)
{
	object who, me,pai;
	who=this_player();
	me=this_object();
	pai=new("/d/sea/obj/pai");

	if( (string)who->query("family/family_name")!="东海龙宫" ) 
	{
		if( (int)who->query_temp("pending/ask_time") >= 3) 
		{
			message_vision("$N突然跳起，恶狠狠的瞪着$n说：看来你是不想活了！\n", me, who);
			command("kill " + who->query("id"));
			return 1;
		}
		message_vision("$N斜斜地瞟了$n一眼，说：此不足为外人道也！\n", me, who);
		who->add_temp("pending/ask_time", 1);
		return 1;
	}     
       	else 
       	{
		if( who->query_level()<20 )
		{
			command("baobao " +who->query("id"));
			return 1;
		}
       		if( (int)who->query("jing_time")>time() )
           	{
             		message_vision("$N摇了摇头：你刚才不是已经要过了吗？\n",me);
             		return 1;
            	}
       		if(objectp(present("yao pai",who)))
           	{
           		message_vision("$N很疑惑地看着你说到：你身上不是已经有了吗。\n",me);
           		return 1;
           	}
		if( (int)me->query("have") )
		{
			command("nod "+who->query("id"));
			message_vision(CYN"$N拿出一只腰牌给$n。\n"NOR,me,who);
			me->add("have", -1);
			pai->set("obj_owner",who->query("id"));
			pai->move(who);
			who->add_temp("pending/ask_time", 1);
                	who->set("jing_time",time()+300);
              		return 1;
		}
	}
	message_vision("$N对$n无奈的一伸手，说：今日腰牌已发完了，明日再来领吧。\n", me, who);
	return 1;
}


int create_pai(object ob)
{
	ob->set("have",3);
        remove_call_out("create_pai");
        call_out("create_pai",920,ob);	
	return 1;
}

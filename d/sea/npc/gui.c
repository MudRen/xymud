inherit SUPER_NPC;
#include <ansi.h>

string expell_me(object me);
int give_me(object ob);

void create()
{
       	set_name("龟八斗", ({"gui badou", "gui"}));
       	set_level(59);
	set("long","海底的大才子，以才智过人著称，并且会画金龙符。\n");
       	set("gender", "男性");
	create_family("东海龙宫", 3, "水族");
       	set("age", 56);
        set("title", HIY"东海宰相"NOR);
        set("per", 10);
       	set("attitude", "peaceful");
       	set_skill("huntian-hammer", 590);
	set_skill("hammer", 590);
	set_skill("literate",590);
	set_skill("unarmed", 590);
	set_skill("dodge", 590);
	set_skill("force", 590);
	set_skill("parry", 590);
	set_skill("spells", 590);
	set_skill("seashentong", 590);
	set_skill("dragonfight", 590);
	set_skill("dragonforce", 590);
	set_skill("dragonstep", 590);
	map_skill("hammer", "huntian-hammer");
	map_skill("spells", "seashentong");
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("parry", "huntian-hammer");
	map_skill("dodge", "dragonstep");
	set_skill("jiefeng",590);
        set("inquiry", ([
                "金龙符": (: give_me :),
                "fu": (: give_me :),
		"离宫": (: expell_me :),
      		"leave": (: expell_me :), 
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
  	carry_object(0,"hammer",random(3))->wield();	
  	powerup(0,1);
}

int give_me(object ob)
{
        object who, me;
        who=this_player();
        me=this_object();

        if( (string)who->query("family/family_name")!="东海龙宫" ) {
                message_vision("$N斜斜地瞟了$n一眼，说：此不足为外人道也！\n", me, who);
                return 1;
        }
	if ((int)me->query("number") >= 10)
		return notify_fail("龟八斗把手一伸，今天写太多了，明儿个再说吧！\n");

                ob=new("/d/sea/obj/fu");
                ob->move(who);
		me->add("number",1);

		message_vision("$N拿出张符纸来，画出金龙，递给了$n。\n", me, who);
                return 1;
}

void init()
{
	::init();
	add_action("do_agree", "agree");
}

string expell_me(object me)
{
  	me=this_player();
  	if( me->query_level()<40 )
  		return "你什么意思？！\n";
  	if((string)me->query("family/family_name")=="东海龙宫")
    	{
      		me->set_temp("betray", "lg");
      		command("sigh");
      		return ("你要离开我也不能强留。只是按我东海规矩，却须受罚。恐怕既是身非龙类，这龙神心法与博击并不能如前般运转，你可愿意(agree)?\n");
    	}
  	return 0;
}

int do_agree(string arg)
{
  	object me;
  	me = this_player();
  	if((string)this_player()->query("family/family_name")!="东海龙宫")
		return 0;
  	if(me->query_temp("betray")=="lg")
    	{
    		if( FAMILY_D->leave_family(this_player(),this_object()) )
    		{
      			message_vision("$N答道：弟子愿意。\n\n", me);
      			command("say 人各有志，既是" + RANK_D->query_respect(me) +"不愿留在东海，就请出宫去吧。只是江湖险恶，" + RANK_D->query_respect(me) +"当好自为之。。。\n");
      			return 1;
      		}	
    	}
  	return 0;
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
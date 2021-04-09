// sgzl, 99.0.15.
// 换个名字好听点的好张罗生意
#include <ansi.h>
inherit SUPER_NPC;

int test_hispai(object ob);
void give_yaopai(object ob);
string give_map(object me);
int do_yes(string arg);
string ask_mieyao();
string ask_cancel();

void create()
  {
   set_name("神鹰使者", ({"shenying shizhe", "shizhe", "shenying", "eagle"}));
   set_level(70);
   set("gender", "男性" );
   set("age", 34);

   set("long", "大雪山巡山总督－－神鹰使者，负责四处巡查，八方联络。\n");
   set("class", "yaomo");
   set("combat_exp", 80000);
   set("daoxing", 75000);

   set("attitude", "heroism");
   create_family("大雪山", 3, "弟子");
   set_skill("unarmed",700);
   set_skill("cuixin-zhang",700);
   set_skill("dodge",700);
   set_skill("xiaoyaoyou", 700);
   set_skill("parry",700);
   set_skill("sword",700);
   set_skill("bainiao-jian",700);
   set_skill("force",700);   
   set_skill("ningxie-force", 700);
   set_skill("literate", 700);
   set_skill("spells",700);
   set_skill("dengxian-dafa",700);
   set_skill("throwing",700);
   map_skill("spells", "dengxian-dafa");
   map_skill("force", "ningxie-force");
   map_skill("unarmed", "yingzhaogong");
   map_skill("sword", "bainiao-jian");
   map_skill("parry", "bainiao-jian");
   map_skill("throwing", "bainiao-jian");
   set_skill("jiefeng",700);
   set("force_factor", 55);
   set("mana_factor", 55);

   set("inquiry", ([
	"name" : "在下大雪山神鹰使者，有何贵干？\n",
	"here" : "管它呢！反正比不上我们大雪山。\n",
        "腰牌" : (: test_hispai :),
	"大雪山" : (: give_map :),
   	"kill": (: ask_mieyao :),
   	"师门任务": (: ask_mieyao :),
    	"cancel": (: ask_cancel :),
	]) );

   set("no_map", 0);

   setup();
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
	carry_object(0,"neck",random(2))->wear();
	carry_object(0,"armor",random(2))->wear();
	carry_object(0,"pifeng",random(2))->wear();
	carry_object(0,"sword",random(3))->wield();

}

int test_hispai(object ob)
{
    object me=this_object();
    ob=this_player();
    if( (! ob->query_temp("get_yaopai") ) && ob->query("family/master_name")=="神鹰使者")   
      {
      give_yaopai(ob);
      return 1;
      }
}


void give_yaopai(object ob)
{
    object yaopai;
    object me=this_object();
    ob=this_player();
    yaopai=new("/d/xueshan/obj/yaopai");
    yaopai->move(me);
    yaopai->set("long","\n  
              ＊＊＊＊＊＊＊＊＊＊
              ＊　　威镇群魔　　＊
              ＊＊＊＊＊＊＊＊＊＊

　              大雪山巡山使者－"+ob->query("name")+"\n");
    command("whisper " + ob->query("id") + " 这是你巡山的腰牌，收好了。");
    command("give yao pai to " + ob->query("id"));
    ob->set_temp("get_yaopai", 1);
    return;
}


string give_map(object me)
{
	me=this_player();
	me->set_temp("need_map", 1);
	return "大雪山，那可是个好地方，你想去吗(yes)？\n";
}

void init()
{
	add_action("do_yes", "yes");
}

int do_yes(string arg)
{
	object me;

	me=this_player();
	
	if(me->query_temp("need_map")) 
	{
		message_vision("$N答道：想去！\n\n", me);
		if( query("no_map") == 0 )
		{
			message_vision("神鹰使者说道：好！那我给你一张地图吧！\n", me);
			me->set_temp("need_map", 0);

			carry_object("/d/obj/misc/xueshan-map");
			command("give xueshan map to " + me->query("id"));
			set("no_map", 1);
			call_out("regenerate", 480);
		}
		else
		{
			message_vision("神鹰使者说道：我本来想给你一张地图的，但是刚才发完了。\n", me);
		}

		return 1;
	}
	return 0;
}

int regenerate()
{
	set("no_map", 0);
	return 1;
}

void attempt_apprentice(object ob)
{
	if( ob->query_level()>95 )
	{
		EMOTE_D->do_emote(this_object(), "pa",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：" + RANK_D->query_respect(ob) +"是我的前辈，还是进大雪山去找将军吧。\n"NOR);
		return;
	}
	if( ob->query("class") && ob->query("class")!="yaomo" )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你是啥来头啊？带艺拜师，还是进大雪山去找将军吧。\n"NOR);
		return;
	}
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们大雪山发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","大雪山又多了一个弟子  "+ob->name(1)+HIW"\n                                 大雪山的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}

string ask_mieyao()
{
    	object who=this_player();
    	if((string)who->query("family/family_name")=="大雪山") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="大雪山" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
}
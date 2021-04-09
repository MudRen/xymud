inherit SUPER_NPC;
inherit F_MASTER;

#include <ansi.h>
string ask_mieyao();
string ask_cancel();
string ask_for_leave();

void create()
{
	set_name("钟馗", ({ "zhong kui","kui", "zhong" }));
        set_level(120);
        set("long","一个豹头环眼，铁面虬髯的判官，黝黑的脸上看不出任何喜怒哀乐。\n");
        set("attitude", "peaceful");
        set("age", 30);
        create_family("阎罗地府", 4, "你好");
	set("title", "铁面判官");
        set("per",25);
	set("class", "ghost");
	set("force_factor", 50);
	set("mana_factor", 40);
	set_skill("ghost-steps",1200);
        set_skill("dodge",1200);
        set_skill("unarmed",1200);
	set_skill("parry",1200);
	set_skill("spells",1200);
	set_skill("gouhunshu",1200);
	set_skill("jinghun-zhang",1200);
	set_skill("force",1200);
	set_skill("tonsillit",1200);
	set_skill("literate",1200);
	map_skill("parry", "jinghun-zhang");
	map_skill("spells", "gouhunshu");
	map_skill("dodge", "ghost-steps");
	map_skill("force", "tonsillit");
	map_skill("unarmed", "jinghun-zhang");
   	set("env/test","HIB");
   	set("inquiry", ([
	   	"灭妖": (: ask_mieyao :),
	   	"kill": (: ask_mieyao :),
	    	"cancel": (: ask_cancel :),
	    	"出山" : (: ask_for_leave :),
		"leave" : (: ask_for_leave :),
	]));  
        setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	powerup(0,1);
}

void init()
{
	if( living(this_player()) )
		add_action("do_agree", "agree");
}

string ask_mieyao()
{
    	object who=this_player();

    	if((string)who->query("family/family_name")=="阎罗地府") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	mixed foo = this_player()->cancel_job("师门任务");
	if( !foo || !stringp(foo) )
		return 0;
	return foo;	
}

string ask_for_leave()
{
	object me=this_player();

	if (me->query("family/family_name") == "阎罗地府" ) 
	{
		if( me->query_level()<40 )
			return "你这样的修为，我可不放心！";
		command("say 你既是执意下山，我却有几句话说。");
		me->set_temp("betray", "hell");
		return ("脱离师门要需要有一定惩罚，你可愿意(agree)？");
	}

	return 0;
}

int do_agree(string arg)
{
	if( this_player()->query_temp("betray")=="hell"
	 && this_player()->query("family/family_name") == "阎罗地府" )
	{
		if( FAMILY_D->leave_family(this_player(),this_object()) )
		{
			message_vision("$N答道：弟子愿意。\n\n", this_player());
			command("say 既是你与阎罗地府无缘，你便下山去吧！");
			return 1;
		}
	}
	return 0;
}
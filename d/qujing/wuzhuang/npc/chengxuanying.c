#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

string ask_mieyao();
string ask_cancel();
string ask_for_leave();

void create()
{
	set_name("成玄英", ({"cheng xuanying", "cheng", "xi hua"}));
	set_level(90);
	set("title", "西华法师");
	set("gender", "男性" );
	set("age", 35);
	set("per", 24);
	set("str", 30);
	set("long", "乃太宗亲授道号！\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 2, "祖师");
	set_skill("unarmed",900);
	set_skill("wuxing-quan",900);
	set_skill("dodge",900);
	set_skill("baguazhen",900);
	set_skill("parry",900);
	set_skill("sword",900);
	set_skill("sanqing-jian",900);
	set_skill("staff",900);
	set_skill("fumo-zhang",900);
	set_skill("hammer",900);
	set_skill("kaishan-chui",900);
	set_skill("blade",900);
	set_skill("yange-blade",900);
	set_skill("force",900);   
	set_skill("zhenyuan-force",900);
	set_skill("literate",900);
	set_skill("spells",900);
	set_skill("taiyi",900);
   	map_skill("spells", "taiyi");
   	map_skill("force", "zhenyuan-force");
   	map_skill("unarmed", "wuxing-quan");
   	map_skill("sword", "sanqing-jian");
   	map_skill("dodge", "baguazhen");
   	map_skill("staff", "fumo-zhang");
   	map_skill("blade", "yange-blade");
   	map_skill("hammer", "kaishan-chui");

	set("force_factor", 200);
	set("mana_factor", 200);
	set_temp("weapon_level",40+random(20));
	set_temp("armor_level",40+random(20));
	set("env/test","HIB");
	set("inquiry", ([
	   	"kill": (: ask_mieyao :),
	   	"师门任务": (: ask_mieyao :),
	    	"cancel": (: ask_cancel :),
	    	"下山" : (: ask_for_leave :),
		"leave" : (: ask_for_leave :),
	])); 
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"sword",1)->wield();
	powerup(0,1);
}

void attempt_apprentice(object ob)
{
        if( ob->query_level()<40 )
        {
        	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是打好基础再来吧。\n"NOR);
           	return ;
        }
        if( ob->query("class")!="xian" )
        {
       		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		return ;
        }          
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们道教正理发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        return;
}

void init()
{
	 add_action("do_agree", "agree");
}

string ask_mieyao()
{
    	object who=this_player();
    	if((string)who->query("family/family_name")=="五庄观") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="五庄观" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
}

string ask_for_leave()
{
	object me=this_player();

	if (me->query("family/family_name") == "五庄观" ) 
	{
		if( me->query_level()<40 )
			return "你个外门弟子，也想下山？";
		command("say 你既是执意下山，我却有几句话说。");
		me->set_temp("betray", "wzg");
		return ("脱离师门要需要有一定惩罚，你可愿意(agree)？");
	}

	return 0;
}

int do_agree(string arg)
{
	if( this_player()->query_temp("betray")=="wzg"
	 && this_player()->query("family/family_name") == "五庄观" )
	{
		if( FAMILY_D->leave_family(this_player(),this_object()) )
		{
			message_vision("$N答道：弟子愿意。\n\n", this_player());
			command("say 既是你与五庄观无缘，你便下山去吧！");
			return 1;
		}
	}
	return 0;
}

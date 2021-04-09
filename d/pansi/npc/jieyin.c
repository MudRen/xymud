#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

string ask_for_leave();
string ask_mieyao();
string ask_cancel();

void create()
{
   	set_name("染红霞", ({"rang hongxia","xia","hong","rang","girl"}));
   	set("long", "乃盘丝洞下水月亭轩二掌院，镇北将军染苍群之女。\n");
   	set("title", HIC"门派接引使"NOR);
   	set("nickname",HIM"盘丝洞"NOR);
   	set("gender", "女性");
   	set_level(40);
   	set("age",24);
   	set("class","yaomo");
   	set("attitude", "friendly");
   	set("rank_info/respect", "姑娘");
   	set("force_factor", 125);
   	set("mana_factor",400);
   	set_skill("literate",400);
   	set_skill("unarmed",400);
   	set_skill("dodge",400);
   	set_skill("force",400);
   	set_skill("parry",400);
   	set_skill("sword",400);
   	set_skill("spells",400);
   	set_skill("pansi-dafa",400);
   	set_skill("lanhua-shou",400);
   	set_skill("jiuyin-xinjing",400);
   	set_skill("chixin-jian",400);
   	set_skill("yueying-wubu",400);
   	map_skill("spells", "pansi-dafa");
   	map_skill("unarmed", "lanhua-shou");
   	map_skill("force", "jiuyin-xinjing");
   	map_skill("sword", "chixin-jian");
   	map_skill("parry", "chixin-jian");
   	map_skill("dodge", "yueying-wubu");
   	map_skill("whip", "yinsuo-jinling");
	create_family("盘丝洞", 3, "红");
	set_temp("weapon_level",40+random(20));
	set_temp("armor_level",40+random(20));
	set("env/test","HIB");
	set("inquiry", ([
		"下山" : (: ask_for_leave :),
           	"leave" : (: ask_for_leave :),
           	"修炼": (: ask_mieyao :),
           	"kill": (: ask_mieyao :),
           	"cancel": (: ask_cancel :),		
	]) );
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"sword",1)->wield();
	carry_object(0,"neck",1)->wear();
	carry_object(0,"ring",1)->wear();
	powerup(0,1);
}

void attempt_apprentice(object ob)
{
        if( ob->query("class") && ob->query("class")!="yaomo" )
        {
       		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		return ;
        }          
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力。\n"NOR);
        CHANNEL_D->do_channel(this_object(),"chat","五行山盘丝洞又多了一个弟子  "+ob->name(1)+HIW"\n                                 盘丝洞的势力加强了。\n"NOR);	
        command("recruit " + geteuid(ob) );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}

void init()
{
        add_action("do_agree", "agree");
}

string ask_for_leave()
{
	object me=this_player();

	if (me->query("family/family_name") == "盘丝洞" ) {
		command("say 你既是执意下山，我却有几句话说。");
		me->set_temp("betray", "pansi");
		return ("脱离师门要需要有一定惩罚，你可愿意(agree)？");
	}

	return ("不知道。\n");
}

int do_agree(string arg)
{
	if((string)this_player()->query("family/family_name")!="盘丝洞")
		return 0;
	if(this_player()->query_temp("betray")=="pansi") 
	{
		if( FAMILY_D->leave_family(this_player(),this_object()) )
		{
			message_vision("$N答道：弟子愿意。\n\n", this_player());
			command("say 既是你与盘丝洞无缘，你便下山去吧！");
			command("say 江湖风波，善恶无形，好自为之。。。\n");
			return 1;
		}	
	}
	return 0;
}

string ask_mieyao()
{
    	object who=this_player();
    	if((string)who->query("family/family_name")=="盘丝洞") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="盘丝洞" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
}
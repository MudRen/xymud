#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

string ask_mieyao();
string ask_cancel();

void create()
{
	set_name("神秘女子",({"shenmi nvzi","nv zi","nv","girl",}));
	set_level(45);
	set("gender", "女性" );
	set("age", 23);
	set("long", "长得鼠眉鼠眼的一个女子。\n");
	set("title", HIC"门派接引使"NOR);
	set("nickname",HIR"无底洞"NOR);
  	create_family("陷空山无底洞", 3, "弟子");
	set("per",20);
	set_skill("unarmed",450);
	set_skill("dodge", 450);
	set_skill("parry", 450);
	set_skill("spells", 450); 
	set_skill("yaofa", 450);
	set_skill("sword",450);
	set_skill("qixiu-jian",450);
	set_skill("blade", 450);
	set_skill("kugu-blade", 450);
	set_skill("lingfu-steps", 450);
	set_skill("yinfeng-zhua", 450);
	set_skill("force", 450);   
	set_skill("huntian-qigong", 450);
  	map_skill("force", "huntian-qigong");
  	map_skill("spells", "yaofa");
  	map_skill("unarmed", "yinfeng-zhua");
  	map_skill("sword", "qixiu-jian");
  	map_skill("parry", "kugu-blade");
  	map_skill("blade", "kugu-blade");
  	map_skill("dodge", "lingfu-steps");
	set("force_factor", 150);
	set("mana_factor", 50);
	set_skill("literate",450);
	set_temp("weapon_level",20+random(20));
	set_temp("armor_level",20+random(20));
	set("env/test","HIB");
	set("inquiry", ([
	   	"kill": (: ask_mieyao :),
	   	"师门任务": (: ask_mieyao :),
	    	"cancel": (: ask_cancel :),
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
        if( ob->query("class")=="xian" || ob->query("class")=="dragon"
         || ob->query("class")=="bonze" || ob->query("class")=="taoist" )
        {
		EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你是哪路神仙派来的？！\n"NOR);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们妖族发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","陷空山无底洞又多了一个弟子  "+ob->name(1)+HIW"\n                                 无底洞的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob))
		ob->set("class", "yaomo");
}

string ask_mieyao()
{
    	object who=this_player();
    	if((string)who->query("family/family_name")=="陷空山无底洞") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="陷空山无底洞" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
}
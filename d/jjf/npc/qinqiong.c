inherit SUPER_NPC;
#include <ansi.h>
inherit F_MASTER;

string ask_mieyao();
string ask_cancel();
string ask_for_leave();

void create()
{
	set_name("秦琼", ({ "qin qiong", "qin", "shubao", "qiong", "qin shubao", "master", "shifu" }));
	set_level(39);
	create_family("将军府", 2, "蓝");
	set("title", "开国元勋");
	set("gender", "男性");
	set("age", 43);
	set("per", 26);
	set("long", "秦叔宝是大唐国开国名臣，更是一位出名的武将。\n");
	
	set_skill("literate", 390);
	set_skill("spear", 100);
	set_skill("force", 390);
	set_skill("dodge", 390);
	set_skill("parry", 390);
	set_skill("mace", 390);
	set_skill("wusi-mace", 390);
	set_skill("yanxing-steps", 390);
	set_skill("lengquan-force", 390);
	set_skill("unarmed", 390);
	set_skill("changquan", 390);
	set_skill("bawang-qiang",100);
	map_skill("spear","bawang-qiang");
	map_skill("mace", "wusi-mace");
	map_skill("force", "lengquan-force");
	map_skill("unarmed", "changquan");
	map_skill("parry", "wusi-mace");
	map_skill("dodge", "yanxing-steps");
	set("max_sen", 2800);
	set("max_kee", 4400);
	set("force", 2000);
	set("max_force", 1800);
	set("force_factor", 80);
	set("env/test","HIY");
	set("inquiry", ([
	   	"kill": (: ask_mieyao :),
	   	"师门任务": (: ask_mieyao :),
	    	"cancel": (: ask_cancel :),
	]));  
	setup();
	carry_object(0,"spear",random(10))->wield();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
}

int accept_fight(object me)
{
	command("say 老夫久未和江湖人动手过招了，今日也不想破例。\n");
	return 0;
}

void attempt_apprentice(object ob)
{
        if( ob->query("class")=="yaomo" || ob->query("class")=="ghost" )
        {
		EMOTE_D->do_emote(this_object(), "fear",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：妖怪！老秦杀了你！\n"NOR);
           	return ;
        }
        if( ob->query("class")!="fighter" )
        {
        	EMOTE_D->do_emote(this_object(), "shake",geteuid(ob),CYN,0,0,0);
        	if( ob->query_level()<30 )
           		tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是先找本府家将打打基础。\n"NOR);
           	else	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是先找本府管家打听门派试练一事再说。\n"NOR);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们大唐将军府发扬光大，也涨涨人族志气。\n"NOR);
        command("recruit " + geteuid(ob) );
        return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class","fighter");
}

string ask_mieyao()
{
    	object who=this_player();
    	if((string)who->query("family/family_name")=="将军府") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="将军府" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
}

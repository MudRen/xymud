//Cracked by Roath
// created 12/18/1997 by snowcat
inherit SUPER_NPC;
#include <ansi.h>

void riding ()
{
	remove_call_out("riding");
	command ("mount jinjing shou");
}

void create()
{
	set_name("牛魔王", ({ "niumo wang", "niumo", "wang" }));
  	set_level(140);
  	create_family("火云洞", 2, "蓝");
  	set("title", "平天大圣");
  	set("nickname",HIR"大力王"NOR);   
  	set("long", "七大圣之首，一双牛蛋眼正煞神一般瞪着你。\n");
  	set("gender", "男性");
  	set("age", 70);
  	set("attitude", "heroism");
  	set("class", "yaomo");
  	set("per", 10);
	set("force_factor", 190);
	set("mana_factor", 145);

	set_skill("spells",1400);
  	set_skill("stick",1400);
  	set_skill("dali-bang",1400);
  	set_skill("unarmed",1400);
  	set_skill("moyun-shou",1400);
  	set_skill("dodge",1400);
  	set_skill("moshenbu",1400);
  	set_skill("parry",1400);
  	set_skill("force",1400);
  	set_skill("huomoforce",1400);
  	set_skill("pingtian-dafa",1400);
  	map_skill("force", "huomoforce");
  	map_skill("spells", "pingtian-dafa");
  	map_skill("stick", "dali-bang");
  	map_skill("parry", "dali-bang");
  	map_skill("unarmed", "moyun-shou");
  	map_skill("dodge", "moshenbu");

	set_skill("zhenshan-handi",1400);
	set_skill("dali",1400);
	set_skill("jiefeng",1400);
	set_skill("qiqing",1400);
	
  	setup();
  	carry_object("/d/obj/cloth/shoupiqun")->wear();
  	call_out ("riding",1);
}

int prevent_learn(object who,string skill)
{
	if( skill=="zhenshan-handi" )
	{
		if( who->query_level()<120 )
			return err_msg(name()+"朝你摇了摇头：你这点修为，不要侮辱了老牛的神通。\n");
        }
        if( skill=="dali") 
        {
		if( who->query_level()<90 )
			return err_msg(name()+"朝你摇了摇头：你这点修为，不要侮辱了老牛的神通。\n");
        }
        if( skill=="qiqing" )
        {
        	if( who->query_level()<80 )
        		return err_msg(name()+"朝你摇了摇头：你这点修为，不要侮辱了老牛的神通。\n");
        }
	return 0;
} 

void attempt_apprentice(object ob)
{       
	if( !ob )
		return;
	if( ob->query("class")=="xian" || ob->query("class")=="bonze" || ob->query("class")== "taoist" )
        {
		EMOTE_D->do_emote(this_object(), "pei",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：我们妖魔鬼怪也有节操的，你还是另请高就吧。\n"NOR);
           	return ;
        }
	if( ob->query_level()<60 )
        {
        	EMOTE_D->do_emote(this_object(), "haha",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是先下去打好基础再来吧。\n");
           	return ;
        }	
        if( (string)ob->query("family/family_name") == "火云洞") 
        {

                if( (int)ob->query("max_mana") > 200 
                && (int)ob->query("max_force") > 200 ) 
                {
			EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
			tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们妖族发扬光大。\n"NOR);
			command("recruit " + geteuid(ob) );
			return ;
                }
        }
        EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "yaomo");
                ob->set("kusong/Teach_Niu", 1);
        }
}

void destruct_me (object me)
{
	destruct (me);
}

int accept_fight(object ob)
{
	return 0;
}

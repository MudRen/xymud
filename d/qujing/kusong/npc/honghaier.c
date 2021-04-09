//Cracked by Roath
inherit SUPER_NPC;
#include <ansi.h>

void create()
{
	set_name("红孩儿", ({"honghai er","er"}));
       	set_level(89);
       	create_family("火云洞", 2, "蓝");
        set("title", "圣婴大王");
        set("long", "牛魔王与罗刹女的儿子，于火焰山中修炼了一身好本领。\n");
       	set("gender", "男性");
       	set("age", 16);
        set("attitude", "heroism");

        set("eff_dx", -500000);
        set("nkgain", 500);
        set("class","yaomo");
        set("force_factor", 100);
        set("mana_factor", 180);
       
        set_skill("unarmed",890);
        set_skill("dodge", 890);
        set_skill("force",890);
        set_skill("parry",890);
        set_skill("spear",890);
        set_skill("spells",890);
        set_skill("huoyun-qiang",890);
        set_skill("moshenbu", 890);
        set_skill("moyun-shou",890);
        set_skill("huomoforce",890);
        set_skill("pingtian-dafa",890);

        map_skill("force", "huomoforce");
        map_skill("spells", "pingtian-dafa");
        map_skill("unarmed", "moyun-shou");
        map_skill("dodge", "moshenbu");
        map_skill("parry", "huoyun-qiang");
        map_skill("spear", "huoyun-qiang");

	set_skill("zhidi-chenggang",890);
	set_skill("tuyan",890);	
	set_skill("jiefeng",890);
	set_skill("qiqing",890);
	
        set("env/test","HIB");
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"waist",1)->wear();
	carry_object(0,"spear",1)->wield();
	powerup(0,1);
}

int prevent_learn(object who,string skill)
{
	if( skill=="zhitie-chenggang" )
	{
		if( who->query_level()<120 )
			return err_msg(name()+"朝你摇了摇头：你这点修为，不要侮辱了本少爷的神通。\n");
        }
        if( skill=="tuyan") 
        {
		if( who->query_level()<90 )
			return err_msg(name()+"朝你摇了摇头：你这点修为，不要侮辱了本少爷的神通。\n");
        }
        if( skill=="qiqing" )
        {
        	if( who->query_level()<80 )
        		return err_msg(name()+"朝你摇了摇头：你这点修为，不要侮辱了本少爷的神通。\n");
        }
	return 0;
} 

void die()
{
   object ob=this_object();
  message_vision(HIY"天上传来观音菩萨的声音：红孩儿，还不随我回南海去。\n"NOR,ob);
  destruct (ob);
}

void unconcious ()
{
  die();
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
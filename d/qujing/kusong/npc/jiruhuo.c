//Cracked by Roath
#include <ansi.h>
inherit SUPER_NPC;

string expell_me(object me);

void create()
{
  	set_name("急如火", ({"jiru huo","huo"}));
  	set_level(59);
  	set("gender", "男性");
  	set("age", 10);
  	create_family("火云洞", 3, "蓝");
  	set("title", "火云洞健将");
  	set("long","一个贼眉鼠眼的小妖精。\n");
	set("per", 15);

  	set_skill("dodge",590);
  	set_skill("parry",590);
  	set_skill("unarmed",590);
  	set_skill("force",590);
  	set_skill("spells",590);
  	set_skill("pingtian-dafa",590);
  	set_skill("huomoforce",590);
  	set_skill("moyun-shou",590);
  	set_skill("moshenbu",590);
  	set_skill("stick",590);
  	set_skill("dali-bang",590);
  
  	map_skill("force", "huomoforce");
  	map_skill("spells", "pingtian-dafa");
  	map_skill("unarmed", "moyun-shou");
  	map_skill("dodge", "moshenbu");
  	map_skill("stick", "dali-bang");
  	map_skill("parry", "dali-bang");
  	set_skill("jiefeng",590);
  	
  	set("force_factor", 120);
  	set("mana_factor", 120);

        set("inquiry", ([
                "下山": (: expell_me :),
                "leave": (: expell_me :),
	]) );
	set("env/test","HIB");
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"waist",1)->wear();
	carry_object(0,"stick",1)->wield();
	powerup(0,1);
}

void attempt_apprentice(object ob)
{
        if( ob->query("class")=="xian" || ob->query("class")=="taoist"
         || ob->query("class")=="bonze" )
        {
		EMOTE_D->do_emote(this_object(), "bite",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你是哪位神仙派来的坐骑？\n"NOR);
           	return ;
        }
        if( ob->query_level()>59 )
        {
		EMOTE_D->do_emote(this_object(), "wow",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"完全秒杀小的哈，您还是找各位大王吧。\n"NOR);
           	return ;
        }	
	EMOTE_D->do_emote(this_object(), "great",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们妖族发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","枯松涧火云洞又多了一个弟子  "+ob->name(1)+HIW"\n                                 火云洞的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) 
        {
                ob->set("class", "yaomo");
        }
}

string expell_me(object me)
{       
	me=this_player();
       	if( me->query_level()<40 )
		return "莫非你是来卧底的？\n";
        if((string)me->query("family/family_name")=="火云洞") 
        {
                me->set_temp("betray", "hyd");
                return ("既是要出山，却需受山规惩罚，你可愿意(agree)?");
        }
        return ("不知。");
}

void init()
{
	add_action("do_agree", "agree");
}

int do_agree(string arg)
{
      if(this_player()->query_temp("betray")== "hyd"
       &&this_player()->query("family/family_name")=="火云洞") 
       {
		if( FAMILY_D->leave_family(this_player(),this_object()) )
		{
			message_vision("$N答道：弟子愿意。\n\n", this_player());
			command("say 滚蛋吧，不送不送！");
			return 1;
		}       	
	}	
        return 0;
}
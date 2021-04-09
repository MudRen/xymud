#include <ansi.h>
inherit SUPER_NPC;

void create()
{
  	set_name("快如风", ({"kuairu feng","feng"}));
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
  	set_skill("spear",590);
  	set_skill("huoyun-qiang",590);
  
  	map_skill("force", "huomoforce");
  	map_skill("spells", "pingtian-dafa");
  	map_skill("unarmed", "moyun-shou");
  	map_skill("dodge", "moshenbu");
  	map_skill("spear", "huoyun-qiang");
  	map_skill("parry", "huoyun-qiang");
  	set_skill("jiefeng",590);
  	
  	set("force_factor", 120);
  	set("mana_factor", 120);

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

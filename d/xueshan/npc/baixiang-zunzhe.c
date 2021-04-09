// baixiang-zunzhe.c...weiqi, 97.09.15.
#include <ansi.h>
inherit SUPER_NPC;

void create()
{
	set_name("白象尊者", ({"baixiang zunzhe", "baixiang", "zunzhe"}));
	set_level(120);
	set("title", "明王护法");
	set("gender", "男性" );
	set("age", 43);
	set("per", 112);//no rongmao description.
	set("str", 50);
	set("long", "这位白象尊者是有名的大力士。狮驼山二大王，大雪山护法尊者。\n生平最怕的是老鼠，看到尖嘴猴腮的人就讨厌。\n");
	set("class", "yaomo");
	set("attitude", "peaceful");
   	create_family2("大雪山","象族",2, "明王护法");
	set_skill("unarmed",1200);
	set_skill("cuixin-zhang",1200);
	set_skill("dodge",1200);
	set_skill("xiaoyaoyou",1200);
	set_skill("parry",1200);
	set_skill("blade", 1200);
	set_skill("bingpo-blade",1200);
	set_skill("throwing",1200);
	set_skill("force",1200);
	set_skill("ningxie-force",1200);
	set_skill("literate",1200);
	set_skill("spells",1200);
	set_skill("dengxian-dafa",1200);
   	
   	map_skill("spells", "dengxian-dafa");
   	map_skill("force", "ningxie-force");
   	map_skill("parry", "cuixin-zhang");
   	map_skill("unarmed", "cuixin-zhang");
   	map_skill("blade", "bingpo-blade");
   	map_skill("dodge", "xiaoyaoyou");

	set_skill("huitian-fanri",1200);
	set_skill("qushen",1200);
     	set("eff_dx", -200000);
     	set("nkgain", 400);

	set("env/test","HIB");
	set_temp("weapon_level",60+random(50));
	set_temp("armor_level",60+random(50));
	setup();
	carry_object(0,"blade",random(10))->wield();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	powerup(1,1);
}

void _attempt_apprentice(object ob)
{
	if( !ob )
		return;
	if( ob->query_level()>=125 )
	{
		EMOTE_D->do_emote(this_object(), "hoho",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你都这么厉害了，还是去找明王吧。\n"NOR);
		return;
	}	
	else if( ob->query_level()>=95 )
	{
		EMOTE_D->do_emote(this_object(), "nod",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们大雪山发扬光大。\n"NOR);
        	command("recruit " + geteuid(ob) );
        	return;
	}
	else
	{
		EMOTE_D->do_emote(this_object(), "en",0,CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：嗯，有志不在年高，你先去打好基础再来吧。\n"NOR);
		return;
	}
}

void attempt_apprentice(object ob)
{
	if( ob->query("class") && ob->query("class")!="yaomo" )
	{
		EMOTE_D->do_emote(this_object(), "pei",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你是啥来头啊？带艺拜师，还是先去找将军问问吧。\n"NOR);
		return;
	}
	return _attempt_apprentice(ob);
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}

int prevent_learn(object me, string skill)
{
  	if( skill != "huitian-fanri")
  		return 0;
	if( me->query_skill("jiuxi-fuqi",2)>0 )
	{
                tell_object(me,CYN+name()+CYN"说道：你学了大哥的神通，本尊者就不教你了。\n"NOR);
		return 1;
	} 
	if( me->query_skill("qisi-huisheng",2)>0 )
	{
                tell_object(me,CYN+name()+CYN"说道：你学了小公主的神通，本尊者就不教你了。\n"NOR);
		return 1;
	} 
	return 0;		
}

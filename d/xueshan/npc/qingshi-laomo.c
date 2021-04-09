// qingshi-laomo.c...weiqi, 97.09.15.
#include <ansi.h>
inherit SUPER_NPC;

void create()
{
	set_name("青狮老魔", ({"qingshi laomo", "qingshi", "laomo"}));
      	set_level(120);
	set("title", "明王护法");
	set("gender", "男性" );
	set("age", 63);
	set("long", "这位青狮老魔原来在狮驼山逍遥，跟大鹏明王颇有交情。\n后来狮驼山被方寸山三星洞的一位得道高人剿灭，\n老魔就投奔大鹏明王做了护法尊者。一个跟和尚有仇，\n一个跟道士有仇，也算是知交好友。\n");
	set("class", "yaomo");
	set("attitude", "peaceful");
	create_family2("大雪山","狮族",2, "明王护法");
	set_skill("unarmed",1200);
	set_skill("cuixin-zhang",1200);
	set_skill("dodge", 1200);
	set_skill("xiaoyaoyou", 1200);
	set_skill("parry", 1200);
	set_skill("blade", 1200);
	set_skill("bingpo-blade", 1200);
	set_skill("force", 1200);   
	set_skill("ningxie-force", 1200);
	set_skill("literate", 1200);
	set_skill("spells", 1200);
	set_skill("throwing",1200);
	set_skill("dengxian-dafa", 1200);
	
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("parry", "cuixin-zhang");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
	
	set_skill("jiuxi-fuqi",1200);
	set_skill("qushen",1200);
	set("force_factor", 160);
	set("mana_factor", 125);

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
	object ob = me;
  	if( skill != "jiuxi-fuqi")
  		return 0;
	if( me->query_skill("qisi-huisheng",2)>0 )
	{
		tell_object(ob,CYN+name()+CYN"说道：你学了公主的神通，本尊者就不教你了。\n"NOR);
		return 1;
	} 
	if( me->query_skill("huitian-fanri",2)>0 )
	{
		tell_object(ob,CYN+name()+CYN"说道：你学了二哥的神通，本尊者就不教你了。\n"NOR);
		return 1;
	} 
	return 0;		
}
#include <ansi.h>
inherit SUPER_NPC;

void create()
{
       	set_name("摩揭",({"mo jie","long shao","da shao","shao","mo"}));
       	set_level(120);
	set("long","龙王的大少爷。\n");
       	set("gender", "男性");
       	set("age", 26);
       	create_family("东海龙宫", 2, "水族");
       	set("title", HIR"龙宫太子"NOR);
       	set("attitude", "peaceful");
       	set("rank_info/respect", "殿下");
       	set("class","dragon");
	set("force_factor", 140);
	set("mana_factor", 240);

	set_skill("literate", 1200);
       	set_skill("unarmed", 1200);
       	set_skill("dodge", 1200);
       	set_skill("force", 1200);
       	set_skill("parry", 1200);
       	set_skill("fork", 1200);
       	set_skill("spells", 1200);
        set_skill("seashentong", 1200);
        set_skill("dragonfight", 1200);
        set_skill("dragonforce", 1200);
        set_skill("fengbo-cha", 1200);
        set_skill("dragonstep", 1200);
        set_skill("hammer", 1200);
        set_skill("huntian-hammer", 1200);
        map_skill("spells", "seashentong");
        map_skill("unarmed", "dragonfight");
        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("dodge", "dragonstep");
        map_skill("hammer", "huntian-hammer");
        
        set_skill("jiefeng",1200);
        set_skill("danshan",1200);
        set_skill("duanliu",1200);
        
	set("env/test",({"HIR","HIB"})[random(2)]);
	set_temp("weapon_level",60);
	set_temp("armor_level",60);
	setup();
        carry_object(0,"unarmed",1)->wield();
        carry_object(0,"armor",1)->wear();
        carry_object(0,"cloth",1)->wear();        
        carry_object(0,"neck",1)->wear();        
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"hand",1)->wear();
        carry_object(0,"waist",1)->wear();
        powerup(0,1);
}

void _attempt_apprentice(object ob)
{
	if( !ob )
		return;
	if( ob->query_level()>=125 )
	{
		EMOTE_D->do_emote(this_object(), "zeze",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你都这么厉害了，还是去找父王吧。\n"NOR);
		return;
	}	
	else if( ob->query_level()>=60 )
	{
		EMOTE_D->do_emote(this_object(), "nod",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们东海龙宫发扬光大。\n"NOR);
        	command("recruit " + geteuid(ob) );
        	return;
	}
	else
	{
		EMOTE_D->do_emote(this_object(), "en",0,CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：嗯，有志不在年高，你先去找宰相与将军打好基础再来吧。\n"NOR);
		return;
	}
}

void attempt_apprentice(object ob)
{
	if( ob->query("class") && ob->query("class")!="dragon" )
	{
		EMOTE_D->do_emote(this_object(), "pei",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你是啥来头啊？带艺拜师，还是先去找母亲大人问问吧。\n"NOR);
		return;
	}
	return _attempt_apprentice(ob);
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "dragon");
}

int prevent_learn(object me, string skill)
{
  	if( skill != "duanliu")
  		return 0;
	if( me->query_skill("qiyu",2)>0 )
	{
                tell_object(me,CYN+name()+CYN"说道：你既然学了她的神通，还来找我干甚？！\n"NOR);
		return 1;
	} 
	return 0;		
}

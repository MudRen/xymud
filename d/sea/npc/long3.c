// long3.c
// created 6-6-97 pickle

#include <skill.h>
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;

void create()
{
  set_name("睚眦",({"ya zi","zi","ya","long","yazi","dragon"}));
  set_level(81);
  set("long","龙生九子不成龙，各有所好：睚眦乃第三子，平生好杀。\n");
  set("gender", "男性");
  set("age", 39);
  set("title", "龙王九子之");
  set("class","dragon");
  set("attitude", "heroic");
  set("force_factor",50);
  set("mana_factor",30);
  set("per",10+random(10));

	create_family("东海龙宫", 2, "水族");
  	set_skill("unarmed",810);
  	set_skill("dodge",810);
  	set_skill("force",810);
  	set_skill("parry",810);
  	set_skill("spells", 810);
  	set_skill("seashentong", 810);
  	set_skill("dragonfight",810);
  	set_skill("dragonforce",810);
  	set_skill("dragonstep", 810);
  	
  	map_skill("spells", "seashentong");
  	map_skill("unarmed", "dragonfight");
  	map_skill("force", "dragonforce");
  	map_skill("parry", "dragonfight");
  	map_skill("dodge", "dragonstep");

  	set("nkgain", 400);

  	set("inquiry", ([
               //  "whokillme"    : (: begin_go :),
		               ]) );
  	set("env/test",({"HIC","HIY"})[random(2)]);
	set_temp("weapon_level",40);
	set_temp("armor_level",40);
	setup();
        carry_object(0,"fork",random(10))->wield();
        carry_object(0,"armor",random(10))->wear();
        carry_object(0,"cloth",random(10))->wear();        
        carry_object(0,"neck",random(10))->wear();        
        carry_object(0,"shoes",random(10))->wear();
        carry_object(0,"kui",random(10))->wear();
        carry_object(0,"pifeng",random(10))->wear();
        carry_object(0,"ring",random(10))->wear();
        carry_object(0,"hand",random(10))->wear();
        carry_object(0,"waist",random(10))->wear();
        powerup(0,1);
  	carry_object("/d/sea/obj/longzhu3");
}
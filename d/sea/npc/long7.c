// long7.c
// created 6-6-97 pickle
#include <ansi.h>
#include <skill.h>

inherit NPC;
//inherit F_MASTER;

void create()
{
  set_name("蚣蝮",({"gong fu","gong","fu","long","gongfu","dragon"}));
  set_level(85);
  set("long","龙生九子不成龙，各有所好：蚣蝮乃第七子，平生好水。\n");
  set("gender", "男性");
  set("age", 41);
  set("title", "龙王九子之");
  set("class","dragon");
  set("attitude", "peaceful");
  set("force_factor", 70);
  set("mana_factor",40);

  set("per",10+random(10));
  set("bellicosity",500);

	create_family("东海龙宫", 2, "水族");
  	set_skill("unarmed",850);
  	set_skill("dodge",850);
  	set_skill("force",850);
  	set_skill("parry",850);
  	set_skill("spells", 850);
  	set_skill("seashentong", 850);
  	set_skill("dragonfight",850);
  	set_skill("dragonforce",850);
  	set_skill("dragonstep", 850);
  	
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
  	carry_object("/d/sea/obj/longzhu7");
}
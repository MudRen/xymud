// long1.c
// created 6-6-97 pickle
// by take 2001.8.12
#include <ansi.h>
inherit NPC;
//inherit F_MASTER;
int begin_go();

void create()
{
  set_name("椒图",({"shu tu","shu","tu","long","shutu","dragon"}));
  set_level(95);
  create_family("东海龙宫", 2, "水族");
  set("long","龙生九子不成龙，各有所好：椒图乃第九子，平生好闭。\n");
  set("gender", "男性");
  set("age", 41);
  set("title", "龙王九子之");
  set("class","dragon");
  set("attitude", "peaceful");
  set("force_factor", 80);
  set("mana_factor",50);

  set("bellicosity",500);
  set("cor",30);

  set_skill("unarmed",950);
  set_skill("dodge",950);
  set_skill("force",950);
  set_skill("parry",950);
  set_skill("spells", 950);
  set_skill("seashentong", 950);
  set_skill("dragonfight",950);
  set_skill("dragonforce",950);
  set_skill("dragonstep", 950);
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
  	carry_object("/d/sea/obj/longzhu9");
}

int accept_fight(object me)
{
  command("fear");
  command("say 俺就喜欢在屋里躲着，从来不喜欢打架。");
  command("say 不过既然" + RANK_D->query_respect(me) + "想比划两招，俺也只好奉陪了。");
  return 1;
}

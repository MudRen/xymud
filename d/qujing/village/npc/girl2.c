//Cracked by Roath
//  妖神之争 １。０
//  by happ@YSZZ 2000.4.7
//  /d/qujing/village/npc/girl1.c

inherit NPC;
#include <ansi.h>

void create()
{
   set_name(HIG"真真"NOR, ({ "zhen zhen", "zhenzhen"}));
   set("gender", "女性" );
   set("age", 15);
   set("long",
     "一位绝色美女。\n");

   set_level(40);
   set("attitude", "friendly");
   set_skill("dodge", 10);
   set_skill("unarmed", 10);
   setup();
   carry_object("/obj/cloth")->wear();
   add_money("silver", 3+random(20));
}


//Cracked by Roath
// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit NPC;

void create()
{
	set_name("凌虚子", ({"lingxu zi", "zi"}));
        set("gender", "男性");
        set("age", 30);
        set("long", "一个身高臂长的道士，容貌还看的过去。
可仔细一瞧，颈中竟长着密密麻麻的长毛。\n");
        set("attitude", "heroism");
   	set("class", "yaomo");
   	set("bellicosity", 800);
   	set("per", 18);
   	set("looking", "相貌凶恶，满脸横肉。");
   	set("str", 25);
        set_level(65);

        set_skill("unarmed",650);
        set_skill("dodge",650);
        set_skill("blade",650);
        set_skill("parry",650);
   	set_skill("force",650);
   	set_skill("spells",650);
   	set_skill("moshenbu",650);
   	set_skill("cuixin-zhang",650);
   	map_skill("unarmed", "cuixin-zhang");
   	map_skill("parry", "cuixin-zhang");
   	map_skill("dodge", "moshenbu");
        set("force_factor", 30);
	set("mana_factor", 20);
   	set("eff_dx", -50000);
   	set("nkgain", 300);
	setup();
   	carry_object("/d/obj/cloth/changpao")->wear();
   	carry_object("/d/qujing/jisaiguo/obj/panzi");
}

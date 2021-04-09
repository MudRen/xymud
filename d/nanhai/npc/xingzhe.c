//Cracked by Roath
// xingzhe.c i方行者?// By Dream Dec. 20, 1996
#include <ansi.h> 
inherit SUPER_NPC;

void create()
{
	set_name("游方行者", ({ "xingzhe" }));
      	set_level(70);
	set("gender", "男性");
	set("age", 40);
	set("attitude", "peaceful");
	set("class", "bonze");
	set("force_factor", 120);
	set("mana_factor", 110);

        set("eff_dx", 40000);
        set("nkgain", 250);

	set_skill("literate",700);
	set_skill("spells",700);
	set_skill("buddhism",700);
	set_skill("unarmed", 700);
	set_skill("jienan-zhi",700);
	set_skill("dodge",700);
	set_skill("lotusmove",700);
	set_skill("parry", 700);
	set_skill("force",700);
	set_skill("lotusforce",700);
	set_skill("staff", 700);
	set_skill("lunhui-zhang",700);
	set_skill("blade", 700);
	set_skill("cibeidao", 700);
	map_skill("blade", "cibeidao");
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
        create_family("南海普陀山", 3, "弟子");
        set("env/test","HIY");
	set_temp("armor_level",21+random(20));
	set_temp("weapon_level",21+random(20));
	setup();
	carry_object("/d/nanhai/obj/sengpao")->wear();
	carry_object(0,"shoes",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"hand",1)->wear();
        carry_object(0,"wrists",1)->wear();
        carry_object(0,"waist",1)->wear();
        carry_object(0,"staff",1)->wield();
        powerup(0,1);
}
//write by yesi
//yeahsi@21cn.com
inherit SUPER_NPC;
#include <ansi.h>

void create()
{
  set_name("如来佛", ({ "rulai fo", "rulai", "fo" }));
  set("title", "佛祖多陀阿伽陀");
  set("long", "大慈大悲灵山雷音古刹佛祖多陀阿伽陀如来佛爷。\n");
  set("gender", "男性");
  set("age", 10000);
  set_level(180);
  set("attitude", "peaceful");
  set("rank_info/self", "贫僧");
  set("rank_info/respect", "佛祖爷爷");
  set("class", "bonze");
  set("force_factor", 500);
  set("mana_factor", 500);

  set_skill("literate",1800);
  set_skill("spells",1800);
  set_skill("buddhism",1800);
  set_skill("unarmed",1800);
  set_skill("jienan-zhi",1800);
  set_skill("dodge",1800);
  set_skill("lotusmove",1800);
  set_skill("parry",1800);
  set_skill("blade",1800);
  set_skill("cibeidao",1800);
  set_skill("force",1800);
  set_skill("lotusforce",1800);
  set_skill("staff",1800);
  set_skill("lunhui-zhang",1800);
  map_skill("spells", "buddhism");
  map_skill("blade", "cibeidao");
  map_skill("unarmed", "jienan-zhi");
  map_skill("dodge", "lotusmove");
  map_skill("force", "lotusforce");
  map_skill("parry", "lunhui-zhang");
  map_skill("staff", "lunhui-zhang");
	set_skill("tianlong-chanchang",1800);
	set_skill("jingang-sanmei",1800);
	set_skill("jingang-zhenshen",1800);
	set_skill("longxiang-li",1800);
	set_skill("qu-yue",1800);
	set_skill("bubu-shenglian",1800);  
  set("chat_chance_combat", 80);
  set("chat_msg_combat", ({
   (: cast_spell, "bighammer" :),
  }) );
  setup();
  carry_object("/d/obj/cloth/jia_sha")->wear();
}

void die()
{
  	if (environment())
    		message("sound", "\n\n如来缓缓一点头：佛法无边！\n\n", environment());
	powerup(0,1);
}

void unconcious()
{
  die ();
}
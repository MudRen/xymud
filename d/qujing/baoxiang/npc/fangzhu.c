//Cracked by Roath
// by snowcat oct 15 1997

inherit F_VENDOR_SALE;

void create()
{
  set_name("坊主", ({"fang zhu","zhu"}));
  set("gender", "男性");
  set("combat_exp", 1000);
  set("age", 46);
  set("per", 14);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 100);
  set("vendor_goods", ([
        "caisepitan": "/d/qujing/baoxiang/obj/cspitan",
        "baipitan": "/d/qujing/baoxiang/obj/bpitan",
        "yizi": "/d/qujing/baoxiang/obj/yizi",
        "zhuozi": "/d/qujing/baoxiang/obj/zhuozi",
      "guatan":  "/d/qujing/baoxiang/obj/guatan",
      ]) );

  setup();
  carry_object("/d/qujing/baoxiang/obj/changpao")->wear();
  add_money("silver", 5);
}
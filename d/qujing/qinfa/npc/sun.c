// by snowcat oct 15 1997


inherit F_VENDOR_SALE;

void create()
{
  set_name("孙小二", ({"sun xiaoer", "sun", "xiaoer", "xiao", "er"}));
  set("shop_id", ({"xiaoer", "xiao", "er"}));
  set("gender", "男性");
  set("combat_exp", 5000);
  set("age", 30);
  set("per", 21);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 30);
  set("vendor_goods", ([
    "pipao" : "/d/obj/cloth/piyi",
    "boots" : "/d/obj/cloth/bullboots",
    "beixin" : "/d/obj/cloth/beixin",
  ]));

  setup();
  carry_object("/d/obj/cloth/choupao")->wear();
}
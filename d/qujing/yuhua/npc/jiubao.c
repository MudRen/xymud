// by snowcat 12/8/1997


inherit F_VENDOR_SALE;

void create()
{
  set_name("酒保", ({"jiu bao", "jiubao", "bao"}));
  set("shop_id", ({"jiubao", "bao"}));
  set("gender", "男性");
  set("combat_exp", 5000);
  set("age", 30);
  set("per", 21);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 30);
  set("vendor_goods", ([
        "ruzhu": "/d/qujing/yuhua/obj/pig",
        "qianyang": "/d/qujing/yuhua/obj/lamb",
        "baijiu": "/d/obj/food/baijiu",
	"jitui": "/d/ourhome/obj/jitui",
        "jiunang": "/d/obj/food/jiunang",
      ]) );

  setup();
  carry_object("/d/obj/cloth/choupao")->wear();
}
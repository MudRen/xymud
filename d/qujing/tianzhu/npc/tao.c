// by snowcat 12/8/1997


inherit F_VENDOR_SALE;

void create()
{
  set_name("陶娘子", ({"tao niangzi", "tao", "niangzi"}));
  set("shop_id", ({"niangzi", "tao"}));
  set("gender", "女性");
  set("combat_exp", 2000);
  set("age", 40);
  set("per", 30);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 30);
  set("vendor_goods", ([
        "hongqun": "/d/qujing/tianzhu/obj/hongqun",
        "huaqun": "/d/qujing/tianzhu/obj/huaqun",
        "baipao": "/d/qujing/tianzhu/obj/baipao",
        "huapao": "/d/qujing/tianzhu/obj/huapao",
        "pifeng": "/d/qujing/tianzhu/obj/pifeng",
        "dachang": "/d/qujing/tianzhu/obj/dachang",
      ]) );

  setup();
  carry_object("/d/qujing/tianzhu/obj/huaqun")->wear();
  carry_object("/d/qujing/tianzhu/obj/yinjie")->wear();
}
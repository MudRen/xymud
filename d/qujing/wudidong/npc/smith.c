// waiter.c


inherit F_VENDOR_SALE;

void create()
{
        set_name("张铁臂", ({ "blacksmith", "smith", "zhang", "zhang tiebi", "tiebi" }) );
        set("gender", "男性" );
        set("age", 42);
        set("title", "铁匠");
        set("long","张铁匠正在打铁，炉火把他的脸映得通红。\n");
        set("attitude", "friendly");
        set("rank_info/respect", "张大哥");
        set("per",25);
        set("vendor_goods", ([
		"zhadao"  : "/d/obj/weapon/blade/zhadao.c",
		"tiefu"   : "/d/obj/weapon/axe/tiefu.c",
		"sickle"  : "/d/obj/weapon/blade/sickle.c",
		"scythe"  : "/d/obj/weapon/blade/scythe.c",
		"pickaxe" : "/d/obj/weapon/hammer/pickaxe.c",
		"plow"    : "/d/obj/weapon/hammer/plow.c",
 	"tiekuang" : "/d/obj/yelian/tie",
	]));
	setup();
	carry_object("/obj/cloth")->wear();
}
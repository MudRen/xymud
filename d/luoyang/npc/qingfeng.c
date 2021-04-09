inherit F_VENDOR_SALE;
#include <ansi.h>

void create()
{
    	set_name("小青锋", ({ "qingfeng" }) );
	set("gender", "男性" );
	set("age", 16);
	set("nickname", HIG "急风剑" NOR);
	set_level(25);
	set("long","洛阳金刀王家的武术教头，武功不错。\n");
	set_skill("fonxansword",250);
        set_skill("sword", 250);
        set_skill("unarmed", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
	set_skill("moondance", 250);
	map_skill("dodge", "moondance");
	map_skill("sword", "fonxansword");
	map_skill("parry", "fonxansword");
	set("force", 200);
	set("max_force", 200);
	set("force_factor", 5);

        set("vendor_goods", ([
               "dagger": "/d/obj/weapon/dagger/dagger.c",
                "axe": "/d/obj/weapon/axe/tiefu.c",
                "hammer": "/d/obj/weapon/hammer/hammer",
                "fork": "/d/obj/weapon/fork/fork",
            	"tiegun": "/d/obj/weapon/stick/bintiegun",
                "tielian":"/d/obj/weapon/whip/tielian",
                "shield": "/d/obj/armor/niupi",
                "sword": "/d/obj/weapon/sword/changjian",
                "blade": "/d/obj/weapon/blade/blade",
                "spear": "/d/obj/weapon/spear/tieqiang",
                "staff": "/d/obj/weapon/staff/chanzhang",
        ]) );
	create_family2("将军府","洛阳王家",4,"武术教头");
        setup();
        carry_object("/d/obj/cloth/pink_cloth")->wear();
        carry_object("/d/obj/weapon/sword/changjian")->wield();

}
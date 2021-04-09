#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c";

void create()
{
set_name("黄飞虎", ({"huang feihu", "huang", "feihu", "huangfeihu"}));
set ("long", @LONG
开国武成王黄飞虎，兴周第一大将，封神榜
上五岳之首东岳泰山大齐仁圣大帝，下凡寻
找其五色神牛的下落。
LONG);
set("title", "东岳泰山大齐仁圣大帝");
set("gender", "男性");
set("age", 43);
set_skill("spear", 700);
set_skill("force", 700);
set_skill("dodge", 700);
set_skill("stick", 700);
set_skill("literate", 700);
set_skill("dali-bang", 700);
set_skill("huoyun-qiang", 700);
set_skill("parry", 700);
set_skill("unarmed", 700);
set_skill("wuyue-spear", 700);
set_skill("spells", 700);
set_skill("pingtian-dafa", 700);
set_skill("moshenbu", 700);
set_skill("huomoforce", 700);
set_skill("moyun-shou", 700);
map_skill("force", "huomoforce");
map_skill("spells", "pingtian-dafa");
map_skill("unarmed", "moyun-shou");
map_skill("spear", "wuyue-spear");
map_skill("parry", "wuyue-spear");
map_skill("stick", "dali-bang");
map_skill("dodge", "moshenbu");
create_family("火云洞", 1, "蓝");
setup();
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	carry_object(0,"spear",1)->wield();
}
int is_job(){return 1;}
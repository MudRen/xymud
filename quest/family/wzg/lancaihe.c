#include <ansi.h>
inherit NPC;
#include "baxian.h"

int fabao = 0;

void create()
{
	set_name("蓝采和", ({"lan caihe", "lan", "caihe"}));
	set_level(40);
	set("title", HIC"八仙之"NOR);
	set("gender", "男性" );
	set("age", 18);
	set("per", 20);
	set("long", "一位面腆和善的少年。\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed", 400);
	set_skill("wuxing-quan", 400);
	set_skill("dodge", 400);
	set_skill("baguazhen", 400);
	set_skill("parry", 400);
	set_skill("blade", 400);
	set_skill("yange-blade", 400);
	set_skill("force", 400);  
	set_skill("zhenyuan-force", 400);
	set_skill("literate", 400);
	set_skill("spells", 400);
	set_skill("taiyi", 400);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("blade", "yange-blade");
	map_skill("dodge", "baguazhen");

	set("force_factor", 40);
	set("mana_factor", 40);
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"blade",1)->wield();
}

void donghai()
{
	string *msgs;
	if( fabao==0 )
	{
		fabao=1;
		message_vision("\n$N祭起手中镂花花篮，霞光一闪，花篮顿时迎风涨得巨大，飘在海面上好似一艘小船一般，$N哈哈一笑，跳上去振靴踏歌而去。\n",this_object());
	}
	else
	{
		msgs = ({
			"问谁，侠气如泓？看世间，欢笑悲痛。芳名千载何用，欢笑自在秋冬。我只求，逍遥无穷。\n",
			"竹篮花，恰似琼楼玉宫。\n",
			"踏歌蓝采和，世界能几何？\n",
			"红颜三春树，流年一掷梭。\n",
			"古人混混去不返，今人纷纷来更多。\n",
			"朝骑鸾凤到碧落，暮见桑田生白波。\n",
			"长景明晖在空际，金银宫阙高嵯峨。\n",
		});	
		message_vision("$N唱道："+msgs[random(sizeof(msgs))],this_object());
	}
}
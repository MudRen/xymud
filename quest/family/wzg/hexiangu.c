// hexiangu.c...weiqi, 98.02.24.
#include <ansi.h>
inherit NPC;

int fabao = 0;

void create()
{
	set_name("何仙姑", ({"he xiangu", "he", "xiangu"}));
      	set_level(40);
	set("title", HIC"八仙之"NOR);
	set("gender", "女性" );
	set("age", 25);
	set("long", "何仙姑深得镇元大仙喜爱，各位同门大多跟她交好。\n何仙姑原名何秀姑，父亲是开豆腐坊的，她投入五庄观前是当地有名的“豆腐西施”。\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed", 400);
	set_skill("wuxing-quan", 400);
	set_skill("dodge", 400);
	set_skill("baguazhen", 400);
	set_skill("parry", 400);
	set_skill("sword", 690);
	set_skill("sanqing-jian", 400);
	set_skill("force", 400);   
	set_skill("zhenyuan-force", 400);
	set_skill("literate", 400);
	set_skill("spells", 400);
	set_skill("taiyi", 400);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("sword", "sanqing-jian");
	map_skill("dodge", "baguazhen");
	set("force_factor", 40);
	set("mana_factor", 40);
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"neck",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"sword",1)->wield();
}

void donghai()
{
	string *msgs;
	if( fabao==0 )
	{
		fabao=1;
		message_vision("\n$N祭起手中荷花，顿时红光四射，花似磨盘，$N亭亭玉立于荷花中间，风姿迷人。\n",this_object());
	}
	else
	{
		msgs = ({
			"问谁，侠气如泓？看世间，欢笑悲痛。芳名千载何用，欢笑自在秋冬。我只求，逍遥无穷。\n",
			"骨若白玉青葱，貌似初荷落虹。\n",
			"凤凰云母似天花，炼作芙蓉白云芽。\n",
			"笑煞狂徒无主张，更从何处觅丹砂。\n",
			"麻姑笑我恋尘嚣，一隔仙凡道路遥。\n",
			"飞去沧州弄明月，倒骑黄鹤听吹箫。\n",
		});	
		message_vision("$N唱道："+msgs[random(sizeof(msgs))],this_object());
	}	
}
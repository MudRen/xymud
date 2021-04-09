// hanzhongli.c...weiqi, 98.02.24.
#include <ansi.h>
inherit NPC;

int fabao = 0;

void create()
{
	set_name("汉钟离", ({"han zhongli", "han", "zhongli"}));
      	set_level(40);
	set("title", HIC"八仙之正阳子"NOR);
	set("gender", "男性" );
	set("age", 50);
	set("per", 40);
	set("long", "一位大腹便便的胖老头。大概总是觉得太热，时不时地要扇几扇。\n据说他以前喜欢带兵打仗，却又实在不是当将军的料，每每大败而回。\n心灰意冷之下便出门学道访仙，后拜在了镇元门下。\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed",400);
	set_skill("wuxing-quan",400);
	set_skill("dodge",400);
	set_skill("baguazhen",400);
	set_skill("parry",400);
	set_skill("blade", 590);
	set_skill("yange-blade",400);
	set_skill("force",400);   
	set_skill("zhenyuan-force",400);
	set_skill("literate",400);
	set_skill("spells",400);
	set_skill("taiyi",400);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("blade", "yange-blade");
	map_skill("dodge", "baguazhen");
	set("force_factor", 40);
	set("mana_factor", 40);
	setup();
	carry_object(0,"cloth",random(3))->wear();
	carry_object(0,"blade",random(3))->wield();
}

void donghai()
{
	string *msgs;
	if( fabao==0 )
	{
		fabao=1;
		message_vision("\n$N祭起手中蒲扇，顿时霞光一闪，蒲扇迎风变得大如蒲席，$N醉眼惺忪地跳到迎风踏浪的扇子上，优哉游哉的向大海深处飘去。\n",this_object());
	}
	else
	{
		msgs = ({
			"问谁，侠气如泓？看世间，欢笑悲痛。芳名千载何用，欢笑自在秋冬。我只求，逍遥无穷。\n",
			"我轻摇蒲扇别忧愁，生死掌握手中。\n",
			"坐卧常携酒一壶，不教双眼识皇都。\n",
			"乾坤许大无名姓，疏散人中一丈夫。\n",
		});	
		message_vision("$N唱道："+msgs[random(sizeof(msgs))],this_object());
	}
}
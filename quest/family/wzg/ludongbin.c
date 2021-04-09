#include <ansi.h>
inherit NPC;

int fabao = 0;

void create()
{
	set_name("吕洞宾", ({"lu dongbin", "lu", "dongbin"}));
	set_level(40);
	set("title", HIC"八仙之纯阳子"NOR);
	set("gender", "男性" );
	set("age", 35);
	set("long", "吕洞宾大概是镇元门下最出名的弟子了，文采风流，色胆包天。\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed",400);
	set_skill("wuxing-quan",400);
	set_skill("dodge",400);
	set_skill("baguazhen",400);
	set_skill("parry",400);
	set_skill("sword",400);
	set_skill("sanqing-jian",400);
	set_skill("force",400);   
	set_skill("zhenyuan-force",400);
	set_skill("literate",400);
	set_skill("spells",400);
	set_skill("taiyi",400);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("sword", "sanqing-jian");
	map_skill("dodge", "baguazhen");

	set("force_factor", 40);
	set("mana_factor", 40);
	setup();
	carry_object("/d/obj/cloth/xianpao")->wear();
	carry_object("/d/obj/weapon/sword/changjian")->wield();
}

void donghai()
{
	string *msgs;
	if( fabao==0 )
	{
		fabao=1;
		message_vision("\n$N祭起手中长剑，霞光一闪，长剑迎风涨成丈许，立于波涛之上，$N踏在上面，哈哈一笑。\n",this_object());
	}
	else
	{
		msgs = ({
			"乾坤许大无名姓，疏散人中一丈夫。得道高人不易逢，几时归去愿相从。\n",
			"自言住处连沧海，别是蓬莱第一峰。莫厌追欢笑语频，寻思离乱好伤神。\n",
			"暂别蓬莱海上游，偶逢太守问根由。身居北斗星杓下，剑挂南宫月角头。\n",
			"道我醉来真个醉，不知愁是怎生愁。相逢何事不相认，却驾白云归去休。\n",
			"三千里外无家客，七百年来云水身。行满蓬莱为别馆，道成瓦砾尽黄金。\n",
			"待宾榼里常存酒，化药炉中别有春。积德求师何患少，由来天地不私亲。\n",
		});	
		message_vision("$N唱道："+msgs[random(sizeof(msgs))],this_object());
	}
}
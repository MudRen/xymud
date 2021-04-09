#include <ansi.h>
inherit NPC;

int fabao = 0;

void create()
{
	set_name("曹国舅", ({"cao guojiu", "cao", "guojiu"}));
	set_level(40);
	set("title", HIC"八仙之云阳子"NOR);
	set("gender", "男性" );
	set("age", 40);
	set("long", "一位神情严肃的中年人。曹国舅名景休，天资纯善，\n不喜富贵，酷慕清虚。其弟骄纵不法，后罔逃国宪。\n曹国舅深以为耻，遂隐迹山林，精思元理。后投入镇元门下。\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed",400);
	set_skill("wuxing-quan",400);
	set_skill("dodge",400);
	set_skill("baguazhen",400);
	set_skill("parry",400);
	set_skill("hammer",400);
	set_skill("kaishan-chui",400);
	set_skill("force",400);   
	set_skill("zhenyuan-force",400);
	set_skill("literate",400);
	set_skill("spells",400);
	set_skill("taiyi",400);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("hammer", "kaishan-chui");
	map_skill("dodge", "baguazhen");
	set("force_factor", 40);
	set("mana_factor", 40);
	setup();
	carry_object(0,"cloth",random(3))->wear();
	carry_object(0,"hammer",random(3))->wear();
}

void donghai()
{
	string *msgs;
	if( fabao==0 )
	{
		fabao=1;
		message_vision("\n$N祭起手中白玉板，顿时霞光一闪，玉板迎风涨成丈许，$N踏在上面，哈哈一笑，晏然自得。\n",this_object());
	}
	else
	{
		msgs = ({
			"问谁，侠气如泓？看世间，欢笑悲痛。芳名千载何用，欢笑自在秋冬。我只求，逍遥无穷。\n",
			"玉板声，唤醒一切错综。\n",
			"物表英才性朴纯，天然气象妙精神。\n",
			"眼空四海全无欲，心贯三才绝点尘。\n",
			"帝赐金符微一笑，师传玉诀乐长春。\n",
			"源缘慈父征唐德，积一皇后二仙真。\n",
		});	
		message_vision("$N唱道："+msgs[random(sizeof(msgs))],this_object());
	}
}
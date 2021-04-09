//sgzl
#include <ansi.h>

inherit NPC;

void create()
{
  set_name("猪八戒",({"zhu bajie","bajie","zhu"}));
  set("gender", "男性");
//  set("title", "无能");
  set("age", 35);
  set("long", "    \n原来是管理天河的大元帅，因调戏嫦娥被贬到人间。\n");
  set_level(35);
  set("attitude", "heroism");
  set("class", "xian");
  set("daoxing", 600000);
  set("force_factor", 80);
  set("mana_factor", 80);
  set("per", 13);
  set_skill("spells", 320);
  set_skill("dao", 320);
  set_skill("force", 320);
  set_skill("zhenyuan-force", 320);
  set_skill("rake", 320);
  set_skill("skyriver-rake", 140);
  set_skill("parry", 320);
  set_skill("yanxing-steps", 320);
  set_skill("dodge", 320);
  set_skill("unarmed", 320);
  set_skill("wuxing-quan", 320);
map_skill("spells", "dao");
map_skill("force", "zhenyuan-force");
map_skill("rake", "skyriver-rake");
map_skill("parry", "skyriver-rake");
map_skill("dodge", "yanxing-steps");
map_skill("unarmed", "wuxing-quan");
set("inquiry", ([
	"元帅" : "我原本是天上的天蓬元帅！"
]));


setup();

carry_object("/d/kaifeng/obj/jiuchipa")->wield();
carry_object("/d/obj/armor/tongjia")->wear();

}

int heal_up()
{
	if( environment() && !is_fighting() ) {
		call_out("leave", 1);
		return 1;
	}
	return ::heal_up() + 1;
}

void leave()
{
	message("vision",
		RED"猪八戒喃喃地说道：要睡上一觉多好啊！\n\n"
		"随后猪八戒一声不吭的偷偷溜走了。\n" NOR, environment(),
		this_object() );
	destruct(this_object());
}

void invocation(object who)
{
	int i;
	object *enemy;

	message("vision",
		RED"只听猪八戒大喝一声：大胆，吃我老猪一耙。！\n" NOR,
		environment(), this_object() );
	enemy = who->query_enemy();
	i = sizeof(enemy);
	while(i--) {
		if( enemy[i] && living(enemy[i]) ) {
			kill_ob(enemy[i]);
			if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
			else enemy[i]->kill_ob(this_object());
		}
	}
	set_follow(who);
}

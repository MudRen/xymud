inherit NPC;

string *names = ({
  "老虎",
  "花豹",
  "雄狮",
  "豺狼",
  "大象",
});

string *ids = ({
  "lao hu",
  "hua bao",
  "xiong shi",
  "chai lang",
  "da xiang",
});


void create()
{
	int ii,i = 10+random(90);
	ii=random(sizeof(names));
	set_name(names[ii], ({ids[ii], "jing", "monster"}));
	set_level(i);
	set("race", "野兽");
	set("age", 33);

	set("long", @LONG
一只吸取日月精华而成精的猛兽。
LONG);

	set("attitude", "aggressive");
	set("class", "yaomo");
	set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
	set("verbs", ({ "bite"}));

	set("force_factor", 30);
	set("mana_factor", 30);
		
	set_skill("unarmed", i*10);
	set_skill("parry", i*10);
	set_skill("cuixin-zhang",i*10);
	set_skill("spells", 100);
	set_skill("dengxian-dafa",i*10);
	set_skill("force", 100);
	set_skill("ningxie-force",i*10);

	map_skill("force", "ningxie-force");
	map_skill("spells", "dengxian-dafa");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("parry", "cuixin-zhang");
	setup();
}


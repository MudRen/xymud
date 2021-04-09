//Cracked by Roath
inherit NPC;

string *names = ({
  "[31m花脚蚊子[m",
  "大头蚊子",
  "紫头蚊子",
  "红头蚊子",
  "花边蚊子",
  "花肚蚊子",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ "wen zi","wenzi" }) );
   set("race", "野兽");
   set("age", 3);
   set("long", "一只很小巧的花脚蚊子。\n");
   set_level(39);
   set("str", 32);
   set("limbs", ({ "头部", "身体", "腿", "翅膀", "嘴巴" }) );
   set("verbs", ({ "bite", "claw" }) );
   set("chat_chance",80);
   set("chat_msg",({
        "蚊子嗡嗡嗡的飞来飞去。\n",
        }));
   set_temp("apply/attack", 10);
   setup();
}

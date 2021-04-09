// kulou.c 骷髅
#include <ansi.h>
inherit NPC;

void create()
{
	set_name("骷髅", ({"ku lou", "yao", "kulou", "skeleton", "monster"}));
        set_level(5);
  	set("long","这明明是一付干枯的骸骨，但不知怎么他竟然是活的！\n");
  	set("gender", "男性");
  	set("age", 20+random(15));
  	set("attitude", "peaceful");
        set("class","ghost");

        set_skill("unarmed", 30);
        set_skill("parry", 30);
        set_skill("dodge", 30);
        set_skill("blade", 30);
        set_skill("kugu-blade", 30);
  	map_skill("blade", "kugu-blade");
  	map_skill("parry", "kugu-blade");
  	map_skill("dodge", "kugu-blade");
	set("chat_chance", 1);
	set("chat_msg", ({
		"骷髅道：唉，也不知在这里睡了多久了。\n",
		"骷髅道：都忘了人肉是什么味儿了。\n",
	}) );
	set("inquiry", ([
		"name":		"名字？什么名字？我早就不记得了。",
		"here":		"这里？这里是个破洞。要不是那个混帐绿毛老鼠叫我看着，我早出去吃人肉，享清福了！",
		"rumors":	"嘿嘿，我都在这里睡这么多年了，还能知道点什么？",
		"人肉":		"唉。能吃上点人肉就好了。",
	]));
	setup();
  	carry_object(0,"blade",random(2))->wield();
}

int accept_object(object me, object ob)
{
	if( ob->query("name_recognized") == "人肉包子")
    	{
		tell_object(me,CYN+name()+CYN"说道：不错不错，你小子果然还没忘了我！"NOR"\n");
		me->add_temp("wudidong/gave_bookguard_baozi", 1);
		return 1;
    	}
    	tell_object(me,CYN+name()+CYN"说道：什么破烂？！"NOR"\n");
    	return 0;
}

void die()
{
	message_vision("骷髅散成一堆白骨，滚了开去。\n"CYN"四面八方传来阵阵惨笑：想杀死一具枯骨，你真是痴心妄想！我会回来的！\n"NOR,this_object());
	destruct(this_object());
}

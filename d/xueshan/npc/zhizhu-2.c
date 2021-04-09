// created 12/18/1997 by snowcat
#include <combat.h>
#include <ansi.h>
inherit NPC;

string *name1 = ({
	"碧","赤","金","黑",
});
string *name2 = ({
	"睛","腹","珠","背",
});	

void create()
{
  	set_name(name1[random(sizeof(name1))]+name2[random(sizeof(name2))]+"蜘蛛", ({ "zhi zhu", "zhizhu" }));
  	set_level(30);
  	set("long", "一只大蜘蛛。\n");
	set("race", "野兽");
	set("gender","女性");
  	set("age", 26);
  	set("attitude", "aggressive");
	set("force_factor", 30);
  	set("mana_factor", 30);

  	set_skill("unarmed",300);
  	set_skill("dodge",300);
  	set_skill("parry",300);

	set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
  	set("verbs", ({ "bite"}));
  	setup();
  	add_temp("apply/combat_def",200);
  	add_temp("apply/reduce_busy",10);
}

void unconcious ()
{
  	object ob;
  	object me = this_object();
  	object where = environment (me);

  	ob = new ("/d/xueshan/obj/cookfood");
  	ob->set("name",me->query("name"));
  	ob->set("cook/type","zhizhu");
  	ob->set("cook/value",4);
  	ob->move(where);
  	message_vision ("\n$N缩成一团，不再动了。\n",me);
  	destruct (me);
}

void die ()
{
  	unconcious();  
}


int accept_fight(object ob)
{
	kill_ob(ob);
  	return 1;
}

void kill_ob (object ob)
{
  	object me = this_object();
  	set_temp("my_killer",ob);
  	call_out ("hurting",random(2)+3,me,ob);  
  	::kill_ob(ob);
}


void hurting (object me, object ob)
{
  	string *msgs = ({
    		"$N一翘腹部，朝着$n发出一团蛛丝！\n",
  	});
  	string *strs = ({
    		CYN"$N"CYN"给蛛丝缠住了手脚，动弹不得。\n"NOR,
  	});
  	int damage;

  	if( !me || !ob )
    		return;
	if( !me->is_fighting(ob) )
  		return;
 	if( ob->is_busy() )
 		return;
  	message_vision ("\n"+msgs[random(sizeof(msgs))],me,ob);
  	message_vision (strs[random(sizeof(strs))],ob);
    	ob->start_busy(3);
  	remove_call_out ("hurting");  
  	call_out ("hurting",random(5)+5,me,ob);  
}

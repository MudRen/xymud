// created 12/18/1997 by snowcat
#include <combat.h>
#include <ansi.h>
inherit NPC;

string *name1 = ({
	"碧","赤","金","黑",
});
string *name2 = ({
	"甲","尾","壳","背",
});	

void create()
{
  	set_name(name1[random(sizeof(name1))]+name2[random(sizeof(name2))]+"蜈蚣", ({ "wu gong", "wugong", "jing" }));
  	set_level(30);
  	set("long", "一只长长的大蜈蚣。\n");
	set("race", "野兽");
  	set("age", 26);
  	set("attitude", "aggressive");
	set("force_factor", 30);
  	set("mana_factor", 30);

  	set_skill("unarmed",300);
  	set_skill("dodge",300);
  	set_skill("parry",300);

	set("limbs", ({ "头部", "身体", "腿","腿","腿","腿","腿","腿","腿", "尾巴" }) );
  	set("verbs", ({ "bite"}));
  	setup();
  	add_temp("apply/combat_dodge",50);
  	add_temp("apply/spells_def",1000);
}

int test_player (object who)
{
  	string *names;
  	string name;
  	int len;

  	if(!who)
    		return 0;
	names = who->query_temp("apply/name");
  	if( !names )
    		return 0;
	if( sizeof(names) < 1 )
    		return 0;
	name = names[0];
  	len = strlen (name);
  	if( len < 1)
    		return 0;
	if( name[len-2..len-1] != "鸡")
    		return 0;
	return 1;    
}


void unconcious ()
{
  	object ob;
  	object me = this_object();
  	object where = environment (me);

  	ob = new ("/d/xueshan/obj/cookfood");
  	ob->set("name",me->query("name"));
  	ob->set("cook/type","wugong");
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
  	call_out ("hurting",random(5)+3,me,ob);  
  	::kill_ob(ob);
}


void hurting (object me, object ob)
{
  	string *msgs = ({
    		"$N挥起毒钳，向$n一夹！\n",
    		"$N张开血盆大口吐出一团红雾，朝$n飘去！\n",
    		"$N百足盘走，趁着$n不注意，张口朝$p吐出一团红雾！\n",
  	});
  	string *strs = ({
    		"( "HIG"$N"HIG"大叫一声：好痛！"NOR" )\n",
    		"( "HIY"$N"HIY"只觉脑袋昏昏沉沉，行动有些迟钝。"NOR" )\n",
    		"( "HIR"$N"HIR"的脸上立刻布满了黑气！"NOR" )\n",
  	});
  	int damage;

  	if( !me || !ob )
    		return;
	if( !me->is_fighting(ob) )
  		return;
 
  	message_vision ("\n"+msgs[random(sizeof(msgs))],me,ob);
  	if( !test_player(ob) )
  	{
    		message_vision (strs[random(sizeof(strs))],ob);
    		damage = ob->query_maxkee()/(10+random(6));
    		ob->receive_damage("sen",damage,me,TYPE_CAST);
    		ob->receive_wound("sen",damage,me,TYPE_CAST);
	}
  	else
  	{
    		message_vision ("只见$N发出一声鸡叫，"+"$n顿时慌乱转身收起攻击。\n",ob,me);
  	}	
  	remove_call_out ("hurting");  
  	call_out ("hurting",random(5)+3,me,ob);  
}
